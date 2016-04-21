/*
 * 'x' (120) = Stop
 * 'w' (119) = Turn on motor.
 * 'A'(65) --> 'Z'(90) --> 's'(115) = Max left --> Neutral --> Max right
 * 'z' (122) = Reverse
 */
 
#include <Servo.h>
#define LOWER_MESSAGE_ANGLE 'A'
#define UPPER_MESSAGE_ANGLE 's'
#define LOWER_WHEEL_ANGLE 60
#define UPPER_WHEEL_ANGLE 120
#define STATIONARYTHRESHOLD  1;

Servo esc, Sservo;
const int motor = 9;
const int servo = 6;
int delay_sec = 10;
int neutral = 1500; // //value for making car stand still
int high = 2000;  ////value for making car go forward
int low = 1000;  //value for making car go backwards
char buffer;

//accelerometer constants 
const int groundpin = 
const int powerpin =
const int xpin=   //x-axis of the accelerometer
const int ypin=  // y-axis
const int zpin=  // z-axis

int movement = 0;
int totalAcceleration = 0;
int x = 0; 
int y = 0;
int z = 0;
boolean stationary;

boolean driving = false;

 
void setup(){
  //interup for safety, triggered when remote controll is turned on
  attachInterrupt(digitalPinToInterrupt(3), manualOverride, FALLING); 
  
  Serial.begin(9600);
  pinMode(motor, OUTPUT);
  // accelerometer
  pinMode(groundpin, OUTPUT);
  pinMode(powerpin, OUTPUT);
  digitalWrite(groundpin, LOW);
  digitalWrite(powerpin, HIGH);
  //end
  esc.attach(motor);
  Sservo.attach(servo); 
  Sservo.write(90);


  esc.writeMicroseconds(neutral);
  int i = 5;
  

  Serial.println("listening");

  

}

void loop(){
  
  if(driving)
    esc.writeMicroseconds(1572);
  if(Serial.available() > 0){  // checks if there's any buffered data
    char last_input = Serial.read();  // if so, fetch it
    Serial.print("user input: " + String(last_input) + " - ");

    if(last_input >= LOWER_MESSAGE_ANGLE && last_input <= UPPER_MESSAGE_ANGLE){
        setWheelAngle(last_input);
    }else{
        Serial.println("Not in Range?");
    }
    
    switch(last_input){  // check what key was pressed (ASCII)
      case 'w': //w
        //forward
        if(buffer != 'w'){
          driving = true;
          Serial.println("Forward?");
        }
        buffer = 'w';
        break;
        
      case 'z': //z
        //back
        if(buffer != 'z'){
          esc.writeMicroseconds(1250);
        }
        buffer = 'z';
        break;
        
      case 'x': //x
        if(buffer != 'x'){
          driving = false;
          esc.writeMicroseconds(1500);
        }
        buffer = 'x';
        break;       
        
      default:
        Serial.println("unknown input?");
    }
  }
  // read accelerometer data
  // print the sensor values:
  Serial.print(analogRead(xpin));
  Serial.print("\t");
  Serial.print(analogRead(ypin));
  Serial.print("\t");
  Serial.print(analogRead(zpin));
  Serial.println();
  delay(100);
  // read the acceleration on each axis as analog voltage and converts into meter
  x = voltageToCm(analogRead(xpin);
  y = voltageToCm(analogRead(ypin));
  z = voltageToCm(analogRead(zpin));
  movement = x + y + z;
  totalAcceleration = movement * movement;
  
   
  if(totalAcceleration > STATIONARYTHRESHOLD*STATIONARYTHRESHOLD){
     stationary = true;
  }else {
     stationary = false;
  }
  

}

/*
 * Takes the voltage respresenation read from an analog port, transforms it into
 * voltages, and calculates and returns the value in meter
 */
int voltageToCm(int voltrep){
  float voltage = voltrep * (5.0 / 1023.0);
  float value = 12.5 / voltage;
  int i = (int) value;
  if (value > 45) return 100 / 100;
  return i / 100;
}



void manualOverride(){  //function that runs when the remote controll is turned on
  esc.writeMicroseconds(neutral);
  Serial.println("INTERUPTED");
}

void setWheelAngle(int input){


  
  Serial.print("degs:");
  Serial.println((int)input);
  input -= LOWER_MESSAGE_ANGLE;
  Serial.print("degs:");
  Serial.println((int)input);
  input *= (UPPER_WHEEL_ANGLE - LOWER_WHEEL_ANGLE);
  Serial.print("degs:");
  Serial.println((int)input);
  input /= (UPPER_MESSAGE_ANGLE - LOWER_MESSAGE_ANGLE);
  Serial.print("degs:");
  Serial.println((int)input);
  input += LOWER_WHEEL_ANGLE;
  Sservo.write(input);
  
  Serial.print("degs:");
  Serial.println((int)input);
}


