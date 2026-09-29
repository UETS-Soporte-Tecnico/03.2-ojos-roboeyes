// main.ino
// ============================================
// RESPONSABILIDAD: Orquestar arranque y bucle principal del sistema.
// No sabe como hacer nada: solo llama a cada modulo en el orden correcto.
// ============================================

#include "config.h"
#include "i2c_manager.h"
#include "display.h"
#include "logo.h"
#include "logboot.h"
#include "eyes.h"
#include "debug_serial.h"

// Estados de la maquina de arranque y marca de tiempo de su ventana
bool bootComplete = false;
unsigned long bootTime = 0;

void setup() {
    Serial.begin(115200);
    Serial.println(F("[BOOT] sistema de ojos OLED"));
    Serial.begin(115200);
    delay(100);
    Serial.println(F("[BOOT] sistema de ojos OLED"));
    initI2C();
    scanI2C();
    testI2CDevice();
    initDisplay();
    showLogo();
    delay(1500); // Muestra brevemente el logo antes del POST
    testDisplay();
    initEyes();
    printHelp();
    bootTime = millis();
}

void loop() {
    
    if (!bootComplete) {
        if (millis() - bootTime >= BOOT_WINDOW_MS) {
            bootComplete = true;
            Serial.println(F("[FSM] Transición: Arranque completado. Pasando a modo de operacion de ojos."));
        }
        return; 
    }
    
    debugSerialTick(); 
    updateEyes();
}
