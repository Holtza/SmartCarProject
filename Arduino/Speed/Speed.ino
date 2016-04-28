#include <TimerOne.h>
unsigned int counter=0;
 
int b1a = 5;  // L9110 B-1A 
int b1b = 3;  // L9110 B-1B
 
void docount()  // counts from the speed sensor
{
  counter++;  // increase +1 the counter value
} 
 
void timerIsr()
{
  Timer1.detachInterrupt();  //stop the timer
  Serial.print("Motor Speed: ");
  Serial.print(counter);  
  Serial.println(" Holes per seconds"); 
  counter=0;  //  reset counter to zero
  Timer1.attachInterrupt( timerIsr );  //enable the timer
}
 
void setup() 
{
  Serial.begin(9600);
  
 pinMode(b1a, INPUT); 
 pinMode(b1b, INPUT); 
  
  Timer1.initialize(1000000); // set timer for 1sec
  attachInterrupt(digitalPinToInterrupt(b1b), docount, RISING);  // increase counter when speed sensor pin goes High
  Timer1.attachInterrupt( timerIsr ); // enable the timer
} 
 
void loop()
{
  //Serial.println(digitalRead(b1b));

  
  /*
  int potvalue = analogRead(1);  // Potentiometer connected to Pin A1
  int motorspeed = map(potvalue, 0, 680, 255, 0);
  analogWrite(b1a, motorspeed);  // set speed of motor (0-255)
  digitalWrite(b1b, 1);  // set rotation of motor to Clockwise
  */
}
