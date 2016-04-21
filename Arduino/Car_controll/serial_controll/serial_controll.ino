#include <Servo.h>

#define STATIONARYTHRESHOLD  1;

Servo esc, Sservo;
const int motor = 9;
const int servo = 6;
int delay_sec = 10;
int neutral = 1500; // //value for making car stand still
int high = 2000;  ////value for making car go forward
int low = 1000;  //value for making car go backwards

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
  while(i > 0){
    Serial.println(String(i));
    i--;
    delay(1000);
  }

  Serial.println("listening");

  

}

void loop(){
  

  if(Serial.available() > 0){  // checks if there's any buffered data
    char last_input = Serial.read();  // if so, fetch it
    Serial.print("user input: " + String(last_input) + " - ");

    switch(last_input){  // check what key was pressed (ASCII)
      case 'w':
        //forward
        esc.writeMicroseconds(1570);
        Serial.println("Forward?");
        break;
        
      case 'z':
        //back
        esc.writeMicroseconds(1250);
        break;
        
      case 'x':
        esc.writeMicroseconds(neutral);
        break;
        
      case 'a':
        //left
        Sservo.write(60);
        Serial.println("left?");
        break;
        
      case 'd':
        //right
        Sservo.write(120);
        Serial.println("right?");
        break;

      case 's':
        //straight
        Sservo.write(90);
        Serial.println("Straight?");
        break;
        
      default:
        Serial.println("unknown input");
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
  // read the acceleration on each axis as analog voltage
  x = analogRead(xpin);
  y = analogRead(ypin);
  z = analogRead(zpin);
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
 * voltages, and calculates and returns the distance in cm
 */
float VoltageToCm(int voltrep){
  float voltage = voltrep * (5.0 / 1023.0);
  float value = 12.5 / voltage;
 // int i = (int) value;
  if (value > 45.0) return 100.0;
  return i;
}

// converts centimeter into meter
float CmToMeter(float cm){
     return float meter = cm / 100.0;
}



void manualOverride(){  //function that runs when the remote controll is turned on
  esc.writeMicroseconds(neutral);
  Serial.println("INTERUPTED");
}

