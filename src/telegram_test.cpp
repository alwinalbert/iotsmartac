// #include <Arduino.h>
// #include <WiFi.h>
// #include <WiFiClientSecure.h>
// #include <UniversalTelegramBot.h>

// const char* ssid = "Nop";
// const char* password = "qwmnpozx8ie3";

// #define BOT_TOKEN "8625629426:AAEIwdP6D5HOnF8vju1n9ePChy4R_e8fQM0"
// #define CHAT_ID "1446264930"

// WiFiClientSecure client;
// UniversalTelegramBot bot(BOT_TOKEN, client);

// #define RELAY 26

// unsigned long lastTime = 0;
// const unsigned long interval = 2000;

// void setup() {
//   Serial.begin(9600);

//   pinMode(RELAY, OUTPUT);
//   digitalWrite(RELAY, LOW);

//   WiFi.begin(ssid, password);
//   Serial.print("Connecting WiFi");

//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }

//   Serial.println("\nWiFi Connected");

//   client.setInsecure();

//   Serial.println("Telegram Bot Ready");
// }

// void handleMessages(int numNewMessages) {
//   for (int i = 0; i < numNewMessages; i++) {

//     String text = bot.messages[i].text;
//     String from_id = bot.messages[i].chat_id;

//     text.toLowerCase();

//     Serial.println("Received: " + text);

//     if (from_id != CHAT_ID) {
//       bot.sendMessage(from_id, "Unauthorized user", "");
//       continue;
//     }

//     if (text == "/start") {
//       String welcome = "Smart AC Control Bot\n";
//       welcome += "Commands:\n";
//       welcome += "ac on\nac off\nstatus";
//       bot.sendMessage(CHAT_ID, welcome, "");
//     }

//     else if (text == "ac on") {
//       digitalWrite(RELAY, HIGH);
//       bot.sendMessage(CHAT_ID, "Fan ON", "");
//     }

//     else if (text == "ac off") {
//       digitalWrite(RELAY, LOW);
//       bot.sendMessage(CHAT_ID, "Fan OFF", "");
//     }

//     else if (text == "status") {
//       int state = digitalRead(RELAY);
//       bot.sendMessage(CHAT_ID, state ? "Fan is ON" : "Fan is OFF", "");
//     }

//     else {
//       bot.sendMessage(CHAT_ID, "Use: ac on / ac off / status", "");
//     }
//   }
// }

// void loop() {

//   if (WiFi.status() != WL_CONNECTED) {
//     WiFi.begin(ssid, password);
//   }

//   if (millis() - lastTime > interval) {

//     int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

//     while (numNewMessages) {
//       handleMessages(numNewMessages);
//       numNewMessages = bot.getUpdates(bot.last_message_received + 1);
//     }

//     lastTime = millis();
//   }
// }