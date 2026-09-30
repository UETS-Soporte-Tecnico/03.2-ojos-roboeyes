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

// TODO 2.2: Pinta el marco del logo desde logo_bitmap y preséntalo en el panel.
inline void showLogo() {
    display.clearDisplay();
    // drawBitmap(x, y, bitmap, ancho, alto, color)
    display.drawBitmap(0, 0, logo_bitmap, OLED_WIDTH, OLED_HEIGHT, SSD1306_WHITE);
    display.display();
}

// TODO 2.3: Dibuja el cuadrado de autoprueba centrado e informa sus coordenadas.
inline void testDisplay() {
    // Definimos un cuadrado de autoprueba (ej. 8x8 píxeles)
    const int rectSize = 8;
    
    // Cálculo de posición centrada: (AnchoTotal - AnchoFigura) / 2
    int x = (OLED_WIDTH - rectSize) / 2;   // (128 - 8) / 2 = 60
    int y = (OLED_HEIGHT - rectSize) / 2;  // (64 - 8) / 2 = 28

    display.clearDisplay();
    // drawRect(x, y, ancho, alto, color)
    display.drawRect(x, y, rectSize, rectSize, SSD1306_WHITE);
    display.display();

    // Salida esperada en el Monitor Serie
    Serial.print(F("[POST] cuadrado de pantalla en x="));
    Serial.print(x);
    Serial.print(F(" y="));
    Serial.println(y);
}

#endif