#include <SPI.h>
#include <LoRa.h>
#include <DHT.h>

#define DHTPIN 3     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value
int counter = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  delay(10000);
  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  LoRa.setTxPower(20);
  
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  //Read data and store it to variables hum and temp
  hum = dht.readHumidity();
  temp= dht.readTemperature();

  // send packet
  LoRa.beginPacket();
  LoRa.print("Humidity: ");
  LoRa.print(hum);
  LoRa.print(" %, Temp: ");
  LoRa.print(temp);
  LoRa.print(" Celsius");
  LoRa.endPacket();

  counter++;
  delay(10000);
}
