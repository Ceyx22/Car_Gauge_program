// Include the AccelStepper Library
#include <AccelStepper.h>
 
// Define Constants
int targetPosition;
bool rotComplete = false;
 
// Define step constants
#define FULLSTEP 4
//#define HALFSTEP 8
 
// Define Motor Pins (2 Motors used)
 
#define motorPin1  8     // Blue   - 28BYJ48 pin 1
#define motorPin2  9     // Pink   - 28BYJ48 pin 2
#define motorPin3  10    // Yellow - 28BYJ48 pin 3
#define motorPin4  11    // Orange - 28BYJ48 pin 4
                        
                        
 // const varaible needed for calculations and comletetion of cuircuts
 const int preasureInput = A1; //PIN A1
 const double preasureZero = 102.4; //Anlog reading of transducer at 0 PSI
 const double preasureMax = 921.6; //Anlog reading of transducer at 30 PSI
 const int preasureTransducerMaxPSI = 30; //Max PSI
 const int baudRate = 9600; //Serial moniter
 const int sensorReadDelay = 250; //delay in millliseconds

 float preasureValue = 0; //varible for storing the preasure from the transducer
 
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
  //if(stepper1.currentPosition() != 0)
    //stepper1.moveTo(0);  
    //Serial.println("0");

 
}
 
 
void loop()
{
  //targetPosition = Serial.read();
  
  // put your main code here, to run repeatedly:
   
  //Change direction at the limits
  stepper1.run();
  rotComplete = false;

        
  if (rotComplete == false ){ 
      while(targetPosition <= 0.5 && targetPosition > -0.5){
        //Hang time
        Serial.println("hangtime");
        preasureValue = analogRead(preasureInput); //reads the tranducer
        preasureValue = ((preasureValue - preasureZero)*preasureTransducerMaxPSI)/(preasureMax - preasureZero); //Converts from anolog to
        targetPosition = preasureValue;
        Serial.println(preasureValue);
        delay(sensorReadDelay);
      }
    if(targetPosition >= 0){
      targetPosition = targetPosition * 40;
      Serial.println("moving forward");
    }
    if (targetPosition < 0){
      targetPosition = targetPosition * 20;
      Serial.println("moving backward");
    }
    Serial.println(targetPosition);
    stepper1.moveTo(targetPosition);//stops completely at 0 fix later
    //while(stepper1.currentPosition() != targetPosition){
      Serial.println(stepper1.currentPosition());
    //}
    rotComplete = true;
  }

  
  

 
}
