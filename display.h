// display.h
// ============================================
// RESPONSABILIDAD: Controlar el OLED SSD1306 (inicializacion y texto).
// No sabe nada de: ojos, logos, POST ni comandos del Monitor Serie.
// ============================================

#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

// Definición de la instancia global (debe estar aquí obligatoriamente)
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET_PIN);

inline void initDisplay() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
        Serial.println(F("[DISPLAY] Fallo en la inicializacion SSD1306. Sistema detenido.\r\n"));
        while (true) {
            delay(100);
        }
    }
    Serial.printf("[DISPLAY] SSD1306 inicializado\r\n", 
                  OLED_WIDTH, OLED_HEIGHT, (I2C_FREQUENCY_HZ / 1000));
}

inline void showText(const __FlashStringHelper* texto, int x, int y, uint8_t tamano) {
    display.setTextSize(tamano);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x, y);
    display.println(texto);
    display.display();
}

#endif
