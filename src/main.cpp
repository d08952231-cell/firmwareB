#include <Arduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup() {
  Serial.begin(115200);

  // МАГИЯ BRUCE: Включаем коммутатор экрана (SN74LVC1G3157)
  // Без этого экран физически не подключен к шине SPI
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);

  // Включаем подсветку
  pinMode(27, OUTPUT);
  digitalWrite(27, HIGH);

  // Инициализация экрана
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
