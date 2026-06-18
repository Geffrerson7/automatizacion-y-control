#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHTesp.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define DHT_PIN 15

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

DHTesp dhtSensor;

void setup() {

  Serial.begin(115200);

  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  if (!display.begin(
      SSD1306_SWITCHCAPVCC,
      0x3C)) {

    Serial.println("OLED no encontrada");

    while (true);
  }

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(10, 10);
  display.println("Sistema Iniciado");

  display.display();

  delay(2000);
}

void loop() {

  TempAndHumidity data =
      dhtSensor.getTempAndHumidity();

  Serial.print("Temperatura: ");
  Serial.print(data.temperature);
  Serial.println(" °C");

  Serial.print("Humedad: ");
  Serial.print(data.humidity);
  Serial.println(" %");

  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(0, 0);
  display.println("Monitoreo Ambiental");

  display.drawLine(0, 12, 128, 12, SSD1306_WHITE);

  display.setTextSize(2);

  display.setCursor(0, 20);
  display.print(data.temperature, 1);
  display.println(" C");

  display.setCursor(0, 45);
  display.print(data.humidity, 1);
  display.println("%");

  display.display();

  delay(2000);
}