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
    Serial.println(F("\n[EYES] comandos:"));
    Serial.println(F("1 NORMAL  | 2 FELIZ   | 3 ENOJADO | 4 CANSADO"));
    Serial.println(F("5 DORMIDO | 6 ASUSTADO| 7 CURIOSO"));
    Serial.println(F("h/H ayuda"));
}

// TODO 4.2: Atiende el puerto sin bloquear: una tecla, respuesta inmediata; teclas 1 a 7 cambian la expresión, h repite la ayuda, los caracteres de control se ignoran en silencio.
// Pregunta Guía: ¿Qué pasa con una tecla desconocida y qué pasa con un carácter de control?
inline void debugSerialTick() {
    if (!Serial.available()) {
        return;
    }

    const char key = static_cast<char>(Serial.read());
    if (key == 'h' || key == 'H') {
        printHelp();
    } else if (key >= '1' && key <= '7') {
        setEyesMood(key);
    }
}

#endif
