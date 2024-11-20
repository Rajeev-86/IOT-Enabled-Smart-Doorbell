#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "SSID";           // Replace with your WiFi SSID
const char* password = "PASSWORD";   // Replace with your WiFi password

const char* botToken = "8176504356:AAHj_lQ6CvgAbnYJIblhsg6Sr0Y03Ia_u1k";
const char* chatIDs[] = { "5998875572", "2098139314" };
const int numChatIDs = 2;

const int buttonPin = D1;
const int buzzerPin = D2;

int melody[] = {
  523, // C5
  392, // G4
  698, // F5
  587, // D5
  523, // C5
  440, // A4
  349  // F4
};

int noteDurations[] = {
  500, // Duration for C5
  500, // Duration for G4
  400, // Duration for F5
  500, // Duration for D5
  500, // Duration for C5
  600, // Duration for A4
  700  // Duration for F4
};

bool messageSent = false;

WiFiClientSecure client;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);       // Set button pin as input with pull-up
  pinMode(buzzerPin, OUTPUT);             // Set buzzer pin as output
  digitalWrite(buzzerPin, LOW);           // Ensure the buzzer is off initially
  client.setInsecure();                   // Disable SSL certificate validation

  // Connect to Wi-Fi
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && !messageSent) {  // Button pressed, message not sent
    playMelody();                            // Play the melody
    sendTelegramMessage("Someone's at the Door!🚪"); // Send Telegram message
    messageSent = true;                      // Mark message as sent
  }

  if (buttonState == HIGH) {                 // Reset message status when button is released
    messageSent = false;
  }

  delay(100);  // Debounce delay
}

void playMelody() {
  for (int i = 0; i < 4; i++) {              // Loop through each note in the melody
    int noteDuration = noteDurations[i];
    tone(buzzerPin, melody[i], noteDuration); // Play the note
    delay(noteDuration * 1.3);               // Wait before playing the next note
  }
  noTone(buzzerPin);                         // Stop the tone after the melody
}

void sendTelegramMessage(String message) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient https;
    for (int i = 0; i < numChatIDs; i++) {   // Loop through each chat ID
      String url = String("https://api.telegram.org/bot") + botToken + "/sendMessage?chat_id=" + chatIDs[i] + "&text=" + message;
      https.begin(client, url);

      int httpCode = https.GET();
      if (httpCode > 0) {
        Serial.println("Message sent to chat ID: " + String(chatIDs[i]));
      } else {
        Serial.println("Error sending message to chat ID: " + String(chatIDs[i]));
      }
      https.end();
    }
  } else {
    Serial.println("Not connected to WiFi.");
  }
}
