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

Smart speakers just sit there and talk. I wanted something that actually interacts with my space,watches for movement, sees faces, responds to different inputs with physical actions. The goal is a desk companion that feels alive.

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
