/*
 * 'x' (120) = Stop
 * 'w' (119) = Turn on motor.
 * 'A'(65) --> 'Z'(90) --> 's'(115) = Max left --> Neutral --> Max right
 * 'z' (122) = Reverse
 */

#include <Wire.h>
#include <TimerOne.h>
#include <Servo.h>
#define LOWER_MESSAGE_ANGLE 'A'
#define UPPER_MESSAGE_ANGLE 's'
#define LOWER_WHEEL_ANGLE 60
#define UPPER_WHEEL_ANGLE 120
#define STATIONARYTHRESHOLD 1
#define XPIN A3
#define YPIN A4
#define WHEEL_A 5
#define WHEEL_B 3
#define BASE_SPEED 1296
#define BOOST_SPEED 1349
#define HOLE_MIN 1
#define HOLE_MAX 2

#define IR1 A0 //IR pin
#define IR2 A1 //IR pin
#define IR3 A2 //IR pin
int US1 = 112; //Ultrasonic addresses
int US2 = 114; //Ultrasonic addresses


Servo esc, Sservo;
const int motor = 9;
const int servo = 6;
int delay_sec = 10;

int neutral = 1200; // //value for making car stand still
int high = 2000;  ////value for making car go forward
int low = 800;  //value for making car go backwards
char buffer;

int lastReset = 0;
int rotation;
int clicks;
unsigned long updateSinceChange;
int encoder;
int compare;
boolean stationary = true;
boolean driving = false;
 
void setup(){

  Timer1.initialize(250000); // set timer for 1sec
  attachInterrupt(digitalPinToInterrupt(WHEEL_B), docount, RISING);  // increase counter when speed sensor pin goes High
  Timer1.attachInterrupt( timerIsr ); // enable the timer
  
  Serial.begin(9600);
  //Serial1.begin(57600);
  pinMode(motor, OUTPUT);
  pinMode(WHEEL_A, INPUT);
  pinMode(WHEEL_B, INPUT);
  pinMode(41, OUTPUT);
  updateSinceChange = 0;
  
  //end
  esc.attach(motor);
  Sservo.attach(servo); 
  Sservo.write(90);
  encoder = digitalRead(WHEEL_A);

  esc.writeMicroseconds(neutral);
  int i = 5;
  
  Wire.begin();
 // Serial.println("listening");

  

}

void loop(){
  
  if(lastReset < 5000){
  if(stationary)digitalWrite(41, HIGH);
  else digitalWrite(41, LOW);
  compare = digitalRead(WHEEL_A);
  if(updateSinceChange >= 70){
     stationary = true;
  }
  if(encoder != compare){
    stationary = false;
    updateSinceChange = 0;
    encoder = compare;
  }
  if(driving){
    if(rotation<HOLE_MIN)esc.writeMicroseconds(BOOST_SPEED);
    else if(rotation<HOLE_MAX)esc.writeMicroseconds(BASE_SPEED);
    else esc.writeMicroseconds(neutral);
  }else{
     esc.writeMicroseconds(neutral);
  }
  //Serial.println(stationary);  
  //Serial.println(driving);         
  if(Serial.available() > 0){  // checks if there's any buffered data
    char last_input = Serial.read();  // if so, fetch it
    //Serial.print("user input: " + String(last_input) + " - ");

    if(last_input >= LOWER_MESSAGE_ANGLE && last_input <= UPPER_MESSAGE_ANGLE){
        setWheelAngle(last_input);
    }
    
    switch(last_input){  // check what key was pressed (ASCII)
      case 'w': //w
        //forward
          driving = true;
          Serial.println("Forward?");
        break;
        
      case 'z': //z
        //back
        esc.writeMicroseconds(1100);
        break;
        
      case 'x': //x
        driving = false;
        esc.writeMicroseconds(1200);
        break;       
        
      default:
        Serial.println("unknown input?");
    }
  
  }
  // read accelerometer data
  // print the sensor values:
  //Serial.println(Serial1.read());

  updateSinceChange++;

  }
/*
  // read the acceleration on each axis as analog voltage and converts into meter
  float x = voltageToCm(analogRead(XPIN));
  float y = voltageToCm(analogRead(YPIN));
  float movement = x*x + y*y;
  Serial.print(movement);
  Serial.println();
  delay(100);
  if(movement > STATIONARYTHRESHOLD*STATIONARYTHRESHOLD){
     stationary = true;
  }else {
     stationary = false;
  }
*/
  if(lastReset >= 5000){  
    String netstring = readSensors();
    Serial.println(netstring);
    lastReset = 0;
  }
  lastReset++;
  
}

void setWheelAngle(int input){

  switch(input){
    case '@':
      Sservo.write(40);
      break;
    case 'v':
      Sservo.write(140);
      break;
    case 's':
      Sservo.write(115);
      break;
    case 'A':
      Sservo.write(65);
      break;
    case 'Z':
      Sservo.write(90);
      break;
    case 'c':
      Sservo.write(98);
      break;
    case 'f':
      Sservo.write(109);
      break;
    case 'R':
      Sservo.write(82);
      break;
    case 'L':
      Sservo.write(71);
      break;
    default:
      Serial.println("passed no known angles");    
  }
//  input -= LOWER_MESSAGE_ANGLE;
//  input *= (UPPER_WHEEL_ANGLE - LOWER_WHEEL_ANGLE);
//  input /= (UPPER_MESSAGE_ANGLE - LOWER_MESSAGE_ANGLE);
//  input += LOWER_WHEEL_ANGLE;
//  Sservo.write(input);
}

void docount(){
  rotation++;
  clicks++;
}

void timerIsr(){
  Timer1.detachInterrupt();  //stop the timer
 // Serial.print("Motor Speed: ");
 // Serial.print(rotation);  
 // Serial.println(" Holes per seconds"); 
  rotation=0;  //  reset counter to zero
  Timer1.attachInterrupt( timerIsr );  //enable the timer
}

/*
 * Reads the sensors and returns a netstring, using helper functions.
 */
String readSensors(){
  int sonar1 = ReadUSSensor(US1); //Read ultrasonic sensors
  int sonar2 = ReadUSSensor(US2);
  int inred1 = voltageToCm(analogRead(IR1));  //Read IR sensors
  int inred2 = voltageToCm(analogRead(IR2));
  int inred3 = voltageToCm(analogRead(IR3));
  String valueString = setString(sonar1, sonar2, inred1, inred2, inred3); //Create string containing the sensor values as ints
  //String encodedString = encodeNetstring(valueString); //Create netstring and return it
  return valueString;
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
  String s1 = intToString(i_1);
  String s2 = intToString(i_2);
  String s3 = intToString(i_3);
  String s4 = intToString(i_4);
  String s5 = intToString(i_5);
  if (clicks > 99999) clicks = 0; //After ~300m 
  String s6 = clicksToString(clicks); //return wheel encoder data

  String valueS = "<" + s1 + s2 + s3 + s4 + s5 + s6 +">";

  return valueS;
}

String intToString(int i_1){
  if(i_1<-1)i_1 *= -1;
  if(i_1==-1)return "-01";
  else if(i_1<100 && i_1>=10){
    return "0" + String(i_1);
  }else if(i_1<10){
    return "00" + String(i_1);
  }else{
    return String(i_1);
  }
}

String clicksToString(int i){
  if(i<10) return "0000" + String(i);
  else if(i<100 && i>=10) return "000" + String(i);
  else if(i<1000 && i>=100) return "00" + String(i);
  else if(i<10000 && i>=1000) return "0" + String(i);
  else return String(i);
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


