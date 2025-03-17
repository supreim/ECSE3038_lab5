# ECSE3038 Lab 5

## Purpose
This project was developed as part of the ECSE3038 Lab 5 exercise. The objective is to program an ESP32 microcontroller to connect to an API, extract a message from the JSON response, and display it on a 16x2 LCD.

## Function Descriptions

### `setup()`
- Initializes serial communication for debugging.
- Connects the ESP32 to WiFi.
- Sets up the LCD display.

### `loop()`
- Checks WiFi connectivity.
- Sends a GET request to the API endpoint.
- Parses the JSON response.
- Extracts `line_1` and `line_2` from the JSON.
- Displays the message on the LCD.
- Waits for a predefined time before making another request.

## Riddle
I have keys but open no locks. I have space but no room. You can enter, but you can't go outside. What am I?

