#include "BluetoothSerial.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"

void callback(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param);

void setup() {
  Serial.begin(115200);
  Serial.println("Spúšťam Bluetooth...");

  if (!btStart()) {
    Serial.println("Chyba pri spustení BT stacku");
    return;
  }

  esp_bluedroid_init();
  esp_bluedroid_enable();
  esp_bt_gap_register_callback(callback);
  esp_bt_gap_start_discovery(ESP_BT_INQ_MODE_GENERAL_INQUIRY, 10, 0);
}

void loop() {
  delay(1000);
}

void callback(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param) {
  if (event == ESP_BT_GAP_DISC_RES_EVT) {
    char bda_str[18];
    sprintf(bda_str, "%02x:%02x:%02x:%02x:%02x:%02x",
            param->disc_res.bda[0], param->disc_res.bda[1],
            param->disc_res.bda[2], param->disc_res.bda[3],
            param->disc_res.bda[4], param->disc_res.bda[5]);

    Serial.print("Nájdené zariadenie: ");
    Serial.println(bda_str);

    // Príklad: identifikuj Android zariadenia podľa prefixu MAC adresy
    if (param->disc_res.bda[0] == 0xFC && param->disc_res.bda[1] == 0xFB) {
      Serial.println("Možné Android zariadenie!");
    }
  }
}