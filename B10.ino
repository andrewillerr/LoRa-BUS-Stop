/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/ttgo-lora32-sx1276-arduino-ide/
*********/

//Libraries for LoRa
#include <SPI.h>
#include <LoRa.h>

//Libraries for OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//define the pins used by the LoRa transceiver module
#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISnO
#define MOSI    27   // GPIO27 -- SX1278's MOSI
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     23   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND  915E6

//Test 7
//433E6 for Asia
//866E6 for Europe
//915E6 for North America
// #define BAND 866E6
       
//OLED pins
#define OLED_SDA 21
#define OLED_SCL 22 
#define OLED_RST 16
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);
unsigned int counter = 0;
String LoRaData;

void setup() { 
  //initialize Serial Monitor
  Serial.begin(9600);
  
  //reset OLED display via software
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);
  
  //initialize OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("B.10 ");
  display.display();

  Serial.println("LoRa Receiver Test");
  
  //SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);
  //setup LoRa transceiver module
  LoRa.setPins(SS, RST, DI0);

  if (!LoRa.begin(BAND)) {
    Serial.println("Starting failed!");
    while (1);
  }
  //Serial.println("waiting!");
  Serial.println("waiting!");
  display.setCursor(0,10);
  display.println("B.10...waiting!");
  display.display();  
}

void loop() {

  //try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    //received a packet
    Serial.print("Received packet ");

    //read packet
    while (LoRa.available()) {
      LoRaData = LoRa.readString();
      Serial.print(LoRaData);
    }

    //print RSSI of packet
    int rssi = LoRa.packetRssi();
    Serial.print(" with RSSI ");    
    Serial.println(rssi);

   // Display information
   display.clearDisplay();
   //display.setTextSize(0.8);
   display.setCursor(0,0);
   display.print("Building 10");
   display.setCursor(0,10);
   display.print("=====================");
   display.setCursor(0,20);
   display.print("People: ");
   display.print("10");
   display.setCursor(0,27.5);
   display.print("---------------------");
   display.setCursor(0,35);
   display.print("BUS1 coming: ");
   display.print("2 min.");
   //display.print(LoRaData);
   display.setCursor(0,45);
   display.print("BUS2 coming: ");
   display.print("10 min.");
   //display.print(LoRaData);
   display.setCursor(0,55);
   display.print("BUS3 coming: ");
   display.print("15 min.");
   //display.print(LoRaData);
   display.setCursor(0,70);
   //display.print("RSSI:");
   display.setCursor(30,70);
   //display.print(rssi);
   display.display();   
  }
}