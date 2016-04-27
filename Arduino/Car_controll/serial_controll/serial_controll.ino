/*
 * 'x' (120) = Stop
 * 'w' (119) = Turn on motor.
 * 'A'(65) --> 'Z'(90) --> 's'(115) = Max left --> Neutral --> Max right
 * 'z' (122) = Reverse
 */

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
#define BASE_SPEED 1293
#define BOOST_SPEED 1345
#define HOLE_MIN 1
#define HOLE_MAX 2


Servo esc, Sservo;
const int motor = 9;
const int servo = 6;
int delay_sec = 10;

int neutral = 1200; // //value for making car stand still
int high = 2000;  ////value for making car go forward
int low = 800;  //value for making car go backwards
char buffer;

int rotation;
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
  

  Serial.println("listening");

  

}

void loop(){
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


void setWheelAngle(int input){

  input -= LOWER_MESSAGE_ANGLE;
  input *= (UPPER_WHEEL_ANGLE - LOWER_WHEEL_ANGLE);
  input /= (UPPER_MESSAGE_ANGLE - LOWER_MESSAGE_ANGLE);
  input += LOWER_WHEEL_ANGLE;
  Sservo.write(input);
}

void docount(){
  rotation++;
}

void timerIsr(){
  Timer1.detachInterrupt();  //stop the timer
  Serial.print("Motor Speed: ");
  Serial.print(rotation);  
  Serial.println(" Holes per seconds"); 
  rotation=0;  //  reset counter to zero
  Timer1.attachInterrupt( timerIsr );  //enable the timer
}

