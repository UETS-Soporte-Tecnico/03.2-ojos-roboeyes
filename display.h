// display.h
// ============================================
// RESPONSABILIDAD: Controlar el OLED SSD1306 (inicialización y texto).
// No sabe nada de: ojos, logos, POST ni comandos del Monitor Serie.
// ============================================

#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

// Declaración extern: le dice al compilador que la instancia global existe en main.ino
extern Adafruit_SSD1306 display;

// TODO 1.4: Inicializa el panel con el modo de alimentación interna y la dirección de config.h.
inline void initDisplay() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
        Serial.print(F("¡ERROR FATAL! Fallo OLED en 0x"));
        Serial.println(OLED_I2C_ADDRESS, HEX);
        Serial.println(F("Deteniendo el arranque del sistema."));
        
        while (1) {
            delay(1000);
        }
    }

    display.clearDisplay();
    display.display();
    
    Serial.println(F("Panel OLED SSD1306 inicializado correctamente."));
}

inline void showText(const __FlashStringHelper* texto, int x, int y, uint8_t tamano) {
    display.setTextSize(tamano);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x, y);
    display.println(texto);
    display.display();
}

#endif