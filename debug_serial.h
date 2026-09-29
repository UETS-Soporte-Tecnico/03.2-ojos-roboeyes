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
    Serial.println("[DEBUG] 1=DEFAULT 2=HAPPY 3=ANGRY 4=TIRED");
    Serial.println("[DEBUG] 5=SLEEPY 6=SCARY 7=CURIOUS h=ayuda");
}

// TODO 4.2: Atiende el puerto sin bloquear: una tecla, respuesta inmediata; teclas 1 a 7 cambian la expresión, h repite la ayuda, los caracteres de control se ignoran en silencio.
// Pregunta Guía: ¿Qué pasa con una tecla desconocida y qué pasa con un carácter de control?
inline void debugSerialTick() {
    if (!Serial.available()) {
        return;
    }

    char c = Serial.read();

    // Ignorar caracteres de control en silencio ('\n', '\r', espacios, nulos)
    if (c == '\n' || c == '\r' || c == ' ' || c == '\t' || c == '\0') {
        return;
    }

    // Teclas del 1 al 7: cambiar la expresión usando el módulo eyes.h
    if (c >= '1' && c <= '7') {
        setEyesMood(c);
    } 
    // Tecla de ayuda
    else if (c == 'h' || c == 'H') {
        printHelp();
    } 
    // Cualquier otro carácter no reconocido
    else {
        Serial.print("[DEBUG] comando desconocido: ");
        Serial.println(c);
    }
}

#endif
