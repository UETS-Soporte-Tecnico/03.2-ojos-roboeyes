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

// 22.2: Pinta el marco del logo desde logo_bitmap y preséntalo en el panel.
// Pregunta Guía: ¿Qué debe verse en el panel durante la ventana de arranque?
inline void showLogo() {
    /* ESCRIBE TU CÓDIGO AQUÍ */
        display.clearDisplay();
    display.drawBitmap(0, 0, logo_bitmap, OLED_WIDTH, OLED_HEIGHT, SSD1306_WHITE);
    display.display();
}

// 22.3: Dibuja el cuadrado de autoprueba centrado e informa sus coordenadas.
// Pregunta Guía: ¿Cómo compruebas que el cuadrado quedó centrado sin medir a ojo?
inline void testDisplay() {
    /* ESCRIBE TU CÓDIGO AQUÍ */
    const int squareSize = 20;
    int x = (OLED_WIDTH - squareSize) / 2;
    int y = (OLED_HEIGHT - squareSize) / 2;

    Serial.print(F("[DISPLAY] Cuadrado centrado en x="));
    Serial.print(x);
    Serial.print(F(" y="));
    Serial.print(y);
    Serial.print(F(" size="));
    Serial.println(squareSize);

    display.clearDisplay();
    display.drawRect(x, y, squareSize, squareSize, SSD1306_WHITE);
    display.display();


}

#endif
