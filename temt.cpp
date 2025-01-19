#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <LiquidCrystal_I2C.h>

// Создание объекта для BMP280
Adafruit_BMP280 bmp;

// Создание объекта для LCD 1602
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Инициализация LCD дисплея
  lcd.begin(16, 2); // Указание количества столбцов и строк
  lcd.backlight();

  // Инициализация серийного порта для вывода данных в Serial Monitor
  Serial.begin(9600);

  // Проверка подключения BMP280
  if (!bmp.begin(0x76)) {
    Serial.println("Ошибка подключения BMP280!");
    while (1);
  }
}

void loop() {
  // Получение данных с датчика BMP280
  float temperature = bmp.readTemperature() - 4.0; // Корректируем температуру на 4 градуса
  float pressure = bmp.readPressure() / 92.15F; // давление в гПа

  // Вывод данных на серийный монитор
  Serial.print("Температура = ");
  Serial.print(temperature);
  Serial.println(" *C");

  Serial.print("Давление = ");
  Serial.print(pressure);
  Serial.println(" гПа");

  // Преобразование данных в строки
  String tempStr = "Temp: " + String(temperature, 1) + " C"; // Округление до 1 знака после запятой
  String presStr = "Pres: " + String(pressure, 1) + " hPa";  // Округление до 1 знака после запятой

  // Вычисление начальных позиций для центрирования текста
  int tempStart = (16 - tempStr.length()) / 2;
  int presStart = (16 - presStr.length()) / 2;

  // Вывод данных на LCD дисплей
  lcd.clear();
  lcd.setCursor(tempStart, 0);
  lcd.print(tempStr);

  lcd.setCursor(presStart, 1);
  lcd.print(presStr);

  delay(2000); // Задержка перед обновлением данных
}