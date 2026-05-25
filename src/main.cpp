#include <Arduino.h>
#include <LovyanGFX.hpp>
#include <SPI.h>

// --- НАСТРОЙКА CC1101 ---
#define CC1101_CS    5

SPIClass * cc1101_spi = NULL;

void writeCC1101Register(byte reg, byte value) {
  cc1101_spi->beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
  digitalWrite(CC1101_CS, LOW);
  cc1101_spi->transfer(reg);
  cc1101_spi->transfer(value);
  digitalWrite(CC1101_CS, HIGH);
  cc1101_spi->endTransaction();
}

// --- АВТОМАТИЧЕСКАЯ НАСТРОЙКА ЭКРАНА LILYGO T-EMBED ---
class LGFX : public lgfx::LGFX_Default
{
public:
  LGFX(void)
  {
    auto cfg = bus_spi(); // Берем дефолтные настройки шины
    cfg.spi_host = SPI2_HOST;
    cfg.spi_mode = 0;
    cfg.freq_write = 20000000;
    cfg.freq_read  = 10000000;
    cfg.spi_3wire  = true;
    cfg.use_lock   = true;
    cfg.dma_channel = SPI_DMA_CH_AUTO;
    cfg.pin_sclk = 18;
    cfg.pin_mosi = 23;
    cfg.pin_miso = -1;
    cfg.pin_dc   = 15;
    bus_spi(cfg); // Применяем настройки шины

    auto panel_cfg = panel(); // Берем дефолтные настройки панели
    panel_cfg.pin_cs           = 5;
    panel_cfg.pin_rst          = 13;
    panel_cfg.pin_busy         = -1;
    panel_cfg.panel_width      = 240;
    panel_cfg.panel_height     = 135;
    panel_cfg.offset_x         = 40;
    panel_cfg.offset_y         = 52;
    panel_cfg.offset_rotation  = 0;
    panel_cfg.dummy_read_pixel = 8;
    panel_cfg.dummy_read_bits  = 1;
    panel_cfg.readable         = false;
    panel_cfg.invert           = true;
    panel_cfg.rgb_order        = false;
    panel_cfg.dlen_16bit       = false;
    panel_cfg.bus_shared       = true; // ВАЖНО: bus_shared = true для ESP32
    panel(panel_cfg); // Применяем настройки панели
  }
};

LGFX lcd;

void setup() {
  Serial.begin(115200);

  // Настройка пина CC1101
  pinMode(CC1101_CS, OUTPUT);
  digitalWrite(CC1101_CS, HIGH);
  cc1101_spi = new SPIClass(HSPI);
  
  // Запуск экрана
  lcd.init();
  lcd.setRotation(1);
  lcd.fillScreen(TFT_BLACK);
  
  // Отрисовка меню
  lcd.setTextColor(TFT_WHITE, TFT_BLACK);
  lcd.setTextSize(3);
  lcd.setCursor(10, 20);
  lcd.print("ГЛАВНОЕ МЕНЮ");

  lcd.setTextSize(4);
  lcd.setTextColor(TFT_GREEN, TFT_BLACK);
  lcd.setCursor(30, 60);
  lcd.print("Привет!");

  lcd.setTextSize(2);
  lcd.setTextColor(TFT_CYAN, TFT_BLACK);
  lcd.setCursor(10, 110);
  lcd.print("CC1101 Ready...");

  // Отправка команды сброса в CC1101
  writeCC1101Register(0x30, 0x00);
}

void loop() {
  delay(1000);
}
