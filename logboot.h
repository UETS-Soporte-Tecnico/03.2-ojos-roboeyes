// logboot.h
// ============================================
// RESPONSABILIDAD: Dibujar el logo de arranque y hacer el POST de pantalla.
// No sabe nada de: ojos, bus I2C ni comandos del Monitor Serie.
// ============================================

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
    int tamano = 8;
    int x = (OLED_WIDTH - tamano) / 2;   // (128 - 8) / 2 = 60
    int y = (OLED_HEIGHT - tamano) / 2;  // (64 - 8) / 2 = 28

    display.clearDisplay();
    display.fillRect(x, y, tamano, tamano, SSD1306_WHITE);
    display.display();

    Serial.print("[POST] cuadrado de pantalla en x=");
    Serial.print(x);
    Serial.print(" y=");
    Serial.println(y);
}

#endif
