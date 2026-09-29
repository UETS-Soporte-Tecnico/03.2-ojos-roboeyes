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

    // Dibuja el bitmap usando las dimensiones declaradas en logo.h
    display.drawBitmap(
        (OLED_WIDTH - LOGO_WIDTH) / 2,   // Coordenada X (centrado)
        (OLED_HEIGHT - LOGO_HEIGHT) / 2, // Coordenada Y (centrado)
        logo_bitmap,                     // Arreglo en PROGMEM
        LOGO_WIDTH, 
        LOGO_HEIGHT, 
        SSD1306_WHITE
    );

    display.display();
    Serial.println(F("[LOGBOOT] Logo de arranque desplegado en pantalla."));
}

// TODO 2.3: Dibuja el cuadrado de autoprueba centrado e informa sus coordenadas.
// Pregunta Guía: ¿Cómo compruebas que el cuadrado quedó centrado sin medir a ojo?
inline void testDisplay() {
    display.clearDisplay();

    // Tamaño del cuadrado de autoprueba
    const int boxSize = 32;

    // Cálculo dinámico de coordenadas para asegurar el centrado exacto
    int x = (OLED_WIDTH - boxSize) / 2;   // (128 - 32) / 2 = 48
    int y = (OLED_HEIGHT - boxSize) / 2;  // (64 - 32) / 2 = 16

    // Dibuja un rectángulo relleno para validar la respuesta del panel
    display.fillRect(x, y, boxSize, boxSize, SSD1306_WHITE);
    display.display();

    // Telemetría con las coordenadas exactas por Serial
    Serial.print(F("[POST] Autoprueba visual dibujada. Cuadrado centrado en X: "));
    Serial.print(x);
    Serial.print(F(", Y: "));
    Serial.print(y);
    Serial.print(F(" (tamano: "));
    Serial.print(boxSize);
    Serial.println(F("px)."));
}

#endif
