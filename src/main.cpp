#include <Arduino.h>
#include <Wire.h>

// === ЖЕСТКО ЗАДАЕМ НАСТРОЙКИ ЭКРАНА ===
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
#define LOAD_GLCD
#define LOAD_FONT2
#define SPI_FREQUENCY  20000000

#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

// Функция для принудительного включения подсветки через чип TCA9554
void turnOnBacklight() {
  Wire.begin(18, 17); // Пины I2C на T-Embed
  Wire.beginTransmission(0x38); // Адрес чипа подсветки
  Wire.write(0x01); // Отправляем команду включения
  Wire.endTransmission();
  pinMode(27, OUTPUT);
  digitalWrite(27, HIGH); // Дублируем сигналом на пин
}

void setup() {
  Serial.begin(115200);

  // ВКЛЮЧАЕМ ПОДСВЕТКУ ПЕРЕД ИНИЦИАЛИЗАЦИЕЙ ЭКРАНА
  turnOnBacklight();

  tft.init();
  tft.setRotation(1);
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
