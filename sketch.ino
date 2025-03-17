#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

WiFiClientSecure client;  // Create a secure client for HTTPS
#include "env.h" 

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    Serial.begin(115200);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Connecting...");

    // Connect to WiFi
    if (IS_WOKWI)
        WiFi.begin(SSID, PASS, CHANNEL);
    else
        WiFi.begin(SSID, PASS);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");
    lcd.clear();
    lcd.print("WiFi Connected");
    delay(1000);

    client.setInsecure(); 
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(client,ENDPOINT);
        http.addHeader("api-key", API_KEY);

        int httpResponseCode = http.GET();
        if (httpResponseCode == 200) {
            String response = http.getString();
            Serial.println("Response: " + response);

            StaticJsonDocument<200> doc;
            DeserializationError error = deserializeJson(doc, response);
            if (!error) {
                String line1 = doc["line_1"].as<String>();
                String line2 = doc["line_2"].as<String>();

                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print(line1);
                lcd.setCursor(0, 1);
                lcd.print(line2);
            } else
                Serial.println("JSON Parsing Error");
        } else {
            Serial.print("HTTP Error: ");
            Serial.println(httpResponseCode);
        }

        http.end();
    } else
        Serial.println("WiFi Disconnected!");

    delay(10000);
}
