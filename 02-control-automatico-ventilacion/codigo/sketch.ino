#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHTesp.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define DHT_PIN 15
#define FAN_PIN 18

#define TEMP_THRESHOLD 30.0

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
  );

DHTesp dhtSensor;

void setup() {

  Serial.begin(115200);

  pinMode(FAN_PIN, OUTPUT);

  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  Wire.begin(21, 22);

  if (!display.begin(
      SSD1306_SWITCHCAPVCC,
      0x3C)) {

    Serial.println("OLED no encontrada");

    while (true);
  }

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(10, 20);
  display.println("OLED OK");

  display.display();

  delay(2000);
}

void loop() {

  TempAndHumidity data =
    dhtSensor.getTempAndHumidity();

  float temperatura =
    data.temperature;

  bool ventilador =
    temperatura > TEMP_THRESHOLD;

  digitalWrite(
    FAN_PIN,
    ventilador ? HIGH : LOW);

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(0, 0);
  display.println("Control Ventilacion");

  display.drawLine(
    0, 12, 128, 12,
    SSD1306_WHITE);

  display.setTextSize(2);

  display.setCursor(0, 18);
  display.print(temperatura, 1);
  display.print("C");

  display.setTextSize(1);

  display.setCursor(0, 45);

  if (ventilador) {

    display.println("Estado: ALARMA");
    display.println("Ventilacion ON");

  } else {

    display.println("Estado: NORMAL");
    display.println("Ventilacion OFF");

  }

  display.display();

  delay(2000);
}