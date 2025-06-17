# ESP32 Evil Twin Awareness Demo

This project is an educational demonstration of an Evil Twin Wi-Fi attack using an ESP32. It sets up a fake "Free WiFi" access point and serves a cloned Gmail-style login page. The goal is to help raise awareness about the dangers of connecting to open Wi-Fi networks and falling for phishing attempts.

## Legal & Ethical Disclaimer

This code is for **educational and security awareness purposes only**. Do not use this project for any malicious activity or without consent. Unauthorized use may be illegal and is strictly discouraged.

## Features

- ESP32-based fake Wi-Fi access point (`Free_WiFi`)
- Captive portal compatibility with Android, iOS, and Windows
- Gmail-style fake login page for phishing simulation
- Logs captured credentials to Serial Monitor for demonstration

## Hardware Required

- ESP32 development board
- Micro USB cable
- Arduino IDE

## Installation

1. Open Arduino IDE
2. Install the ESP32 board via Board Manager
3. Select the correct ESP32 board and port
4. Upload the code to your ESP32

## Usage

- After uploading, the ESP32 will start broadcasting a Wi-Fi network named `Free_WiFi`
- When a device connects, it will be redirected to a fake login page
- Any credentials entered will be printed to the Serial Monitor

## File Structure

- `main1.ino` – Main Arduino sketch that runs the fake AP page

## Educational Purpose

This demonstration helps students, IT staff, and regular users understand how easy it is to fall into Wi-Fi-based phishing traps. It encourages better cybersecurity habits like:

- Never logging into accounts over unknown public Wi-Fi
- Using VPNs
- Checking URLs for authenticity

## License

MIT License – Use responsibly.
