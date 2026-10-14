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
    display.clearDisplay();
    display.drawBitmap(0, 0, logo_bitmap, LOGO_WIDTH, LOGO_HEIGHT, SSD1306_WHITE);
    display.display();
}

// TODO 2.3: Dibuja el cuadrado de autoprueba centrado e informa sus coordenadas.
// Pregunta Guía: ¿Cómo compruebas que el cuadrado quedó centrado sin medir a ojo?
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
