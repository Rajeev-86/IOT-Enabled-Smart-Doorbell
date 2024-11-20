# Smart Doorbell IoT Project

## Description
This is a **Smart Doorbell** project built using **NodeMCU (ESP8266)**, a **push button**, and a **buzzer**. The system sends a notification to predefined users via **Telegram** when the button is pressed. It plays a melody on the buzzer and automatically resets for future presses.

## Features
- Push button triggers the buzzer and sends a notification.
- Sends a message via Telegram API to multiple users.
- Melody alert on buzzer.
- Wi-Fi-enabled using NodeMCU (ESP8266).

## Components Used
- NodeMCU (ESP8266)
- Push button
- Buzzer
- Power bank (for portable power supply)
- Wi-Fi connectivity

## Installation

### 1. Setup NodeMCU
- Connect the **push button** to the NodeMCU and configure it in the code.
- Connect the **buzzer** to the NodeMCU.

### 2. Setup Telegram Bot
- Create a bot on **Telegram** and get the bot token.
- Get the **chat ID** of the users who should receive notifications.

### 3. Upload the Code
- Install the **ESP8266 board** in the Arduino IDE.
- Upload the `doorbell.ino` file to the NodeMCU.

## How to Use
1. Press the push button.
2. The buzzer will play a melody, and Telegram notifications will be sent to the specified users.

## Future Enhancements
- Add facial recognition or a camera module for video doorbell features.
- Integration with other smart home systems (e.g., voice assistants).
