#include <Servo.h>
#define rMotor 11
#define rServo 10
#define motor 9
#define servo 6

Servo esc, Sservo;
int mySpeed = 0;
int rotation = 0;
//int rMotor = 11;
//int rServo = 10;

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(11, INPUT);
  pinMode(10, INPUT);
  esc.attach(motor);
  Sservo.attach(servo);
  Sservo.write(90);
}

void loop() {
  if(pulseIn(rMotor, HIGH) > 1500){
    mySpeed = ((pulseIn(rMotor, HIGH) - 1500) * 0.25) + 1500;
  }else if(pulseIn(rMotor, HIGH) < 1500){
    mySpeed = 1500 - (1500 - (pulseIn(rMotor, HIGH)) * 0.85);
  }
  esc.writeMicroseconds(mySpeed);
  if(pulseIn(rServo, HIGH) > 1340 && pulseIn(rServo, HIGH) < 1380){
    Sservo.write(90);
  }else if(pulseIn(rServo, HIGH) < 1370){
   rotation = (90 - ((1370 - pulseIn(rServo, HIGH)) / 25));
   if(rotation > 69 && rotation < 90){
     Sservo.write(rotation);
   }
  }else if(pulseIn(rServo, HIGH) > 1369){
   rotation = (90 + ((pulseIn(rServo, HIGH) - 1370) / 25));
    if(rotation > 90 && rotation < 111){
    Sservo.write(rotation);
  }
  }
  Serial.print(pulseIn(rMotor, HIGH));
  Serial.print("\t");
  Serial.println(pulseIn(rServo, HIGH));  
  
}
