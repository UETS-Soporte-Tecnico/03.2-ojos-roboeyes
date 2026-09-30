// i2c_manager.h
// ============================================
// RESPONSABILIDAD: Hablar con el bus I2C (pines, velocidad, escaneo y verificacion).
// No sabe nada de: OLED, logos, ojos ni comandos del Monitor Serie.
// ============================================

#ifndef I2C_MANAGER_H
#define I2C_MANAGER_H

#include <Arduino.h>
#include <Wire.h>
#include "config.h"

/// TODO 1.1: Levanta el bus I2C compartido con los pines y la velocidad declarados en config.h.
inline void initI2C() {
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
    Wire.setClock(I2C_FREQUENCY_HZ);
}

// TODO 1.2: Barre el rango completo de direcciones e informa cada dispositivo hallado y el conteo final.
inline void scanI2C() {
    byte error, address;
    int nDevices = 0;
    
    Serial.println(F("Escaneando bus I2C..."));
    
    for (address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        
        if (error == 0) {
            Serial.print(F("Dispositivo I2C encontrado en la dirección 0x"));
            if (address < 16) {
                Serial.print("0");
            }
            Serial.println(address, HEX);
            nDevices++;
        } else if (error == 4) {
            Serial.print(F("Error desconocido en la dirección 0x"));
            if (address < 16) {
                Serial.print("0");
            }
            Serial.println(address, HEX);
        }
    }
    
    if (nDevices == 0) {
        Serial.println(F("No se encontraron dispositivos I2C.\n"));
    } else {
        Serial.print(F("Escaneo finalizado. Total de dispositivos encontrados: "));
        Serial.println(nDevices);
    }
}

// TODO 1.3: Sondea la dirección del panel e informa si responde o si el arranque debe detenerse.
inline void testI2CDevice() {
    Wire.beginTransmission(OLED_I2C_ADDRESS);
    byte error = Wire.endTransmission();
    
    if (error == 0) {
        Serial.println(F("Panel OLED detectado y respondiendo correctamente."));
    } else {
        Serial.print(F("¡ERROR FATAL! Panel OLED no responde en la dirección 0x"));
        Serial.println(OLED_I2C_ADDRESS, HEX);
        Serial.println(F("Deteniendo el arranque del sistema."));
        
        while (1) {
            delay(1000);
        }
    }
}

#endif