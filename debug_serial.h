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
    /* ESCRIBE TU CÓDIGO AQUÍ */
    Serial.println(F("[DEBUG] 1=DEFAULT 2=HAPPY 3=ANGRY 4=TIRED"));
    Serial.println(F("[DEBUG] 5=SLEEPY 6=SCARY 7=CURIOUS h=ayuda"));
}

// TODO 4.2: Atiende el puerto sin bloquear: una tecla, respuesta inmediata; teclas 1 a 7 cambian la expresión, h repite la ayuda, los caracteres de control se ignoran en silencio.
// Pregunta Guía: ¿Qué pasa con una tecla desconocida y qué pasa con un carácter de control?
inline void debugSerialTick() {
    /* ESCRIBE TU CÓDIGO AQUÍ */
    if (Serial.available() <= 0) {
        return;
    }

    int command = Serial.read();
    if (command < 32 || command == 127) {
        return;
    }

    if (command >= '1' && command <= '7') {
        setEyesMood(static_cast<char>(command));
    } else if (command == 'h' || command == 'H') {
        printHelp();
    } else {
        Serial.printf("[DEBUG] comando desconocido: %c\n", static_cast<char>(command));
    }
}

#endif
