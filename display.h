#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET_PIN);

inline void initDisplay() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
        Serial.println("[OLED] ERROR: Pantalla no detectada.");
        while (true);
    }
    Serial.println(
        "[DISPLAY] SSD1306 inicializado %dx%d a %d kHz\n",
        OLED_WIDTH,
        OLED_HEIGHT,
        I2C_FREQUENCY_HZ / 1000
    );
}

// Ejemplo de uso de la API del panel: imprime una linea de texto y la presenta.
inline void showText(const __FlashStringHelper* texto, int x, int y, uint8_t tamano) {
    display.setTextSize(tamano);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x, y);
    display.println(texto);
    display.display();
}

#endif
