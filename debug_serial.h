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

inline void printHelp() {
    Serial.println("[DEBUG] 1=DEFAULT 2=HAPPY 3=ANGRY 4=TIRED");
    Serial.println("[DEBUG] 5=SLEEPY 6=SCARY 7=CURIOUS h=ayuda");
}

inline void debugSerialTick() {
    if (Serial.available() > 0) {
        char key = Serial.read();

        if (key == '\r' || key == '\n') {
            return;
        }

        if (key >= '1' && key <= '7') {
            setEyesMood(key);
        } 

        else if (key == 'h' || key == 'H') {
            printHelp();
        } 

        else {
            Serial.print("[DEBUG] comando desconocido: ");
            Serial.println(key);
        }
    }
}

#endif
