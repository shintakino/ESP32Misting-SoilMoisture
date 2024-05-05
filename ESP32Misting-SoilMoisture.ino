#include <DHT.h>
#include <BluetoothSerial.h>
#include <U8g2lib.h>
#include <EEPROM.h> // Include EEPROM library

#define DHTPIN 33
#define DHTTYPE DHT11
#define btn_Select 25
#define btn_Up 26
#define btn_Down 27
#define btn_Back 14 // Define new back button pin
#define RELAY_MIST 19
#define RELAY_WATER 18
#define SENSOR_VP 36
#define SENSOR_VN 39
#define SENSOR_IO34 34
#define SOIL_MOISTURE_THRESHOLD 1500
#define temp_THRESHOLD 37

int moisture_vp;
int moisture_vn;
int moisture_IO34;

DHT dht(DHTPIN, DHTTYPE);
BluetoothSerial SerialBT;
U8G2_SH1106_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

float tempThreshold;
int moistureThreshold;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT");
  pinMode(RELAY_MIST, OUTPUT);
  pinMode(RELAY_WATER, OUTPUT);
  digitalWrite(RELAY_MIST, HIGH);
  digitalWrite(RELAY_WATER, HIGH);
  pinMode(SENSOR_VP, INPUT);
  pinMode(SENSOR_VN, INPUT);
  pinMode(SENSOR_IO34, INPUT);
  dht.begin();
  pinMode(btn_Select, INPUT_PULLUP);
  pinMode(btn_Down, INPUT_PULLUP);
  pinMode(btn_Up, INPUT_PULLUP);
  pinMode(btn_Back, INPUT_PULLUP); // Set back button pin mode

  // Initialize OLED display
  u8g2.begin();

  // Read settings from EEPROM
  readSettings();
}

void loop() {
  waterSensor();
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  float VPD = calculateVPD(temperature, humidity);

  // Display main menu
  displayMainMenu();

  // Handle button actions
  handleButtons();

  // Display sensor readings
  displaySensorReadings(temperature, humidity, VPD);

  // Control misting and watering
  controlMisting(temperature);
  controlWatering();

  delay(1000);
}

void displayMainMenu() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 10, "1. Dashboard");
  u8g2.drawStr(0, 20, "2. Set Temp Threshold");
  u8g2.drawStr(0, 30, "3. Set Moisture Threshold");
  u8g2.sendBuffer();
}

void handleButtons() {
  static int menuState = 0;

  if (digitalRead(btn_Select) == LOW) {
    switch (menuState) {
      case 0: break; // Dashboard
      case 1: tempThreshold++; break; // Set Temp Threshold
      case 2: moistureThreshold += 100; break; // Set Moisture Threshold
    }
    delay(300);
  }

  if (digitalRead(btn_Up) == LOW) {
    menuState = (menuState - 1 + 3) % 3;
    delay(300);
  }

  if (digitalRead(btn_Down) == LOW) {
    menuState = (menuState + 1) % 3;
    delay(300);
  }

  if (digitalRead(btn_Back) == LOW) { // If back button pressed
    menuState = 0; // Go back to Dashboard
    writeSettings(); // Save settings to EEPROM
    delay(300);
  }
}

void displaySensorReadings(float temperature, float humidity, float VPD) {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setCursor(0, 10);
  u8g2.print("Temperature: ");
  u8g2.print(temperature);
  u8g2.println(" °C");
  u8g2.print("Humidity: ");
  u8g2.print(humidity);
  u8g2.println("%");
  u8g2.print("VPD: ");
  u8g2.print(VPD);
  u8g2.println(" kPa");
  u8g2.sendBuffer();
}

float calculateVPD(float temperature, float humidity) {
  float es = 0.611 * exp((17.27 * temperature) / (temperature + 237.3));
  float e = (humidity / 100) * es;
  float vpd = (1 - (e / es)) * es;
  return vpd;
}

void waterSensor() {
  moisture_vp = analogRead(SENSOR_VP);
  moisture_vn = analogRead(SENSOR_VN);
  moisture_IO34 = analogRead(SENSOR_IO34);
  delay(5000);
}

void controlMisting(float temperature) {
  if (temperature > tempThreshold) {
    digitalWrite(RELAY_MIST, LOW);
  } else {
    digitalWrite(RELAY_MIST, HIGH);
  }
}

void controlWatering() {
  if (moisture_IO34 <= moistureThreshold) {
    digitalWrite(RELAY_WATER, LOW);
  } else {
    digitalWrite(RELAY_WATER, HIGH);
  }
}

void readSettings() {
  EEPROM.get(0, tempThreshold);
  EEPROM.get(sizeof(float), moistureThreshold);
}

void writeSettings() {
  EEPROM.put(0, tempThreshold);
  EEPROM.put(sizeof(float), moistureThreshold);
}
