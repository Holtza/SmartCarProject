/*
 * Sketch to read the distance sensors
 * Returns a netstring into the following format CSV
 * "[length], [US1_value], [US2_value], [IR1_value], [IR2_value], [IR3_value]"
 * 
 * Author: Kai Salmon
 * 
 * Sources used:
 * https://www.arduino.cc/en/Tutorial/SFRRangerReader
 * https://www.arduino.cc/en/Reference/Wire
 * https://www.arduino.cc/en/Tutorial/ReadAnalogVoltage
 */

#include <Wire.h>
#include <Servo.h>

#define RADIO_MOTOR_PIN 11  //Pin which recieves the radio singnals to 
                          //control the Motor
#define RADIO_SERVO_PIN 10  //Pin which recieves the radio signals to 
                          //control the Servo
#define MOTOR_PIN 9  //Pin which connects to the car's motor
#define SERVO_PIN 6 //Pin which connects to the car's servo
#define SPEED_COF 0.20 //Coefficient to control max speed
#define REVERSE_COF 0.65 //Coefficient to control max speed, whilst reversing
#define SPEED_BASELINE 1500 //Neutral value for the speed radio input 

#define DEFAULT_SERVO_POSITION 1500 //The pulserate for wheels pointing forward
#define DEFAULT_SERVO_SNAP_DIST 70  //The distance which the car will "Snap" to the default 
                                    //wheel forward position
#define ANGLE_COF 0.065 //Coefficient to control max turning angles 

#define IR1 A0 //IR pin
#define IR2 A1 //IR pin
#define IR3 A2 //IR pin
#define US1 112 //Ultrasonic addresses
#define US2 114 //Ultrasonic addresses

/*
  precalculate upper and lower bounds for turning
*/
int upper_bound = DEFAULT_SERVO_POSITION + DEFAULT_SERVO_SNAP_DIST;
int lower_bound = DEFAULT_SERVO_POSITION - DEFAULT_SERVO_SNAP_DIST;

/*
  Servo objects to control the motor and servo of the car
*/
Servo motor, servo;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(SERVO_PIN, OUTPUT);
  pinMode(RADIO_MOTOR_PIN, INPUT);
  pinMode(RADIO_SERVO_PIN, INPUT);
  motor.attach(MOTOR_PIN);
  servo.attach(SERVO_PIN);
  servo.write(90);
}

void loop() {
  Serial.print(millis());
  String netstring = readSensors();
  Serial.println(netstring);
  motor.writeMicroseconds(getRequestedSpeed());
  servo.write(getRequestedRotation()); 
}

/*
 * Reads the sensors and returns a netstring, using helper functions.
 */
String readSensors(){
  int sonar1 = readUSSensor(US1);  //Read ultrasonic sensors
  int sonar2 = readUSSensor(US2);
  int inred1 = voltageToCm(analogRead(IR1));  //Read IR sensors
  int inred2 = voltageToCm(analogRead(IR2));
  int inred3 = voltageToCm(analogRead(IR3));
  
  String valueString = setString(sonar1, sonar2, inred1, inred2, inred3); //Create string containing the sensor values as ints
  String encodedString = encodeNetstring(valueString); //Create netstring and return it
  
  return encodedString;
}

/*
 * Function which uses the Wire library to read from an ultrasonic sensor,
 * given the address of that sensor.
 */
int readUSSensor(int address){
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
  if(2 <= Wire.available()){ //if 2 bytes were received
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

  String valueS = s1 + "," + s2 + "," + s3 + "," + s4 + "," + s5;
  return valueS;
}

/*
 * Takes a string as an argument and encodes it as a netstring
 */
String encodeNetstring(String string){
  int len = string.length();
  if (len <= 0){
    return "empty";
  }
  return String(",") + len + String("," + string);
}

/*
 * Takes the voltage respresenation read from an analog port, transforms it into
 * voltages, and calculates and returns the distance in cm
 */
int voltageToCm(int voltrep){
  float voltage = voltrep * (5.0 / 1023.0);
  float value = 12.5 / voltage;
  int i = (int) value;
  if (value > 45) return -1;
  return i;
}

int getRequestedSpeed(){
  int pulse = pulseIn(RADIO_MOTOR_PIN, HIGH); //Read pulse rate
  float scale = pulse > SPEED_BASELINE ? SPEED_COF : REVERSE_COF;
  /*
    Scale pulse by relivant speed Coefficient, with SPEED_BASELINE as the origin
  */
  int s = pulse - SPEED_BASELINE; 
  s *= scale; 
  s += SPEED_BASELINE; 
  return s;
}

int getRequestedRotation(){
  int pulse = pulseIn(RADIO_SERVO_PIN, HIGH);
  if(pulse >= lower_bound && pulse <= upper_bound){ //Snap to 90deg position
    return 90;
  }
  int requestedRotation = 90 + (pulse - DEFAULT_SERVO_POSITION) * ANGLE_COF;
  return requestedRotation;
}
