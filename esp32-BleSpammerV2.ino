#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <BLEAdvertising.h>




// install Library here
// https://github.com/nkolban/ESP32_BLE_Arduino
// then add it to your libraries




const char* names[] = {
  "JBL Charge 3", "Airpods Pro Max", "Galaxy Buds",
  "Mi True Wireless", "Galaxy Buds Plus", "JBL Flip"
};
int index = 0;

BLEServer* pServer = nullptr;
BLEService* pService = nullptr;
BLECharacteristic* pCharacteristic = nullptr;
BLEAdvertising* pAdvertising = nullptr;

void setup() {
  Serial.begin(115200);
  startAdvertisingWithName(names[index]);
}

void loop() {
  delay(10000); // reklamuj nové zariadenie každých 10 sekúnd
  index = (index + 1) % (sizeof(names) / sizeof(names[0]));
  stopAdvertising();
  delay(100);
  startAdvertisingWithName(names[index]);
}

void startAdvertisingWithName(const char* deviceName) {
  BLEDevice::init(deviceName);

  pServer = BLEDevice::createServer();

  // Služba s charakteristikou vyžadujúcou bezpečné spojenie (bonding/pairing)
  pService = pServer->createService(BLEUUID((uint16_t)0xFFF0));
  pCharacteristic = pService->createCharacteristic(
                      BLEUUID((uint16_t)0xFFF1),
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  // Vyžaduje párovanie na čítanie (trigger pairing dialog)
  pCharacteristic->setAccessPermissions(ESP_GATT_PERM_READ_ENC_MITM);
  pCharacteristic->setValue("pair_me");
  pService->start();

  pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(pService->getUUID());
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x06);  // iOS optimalizácia
  pAdvertising->setMinPreferred(0x12);

  pAdvertising->start();
  Serial.println(String("Advertising as: ") + deviceName);
}

void stopAdvertising() {
  pAdvertising->stop();
  BLEDevice::deinit(true);
}