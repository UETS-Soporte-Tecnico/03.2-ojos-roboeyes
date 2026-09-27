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

// 33.1: Inicializa los ojos con las dimensiones del panel y el objetivo de cuadros por segundo de config.h.
// Pregunta Guía: ¿Qué tres números necesita la inicialización y de dónde sale cada uno?
inline void initEyes() {
    /* ESCRIBE TU CÓDIGO AQUÍ */
     roboEyes.begin(OLED_WIDTH, OLED_HEIGHT, EYES_MAX_FPS);
}

// 33.2: Avanza la animación un paso sin bloquear; nunca envuelvas este paso en borrado/presentación ni en esperas.
// Pregunta Guía: ¿Quién es dueño del borrado y la presentación del cuadro, tu código o la librería?
inline void updateEyes() {
    /* ESCRIBE TU CÓDIGO AQUÍ */
roboEyes.update();
   
}

// 33.3: Aplica la expresión pedida por tecla (1 a 7) y restablece la base limpia antes de calibrar.
// Pregunta Guía: ¿Qué cambia en pantalla entre una tecla y otra si la base no se restablece?
inline void setEyesMood(char key) {
    /* ESCRIBE TU CÓDIGO AQUÍ */
      if (key < '1' || key > '7') {
        Serial.println(F("[EYES] Tecla invalida para expresion."));
        return;
    }

    roboEyes.setCuriosity(OFF);
    roboEyes.setHFlicker(OFF, 0);
    roboEyes.setVFlicker(OFF, 0);
    roboEyes.setAutoblinker(ON, 4, 2);
    roboEyes.setIdleMode(OFF);

   switch (key) {
        case '1':
            roboEyes.setMood(DEFAULT);
            roboEyes.setIdleMode(ON);
            Serial.println(F("[EYES] Expresion aplicada: DEFAULT"));
            break;

        case '2':
            roboEyes.setMood(HAPPY);
            roboEyes.setIdleMode(ON);
            Serial.println(F("[EYES] Expresion aplicada: HAPPY"));
            break;

        case '3':
            roboEyes.setMood(ANGRY);
            Serial.println(F("[EYES] Expresion aplicada: ANGRY"));
            break;

        case '4':
            roboEyes.setMood(TIRED);
            Serial.println(F("[EYES] Expresion aplicada: TIRED"));
            break;

        case '5':
            roboEyes.setMood(TIRED);
            roboEyes.setAutoblinker(ON, 8, 3);
            Serial.println(F("[EYES] Expresion aplicada: SLEEPY"));
            break;

        case '6':
            roboEyes.setMood(ANGRY);
            roboEyes.setAutoblinker(OFF, 0, 0);
            roboEyes.setVFlicker(ON, 2);
            Serial.println(F("[EYES] Expresion aplicada: SCARY"));
            break;

        case '7':
            roboEyes.setMood(DEFAULT);
            roboEyes.setCuriosity(ON);
            roboEyes.setIdleMode(ON, 1, 2);
            Serial.println(F("[EYES] Expresion aplicada: CURIOUS"));
            break;
    }
}

#endif
