
#ifndef DEBUG_SERIAL_H
#define DEBUG_SERIAL_H

#include <Arduino.h>
#include "config.h"
#include "eyes.h"

inline void printHelp() {
    Serial.println("1=DEFAULT");
    Serial.println("2=HAPPY");
    Serial.println("3=ANGRY");
    Serial.println("4=TIRED");
    Serial.println("5=SLEEPY");
    Serial.println("6=SCARY");
    Serial.println("7=CURIOUS");
    Serial.println("h=ayuda");
}

inline void debugSerialTick() {
    if (Serial.available() > 0) {
        char c = Serial.read();

        if (c == '\n' || c == '\r' || c == ' ' || c == 0) {
            return;
        }

        if (c == 'h' || c == 'H') {
            printHelp();
        }

        else if (c >= '1' && c <= '7') {
            setEyesMood(c);
        }
    }
}

#endif
