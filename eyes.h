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
inline void initEyes() {
    // roboEyes.begin(ANCHO, ALTO, FPS)
    roboEyes.begin(OLED_WIDTH, OLED_HEIGHT, EYES_MAX_FPS);
    
    // Mensaje de confirmación por puerto serie
    Serial.print(F("[EYES] RoboEyes listo a "));
    Serial.print(EYES_MAX_FPS);
    Serial.println(F(" fps"));
}

// TODO 3.2: Avanza la animación un paso sin bloquear; nunca envuelvas este paso en borrado/presentación ni en esperas.
inline void updateEyes() {
    // La librería se encarga internamente de borrar, dibujar y llamar a display()
    roboEyes.update();
}

// TODO 3.3: Aplica la expresión pedida por tecla (1 a 7) y restablece la base limpia antes de calibrar.
inline void setEyesMood(char key) {
    // Validación de entrada: únicamente aceptamos teclas del '1' al '7'
    if (key < '1' || key > '7') {
        return;
    }

    // --- BASE LIMPIA (Restablecimiento neutro de parámetros) ---
    // Si no se limpia, efectos como el temblor o la curiosidad de una tecla previa 
    // continuarían afectando a la nueva expresión elegida.
    roboEyes.setCuriosity(OFF);
    roboEyes.setHFlicker(OFF, 0);
    roboEyes.setVFlicker(OFF, 0);
    roboEyes.setAutoblinker(ON, 3, 2); // Parpadeo automático habilitado por defecto
    roboEyes.setIdleMode(OFF);

    // --- APLICACIÓN DE EXPRESIÓN SEGÚN LA TABLA ---
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
            break;

        case '4': // Cansada: Ánimo cansado, sin movimiento
            roboEyes.setMood(TIRED);
            break;

        case '5': // Soñolienta: Cansado + parpadeo lento
            roboEyes.setMood(TIRED);
            roboEyes.setAutoblinker(ON, 6, 4); // Intervalos más largos de parpadeo
            break;

        case '6': // Temible: Enojado + parpadeo apagado + temblor vertical
            roboEyes.setMood(ANGRY);
            roboEyes.setAutoblinker(OFF);
            roboEyes.setVFlicker(ON, 2); // Temblor en eje Y con amplitud 2
            break;

        case '7': // Curiosa: Neutro + curiosidad + movimiento inactivo rápido
            roboEyes.setMood(DEFAULT);
            roboEyes.setCuriosity(ON);
            roboEyes.setIdleMode(ON, 2, 1); // Intervalos cortos para mayor velocidad
            break;
    }

    // Reportar expresión aplicada según el formato esperado
    Serial.print(F("[EYES] expresion aplicada: "));
    Serial.println(key);
}

#endif