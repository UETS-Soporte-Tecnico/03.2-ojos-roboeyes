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

// TODO 3.1: Inicializa los ojos con las dimensiones del panel y el objetivo de cuadros por segundo de config.h.
// Pregunta Guía: ¿Qué tres números necesita la inicialización y de dónde sale cada uno?
inline void initEyes() {
    roboEyes.begin(OLED_WIDTH, OLED_HEIGHT, EYES_MAX_FPS);
    Serial.println("[EYES] RoboEyes listo a 60 fps");
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
        Serial.println("[DEBUG] comando desconocido: x");
        return;
    }
    roboEyes.setCuriosity(false);
    roboEyes.setHFlicker(false, 0);
    roboEyes.setVFlicker(false, 0);
    roboEyes.setAutoblinker(true, 4, 2);
    roboEyes.setIdleMode(false);

    switch (key) {
    case '1':
        roboEyes.setMood(DEFAULT);
        roboEyes.setIdleMode(true, 2, 2);
        Serial.println("[EYES] expresion aplicada: 1");
        break;
    case '2':
        roboEyes.setMood(HAPPY);
        roboEyes.setIdleMode(true, 2, 2);
        Serial.println("[EYES] expresion aplicada: 2");
        break;
    case '3':
        roboEyes.setMood(ANGRY);
        roboEyes.setIdleMode(false);
        Serial.println("[EYES] expresion aplicada: 3");
        break;
    case '4':
        roboEyes.setMood(TIRED);
        roboEyes.setIdleMode(false);
        Serial.println("[EYES] expresion aplicada: 4");
        break;
    case '5':
        roboEyes.setMood(TIRED);
        roboEyes.setAutoblinker(true, 6, 3);
        Serial.println("[EYES] expresion aplicada: 5");
        break;
    case '6':
        roboEyes.setMood(ANGRY);
        roboEyes.setAutoblinker(false, 0, 0);
        roboEyes.setVFlicker(true, 2);
        Serial.println("[EYES] expresion aplicada: 6");
        break;
    case '7':
        roboEyes.setMood(DEFAULT);
        roboEyes.setCuriosity(true);
        roboEyes.setIdleMode(true, 1, 1);
        Serial.println("[EYES] expresion aplicada: 7");
        break;
}

#endif
