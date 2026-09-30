
#ifndef I2C_MANAGER_H
#define I2C_MANAGER_H

#include <Arduino.h>
#include <Wire.h>
#include "config.h"

inline void initI2C() {
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
    Wire.setClock(I2C_FREQUENCY_HZ);
    Serial.println("[I2C] bus listo SDA=21 SCL=22");
}

inline void scanI2C() {
    byte error, direccion;
    int cont = 0;
    Serial.println("[I2C] escaneando direcciones 1-126");
    for (direccion = 1; direccion < 127; direccion++) {
        Wire.beginTransmission(direccion);
        error = Wire.endTransmission();
        if (error == 0) {
            Serial.print("[I2C] dispositivo en 0x");
            if (direccion < 16) Serial.print("0");
            Serial.print(direccion, HEX);
            cont ++;
        }
    }
    Serial.print("[I2C] dispositivos encontrados: ");
    Serial.println(cont);
}

inline void testI2CDevice() {
    Wire.beginTransmission(OLED_I2C_ADDR);
    byte error = Wire.endTransmission();
    if (error == 0) {
        Serial.print("[POST] OLED responde en 0x");
        if (OLED_I2C_ADDR < 16) Serial.print("0");
        Serial.println(OLED_I2C_ADDR, HEX);
    } else {
        Serial.println("[POST] OLED no responde. Arranque detenido");
        while (1);
    }
    
}

#endif
