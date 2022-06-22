

#include <Otto.h>
Otto Otto;  //This is Otto!

#define LeftLeg 2 
#define RightLeg 3
#define LeftFoot 4 
#define RightFoot 5 
#define Buzzer  13

const int sensorPin = A0;

int sensorValue = 0;
const int threshold = 500;

///////////////////////////////////////////////////////////////////
//-- Setup ------------------------------------------------------//
///////////////////////////////////////////////////////////////////
void setup(){
  Otto.init(LeftLeg, RightLeg, LeftFoot, RightFoot, true, Buzzer); //Set the servo pins and Buzzer pin
  pinMode(sensorPin, INPUT);
  
  Otto.home();
  Otto.sing(S_happy); // a happy Otto :)
}
  
///////////////////////////////////////////////////////////////////
//-- Principal Loop ---------------------------------------------//
///////////////////////////////////////////////////////////////////
void loop() {
  sensorValue = analogRead(A0);
  int absValue = sensorValue - threshold;

  if (absValue > 0)
  {
    Otto.sing(S_surprise);
  }
}
