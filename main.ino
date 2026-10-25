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

    // TODO 1.5: Escribe las llamadas de los pasos 1 a 4 para dejar el bus y el panel listos.
    // Paso 1 — Puerto serie

// Paso 2 — Inicializar el bus I2C
initI2C();

// Paso 3 — Escanear el bus I2C
scanI2C();

// Paso 4 — Comprobar el panel OLED
testI2CDevice();
initDisplay();

    // TODO 2.4: Escribe las llamadas de los pasos 5 y 6 para pintar el logo y ejecutar el POST de pantalla.
    testDisplay();
    showLogo();

    // TODO 3.4: Escribe la llamada del paso 7 para dejar los ojos listos.
    initEyes();

    // TODO 4.3: Escribe la llamada del paso 8, publica la ayuda y arma la ventana de arranque.
     printHelp();
bootTime = millis();

void loop() {
    void loop() {
    if (!bootComplete) {
        if (millis() - bootTime >= LOGO_TIME_MS) {
            bootComplete = true;
            Serial.println(F("[BOOT] estado RUN"));
        } else {
            return;
        }
    }
    debugSerialTick();
    updateEyes();
}
