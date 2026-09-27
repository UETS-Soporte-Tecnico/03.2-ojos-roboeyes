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
    roboEyes.setDisplayColors(SSD1306_BLACK, SSD1306_WHITE);
    roboEyes.setMood(DEFAULT);
    roboEyes.setCuriosity(false);
    Serial.printf("[EYES] ojos listos a %d fps\n", EYES_MAX_FPS);
}

// TODO 3.2: Avanza la animación un paso sin bloquear; nunca envuelvas este paso en borrado/presentación ni en esperas.
// Pregunta Guía: ¿Quién es dueño del borrado y la presentación del cuadro, tu código o la librería?
inline void updateEyes() {
    roboEyes.update();
}

// TODO 3.3: Aplica la expresión pedida por tecla (1 a 7) y restablece la base limpia antes de calibrar.
// Pregunta Guía: ¿Qué cambia en pantalla entre una tecla y otra si la base no se restablece?
inline void setEyesMood(char key) {
    roboEyes.setMood(DEFAULT);
    roboEyes.setCuriosity(false);
    roboEyes.setHeight(36, 36);
    const __FlashStringHelper* nombre = F("normal");

    switch (key) {
        case '1':
            break;
        case '2':
            roboEyes.setMood(HAPPY);
            nombre = F("feliz");
            break;
        case '3':
            roboEyes.setMood(ANGRY);
            nombre = F("enojado");
            break;
        case '4':
            roboEyes.setMood(TIRED);
            nombre = F("cansado");
            break;
        case '5':
            roboEyes.setMood(TIRED);
            roboEyes.setHeight(24, 24);
            nombre = F("dormido");
            break;
        case '6':
            roboEyes.setMood(ANGRY);
            roboEyes.setHeight(42, 42);
            nombre = F("asustado");
            break;
        case '7':
            roboEyes.setCuriosity(true);
            nombre = F("curioso");
            break;
        default:
            return;
    }

    Serial.printf("[OJOS] expresion seleccionada: %c - ", key);
    Serial.println(nombre);
}

#endif
