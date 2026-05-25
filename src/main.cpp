#include <Arduino.h>
#include <LovyanGFX.hpp>
#include <SPI.h>

// --- НАСТРОЙКА SPI ДЛЯ CC1101 НА LILYGO T-EMBED ---
#define CC1101_SCLK  18
#define CC1101_MOSI  23
#define CC1101_MISO  -1 
#define CC1101_CS    5
#define CC1101_GDO0  4

SPIClass * cc1101_spi = NULL;

void writeCC1101Register(byte reg, byte value) {
  cc1101_spi->beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
  digitalWrite(CC1101_CS, LOW);
  cc1101_spi->transfer(reg);
  cc1101_spi->transfer(value);
  digitalWrite(CC1101_CS, HIGH);
  cc1101_spi->endTransaction();
}

// --- НАСТРОЙКА ЭКРАНА ---
class LGFX : public lgfx::LGFX_Default {
public:
  LGFX(void) {
    { 
      auto cfg = bus_spi();
      cfg.spi_host = SPI2_HOST;
      cfg.spi_mode = 0;
      cfg.freq_write = 20000000;  // ИСПРАВЛЕНО: безопасная частота для сборки
      cfg.freq_read  = 10000000;  // ИСПРАВЛЕНО
      cfg.spi_3wire  = true;
      cfg.use_lock   = true;
      cfg.dma_channel = SPI_DMA_CH_AUTO;
      cfg.pin_sclk = 18;
      cfg.pin_mosi = 23;
      cfg.pin_miso = -1;
      cfg.pin_dc   = 15;
      bus_spi(cfg);
    }
    { 
      auto cfg = panel();
      cfg.pin_cs           = 5;
      cfg.pin_rst          = 13;
      cfg.pin_busy         = -1;
      cfg.panel_width      = 240;
      cfg.panel_height     = 135;
      cfg.offset_x         = 40;
      cfg.offset_y         = 52;
      cfg.offset_rotation  = 0;
      cfg.dummy_read_pixel = 8;
      cfg.dummy_read_bits  = 1;
      cfg.readable         = false;
      cfg.invert           = true;
      cfg.rgb_order        = false;
      cfg.dlen_16bit       = false;
      cfg.bus_shared       = false;
      panel(cfg);
    }
  }
};

LGFX lcd;

void setup() {
  Serial.begin(115200);

  // Инициализация пинов CC1101
  pinMode(CC1101_CS, OUTPUT);
  digitalWrite(CC1101_CS, HIGH);
  cc1101_spi = new SPIClass(HSPI);
  
  // Инициализация экрана
  lcd.init();
  lcd.setRotation(1);
  lcd.fillScreen(TFT_BLACK);
  
  // Рисуем меню
  lcd.setTextColor(TFT_WHITE, TFT_BLACK);
  lcd.setTextSize(3);
  lcd.setCursor(10, 20);
  lcd.print("ГЛАВНОЕ МЕНЮ");

  lcd.setTextSize(4);
  lcd.setTextColor(TFT_GREEN, TFT_BLACK);
  lcd.setCursor(30, 60);
  lcd.print("Привет!"); // Твое слово

  lcd.setTextSize(2);
  lcd.setTextColor(TFT_CYAN, TFT_BLACK);
  lcd.setCursor(10, 110);
  lcd.print("CC1101 Ready...");

  // Сброс CC1101
  writeCC1101Register(0x30, 0x00);
}

void loop() {
  delay(1000);
}
