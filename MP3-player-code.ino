
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <DFRobotDFPlayerMini.h>

//TFT
#define TFT_CS   10
#define TFT_DC   9
#define TFT_RST  13
#define TFT_SCK  12
#define TFT_MOSI 11

//RE
#define ENC_A 6
#define ENC_B 7
#define ENC_SW 8

#define SONG_COUNT 10

Adafruit_ST7735 tft(TFT_CS, TFT_DC, TFT_RST);
DFRobotDFPlayerMini player;

int song = 1;
bool paused = false;
int lastA = HIGH;
int lastButton = HIGH;

unsigned long lastTurn = 0;
unsigned long lastClick = 0;

void showScreen() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(3);

  tft.setCursor(10, 25);
  tft.print("Song ");
  tft.println(song);

  tft.setCursor(10, 75);
  tft.setTextColor(paused ? ST77XX_RED : ST77XX_GREEN);
  tft.println(paused ? "PAUSED" : "PLAYING");
}

void playSong() {
  player.playMp3Folder(song);
  paused = false;
  showScreen();
}

void setup() {
  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);
  pinMode(ENC_SW, INPUT_PULLUP);

  lastA = digitalRead(ENC_A);

  SPI.begin(TFT_SCK, -1, TFT_MOSI, TFT_CS);
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);

  Serial1.begin(9600, SERIAL_8N1, -1, 43);
  player.begin(Serial1, false, false);

  delay(1500);
  player.volume(20);
  delay(100);

  playSong();
}

void loop() {
  int a = digitalRead(ENC_A);
  int button = digitalRead(ENC_SW);

  if (a != lastA && a == LOW && millis() - lastTurn > 60) {
    if (digitalRead(ENC_B) == HIGH) {
      song++;
    } else {
      song--;
    }

    if (song > SONG_COUNT) song = 1;
    if (song < 1) song = SONG_COUNT;

    playSong();
    lastTurn = millis();
  }
  lastA = a;

  if (button == LOW && lastButton == HIGH &&
      millis() - lastClick > 250) {

    paused = !paused;

    if (paused) {
      player.pause();
    } else {
      player.start();
    }

    showScreen();
    lastClick = millis();
  }

  lastButton = button;
  delay(1);
}
