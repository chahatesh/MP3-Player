# MP3 Player

A small, custom MP3 player I designed using an ESP32-S3-Zero, DFPlayer Mini, TFT display, and a rotary encoder.

I wanted to make a simple music player becouse playing music on my phone is Data intensive. I designed the PCB in KiCad and also made a 3D-printable case for it.

The player uses a microSD card to store music, a rotary encoder to switch songs, and a small TFT display that shows the current song number and whether the music is playing or paused.

## Images

![MP3 Player](Images/Screenshot%202026-10-30%20194704.png)

![MP3 Player Design](Images/Screenshot%202026-10-31%20205900.png)

## Features

- ESP32-S3-Zero microcontroller
- DFPlayer Mini for MP3 playback
- Small TFT display for song number and playback status
- Rotary encoder for controlling music
- 3.5mm audio jack
- Custom PCB designed in KiCad
- 3D-printable case and encoder cap
- Music stored on a microSD card

## How It Works

The ESP32 controls the DFPlayer Mini through a serial connection. The DFPlayer reads MP3 files from a microSD card and handles audio playback.

A rotary encoder is used to control the songs turning it changes the song, and clicking it plays or pauses it.

The TFT display is kept simple. It only shows the current song number and whether the player is playing or paused.


## Pin Connections

The current Arduino code uses the following GPIO pins.

### TFT Display

| TFT Pin | ESP32 GPIO |
|---|---|
| CS | GPIO10 |
| DC | GPIO9 |
| RST | GPIO13 |
| SCK | GPIO12 |
| MOSI | GPIO11 |

### Rotary Encoder

| Encoder Pin | ESP32 GPIO |
|---|---|
| A | GPIO6 |
| B | GPIO7 |
| Switch | GPIO8 |
| Common | GND |

### DFPlayer Mini

The ESP32 TX pin (GPIO43) connects to the DFPlayer RX pin through a 1kΩ resistor.

The ESP32 and DFPlayer also share a common ground.

The DFPlayer's left and right outputs connect to the audio jack through the PCB.

## PCB Design

I designed the PCB using KiCad. The main goal was to fit all the components into a small board while keeping everything organized.

The board includes connections for the ESP32, TFT display, DFPlayer Mini, rotary encoder, and audio jack.

The KiCad project files are included in the repository:

- [PCB Layout](MP3-Player.kicad_pcb)
- [Schematic](MP3-Player.kicad_sch)
- [KiCad Project](MP3-Player.kicad_pro)

Manufacturing files are available in the [production](production) folder, including a Gerber for PCB fabrication.

## 3D Printed Case

I also designed a case to hold the PCB and a cap for the rotary encoder.

The files are available in both STL and STEP formats:

| Part | STL | STEP |
|---|---|---|
| PCB Case | [Download](CAD/PCB-Case.stl) | [Download](CAD/PCB-Case.step) |
| Rotary Encoder Cap | [Download](CAD/RE-Cap.stl) | [Download](CAD/RE-Cap.step) |

The STL files can be used for 3D printing, while the STEP files can be edited in CAD software.

I used Onshape for this, link [Here](https://cad.onshape.com/documents/7a1423e237ed7c255f250c8c/w/72b5ca8bb9bfd8214d66d290/e/8e44508844e352792cba2dbb?renderMode=0&uiState=6ae691a64f304a127a6a8070)

## Building Your Own

### 1. Order the PCB

Download the manufacturing ZIP from the [production folder](production/MP3-Player.zip) and upload it to a PCB manufacturer.

### 2. Get the Components

Use the component list and BOM to get the required parts.

### 3. Assemble the Board

Solder the headers, resistor, rotary encoder, audio jack, and other required components onto the PCB.

Connect the ESP32, TFT display, and DFPlayer Mini.

Check the power and ground connections before turning it on.

### 4. Upload the Code

Open [MP3-player-code.ino](MP3-player-code.ino) in Arduino IDE.

Install these libraries:

- Adafruit GFX Library
- Adafruit ST7735 and ST7789 Library
- DFRobotDFPlayerMini

Install ESP32 board support, select the appropriate ESP32-S3 board configuration, and upload the sketch.

The code is configured for an ST7735 display. Other display models may require changes.

### 5. Add Music

Format a microSD card as FAT32 and create a folder named `mp3`.

Name your files `0001.mp3`, `0002.mp3`, `0003.mp3`, and so on.

The current code is configured for 10 songs. You can change SONG_COUNT in the Arduino code to match the number of tracks on the card.

### 6. Test It

Power the player and test the rotary encoder.

Turning it should change songs, and pressing it should pause or resume playback.

The screen displays the song number and the playback state requested by the ESP32. It does not independently verify that audio is playing.


The goal was to build a simple, compact music player using my own PCB instead of connecting everything with a breadboard.

Designed by [Chahatesh](https://github.com/chahatesh).
