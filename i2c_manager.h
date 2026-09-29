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
    Serial.println("[I2C] Bus iniciado correctamente.");
}

// TODO 1.2: Barre el rango completo de direcciones e informa cada dispositivo hallado y el conteo final.
// Pregunta Guía: ¿Cómo sabes que el barrido cubrió todo el rango si el monitor solo muestra un conteo?
// Pista: La guía §05 muestra el barrido esperado línea por línea.
inline void scanI2C() {
    byte error, address;
    int nDevices = 0;

    Serial.println("[I2C] Iniciando escaneo del bus...");

    // Se recorre el rango estándar de direcciones I2C (1 a 126)
    for (address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0) {
            Serial.print("  -> Dispositivo encontrado en direccion HEX: 0x");
            if (address < 16) {
                Serial.print("0");
            }
            Serial.println(address, HEX);
            nDevices++;
        } else if (error == 4) {
            Serial.print("  -> Error desconocido en direccion HEX: 0x");
            if (address < 16) {
                Serial.print("0");
            }
            Serial.println(address, HEX);
        }
        
    }

    if (nDevices == 0) {
        Serial.println("[I2C] No se encontraron dispositivos I2C.");
    } else {
        Serial.print("[I2C] Escaneo finalizado. Total de dispositivos encontrados: ");
        Serial.println(nDevices);
    }
}

// TODO 1.3: Sondea la dirección del panel e informa si responde o si el arranque debe detenerse.
// Pregunta Guía: ¿Qué debe imprimir el arranque cuando el panel no responde?
// Pista: Hay dos caminos, uno de éxito y uno fatal; la guía §05 los muestra.
inline void testI2CDevice() {
    Serial.print("[I2C] Probando conexion con pantalla en 0x");
    if (OLED_I2C_ADDRESS < 16) Serial.print("0");
    Serial.println(OLED_I2C_ADDRESS, HEX);

    Wire.beginTransmission(OLED_I2C_ADDRESS);
    byte error = Wire.endTransmission();

    if (error == 0) {
        Serial.println("[I2C] OK: La pantalla OLED respondio correctamente.");
    } else {
        Serial.println("[I2C] FATAL: La pantalla OLED no responde en el bus. Sistema detenido.");
        // Bucle infinito de bloqueo seguro en caso de falla critica
        while (true) {
            delay(1000);
        }
        
    }
    
}

#endif
