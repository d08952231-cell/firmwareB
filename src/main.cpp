#include <Arduino.h>
#include "LilyGo_T-Embed.h" // ОФИЦИАЛЬНАЯ БИБЛИОТЕКА

LilyGo_TEmbed tft;

void setup() {
  Serial.begin(115200);

  // Официальная команда включения экрана и подсветки
  tft.begin();

  tft.fillScreen(TFT_BLACK);
  
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(3);
  tft.setCursor(10, 20);
  tft.print("ГЛАВНОЕ МЕНЮ");

  tft.setTextSize(4);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setCursor(30, 60);
  tft.print("Привет!");

  tft.setTextSize(2);
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.setCursor(10, 110);
  tft.print("CC1101 Ready...");
}

void loop() {
  delay(1000);
}
