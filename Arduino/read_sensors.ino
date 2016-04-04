/*
 * Sketch to read the distance sensors
 * Returns a netstring into the following format:
 * "[length]:[US1_value] [US2_value] [IR1_value] [IR2_value] [IR3_value],"
 * 
 * Author: Martina Freiholtz
 * 
 * Sources used:
 * https://www.arduino.cc/en/Tutorial/SFRRangerReader
 * https://www.arduino.cc/en/Reference/Wire
 * https://www.arduino.cc/en/Tutorial/ReadAnalogVoltage
 */


#include <Wire.h>

//Ultrasonic addresses
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
  int sonar1 = ReadUSSensor(us1);  //Read ultrasonic sensors
  //Serial.println(sonar1);

  //Serial.print("US 2: ");
  int sonar2 = ReadUSSensor(us2);
  //Serial.println(sonar2);
  


  //Serial.print("IR 1: ");
  int inred1 = VoltageToCm(analogRead(IR1));  //Read IR sensors
  //Serial.println(inred1);

  //Serial.print("IR 2: ");
  int inred2 = VoltageToCm(analogRead(IR2));
  //Serial.println(inred2);

  //Serial.print("IR 3: ");
  int inred3 = VoltageToCm(analogRead(IR3));
  //Serial.println(inred3);

  String valueString = setString(sonar1, sonar2, inred1, inred2, inred3); //Create string containing the sensor values as ints
  //Serial.println(valueString);

  String encodedString = encodeNetstring(valueString); //Create netstring and print it to the Serial
  Serial.println(encodedString);

}


/*
 * Function which uses the Wire library to read from an ultrasonic sensor,
 * given the address of that sensor.
 */
int ReadUSSensor(int address){
  
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
  
  return readValue; //Return the value
  
}

/*
 * Takes 5 integer values and separate them with spaces in a string
 */
String setString(int i_1, int i_2, int i_3, int i_4, int i_5){
 String s1 = String(i_1);
 String s2 = String(i_2);
 String s3 = String(i_3);
 String s4 = String(i_4);
 String s5 = String(i_5);

 String valueS = s1 + " " + s2 + " " + s3 + " " + s4 + " " + s5;

 return valueS;
}

/*
 * Takes a string as an argument and encodes it as a netstring
 */
String encodeNetstring(String string){
  int len = string.length();
  if (len <= 0) return "empty";
  return len + String(":" + string + ",");
}

/*
 * Takes the voltage respresenation read from an analog port, transforms it into
 * voltages, and calculates and returns the distance in cm
 */
int VoltageToCm(int voltrep){
  float voltage = voltrep * (5.0 / 1023.0);
  float value = 12.5 / voltage;
  int i = (int) value;
  return i;
}
  
 
