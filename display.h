
#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET_PIN);

inline void initDisplay() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR)) {
        Serial.print("[DISPLAY] Error al inicializar SSD1306");
        while(1);
    } else {
        Serial.print("[DISPLAY] SSD1306 inicializado 128x64 a 400 kHz");
    }
}

inline void showText(const __FlashStringHelper* texto, int x, int y, uint8_t tamano) {
    display.setTextSize(tamano);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x, y);
    display.println(texto);
    display.display();
}

#endif
