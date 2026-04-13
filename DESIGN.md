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
| Part | Price | Where to buy |
|------|-------|--------------|
| ESP32-CAM with camera | $10 | https://www.amazon.com/Seeed-Studio-XIAO-ESP32-Sense/dp/B0C69FFVHH/ref=sr_1_1_sspa?crid=BVHEJDZ5JEWC&dib=eyJ2IjoiMSJ9.PooeaXEgLrTuTEkMB5N2-4KuzAWaLYFoLEoi5aLQzxa5RqvXNKIo2Lx6ewXn7wDykjZpwx3Obm67yOdbY8HD3KOwJKyjEpbJnVL5TDE1rPGHNlzfp20LxxqYENpKgC2r0KJUBprQkZ2T0jKOyZTlWYgfn4m8SiyEGH1ddKueUO0RKA2QRe1RbossNDVQJICP6pz3P-bUcJ67oykRDmFgMdYsMJDvaLq1SfPWe7Ug4hg.alk7VEFhbjKzUnVt14Ol4AZS-Kemtdk4z52QcSmCVng&dib_tag=se&keywords=ESP32-CAM%2Bwith%2Bcamera&qid=1776057912&sprefix=esp32-cam%2Bwith%2Bcamera%2Caps%2C284&sr=8-1-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&th=1  |
| FT232RL FTDI programmer | $6 | Amazon: search "FT232RL FTDI" |
| Sound sensor KY-038 | $4 | Amazon: search "KY-038 sound sensor" |
| Servo motor SG90 (2x) | $6 | Amazon: search "SG90 servo" |
| LED Matrix MAX7219 (2x) | $8 | Amazon: search "MAX7219 LED matrix" |
| Buzzer | $2 | Amazon: search "passive buzzer 3.3V" |
| Breadboard + wires | $8 | Amazon: search "breadboard jumper wires kit" |
| USB cables | $4 | Amazon: search "micro USB cable" |
| **TOTAL** | **~$48** | |

## Custom PCB
No. Using breadboard for prototype.

## Timeline
- Week 1: Order parts, test each component
- Week 2: Write code, combine everything
- Week 3: Build the body, wire it up
- Week 4: Fix bugs, make demo video, submit

## Inspiration
JARVIS from Iron Man
