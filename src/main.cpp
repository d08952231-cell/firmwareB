#include <Arduino.h>
#include <LovyanGFX.hpp>

// Используем готовый класс для LilyGO T-Embed из самой библиотеки
LGFX tft;

void setup() {
  Serial.begin(115200);
  
  // Запуск экрана
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  
  // Рисуем меню
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
