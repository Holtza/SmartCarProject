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
#define BASE_SPEED 1570
#define BOOST_SPEED 1615
#define NEUTRAL 1200
#define MIN 800
#define MAX 2000

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

void loop() {
  if(Serial.available() > 0){  // checks if there's any buffered data
    char last_input = Serial.read();  // if so, fetch it
    Serial.print("user input: " + String(last_input) + " - ");

    if(last_input >= LOWER_MESSAGE_ANGLE && last_input <= UPPER_MESSAGE_ANGLE){
       
    }
    
    switch(last_input){  // check what key was pressed (ASCII)
      case 'w': //w
        //forward
          Serial.println("Neutral");
          esc.writeMicroseconds(NEUTRAL);
        break;
        
      case 'z': //z
        //back
        Serial.println("MIN");
        esc.writeMicroseconds(MIN);
        break;
        
      case 'x': //x
        driving = false;
        Serial.println("MAX");
        esc.writeMicroseconds(MAX);
        break;

      
      case 'a': //x
        driving = false;
        Serial.println("driving");
        esc.writeMicroseconds(1300);
        break;
        
      default:
        Serial.println("unknown input?");
    }
  }
}
