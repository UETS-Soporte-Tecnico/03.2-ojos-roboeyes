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
    Wire.begin(I2C_FREQUENCY_HZ);

    Serial.print(F("[I2C] bus listo SDA="));
    Serial.print(I2C_SDA_PIN);
    Serial.print(F(" SCL="));
    Serial.println(I2C_SCL_PIN);
}

// TODO 1.2: Barre el rango completo de direcciones e informa cada dispositivo hallado y el conteo final.
// Pregunta Guía: ¿Cómo sabes que el barrido cubrió todo el rango si el monitor solo muestra un conteo?
// Pista: La guía §05 muestra el barrido esperado línea por línea.
inline void scanI2C() {

    Serial.println(F("[I2C] escaneando direcciones 1-126"));
    uint8_t found = 0;

    for (uint8_t addr = 1; addr < 127; addr++) {
        Wire.beginTransmission(addr);
        uint8_t error = Wire.endTransmission();

        if (error == 0) {
            Serial.print(F("[I2C] dispositivo en 0x"));
            Serial.println(addr, HEX);
            found++;
        }
    }

    Serial.print(F("[I2C] dispositivos encontrados: "));
    Serial.println(found);
}
}

// TODO 1.3: Sondea la dirección del panel e informa si responde o si el arranque debe detenerse.
// Pregunta Guía: ¿Qué debe imprimir el arranque cuando el panel no responde?
// Pista: Hay dos caminos, uno de éxito y uno fatal; la guía §05 los muestra.
inline void testI2CDevice() {
   Wire.beginTransmission(OLED_I2C_ADDRESS);
    uint8_t error = Wire.endTransmission();

    if (error == 0) {
        Serial.print(F("[POST] OLED responde en 0x"));
        Serial.println(OLED_I2C_ADDRESS, HEX);
    } else {
        Serial.print(F("[FALLO CRITICO] OLED no responde en 0x"));
        Serial.println(OLED_I2C_ADDRESS, HEX);
        Serial.println(F("[I2C] Arranque detenido. Verifica SDA(21)/SCL(22) o alimentacion."));
        while (true) delay(100); // Modo seguro: bucle infinito para proteger el circuito
    }
}

#endif
