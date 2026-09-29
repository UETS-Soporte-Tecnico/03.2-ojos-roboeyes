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
    roboEyes.begin(OLED_WIDTH, OLED_HEIGHT, EYES_TARGET_FPS);
    roboEyes.setAutoblinker(ON, 3, 2);
    roboEyes.setIdleMode(ON, 2, 2);
    Serial.println(F("[EYES] Ojos inicializados correctamente y listos a 60 FPS."));
}

// TODO 3.2: Avanza la animación un paso sin bloquear; nunca envuelvas este paso en borrado/presentación ni en esperas.
// Pregunta Guía: ¿Quién es dueño del borrado y la presentación del cuadro, tu código o la librería?
inline void updateEyes() {
    roboEyes.update();
}

// TODO 3.3: Aplica la expresión pedida por tecla (1 a 7) y restablece la base limpia antes de calibrar.
// Pregunta Guía: ¿Qué cambia en pantalla entre una tecla y otra si la base no se restablece?
inline void setEyesMood(char key) {
    roboEyes.reset();

    switch (key) {
        case '1': // Neutra: Ánimo por defecto + movimiento inactivo
            roboEyes.setMood(DEFAULT);
            roboEyes.setIdleMode(ON, 2, 2);
            roboEyes.setAutoblinker(ON, 3, 2);
            Serial.println(F("[EYES] Expresion 1: Neutra (por defecto + movimiento inactivo)"));
            break;

        case '2': // Feliz: Ánimo alegre + movimiento inactivo
            roboEyes.setMood(HAPPY);
            roboEyes.setIdleMode(ON, 2, 2);
            roboEyes.setAutoblinker(ON, 3, 2);
            Serial.println(F("[EYES] Expresion 2: Feliz (alegre + movimiento inactivo)"));
            break;

        case '3': // Enojada: Ánimo enojado, sin movimiento
            roboEyes.setMood(ANGRY);
            roboEyes.setIdleMode(OFF);
            roboEyes.setAutoblinker(OFF);
            Serial.println(F("[EYES] Expresion 3: Enojada (enojado, sin movimiento)"));
            break;

        case '4': // Cansada: Ánimo cansado, sin movimiento
            roboEyes.setMood(TIRED);
            roboEyes.setIdleMode(OFF);
            roboEyes.setAutoblinker(OFF);
            Serial.println(F("[EYES] Expresion 4: Cansada (cansado, sin movimiento)"));
            break;

        case '5': // Soñolienta: Cansado + parpadeo lento
            roboEyes.setMood(TIRED);
            roboEyes.setIdleMode(OFF);
            roboEyes.setAutoblinker(ON, 6, 4); // Intervalo de parpadeo más espaciado / lento
            Serial.println(F("[EYES] Expresion 5: Soñolienta (cansado + parpadeo lento)"));
            break;

        case '6': // Temible: Enojado + parpadeo apagado + temblor vertical
            roboEyes.setMood(ANGRY);
            roboEyes.setAutoblinker(OFF);
            roboEyes.setIdleMode(OFF);
            roboEyes.setVFlicker(ON, 2); // Temblor o vibración en el eje vertical
            Serial.println(F("[EYES] Expresion 6: Temible (enojado + sin parpadeo + temblor vertical)"));
            break;

        case '7': // Curiosa: Neutro + curiosidad + movimiento
            roboEyes.setMood(DEFAULT);
            roboEyes.setCuriosity(ON);
            roboEyes.setIdleMode(ON, 2, 2);
            roboEyes.setAutoblinker(ON, 3, 2);
            Serial.println(F("[EYES] Expresion 7: Curiosa (neutro + curiosidad + movimiento)"));
            break;

        default:
            Serial.print(F("[EYES] Tecla no valida: "));
            Serial.println(key);
            break;
    }
}

#endif
