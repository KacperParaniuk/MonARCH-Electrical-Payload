// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: Copyright (c) 2026 Ashwin Whitchurch, Protocentral Electronics

/*
 * 01_DeviceInfo - I2C link check + Manufacturer/Device ID readback
 *
 * Copyright (c) 2026 Ashwin Whitchurch, Protocentral Electronics
 * Email: info@protocentral.com
 *
 * Scans the I2C bus and prints any responding addresses, then reads the
 * Manufacturer ID (0x5449 = "TI") and Device ID (0x3055 for FDC2214) from the
 * ProtoCentral FDC2214 breakout. The whole sequence runs from loop() so a
 * Serial Monitor opened after upload still sees the output.
 *
 * The ProtoCentral breakout pulls ADDR HIGH on-board, so the default I2C
 * address is 0x2B. Tie ADDR low to use 0x2A instead.
 *
 * This software is licensed under the MIT License.
 */

//////////////////////////////////////////////////////////////////////////////////////////
//
//    Hardware Setup:
//      Arduino   FDC2214 board
//      -------   -------------
//      3.3V   -> VCC
//      GND    -> GND
//      A4     -> SDA  (or board SDA pin)
//      A5     -> SCL  (or board SCL pin)
//
/////////////////////////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include <Protocentral_FDC2214.h>

FDC2214 fdc;

void setup() {
    Serial.begin(115200);
    Wire.begin();
}

void scanI2CBus() {
    Serial.println(F("Scanning I2C bus (0x03..0x77)..."));

    uint8_t found = 0;
    for (uint8_t addr = 0x03; addr <= 0x77; addr++) {
        Wire.beginTransmission(addr);
        uint8_t err = Wire.endTransmission();

        if (err == 0) {
            Serial.print(F("  device found at 0x"));
            if (addr < 0x10) Serial.print('0');
            Serial.print(addr, HEX);
            if (addr == 0x2A || addr == 0x2B) {
                Serial.print(F("  <- FDC2214"));
            }
            Serial.println();
            found++;
        }
    }

    if (found == 0) {
        Serial.println(F("  no I2C devices responded. Check power, pull-ups, and SDA/SCL wiring."));
    } else {
        Serial.print(F("  "));
        Serial.print(found);
        Serial.println(F(" device(s) found."));
    }
}

void loop() {
    Serial.println();
    Serial.println(F("FDC2214 Device Info"));
    Serial.println(F("==================="));

    scanI2CBus();
    Serial.println();

    if (!fdc.begin()) {
        Serial.println(F("FDC2214 not found at I2C address 0x2B."));
        Serial.println(F("Check 3.3V power, SDA/SCL wiring, and ADDR pin (VDD=0x2B, GND=0x2A)."));
    } else {
        Serial.print(F("Manufacturer ID: 0x"));
        Serial.println(fdc.getManufacturerID(), HEX);

        Serial.print(F("Device ID:       0x"));
        Serial.println(fdc.getDeviceID(), HEX);

        Serial.println(F("Device responding correctly."));
    }

    delay(2000);
}
