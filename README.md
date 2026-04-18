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


Name	Purpose	Quantity	Total Cost (USD)	Link	Distributor
MAX7219 LED Matrix	Display expression	3	13.99	https://www.amazon.com/dp/B0BXDKHZL6?th=1	Amazon
ESP32-CAM	To detect motion and faces	2	15.99	https://www.amazon.com/dp/B09TB1GJ7P?th=1	Amazon
KY-038 Sound Sensor	Listen for claps	2	8.65	https://www.amazon.com/dp/B0DGY3K2PM	Amazon
Passive Buzzer	To play sound as a response	10	5.99	https://www.amazon.com/dp/B0F1KFHSNK?th=1	Amazon
SG90 Servo	For functional arms	4	9.99	https://www.amazon.com/dp/B0FP2P3JC8?th=1	Amazon
Breadboard kit	Wire everything	1	14.99	https://www.amazon.com/dp/B0C1VDKPW2	Amazon
FT232RL FTDI Programmer	To give it Arduino capabilities	2	6.49	https://www.amazon.com/dp/B0FHP71BCQ	Amazon
Micro USB cable	Power it	1	8.09	https://www.amazon.com/dp/B07232M876?th=1	Amazon
3D printed parts	for the chasis	1	20.00		protolabs
Total			105.49		
