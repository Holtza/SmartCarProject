#include <Servo.h>


Servo esc, Sservo;
const int motor = 6;
const int servo = 5;
int delay_sec = 10;
int neutral = 1500; // //value for making car stand still
int high = 2000;  ////value for making car go forward
int low = 1000;  //value for making car go backwards


 
void setup(){
  //interup for safety, triggered when remote controll is turned on
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
  

  if(Serial.available() > 0){  // checks if there's any buffered data
    int last_input = Serial.read();  // if so, fetch it
    Serial.print("user input: " + String(last_input) + " - ");

    switch(last_input){  // check what key was pressed (ASCII)
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

void manualOverride(){  //function that runs when the remote controll is turned on
  esc.writeMicroseconds(neutral);
  Serial.println("INTERUPTED");
}

