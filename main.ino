#include "config.h"
#include "i2c_manager.h"
#include "display.h"
#include "logo.h"
#include "logboot.h"
#include "eyes.h"
#include "debug_serial.h"

// Instancia global única para el hardware
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET_PIN);

// Estados de la máquina de arranque
bool bootComplete = false;
unsigned long bootTime = 0;

void setup() {
    Serial.begin(115200);
    Serial.println(F("[BOOT] sistema de ojos OLED"));

    initI2C();
    scanI2C();
    testI2CDevice();
    initDisplay();

    testDisplay();
    delay(500);
    showLogo();

    initEyes();
    printHelp();
    bootTime = millis();
}

void loop() {
    if (!bootComplete) {
        if (millis() - bootTime >= LOGO_TIME_MS) {
            bootComplete = true;
            Serial.println(F("[FSM] BOOT -> RUN"));
            setEyesMood('1'); // Activa la expresión inicial en pantalla
        }
        return;
    }

    updateEyes();
    debugSerialTick();
}