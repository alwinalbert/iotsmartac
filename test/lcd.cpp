#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // change if needed

void setup() {
    Serial.begin(9600);

    lcd.init();
    lcd.backlight();

    Serial.println("LCD initialized");

    lcd.setCursor(0, 0);
    lcd.print("Hello Ashik");

    lcd.setCursor(0, 1);
    lcd.print("PlatformIO OK");
}

void loop() {
}