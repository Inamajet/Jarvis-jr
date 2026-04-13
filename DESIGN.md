# JARVIS Jr. — Design Document

## What it does

JARVIS Jr. is a desk companion that watches your room with motion detection, recognizes faces through its camera, responds to different clap patterns with physical gestures, and can be controlled from your phone.

## Problem it solves

Smart speakers like Alexa are passive — they wait for you to talk to them. JARVIS Jr. is proactive — it watches, sees, and responds physically. It doesn't just sit there; it feels present in the room.

## How it works

### Input Methods

| Input | What Happens |
|-------|--------------|
| Motion detected | Wakes up automatically |
| 2 claps | Waves arm + shows happy face |
| 3 claps | Points at you + shows alert face |
| 4 claps | Takes photo + saves to SD |
| Phone button "Wave" | Waves arm |
| Phone button "Photo" | Takes photo |
| Phone button "Sleep" | Goes to sleep mode |

### Output Methods

| Output | Hardware |
|--------|----------|
| Arm movement | SG90 servo (wave, point) |
| Face expressions | MAX7219 LED matrix (happy, alert, sleeping) |
| Sound | Passive buzzer (confirmation beeps) |
| Vision | ESP32-CAM with face detection overlay |

## Parts list

| Part | Price | Link |
|------|-------|------|
| ESP32-CAM AI-Thinker (2-pack) | $15.99 | [Amazon](https://www.amazon.com/dp/B09TB1GJ7P) |
| FT232RL FTDI Programmer | $9.99 | [Amazon](https://www.amazon.com/dp/B0FHP71BCQ) |
| KY-038 Sound Sensor | $6.99 | [Amazon](https://www.amazon.com/dp/B0DGY3K2PM) |
| SG90 Servo (2-pack) | $8.99 | [Amazon](https://www.amazon.com/dp/B0FP2P3JC8) |
| MAX7219 LED Matrix (2-pack) | $7.99 | [Amazon](https://www.amazon.com/dp/B0BXDKHZL6) |
| Passive Buzzer | $4.99 | [Amazon](https://www.amazon.com/dp/B0F1KFHSNK) |
| Breadboard 830 points | $3.99 | Included in kit |
| Jumper wires (M-M, M-F) | $3.99 | Included in kit |
| Micro USB cable (2-pack) | $5.98 | [Amazon](https://www.amazon.com/dp/B07232M876) |
| **TOTAL** | **~$67** | |

## Custom PCB

No. Using breadboard for prototype.

## Timeline

- Week 1: Order parts, test each component individually
- Week 2: Combine code, test motion + face detection
- Week 3: Add clap patterns + phone control, build the body
- Week 4: Final assembly, demo video, submit

## Inspiration

JARVIS from Iron Man — specifically the desk presence, not the AI.
