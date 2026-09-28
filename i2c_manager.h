#ifndef I2C_MANAGER_H
#define I2C_MANAGER_H

#include <Arduino.h>
#include <Wire.h>
#include "config.h"

inline void initI2C() {
    Wire.begin(I2C_SCL_PIN, I2C_SDA_PIN);
    Wire.setClock(I2C_FREQUENCY_HZ);
    Serial.println("[I2C] bus listo SDA=21 SCL=22");
}

inline void scanI2C() {
    int devicesFound = 0;

    Serial.println("[I2C] escaneando direcciones 1-126");

    for (byte address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        byte error = Wire.endTransmission();

        if (error == 0) {
            Serial.println("[I2C] dispositivo en 0x%02X\n", address);
            devicesFound++;
        }
    }

    Serial.println("[I2C] dispositivos encontrados: %d\n", devicesFound);

}

inline void testI2CDevice() {
    Wire.beginTransmission(OLED_I2C_ADDRESS);
    byte error = Wire.endTransmission();

        if (error == 0) {
            Serial.println("[POST] OLED responde en 0x3C");
        } else {
            Serial.println("[POST] OLED no responde en 0x3C");
        }
}

#endif
