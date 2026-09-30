
#ifndef EYES_H
#define EYES_H

#include <Arduino.h>
#include "display.h"
#include "config.h"

#undef DEFAULT

#include <FluxGarage_RoboEyes.h>

RoboEyes<Adafruit_SSD1306> roboEyes(display);

inline void initEyes() {
    roboEyes.begin(OLED_WIDTH, OLED_HEIGHT, EYES_MAX_FPS);
    Serial.println("[EYES] RoboEyes listo a 60 fps");
}

inline void updateEyes() {
    roboEyes.update();
}

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
}

#endif
