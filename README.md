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

My favorite superhero from marvel as ironman. I really just wanted to be able to build cool stuff like him so i just decided to start of with a jarvis like companion.

## How it works

| Feature | How It's Implemented |
|---------|---------------------|
| Motion detection | ESP32-CAM compares frames and triggers when pixels change significantly |
| Face detection | Built-in ESP32 face detection API (HAAR cascade) draws boxes in real-time |
| Clap patterns | Sound sensor counts claps within 1.5 seconds, triggers different actions |
| Phone control | Web page with buttons that send HTTP requests to ESP32 |
| LED face | MAX7219 matrix shows pre-programmed expressions |
| Servo arm | SG90 servo controlled by ESP32 for wave/point gestures |

## Inspiration

JARVIS from Iron Man


![JARVIS_Jr_Full_Wiring](https://github.com/user-attachments/assets/9ebf9776-dc8b-440d-ae8b-e7ccc89ca3b6)



<img width="1495" height="1134" alt="Screenshot 2026-04-13 190743" src="https://github.com/user-attachments/assets/7d95bade-822b-403a-be91-d6f76eb4a310" />

