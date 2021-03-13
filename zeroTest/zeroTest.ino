// Include the AccelStepper Library
#include <AccelStepper.h>
 
// Define Constants
int targetPositionPSI;
int stepperPosition;

const int stepperInput = A3; //PIN A3
int readValue;
float currentVoltage = 0;

int falseHome = -1600;
int trueHome = 600;

bool homeSeq1 = false;
bool homeSeq2 = false;

int upStepps = 40;
int downStepps = -20;
 
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
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(100.0);
  stepper1.setSpeed(300);
  while(homeSeq1 == false){
    Serial.println("firstLoop");
    stepper1.moveTo(-800); 
    stepper1.run();
    Serial.println(stepper1.currentPosition());
    
    if(stepper1.currentPosition() == -755){
      Serial.println("Out of first loop");
      homeSeq1 = true;
    }
  }
  
  stepper1.setCurrentPosition(0);
  Serial.println("Set 0 Pos");
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(100.0);
  stepper1.setSpeed(300);
//  
//  while(homeSeq2 == false){
//    Serial.println("Second loop");
//    stepper1.moveTo(600); 
//    stepper1.run();
//    
//    if(stepper1.currentPosition() == 600){
//      homeSeq2 = true;
//      Serial.println("Out of Second loop");
//    }
//  } 
//
//  stepper1.setCurrentPosition(0);
//  stepper1.setMaxSpeed(1000.0);
//  stepper1.setAcceleration(1000.0);
//  stepper1.setSpeed(1000);
//  Serial.println("Set Real 0 pos");
//  
  }

 

 
 
void loop()
{
 stepper1.run();
 
}
  //targetPosition = Serial.read();
  //Change direction at the limits
//  stepper1.run();
//  if (stepper1.currentPosition() == targetPositionPSI){ 
//      while(Serial.available() == 0){
//    
//  }
//    targetPositionPSI = Serial.parseInt();
//    if(targetPositionPSI >= 0){
//      targetPositionPSI = abs(targetPositionPSI);
//      targetPositionPSI = targetPositionPSI * upStepps;
////      readValue = analogRead(stepperInput);
////      currentVoltage = (5.0 / 1023.0)*readValue;
////      Serial.println(currentVoltage);
//    }
//    if(targetPositionPSI < 0){
//      targetPositionPSI = abs(targetPositionPSI);
//      targetPositionPSI = targetPositionPSI * downStepps;
////      readValue = analogRead(stepperInput);
////      currentVoltage = (5.0 / 1023.0)*readValue;
////      Serial.println(currentVoltage);
//    }
//    Serial.println(targetPositionPSI);
//    stepper1.moveTo(targetPositionPSI);//stops completely at 0 fix later
//    Serial.println(stepper1.currentPosition());
////    if(steppChecker == false){
////      readValue = analogRead(stepperInput);
////      currentVoltage = (5.0 / 1023.0)*readValue;
////      Serial.println(currentVoltage);
////      delay(1000);
////      stepper1.moveTo(targetPositionPSI);
////      if(stepper1.currentPosition() != targetPositionPSI){
////        steppChecker = false;
////      }
////      if(stepper1.currentPosition() == targetPositionPSI){
////        steppChecker = true;
////      }
////      
////    }
////    readValue = analogRead(stepperInput);
////    currentVoltage = (5.0 / 1023.0)*readValue;
////    Serial.println(currentVoltage);
  

  
  

 
