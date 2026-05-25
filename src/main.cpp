#include <Arduino.h>

// === ЖЕСТКО ЗАДАЕМ НАСТРОЙКИ ЭКРАНА ПРЯМО В КОДЕ ===
#define USER_SETUP_INFO "LilyGO_TEmbed"
#define ST7789_DRIVER
#define TFT_WIDTH  135
#define TFT_HEIGHT 240

#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   5
#define TFT_DC   15
#define TFT_RST  13
#define TFT_BL   27

#define LOAD_GLCD   // Шрифт 1
#define LOAD_FONT2  // Шрифт 2
#define SPI_FREQUENCY  20000000

#include <TFT_eSPI.h> // Подключаем библиотеку ПОСЛЕ того, как задали настройки

TFT_eSPI tft = TFT_eSPI();

void setup() {
  Serial.begin(115200);

  // Включаем подсветку экрана
  pinMode(27, OUTPUT);
  digitalWrite(27, HIGH);

  // Запускаем экран
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
