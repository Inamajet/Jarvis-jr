# JARVIS Jr. — Design Document

## What it does
JARVIS Jr. is a desk companion robot that wakes up when you clap twice. It has a camera that streams to your phone, an arm that waves, and an LED face that shows expressions.

## Problem it solves
Smart speakers like Alexa just sit there and talk. JARVIS Jr. actually interacts with your room — it waves, looks at things, and responds to you physically.

## How it works
- **Wake up:** Double-clap detected by sound sensor
- **Vision:** ESP32-CAM streams video to your phone over WiFi
- **Arm:** Servo motor waves or points
- **Face:** LED matrix displays eyes and expressions
- **Sound:** Buzzer makes beeps

## Parts list

| Part | Price | Link |
|------|-------|------|
| ESP32-CAM AI-Thinker (2-pack) | $15.99 | https://www.amazon.com/dp/B09TB1GJ7P |
| FT232RL FTDI Programmer (2-pack) | $5.99 | https://www.amazon.com/dp/B0FHP71BCQ |
| KY-038 Sound Sensor (5-pack) | $8.65 | https://www.amazon.com/dp/B0DGY3K2PM |
| SG90 Servo Motor (4-pack) | $9.99 | https://www.amazon.com/dp/B0FP2P3JC8 |
| MAX7219 LED Matrix 4-in-1 (32x8) | $13.99 | https://www.amazon.com/dp/B0BXDKHZL6 |
| Passive Buzzer (20-pack) | $5.99 | https://www.amazon.com/dp/B0F1KFHSNK |
| Breadboard + Jumper Wires Kit | $14.99 | https://www.amazon.com/dp/B0C1VDKPW2 |
| Micro USB Cable (6ft) | $8.09 | https://www.amazon.com/dp/B07232M876 |
| **TOTAL** | **~$83.68** | |

## Custom PCB
No. Using breadboard for prototype.

## Timeline
- Week 1: Order parts, test each component
- Week 2: Write code, combine everything
- Week 3: Build the body, wire it up
- Week 4: Fix bugs, make demo video, submit

## Inspiration
JARVIS from Iron Man
