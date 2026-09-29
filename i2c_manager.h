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
<<<<<<< HEAD

=======
>>>>>>> fbd0979 (chore(raiz):Trabajo terminado)
    Serial.print(F("[I2C] bus listo SDA="));
    Serial.print(I2C_SDA_PIN);
    Serial.print(F(" SCL="));
    Serial.println(I2C_SCL_PIN);
}

// TODO 1.2: Barre el rango completo de direcciones e informa cada dispositivo hallado y el conteo final.
// Pregunta Guía: ¿Cómo sabes que el barrido cubrió todo el rango si el monitor solo muestra un conteo?
// Pista: La guía §05 muestra el barrido esperado línea por línea.
inline void scanI2C() {
<<<<<<< HEAD
    Serial.println(F("[I2C] escaneando direcciones 1-126"));

    uint8_t found = 0;
    for (uint8_t address = 1; address < 127; ++address) {
        Wire.beginTransmission(address);
        uint8_t error = Wire.endTransmission();

        if (error == 0) {
            Serial.print(F("[I2C] dispositivo en 0x"));
            if (address < 0x10) Serial.print('0');
            Serial.println(address, HEX);
            found++;
=======
    uint8_t devicesFound = 0;

    Serial.println(F("[I2C] iniciando barrido"));
    for (uint8_t address = 1; address < 127; ++address) {
        Wire.beginTransmission(address);
        if (Wire.endTransmission() == 0) {
            Serial.print(F("[I2C] dispositivo encontrado en 0x"));
            if (address < 16) {
                Serial.print('0');
            }
            Serial.println(address, HEX);
            ++devicesFound;
>>>>>>> fbd0979 (chore(raiz):Trabajo terminado)
        }
    }

    Serial.print(F("[I2C] dispositivos encontrados: "));
<<<<<<< HEAD
    Serial.println(found);
=======
    Serial.println(devicesFound);
>>>>>>> fbd0979 (chore(raiz):Trabajo terminado)
}

// TODO 1.3: Sondea la dirección del panel e informa si responde o si el arranque debe detenerse.
// Pregunta Guía: ¿Qué debe imprimir el arranque cuando el panel no responde?
// Pista: Hay dos caminos, uno de éxito y uno fatal; la guía §05 los muestra.
inline void testI2CDevice() {
    Wire.beginTransmission(OLED_I2C_ADDRESS);
<<<<<<< HEAD
    uint8_t error = Wire.endTransmission();

    if (error == 0) {
        Serial.print(F("[POST] OLED responde en 0x"));
        if (OLED_I2C_ADDRESS < 0x10) Serial.print('0');
        Serial.println(OLED_I2C_ADDRESS, HEX);
    } else {
        Serial.print(F("[POST] ERROR: OLED no responde en 0x"));
        if (OLED_I2C_ADDRESS < 0x10) Serial.print('0');
        Serial.println(OLED_I2C_ADDRESS, HEX);
        Serial.println(F("[POST] arranque detenido: revisar conexiones I2C"));
        while (true) {
            delay(100);
        }
=======
    if (Wire.endTransmission() == 0) {
        Serial.print(F("[POST] OLED responde en 0x"));
        Serial.println(OLED_I2C_ADDRESS, HEX);
        return;
    }

    Serial.println(F("[ERROR] OLED no responde; se detiene el arranque"));
    while (true) {
>>>>>>> fbd0979 (chore(raiz):Trabajo terminado)
    }
}

#endif
