# JARVIS Jr.

An ESP32-CAM powered desk companion that actually watches your room.

## What it does

- **Motion detection**: Wakes up when it detects movement in front of it
- **Face detection**: Recognizes faces and draws boxes around them in the camera stream
- **Clap patterns**: 2 claps = wave, 3 claps = point at you, 4 claps = take a photo
- **Phone control**: Buttons on the web interface let you trigger actions remotely
- **LED expressions**: Shows different faces based on what it's doing
- **Camera streaming**: Watch live video from your phone with face detection overlay

## Why I'm building it

Smart speakers just sit there and talk. I wanted something that actually interacts with my space — watches for movement, sees faces, responds to different inputs with physical actions. The goal is a desk companion that feels alive, not just another voice assistant.

## How it works

| Feature | How It's Implemented |
|---------|---------------------|
| Motion detection | ESP32-CAM compares frames and triggers when pixels change significantly |
| Face detection | Built-in ESP32 face detection API (HAAR cascade) draws boxes in real-time |
| Clap patterns | Sound sensor counts claps within 1.5 seconds, triggers different actions |
| Phone control | Web page with buttons that send HTTP requests to ESP32 |
| LED face | MAX7219 matrix shows pre-programmed expressions |
| Servo arm | SG90 servo controlled by ESP32 for wave/point gestures |

## Parts list

| Part | Price | Where to buy |
|------|-------|--------------|
| ESP32-CAM with camera | $15.99 (2-pack) | [Amazon](https://www.amazon.com/dp/B09TB1GJ7P) |
| FT232RL FTDI programmer | $9.99 | [Amazon](https://www.amazon.com/dp/B0FHP71BCQ) |
| Sound sensor KY-038 | $6.99 | [Amazon](https://www.amazon.com/dp/B0DGY3K2PM) |
| Servo motor SG90 (2x) | $8.99 | [Amazon](https://www.amazon.com/dp/B0FP2P3JC8) |
| LED Matrix MAX7219 (2x) | $7.99 | [Amazon](https://www.amazon.com/dp/B0BXDKHZL6) |
| Buzzer | $4.99 | [Amazon](https://www.amazon.com/dp/B0F1KFHSNK) |
| Breadboard + wires | $7.99 | [Amazon](https://www.amazon.com/dp/B0C1VDKPW2) |
| USB cables | $5.98 | [Amazon](https://www.amazon.com/dp/B07232M876) |
| **TOTAL** | **~$67** | |

## Status

- [ ] Approved
- [ ] Parts ordered
- [ ] Built
- [ ] Demo submitted

## Inspiration

JARVIS from Iron Man — a desk companion that feels present and responsive.
