// Include the AccelStepper Library
#include <AccelStepper.h>
 
// Define Constants
//int targetPosition = 400;
 
// Define step constants
#define FULLSTEP 4
#define HALFSTEP 8
 
// Define Motor Pins (2 Motors used)
 
#define motorPin1  8     // Blue   - 28BYJ48 pin 1
#define motorPin2  9     // Pink   - 28BYJ48 pin 2
#define motorPin3  10    // Yellow - 28BYJ48 pin 3
#define motorPin4  11    // Orange - 28BYJ48 pin 4
                        
                        

 
// Define two motor objects
// The sequence 1-3-2-4 is required for proper sequencing of 28BYJ48
AccelStepper stepper1(FULLSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

 
void setup()
{ 
  Serial.begin(9600);
  // 1 revolution Motor 1 CW
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(80.0);
  stepper1.setSpeed(200);
  stepper1.moveTo(325);  

 
}
 
 
void loop()
{
  //targetPosition = Serial.read();
  //Change direction at the limits
  if (stepper1.distanceToGo() == 0) 
    stepper1.moveTo(-stepper1.currentPosition());//stops completely at 0 fix later
    Serial.println(stepper1.currentPosition());


  
  stepper1.run();

 
}
