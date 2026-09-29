// eyes.h
// ============================================
// RESPONSABILIDAD: Animar los ojos del OLED y aplicar la expresion elegida.
// No sabe nada de: bus I2C, logos de arranque, POST ni Monitor Serie.
// ============================================

#ifndef EYES_H
#define EYES_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include "display.h"
#include "config.h"

// Declaración anticipada para que la interfaz sea válida aunque la cabecera
// del display se incluya condicionalmente en algún entorno Arduino.
class Adafruit_SSD1306;

// La instancia del display se define en otro módulo; aquí solo se declara.
extern Adafruit_SSD1306 display;

// Arduino.h del ESP32 define DEFAULT como 1 y RoboEyes lo define como 0. Se
// limpia esa macro (sin uso en el core) para evitar el aviso de redefinicion.
#undef DEFAULT

#include <FluxGarage_RoboEyes.h>

// Instancia global: el sistema tiene un solo par de ojos
RoboEyes<Adafruit_SSD1306> roboEyes(display);

// TODO 3.1: Inicializa los ojos con las dimensiones del panel y el objetivo de cuadros por segundo de config.h.
// Pregunta Guía: ¿Qué tres números necesita la inicialización y de dónde sale cada uno?
inline void initEyes() {
    roboEyes.begin(OLED_WIDTH, OLED_HEIGHT, EYES_MAX_FPS);
    Serial.printf("[EYES] RoboEyes listo a %d fps\r\n", EYES_MAX_FPS);
}

// TODO 3.2: Avanza la animación un paso sin bloquear; nunca envuelvas este paso en borrado/presentación ni en esperas.
// Pregunta Guía: ¿Quién es dueño del borrado y la presentación del cuadro, tu código o la librería?
inline void updateEyes() {
    roboEyes.update();
}

// TODO 3.3: Aplica la expresión pedida por tecla (1 a 7) y restablece la base limpia antes de calibrar.
// Pregunta Guía: ¿Qué cambia en pantalla entre una tecla y otra si la base no se restablece?
inline void setEyesMood(char key) {
    if (key < '1' || key > '7') {
        return;
    }

    // 1. BASE LIMPIA
    roboEyes.setCuriosity(OFF);
    roboEyes.setHFlicker(OFF, 0);
    roboEyes.setVFlicker(OFF, 0);
    roboEyes.setAutoblinker(ON, 4, 2);
    roboEyes.setIdleMode(OFF);

    // 2. APLICACIÓN DE LA EXPRESIÓN
    switch (key) {
        case '1': // Neutra
            roboEyes.setMood(DEFAULT);
            roboEyes.setIdleMode(ON);
            break;

        case '2': // Feliz
            roboEyes.setMood(HAPPY);
            roboEyes.setIdleMode(ON);
            break;

        case '3': // Enojada
            roboEyes.setMood(ANGRY);
            break;

        case '4': // Cansada
            roboEyes.setMood(TIRED);
            break;

        case '5': // Soñolienta
            roboEyes.setMood(TIRED);
            roboEyes.setAutoblinker(ON, 1, 3);
            break;

        case '6': // Temible
            roboEyes.setMood(ANGRY);
            roboEyes.setAutoblinker(OFF, 0, 0);
            roboEyes.setVFlicker(ON, 2);
            break;

        case '7': // Curiosa
            roboEyes.setMood(DEFAULT);
            roboEyes.setCuriosity(ON);
            roboEyes.setIdleMode(ON);
            break;
    }
    Serial.printf("[EYES] expresion aplicada: %c\r\n", key);
}

#endif
