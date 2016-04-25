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
#define STATIONARYTHRESHOLD 1
#define XPIN A3
#define YPIN A4
#define WHEEL_A 5
#define WHEEL_B 3
#define BASE_SPEED 1566
#define BOOST_SPEED 1600

Servo esc, Sservo;
const int motor = 9;
const int servo = 6;
int delay_sec = 10;

int neutral = 1500; // //value for making car stand still
int high = 2000;  ////value for making car go forward
int low = 1000;  //value for making car go backwards
char buffer;

unsigned long updateSinceChange;
int encoder;
int compare;
boolean stationary = true;
boolean driving = false;
 
void setup(){
  //interup for safety, triggered when remote controll is turned on
  attachInterrupt(digitalPinToInterrupt(3), manualOverride, FALLING); 
  
  Serial.begin(9600);
  //Serial1.begin(57600);
  pinMode(motor, OUTPUT);
  pinMode(WHEEL_A, INPUT);
  pinMode(WHEEL_B, INPUT);
  updateSinceChange = 0;
  
  //end
  esc.attach(motor);
  Sservo.attach(servo); 
  Sservo.write(90);
  encoder = digitalRead(WHEEL_A);

  esc.writeMicroseconds(neutral);
  int i = 5;
  

  Serial.println("listening");

  

}

void loop(){
  compare = digitalRead(WHEEL_A);
  if(updateSinceChange >= 100){
     stationary = true;
  }
  if(encoder != compare){
    stationary = false;
    updateSinceChange = 0;
    encoder = compare;
  }
  if(driving){
    if(stationary)esc.writeMicroseconds(BOOST_SPEED);
    else esc.writeMicroseconds(BASE_SPEED);
  }else{
     esc.writeMicroseconds(neutral);
  }
  //Serial.println(stationary);  
           
  if(Serial.available() > 0){  // checks if there's any buffered data
    char last_input = Serial.read();  // if so, fetch it
    Serial.print("user input: " + String(last_input) + " - ");

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
        esc.writeMicroseconds(1250);
        break;
        
      case 'x': //x
        driving = false;
        esc.writeMicroseconds(1500);
        break;       
        
      default:
        Serial.println("unknown input?");
    }
  }
  // read accelerometer data
  // print the sensor values:
  //Serial.println(Serial1.read());

  updateSinceChange++;

  // read the acceleration on each axis as analog voltage and converts into meter
  /*float x = voltageToCm(analogRead(XPIN));
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
  

}

/*
 * Takes the voltage respresenation read from an analog port, transforms it into
 * voltages, and calculates and returns the value in meter
 */
float voltageToCm(int voltrep){
  float voltage = voltrep * (5.0 / 1023.0);
  float value = 12.5 / voltage;
  return value;
}



void manualOverride(){  //function that runs when the remote controll is turned on
 
}

void setWheelAngle(int input){

  input -= LOWER_MESSAGE_ANGLE;
  input *= (UPPER_WHEEL_ANGLE - LOWER_WHEEL_ANGLE);
  input /= (UPPER_MESSAGE_ANGLE - LOWER_MESSAGE_ANGLE);
  input += LOWER_WHEEL_ANGLE;
  Sservo.write(input);
}


