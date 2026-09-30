
#ifndef LOGBOOT_H
#define LOGBOOT_H

#include <Arduino.h>
#include "display.h"
#include "logo.h"

inline void showLogo() {
    display.clearDisplay();
    display.drawBitmap(0, 0, logo_bitmap, LOGO_WIDTH, LOGO_HEIGHT, SSD1306_WHITE);
    display.display();
}

inline void testDisplay() {
    display.clearDisplay();

    int cuadrado = 8;
    int x = (OLED_WIDTH - cuadrado) / 2;
    int y = (OLED_HEIGHT - cuadrado) / 2;

    display.drawRect(x, y, cuadrado, cuadrado, SSD1306_WHITE);
    display.display();

    Serial.print(F("POST Display: Cuadrado dibujado en X="));
    Serial.print(x);
    Serial.print(F(", Y="));
    Serial.println(y);
}

#endif
