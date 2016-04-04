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

  //Serial.print("US 1: ");
  int sonar1 = ReadSonarSensor(us1);
  //Serial.println(sonar1);

  //Serial.print("US 2: ");
  int sonar2 = ReadSonarSensor(us2);
  //Serial.println(sonar2);

  //Serial.print("IR 1: ");
  int inred1 = analogRead(IR1);
  //Serial.println(inred1);

  //Serial.print("IR 2: ");
  int inred2 = analogRead(IR2);
  //Serial.println(inred2);

  //Serial.print("IR 3: ");
  int inred3 = analogRead(IR3);
  //Serial.println(inred3);

  String valueString = setString(sonar1, sonar2, inred1, inred2, inred3);
  //Serial.println(valueString);

  String encodedString = encodeNetstring(valueString);
  Serial.println(encodedString);

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

//Method for turning int values into a string
String setString(int i_1, int i_2, int i_3, int i_4, int i_5){
 String s1 = String(i_1);
 String s2 = String(i_2);
 String s3 = String(i_3);
 String s4 = String(i_4);
 String s5 = String(i_5);

 String valueS = s1 + " " + s2 + " " + s3 + " " + s4 + " " + s5;

 return valueS;
}

String encodeNetstring(String string){
  int len = string.length();
  if (len <= 0) return "empty";
  return len + String(":" + string + ",");
}
  
 
