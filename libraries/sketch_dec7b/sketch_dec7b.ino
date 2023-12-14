#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_DS1307.h>
#include <DHT.h>
#define DS1307_ADDRESS 0x68

DS1307 rtc(DS1307_ADDRESS);
#define SDA 21
#define SCL 22
#define DHTPIN 23
#define DHTTYPE DHT11

DS1307 rtc;
Adafruit_8x8matrix ledmatrix[4] = {
  Adafruit_8x8matrix(),
  Adafruit_8x8matrix(),
  Adafruit_8x8matrix(),
  Adafruit_8x8matrix()
};
DHT dht(DHTPIN, DHTTYPE);

// Task để hiển thị thời gian
void task_show_time() {
  // Đọc thời gian từ module RTC
  uint8_t hour = rtc.getHour(true);
  uint8_t minute = rtc.getMinute();
  uint8_t second = rtc.getSecond();

  // Hiển thị thời gian lên 4 led matrix
  for (int i = 0; i < 4; i++) {
    ledmatrix[i].setCursor(0, 0);
    ledmatrix[i].print(hour);
    ledmatrix[i].setCursor(1, 0);
    ledmatrix[i].print(":");
    ledmatrix[i].setCursor(2, 0);
    ledmatrix[i].print(minute);
    ledmatrix[i].setCursor(3, 0);
    ledmatrix[i].print(":");
    ledmatrix[i].setCursor(4, 0);
    ledmatrix[i].print(second);
  }
}

// Task để hiển thị nhiệt độ
void task_show_temperature() {
  // Đọc nhiệt độ và độ ẩm từ cảm biến DHT11
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Hiển thị nhiệt độ lên 4 led matrix
  for (int i = 0; i < 4; i++) {
    ledmatrix[i].setCursor(0, 5);
    ledmatrix[i].print("Nhiệt độ");
    ledmatrix[i].setCursor(8, 5);
    ledmatrix[i].print(temperature);
    ledmatrix[i].setCursor(13, 5);
    ledmatrix[i].print("C");
  }
}

// Task để hiển thị độ ẩm
void task_show_humidity() {
  // Đọc nhiệt độ và độ ẩm từ cảm biến DHT11
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Hiển thị độ ẩm lên 4 led matrix
  for (int i = 0; i < 4; i++) {
    ledmatrix[i].setCursor(0, 10);
    ledmatrix[i].print("Độ ẩm");
    ledmatrix[i].setCursor(8, 10);
    ledmatrix[i].print(humidity);
    ledmatrix[i].setCursor(13, 10);
    ledmatrix[i].print("%");
  }
}

void setup() {
  Wire.begin(SDA, SCL);
  rtc.begin();
  for (int i = 0; i < 4; i++) {
    ledmatrix[i].begin();
  }

  dht.begin();
}

void loop() {
  // Khởi chạy các task
  task_show_time();
  task_show_temperature();
  task_show_humidity();

  // Đợi 1 giây
  delay(1000);
}