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
    /* ESCRIBE TU CÓDIGO AQUÍ */
    roboEyes.begin(OLED_WIDTH, OLED_HEIGHT, EYES_MAX_FPS);
    Serial.println("[EYES] RoboEyes listo a 60 fps");
}

// TODO 3.2: Avanza la animación un paso sin bloquear; nunca envuelvas este paso en borrado/presentación ni en esperas.
// Pregunta Guía: ¿Quién es dueño del borrado y la presentación del cuadro, tu código o la librería?
inline void updateEyes() {
    /* ESCRIBE TU CÓDIGO AQUÍ */
    roboEyes.update();
}

// TODO 3.3: Aplica la expresión pedida por tecla (1 a 7) y restablece la base limpia antes de calibrar.
// Pregunta Guía: ¿Qué cambia en pantalla entre una tecla y otra si la base no se restablece?
inline void setEyesMood(char key) {
    /* ESCRIBE TU CÓDIGO AQUÍ */
    // Validar rango de teclas de '1' a '7'
    if (key < '1' || key > '7') {
        return;
    }

    // Base limpia antes de aplicar cualquier expresión
    roboEyes.setCuriosity(OFF);
    roboEyes.setHFlicker(OFF, 0);
    roboEyes.setVFlicker(OFF, 0);
    roboEyes.setAutoblinker(ON, 3, 2);
    roboEyes.setIdleMode(OFF);

    // Mapeo de expresiones según la tecla
    switch (key) {
        case '1': // Neutra: Ánimo por defecto + movimiento inactivo
            roboEyes.setMood(DEFAULT);
            roboEyes.setIdleMode(ON);
            break;

        case '2': // Feliz: Ánimo alegre + movimiento inactivo
            roboEyes.setMood(HAPPY);
            roboEyes.setIdleMode(ON);
            break;

        case '3': // Enojada: Ánimo enojado, sin movimiento
            roboEyes.setMood(ANGRY);
            roboEyes.setIdleMode(OFF);
            break;

        case '4': // Cansada: Ánimo cansado, sin movimiento
            roboEyes.setMood(TIRED);
            roboEyes.setIdleMode(OFF);
            break;

        case '5': // Soñolienta: Cansado + parpadeo lento
            roboEyes.setMood(TIRED);
            roboEyes.setAutoblinker(ON, 6, 4);
            roboEyes.setIdleMode(OFF);
            break;

        case '6': // Temible: Enojado + parpadeo apagado + temblor vertical
            roboEyes.setMood(ANGRY);
            roboEyes.setAutoblinker(OFF);
            roboEyes.setVFlicker(ON, 2);
            roboEyes.setIdleMode(OFF);
            break;

        case '7': // Curiosa: Neutro + curiosidad + movimiento inactivo rápido
            roboEyes.setMood(DEFAULT);
            roboEyes.setCuriosity(ON);
            roboEyes.setIdleMode(ON, 2, 2);
            break;
    }

    Serial.print("[EYES] expresion aplicada: ");
    Serial.println(key);
}
    

#endif
