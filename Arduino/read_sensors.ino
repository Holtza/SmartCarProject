/*
 * Sources used:
 * https://www.arduino.cc/en/Tutorial/SFRRangerReader
 * https://www.arduino.cc/en/Reference/Wire
 */

#include <Wire.h>

//adresses
int us1 = 112;
int us2 = 114;

//IR pins
#define IR1 A0
#define IR2 A1
#define IR3 A2

void setup() {
  Wire.begin();
  Serial.begin(9600);

}



void loop() {

  Serial.print("US 1: ");
  int sonar1 = ReadSonarSensor(us1);
  Serial.println(sonar1);

  Serial.print("US 2: ");
  int sonar2 = ReadSonarSensor(us2);
  Serial.println(sonar2);

  Serial.print("IR 1: ");
  int inred1 = analogRead(IR1);
  Serial.println(inred1);

  Serial.print("IR 2: ");
  int inred2 = analogRead(IR2);
  Serial.println(inred2);

  Serial.print("IR 3: ");
  int inred3 = analogRead(IR3);
  Serial.println(inred3);

}



int ReadSonarSensor(int address){
  
  int readValue = 0;
  
  Wire.beginTransmission(address);
  Wire.write(byte(0x00)); //sets register pointer to the command register
  Wire.write(byte(0x51)); //command sensor to measure in cm
  Wire.endTransmission(); //stop transmitting

  delay(70); //Wait for readings to happen

  Wire.beginTransmission(address); //transmit to device
  Wire.write(byte(0x02)); //sets register pointer to echo #1 register (0x02)
  Wire.endTransmission(); //stop transmitting

  Wire.requestFrom(address, 2); //request two bytes from us1

  //receiver reading from sensor:
  if (2 <= Wire.available()) { //if 2 bytes were received
    readValue = Wire.read(); //receive high byte (overwrites previous reading
    readValue = readValue << 8; //shift high byte as lower 8 bits
    readValue |= Wire.read(); //receive low byte as lower 8 bits
  }
  
  return readValue;
  
}
  
 
