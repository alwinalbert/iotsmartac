// #define BLYNK_TEMPLATE_ID "TMPL3bMZcP3IS"
// #define BLYNK_TEMPLATE_NAME "esp32"
// #define BLYNK_AUTH_TOKEN "1hqcKqiVXF0-fWrJ-rbCNlSrPbo7kwNz"

// #include <Arduino.h>
// #include <WiFi.h>
// #include <WiFiClientSecure.h>
// #include <BlynkSimpleEsp32.h>
// #include <UniversalTelegramBot.h>
// #include <DHT.h>

// // WiFi
// char ssid[] = "Nop";
// char pass[] = "qwmnpozx8ie3";

// // Telegram
// #define BOT_TOKEN "8625629426:AAEIwdP6D5HOnF8vju1n9ePChy4R_e8fQM0"
// #define CHAT_ID "1446264930"

// WiFiClientSecure client;
// UniversalTelegramBot bot(BOT_TOKEN, client);

// // Pins
// #define RELAY 26
// #define PIR 27
// #define DHTPIN 4
// #define DHTTYPE DHT22

// DHT dht(DHTPIN, DHTTYPE);

// // Power
// #define FAN_POWER_WATTS 10  

// bool manualControl = false;

// // Timers
// unsigned long lastTelegramCheck = 0;
// unsigned long lastSensorUpdate = 0;

// // ---------------- BLYNK CONTROL ----------------
// BLYNK_WRITE(V0) {
//     int value = param.asInt();
//     manualControl = true;

//     if (value == 255) {
//         digitalWrite(RELAY, HIGH);
//         Serial.println("Fan ON (Blynk)");
//     } else {
//         digitalWrite(RELAY, LOW);
//         Serial.println("Fan OFF (Blynk)");
//     }
// }

// // ---------------- TELEGRAM ----------------
// void handleTelegram(int numNewMessages) {
//     for (int i = 0; i < numNewMessages; i++) {

//         String text = bot.messages[i].text;
//         String from_id = bot.messages[i].chat_id;

//         text.toLowerCase();

//         if (from_id != CHAT_ID) {
//             bot.sendMessage(from_id, "Unauthorized user", "");
//             continue;
//         }

//         if (text == "/start") {
//             bot.sendMessage(CHAT_ID,
//             "Smart AC Bot\nCommands:\nac on\nac off\nstatus", "");
//         }

//         else if (text == "ac on") {
//             digitalWrite(RELAY, HIGH);
//             manualControl = true;
//             bot.sendMessage(CHAT_ID, "Fan ON", "");
//         }

//         else if (text == "ac off") {
//             digitalWrite(RELAY, LOW);
//             manualControl = true;
//             bot.sendMessage(CHAT_ID, "Fan OFF", "");
//         }

//         else if (text == "status") {
//             int state = digitalRead(RELAY);
//             bot.sendMessage(CHAT_ID,
//                 state ? "Fan is ON" : "Fan is OFF", "");
//         }
//     }
// }

// // ---------------- SETUP ----------------
// void setup() {
//     Serial.begin(9600);

//     pinMode(RELAY, OUTPUT);
//     pinMode(PIR, INPUT);

//     digitalWrite(RELAY, LOW);

//     dht.begin();

//     // WiFi
//     WiFi.begin(ssid, pass);
//     Serial.print("Connecting WiFi");

//     while (WiFi.status() != WL_CONNECTED) {
//         delay(500);
//         Serial.print(".");
//     }

//     Serial.println("\nWiFi Connected");

//     // Telegram HTTPS
//     client.setInsecure();

//     // Blynk
//     Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

//     Serial.println("System Ready");
//     delay(30000); // PIR calibration
// }

// // ---------------- LOOP ----------------
// void loop() {

//     Blynk.run();

//     // ---- TELEGRAM ----
//     if (millis() - lastTelegramCheck > 2000) {

//         int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

//         while (numNewMessages) {
//             handleTelegram(numNewMessages);
//             numNewMessages = bot.getUpdates(bot.last_message_received + 1);
//         }

//         lastTelegramCheck = millis();
//     }

//     // ---- SENSOR + CONTROL ----
//     if (millis() - lastSensorUpdate > 2000) {

//         float temp = dht.readTemperature();
//         float hum = dht.readHumidity();
//         int motion = digitalRead(PIR);

//         int relayState = digitalRead(RELAY);

//         // AUTO CONTROL
//         if (!manualControl) {
//             if (motion == HIGH && temp > 28) {
//                 digitalWrite(RELAY, HIGH);
//                 relayState = HIGH;
//             } else {
//                 digitalWrite(RELAY, LOW);
//                 relayState = LOW;
//             }
//         }

//         float power = relayState ? FAN_POWER_WATTS : 0;

//         // ---- BLYNK UPDATE ----
//         if (!isnan(temp)) Blynk.virtualWrite(V1, temp);
//         if (!isnan(hum)) Blynk.virtualWrite(V2, hum);

//         Blynk.virtualWrite(V3, motion);
//         Blynk.virtualWrite(V4, power);

//         // ---- SERIAL ----
//         Serial.println("----- STATUS -----");
//         Serial.print("Temp: "); Serial.println(temp);
//         Serial.print("Hum: "); Serial.println(hum);
//         Serial.print("Motion: "); Serial.println(motion);
//         Serial.print("Fan: "); Serial.println(relayState);
//         Serial.print("Power: "); Serial.println(power);
//         Serial.println("------------------\n");

//         lastSensorUpdate = millis();
//     }
// }