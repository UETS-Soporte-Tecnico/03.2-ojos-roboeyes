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
    Serial.println(F("[HELP] expresiones disponibles:"));
    Serial.println(F("1 DEFAULT"));
    Serial.println(F("2 HAPPY"));
    Serial.println(F("3 ANGRY"));
    Serial.println(F("4 TIRED"));
    Serial.println(F("5 SLEEPY"));
    Serial.println(F("6 SCARY"));
    Serial.println(F("7 CURIOUS"));
    Serial.println(F("h ayuda"));
}

// TODO 4.2: Atiende el puerto sin bloquear: una tecla, respuesta inmediata; teclas 1 a 7 cambian la expresión, h repite la ayuda, los caracteres de control se ignoran en silencio.
// Pregunta Guía: ¿Qué pasa con una tecla desconocida y qué pasa con un carácter de control?
inline void debugSerialTick() {
    if (!Serial.available()) {
        return;
    }

    const char key = static_cast<char>(Serial.read());
    if (key < 32 || key == 127) {
        return;
    }

    if (key == 'h' || key == 'H') {
        printHelp();
        return;
    }

    if (key < '1' || key > '7') {
        return;
    }

    setEyesMood(key);
    Serial.print(F("[MOOD] tecla "));
    Serial.println(key);
}

#endif
