#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_AM2320.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_AM2320 am2320 = Adafruit_AM2320();

void setup() {
  Serial.begin(115200);
  delay(2000);

  Wire.begin(21, 22);

  // OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Error OLED");
    while(true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  Serial.println("Iniciando sensor...");
  am2320.begin();
}

void loop() {
  float temp = am2320.readTemperature();
  float hum = am2320.readHumidity();

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" °C  Hum: ");
  Serial.println(hum);

  display.clearDisplay();

  display.setCursor(0, 10);
  display.setTextSize(2);
  display.print("Temp:");
  display.setCursor(0, 30);
  display.print(temp);
  display.print(" C");

  display.setTextSize(1);
  display.setCursor(0, 55);
  display.print("Hum: ");
  display.print(hum);
  display.print(" %");

  display.display();

  delay(2000);
}