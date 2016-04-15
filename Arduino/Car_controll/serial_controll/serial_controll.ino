#include <Servo.h>


Servo esc, Sservo;
const int motor = 6;
const int servo = 5;
int delay_sec = 10;
int neutral = 1500;//1300;
int high = 2000;//1800;
int low = 1000;//850;


 
void setup(){
  attachInterrupt(digitalPinToInterrupt(3), manualOverride, FALLING);
  Serial.begin(9600);
  pinMode(motor, OUTPUT);
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
  

  if(Serial.available() > 0){
    int last_input = Serial.read();
    Serial.print("user input: " + String(last_input) + " - ");

    switch(last_input){
      case 119: //W
        //forward
        esc.writeMicroseconds(1570);
        Serial.println("Forward");
        break;
        
      case 122: //Z
        //back
        esc.writeMicroseconds(1250);
        break;
        
      case 120: //X
        esc.writeMicroseconds(1500);
        break;
        
      case 97: //A
        //left
        Sservo.write(60);
        Serial.println("left");
        break;
        
      case 100: //D
        //right
        Sservo.write(120);
        Serial.println("right");
        break;

      case 115: //S
        //straight
        Sservo.write(90);
        Serial.println("Straight");
        break;
        
      default:
        Serial.println("unknown input");
    }
  }


}

void manualOverride(){
  esc.writeMicroseconds(neutral);
  Serial.println("INTERUPTED");
}

