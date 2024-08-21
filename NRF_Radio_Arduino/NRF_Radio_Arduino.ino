 //Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


struct Data_Package {
  int32_t throttle = 0;
  int32_t brake = 0;
  float speed     = 0;
  float relative_speed = 0;
  int16_t   distance  = 0;
  int16_t threshold = 0;
  uint8_t CollisionWarnings = 0;
};

uint8_t test = 71;
int adaptive = 40;
Data_Package data; // Create a variable with the above structure
float digital = 0;


RF24 radio(7, 8); // CE, CSN
int x = 0;
//address through which two modules communicate.
const byte addresses[][6] = {"00001", "00002"};
uint8_t TxAddress[] = {0xEE,0xDD,0xCC,0xBB,0xAA};
uint8_t speed = 0;
uint8_t Cruise_Control = 0;
int startTime = 0;
int endTime = 0;
uint8_t collisionWarnings = data.CollisionWarnings;
uint8_t ss = 0;
boolean buttonState = 0;

void setup() {
  Serial.begin(115200);
  pinMode(6,OUTPUT);
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00001
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.startListening();
}

void loop() {
 
  radio.startListening();
  
  if ( radio.available()) {
    while(radio.available()){

      radio.read(&data, sizeof(data));
      collisionWarnings = data.CollisionWarnings;
      collisionWarnings |= (1 << 6);
      collisionWarnings &= ~(1 << 7);
      int rearW = (collisionWarnings >> 2) & 1;
      int rightW = (collisionWarnings >> 1) & 1;
      int leftW = (collisionWarnings >> 0) & 1;
      int forwardW = (collisionWarnings >> 3) & 1;
      ss = int((data.speed)/1000);
      
      ss |= (1 << 7);
      ss &= ~(1 << 6);

      Serial.println(collisionWarnings);
      Serial.println(ss);
    }

  }
  if(Serial.available())
  {
    Cruise_Control = Serial.read();
  }
 
  delay  (5);
  radio.stopListening();
 
  buttonState = !buttonState;
  radio.write(&Cruise_Control, sizeof(Cruise_Control));
  delay(5);
  }
  