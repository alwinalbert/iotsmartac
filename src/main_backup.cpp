// #define BLYNK_TEMPLATE_ID "TMPL3bMZcP3IS"
// #define BLYNK_TEMPLATE_NAME "esp32"
// #define BLYNK_AUTH_TOKEN "1hqcKqiVXF0-fWrJ-rbCNlSrPbo7kwNz"

// #include <Arduino.h>
// #include <WiFi.h>
// #include <BlynkSimpleEsp32.h>
// #include <DHT.h>

// #define DHTPIN 4
// #define DHTTYPE DHT22
// #define PIR 27
// #define RELAY 26

// char ssid[] = "MM";
// char pass[] = "alss159265769804";

// DHT dht(DHTPIN, DHTTYPE);

// #define FAN_POWER_WATTS 10  

// bool manualControl = false;

// BLYNK_WRITE(V0) {
//     int value = param.asInt();
//     manualControl = true;

//     if (value == 255) {   // FIXED: was 255
//         digitalWrite(RELAY, HIGH);
//         Serial.println("Fan ON (App)");
//     } else {
//         digitalWrite(RELAY, LOW);
//         Serial.println("Fan OFF (App)");
//     }
// }

// void setup() {
//     Serial.begin(9600);

//     pinMode(PIR, INPUT);
//     pinMode(RELAY, OUTPUT);

//     digitalWrite(RELAY, LOW);

//     dht.begin();

//     Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

//     Serial.println("System Initializing...");
//     delay(30000);  
//     Serial.println("System Ready\n");
// }

// void loop() {
//     Blynk.run();

//     float temp = dht.readTemperature();
//     float hum = dht.readHumidity();
//     int motion = digitalRead(PIR);

//     int relayState = digitalRead(RELAY);  // FIXED

//     if (!manualControl) {
//         if (motion == HIGH && temp > 28) {
//             digitalWrite(RELAY, HIGH);
//             relayState = HIGH;
//         } else {
//             digitalWrite(RELAY, LOW);
//             relayState = LOW;
//         }
//     }

//     float power = relayState ? FAN_POWER_WATTS : 0;

//     Blynk.virtualWrite(V1, temp);
//     Blynk.virtualWrite(V2, hum);
//     Blynk.virtualWrite(V3, motion);
//     Blynk.virtualWrite(V4, power);

//     Serial.println("----------- SYSTEM STATUS -----------");

//     Serial.print("Temperature: ");
//     Serial.print(temp);
//     Serial.print(" °C, ");

//     Serial.print("Humidity: ");
//     Serial.print(hum);
//     Serial.print(" %, ");

//     Serial.print("Motion: ");
//     Serial.print(motion == HIGH ? "YES, " : "NO, ");

//     Serial.print("Fan Status: ");
//     Serial.print(relayState ? "ON, " : "OFF, ");

//     Serial.print("Power Usage: ");
//     Serial.print(power);
//     Serial.println(" W");

//     delay(2000);
// }