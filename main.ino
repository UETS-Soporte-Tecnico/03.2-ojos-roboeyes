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
    // Paso 1 — Puerto serie abierto a la velocidad del monitor (verás [BOOT] sistema de ojos OLED).
    // Paso 2 — Bus I2C compartido levantado (verás [I2C] bus listo SDA=21 SCL=22).
    // Paso 3 — Barrido del bus reportado (verás el dispositivo en 0x3C y el conteo final).
    // Paso 4 — Dirección del panel sondeada (verás la respuesta del POST del OLED).

     initI2C();
    scanI2C();
    testI2CDevice();

    // Paso 5-6: panel inicializado, logo pintado y POST de pantalla
    initDisplay();
    showLogo();
    testDisplay();

    // Paso 7: ojos listos
    initEyes();

    // Paso 8: ayuda publicada y ventana de arranque armada
    printHelp();
    bootTime = millis();

void loop() {
    if (!bootComplete) {
        if (millis() - bootTime >= LOGO_TIME_MS) {
            bootComplete = true;
            Serial.println(F("[BOOT] ventana de arranque finalizada"));
        }
        return; // no hagas nada más mientras el logo sigue en pantalla
    }

    // Con el arranque terminado: atiende la consola y avanza la animación
    debugSerialTick();
    updateEyes();
}
