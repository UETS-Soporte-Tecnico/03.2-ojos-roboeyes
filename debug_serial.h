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
inline void printHelp() {
    Serial.println(F("[DEBUG] 1=DEFAULT 2=HAPPY 3=ANGRY 4=TIRED"));
    Serial.println(F("[DEBUG] 5=SLEEPY 6=SCARY 7=CURIOUS h=ayuda"));
}

// TODO 4.2: Atiende el puerto sin bloquear: una tecla, respuesta inmediata.
inline void debugSerialTick() {
    // Si no hay datos disponibles en el puerto serie, salimos inmediatamente sin bloquear
    if (!Serial.available()) {
        return;
    }

    char c = Serial.read();

    // Ignoramos silenciosamente los caracteres de control (\r, \n, espacio y nulos)
    if (c == '\r' || c == '\n' || c == ' ' || c == '\0') {
        return;
    }

    // Teclas del 1 al 7: cambian la expresión del robot
    if (c >= '1' && c <= '7') {
        setEyesMood(c);
    } 
    // Tecla de ayuda
    else if (c == 'h' || c == 'H') {
        printHelp();
    } 
    // Cualquier otro carácter imprimible se considera comando desconocido
    else {
        Serial.print(F("[DEBUG] comando desconocido: "));
        Serial.println(c);
    }
}

#endif