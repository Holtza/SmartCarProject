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

/*
  precalculate upper and lower bounds for turning
*/
int upper_bound = DEFAULT_SERVO_POSITION + DEFAULT_SERVO_SNAP_DIST;
int lower_bound = DEFAULT_SERVO_POSITION - DEFAULT_SERVO_SNAP_DIST;

/*
  Servo objects to control the motor and servo of the car
*/
Servo motor, servo;

/*
  Sets up the enviroment for the car, including setting all
  pins to approprate input/output modes; setting up the 
  Motor and Servo objects; and setting up the Serial Port.
*/
void setup() {
  Serial.begin(9600);
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(SERVO_PIN, OUTPUT);
  pinMode(RADIO_MOTOR_PIN, INPUT);
  pinMode(RADIO_SERVO_PIN, INPUT);
  motor.attach(MOTOR_PIN);
  servo.attach(SERVO_PIN);
  servo.write(90);
}

/*
  Gets the requested speed and rotation, and writes them to the motor and servo
*/
void loop() {
  motor.writeMicroseconds(getRequestedSpeed());
  servo.write(getRequestedRotation());  
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
