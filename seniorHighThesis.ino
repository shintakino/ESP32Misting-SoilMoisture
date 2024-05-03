#include <DHT.h>
#include <BluetoothSerial.h> // Include BluetoothSerial library

#define DHTPIN 33    // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

#define RELAY_MIST 19   // Pin to control misting relay
#define RELAY_WATER 18  // Pin to control water irrigation relay

#define SENSOR_VP 36    // Pin for soil moisture sensor VP
#define SENSOR_VN 39    // Pin for soil moisture sensor VN
#define SENSOR_IO34 34  // Pin for soil moisture sensor IO34
#define SOIL_MOISTURE_THRESHOLD 1500  
#define VPD_THRESHOLD 1.0 // Adjust threshold as per requirement
int moisture_vp;
int moisture_vn;
int moisture_IO34;

DHT dht(DHTPIN, DHTTYPE);
BluetoothSerial SerialBT; // Define BluetoothSerial object

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
}

void loop() {
  waterSensor();
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  SerialBT.println(moisture_IO34);
  // // Check if any reading failed
  // if (isnan(humidity) || isnan(temperature)) {
  //   Serial.println("Failed to read from DHT sensor!");
  //   SerialBT.println("Failed to read from DHT sensor!"); 
  //   return;
  // }

  float VPD = calculateVPD(temperature, humidity);

  if (VPD > VPD_THRESHOLD) {
    digitalWrite(RELAY_MIST, LOW);
    Serial.println("Misting On");
    SerialBT.println("Misting On");
  } else {
    digitalWrite(RELAY_MIST, HIGH);
    Serial.println("Misting OFF");
    SerialBT.println("Misting OFF");
  }

  // Check soil moisture sensors

  if  (moisture_IO34 <= SOIL_MOISTURE_THRESHOLD) {
    digitalWrite(RELAY_WATER, LOW);
    Serial.println("WaterPump On");
    SerialBT.println("WaterPump On");
  } else{
    digitalWrite(RELAY_WATER, HIGH);
    Serial.println("WaterPump OFF");
    SerialBT.println("WaterPump OFF");
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.print("%, VPD: ");
  Serial.println(VPD);

  SerialBT.print("Temperature: ");
  SerialBT.print(temperature);
  SerialBT.print(" °C, Humidity: ");
  SerialBT.print(humidity);
  SerialBT.print("%, VPD: ");
  SerialBT.println(VPD);

}

float calculateVPD(float temperature, float humidity) {
    float es = 0.611 * exp((17.27 * temperature) / (temperature + 237.3));
    float e = (humidity / 100) * es;
    float vpd = (1 - (e / es)) * es;
    return vpd;
}

void waterSensor(){
  moisture_vp = analogRead(SENSOR_VP);
  moisture_vn = analogRead(SENSOR_VN);
  moisture_IO34 = analogRead(SENSOR_IO34);
  delay(5000);
}

