I think this Will not work properly !

#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
}

void loop() {
  SerialBT.begin("Galaxy Buds");
  delay(5000);

  SerialBT.begin("JBL Charge 3");
  delay(3000);

  SerialBT.begin("JBL Flip");
  delay(3000);

  SerialBT.begin("Galaxy Buds Plus");
  delay(3000);

  SerialBT.begin("Galaxy Buds 2");
  delay(3000);

  SerialBT.begin("Mi True Wireless headphones");
  delay(3000);

  SerialBT.begin("Airpods Pro Max");
  delay(3000);
}
