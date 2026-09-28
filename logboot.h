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
// Pregunta Guía: ¿Qué debe verse en el panel durante la ventana de arranque?
inline void showLogo() {
    /* ESCRIBE TU CÓDIGO AQUÍ */
    display.clearDisplay();
    display.drawBitmap(0, 0, logo_bitmap, OLED_WIDTH, OLED_HEIGHT, SSD1306_WHITE);
    display.display();
}

// TODO 2.3: Dibuja el cuadrado de autoprueba centrado e informa sus coordenadas.
// Pregunta Guía: ¿Cómo compruebas que el cuadrado quedó centrado sin medir a ojo?
inline void testDisplay() {
    /* ESCRIBE TU CÓDIGO AQUÍ */
    int boxSize = 8;
    int x = (OLED_WIDTH - boxSize) / 2;  // (128 - 8) / 2 = 60
    int y = (OLED_HEIGHT - boxSize) / 2; // (64 - 8) / 2 = 28

    display.clearDisplay();
    display.fillRect(x, y, boxSize, boxSize, SSD1306_WHITE);
    display.display();

    Serial.print("[POST] cuadrado de pantalla en x=");
    Serial.print(x);
    Serial.print(" y=");
    Serial.println(y);
}

#endif
