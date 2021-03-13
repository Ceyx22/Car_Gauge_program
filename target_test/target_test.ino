// Include the AccelStepper Library
#include <AccelStepper.h>
 
// Define Constants
int targetPositionPSI;
int stepperPosition;

int readValue;
float currentVoltage = 0;

int gaugeZero = 217;

int upStepps = -14;
int downStepps = 7;
 
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


 
}
 
 
void loop()
{
  //targetPosition = Serial.read();
  //Change direction at the limits
  stepper1.run();
  if (stepper1.currentPosition() == targetPositionPSI){ 
      while(Serial.available() == 0){
        //hangtime!
      }
    targetPositionPSI = Serial.parseInt();
    if(targetPositionPSI >= 0){
      targetPositionPSI = abs(targetPositionPSI);
      Serial.println("Doing this");
      targetPositionPSI = targetPositionPSI * upStepps;
      
      targetPositionPSI = abs(targetPositionPSI) + gaugeZero;
      Serial.println(targetPositionPSI);
    }
    if(targetPositionPSI < 0){
      targetPositionPSI = abs(targetPositionPSI);
      targetPositionPSI = targetPositionPSI * downStepps;
      targetPositionPSI = gaugeZero - targetPositionPSI ;
    }
    //217
    Serial.println(targetPositionPSI);
    stepper1.moveTo(targetPositionPSI);//stops completely at 0 fix later
    Serial.println(stepper1.currentPosition());

  }

  
  

 
}
