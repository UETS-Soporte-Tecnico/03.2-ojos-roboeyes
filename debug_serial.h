// debug_serial.h
// ============================================
// RESPONSABILIDAD: Leer comandos del Monitor Serie y mostrar la ayuda.
// No sabe nada de: bus I2C, OLED, logos ni animacion interna de los ojos.
// ============================================

#ifndef DEBUG_SERIAL_H
#define DEBUG_SERIAL_H

#include <Arduino.h>
#include "config.h"
#include "eyes.h"

// TODO 4.1: Publica el bloque de ayuda con las 7 expresiones y la tecla de ayuda.
// Pregunta Guía: ¿Qué debe ver un compañero que abre el monitor por primera vez?
inline void printHelp() {
    Serial.println(F("\n=============================================="));
    Serial.println(F("     CONSOLA DE CONTROL - ROBOEYES SSD1306    "));
    Serial.println(F("=============================================="));
    Serial.println(F(" Presiona una tecla para cambiar la expresion:"));
    Serial.println(F("   [1] Neutra    - Animo por defecto + idle"));
    Serial.println(F("   [2] Feliz     - Animo alegre + idle"));
    Serial.println(F("   [3] Enojada   - Animo enojado, sin movimiento"));
    Serial.println(F("   [4] Cansada   - Animo cansado, sin movimiento"));
    Serial.println(F("   [5] Soñolienta- Cansado + parpadeo lento"));
    Serial.println(F("   [6] Temible   - Enojado + sin parpadeo + temblor V"));
    Serial.println(F("   [7] Curiosa   - Neutro + curiosidad + idle"));
    Serial.println(F("----------------------------------------------"));
    Serial.println(F("   [h] Mostrar este menú de ayuda"));
    Serial.println(F("==============================================\n"));
}


// TODO 4.2: Atiende el puerto sin bloquear: una tecla, respuesta inmediata; teclas 1 a 7 cambian la expresión, h repite la ayuda, los caracteres de control se ignoran en silencio.
// Pregunta Guía: ¿Qué pasa con una tecla desconocida y qué pasa con un carácter de control?
inline void debugSerialTick() {
    if (Serial.available() > 0) {
        char key = Serial.read();

        // Ignorar en silencio caracteres de control invisibles (\n, \r, espacios, etc.)
        if (key == '\n' || key == '\r' || key == ' ') {
            return;
        }

        // Si se presiona 'h' o 'H', se muestra la ayuda
        if (key == 'h' || key == 'H') {
            printHelp();
        } 
        // Si la tecla está entre '1' y '7', se envía al módulo de ojos
        else if (key >= '1' && key <= '7') {
            setEyesMood(key);
        } 
        // Si es cualquier otra tecla no válida, se reporta por Serial
        else {
            Serial.print(F("[DEBUG] Tecla desconocida no reconocida: '"));
            Serial.print(key);
            Serial.println(F("'. Presiona 'h' para ver el menu de ayuda."));
        }
    }
}


#endif
