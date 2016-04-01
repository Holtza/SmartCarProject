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

//Read values for ultrasonic sensors 1 and 2
int usread1 = 0;
int usread2 = 0;

void loop() {

 Serial.print("Sensor 1: ");
//Instruct sensors to read echoes:
Wire.beginTransmission(us1); //0x70

Wire.write(byte(0x00)); //sets register pointer to the command register
Wire.write(byte(0x51)); //command sensor to measure in cm
Wire.endTransmission(); //stop transmitting

delay(70); //Wait for readings to happen

Wire.beginTransmission(us1); //transmit to device
Wire.write(byte(0x02)); //sets register pointer to echo #1 register (0x02)
Wire.endTransmission(); //stop transmitting

Wire.requestFrom(us1, 2); //request two bytes from us1

//receiver reading from sensor:
if (2 <= Wire.available()) { //if 2 bytes were received
  usread1 = Wire.read(); //receive high byte (overwrites previous reading
  usread1 = usread1 << 8; //shift high byte as lower 8 bits
  usread1 |= Wire.read(); //receive low byte as lower 8 bits
  Serial.println(usread1);
}

Serial.print("Sensor 2: ");
//Instruct sensors to read echoes:
Wire.beginTransmission(us2); //0x72

Wire.write(byte(0x00)); //sets register pointer to the command register
Wire.write(byte(0x51)); //command sensor to measure in cm
Wire.endTransmission(); //stop transmitting

delay(70); //Wait for readings to happen

Wire.beginTransmission(us2); //transmit to device
Wire.write(byte(0x02)); //sets register pointer to echo #1 register (0x02)
Wire.endTransmission(); //stop transmitting

Wire.requestFrom(us2, 2); //request two bytes from us2

//receiver reading from sensor:
if (2 <= Wire.available()) { //if 2 bytes were received
  usread2 = Wire.read(); //receive high byte (overwrites previous reading
  usread2 = usread2 << 8; //shift high byte as lower 8 bits
  usread2 |= Wire.read(); //receive low byte as lower 8 bits
  Serial.println(usread2);
}
//delay(250); //delay for reading output
}
