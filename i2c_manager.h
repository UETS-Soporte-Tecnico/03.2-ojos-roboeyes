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

// TODO 1.1: Levanta el bus I2C compartido con los pines y la velocidad declarados en config.h.
// Pregunta Guía: ¿Qué dos pines y qué velocidad necesita el bus antes de buscar el panel?
// Pista: Los valores viven en config.h; el resultado esperado se describe en la guía §05.
inline void initI2C() {
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
    Wire.setClock(I2C_FREQUENCY_HZ);
}

// TODO 1.2: Barre el rango completo de direcciones e informa cada dispositivo hallado y el conteo final.
// Pregunta Guía: ¿Cómo sabes que el barrido cubrió todo el rango si el monitor solo muestra un conteo?
// Pista: La guía §05 muestra el barrido esperado línea por línea.
inline void scanI2C() {
    int nDevices = 0;
    Serial.println("[I2C] escaneando direcciones 1-126");

    for (byte address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        byte error = Wire.endTransmission();

        if (error == 0) {
            Serial.print("[I2C] dispositivo en 0x");
            if (address < 16) {
                Serial.print("0");
            }
            Serial.println(address, HEX);
            nDevices++;
        }
    }

    Serial.print("[I2C] dispositivos encontrados: ");
    Serial.println(nDevices);
}

// TODO 1.3: Sondea la dirección del panel e informa si responde o si el arranque debe detenerse.
// Pregunta Guía: ¿Qué debe imprimir el arranque cuando el panel no responde?
// Pista: Hay dos caminos, uno de éxito y uno fatal; la guía §05 los muestra.
inline void testI2CDevice() {
    byte address = 0x3C; // Dirección del panel OLED SSD1306
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) {
        Serial.print("[POST] OLED responde en 0x");
        Serial.println(address, HEX);
    } else {
        Serial.println("[POST] ERROR: OLED no responde. Deteniendo arranque...");
        while (1); // Detiene el arranque si falla
    }
}

#endif
