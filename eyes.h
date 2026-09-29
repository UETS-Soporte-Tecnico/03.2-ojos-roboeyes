// eyes.h
// ============================================
// RESPONSABILIDAD: Animar los ojos del OLED y aplicar la expresion elegida.
// No sabe nada de: bus I2C, logos de arranque, POST ni Monitor Serie.
// ============================================

#ifndef EYES_H
#define EYES_H

#include <Arduino.h>
#include "display.h"
#include "config.h"

// Arduino.h del ESP32 define DEFAULT como 1 y RoboEyes lo define como 0. Se
// limpia esa macro (sin uso en el core) para evitar el aviso de redefinicion.
#undef DEFAULT

#include <FluxGarage_RoboEyes.h>

// Instancia global: el sistema tiene un solo par de ojos
RoboEyes<Adafruit_SSD1306> roboEyes(display);

inline void initEyes() {
    roboEyes.begin(OLED_WIDTH, OLED_HEIGHT, EYES_MAX_FPS);
    Serial.printf("[EYES] RoboEyes listo a %d fps\n", EYES_MAX_FPS);
}

inline void updateEyes() {
    roboEyes.update();
}

inline void setEyesMood(char key) {
    if (key < '1' || key > '7') {
        return;
}
    roboEyes.setCuriosity(OFF);
    roboEyes.setHFlicker(OFF, 0);
    roboEyes.setVFlicker(OFF, 0);
    roboEyes.setAutoblinker(ON, 3, 2);
    roboEyes.setIdleMode(OFF);

    switch (key) {
        case '1': // Neutra: Ánimo por defecto + movimiento Inactivo
            roboEyes.setMood(DEFAULT);
            roboEyes.setIdleMode(ON);
            break;

        case '2': // Feliz: Ánimo alegre + movimiento Inactivo
            roboEyes.setMood(HAPPY);
            roboEyes.setIdleMode(ON);
            break;

        case '3': // Enojada: Ánimo enojado, sin movimiento
            roboEyes.setMood(ANGRY);
            break;

        case '4': // Cansada: Ánimo cansado, sin movimiento
            roboEyes.setMood(TIRED);
            break;

        case '5': // Soñolienta: Cansado + parpadeo lento
            roboEyes.setMood(TIRED);
            roboEyes.setAutoblinker(ON, 8, 4); // Parpadeo más lento e interactivo
            break;

        case '6': // Temible: Enojado + parpadeo apagado + temblor vertical
            roboEyes.setMood(ANGRY);
            roboEyes.setAutoblinker(OFF);
            roboEyes.setVFlicker(ON, 2);
            break;

        case '7': // Curiosa: Neutro + curiosidad + movimiento Inactivo rápido
            roboEyes.setMood(DEFAULT);
            roboEyes.setCuriosity(ON);
            roboEyes.setIdleMode(ON, 2, 2); // Inactivo con intervalos más cortos
            break;
    }

    Serial.printf("[EYES] expresion aplicada: %c\n", key);
}
#endif
