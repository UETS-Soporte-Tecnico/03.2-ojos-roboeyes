
#include "config.h"
#include "i2c_manager.h"
#include "display.h"
#include "logo.h"
#include "logboot.h"
#include "eyes.h"
#include "debug_serial.h"

bool bootComplete = false;
unsigned long bootTime = 0;

void setup() {
    Serial.begin(115200);
    Serial.println(F("[BOOT] sistema de ojos OLED"));

    initI2C();
    scanI2C();
    testI2CDevice();

    initDisplay();
    showLogo();

    bootTime = millis();
}

void loop() {
    if (!bootComplete) {
        if (millis() - bootTime >= LOGO_TIME_MS) {
            testDisplay();
            delay(1000);
            
            bootComplete = true;
            Serial.println(F("[FSM] BOOT -> RUN"));

            initEyes();
            printHelp();
        }
    } else {
        debugSerialTick();
        updateEyes();
    }
}
