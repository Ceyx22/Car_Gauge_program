/*
 * Author: Fernando E. Matias
 * Anolog Boost/Vaccum Gauge
 * Commissioned by Digital Metrology Works LLC
 */

// Include the AccelStepper Library
#include <AccelStepper.h>
 
// Define Constants
int targetPositionPSI;
int stepperPosition;

int readValue;
float currentVoltage = 0;

int gaugeZero = 217;

bool homeSeq1 = false;
bool homeSeq2 = false;

int upStepps = -14;
int downStepps = 7;

 // const varaible needed for calculations and comletetion of cuircuts
const int preasureInput = A1; //PIN A1
const double preasureZero = 102.4; //Anlog reading of transducer at 0 PSI
const double preasureMax = 921.6; //Anlog reading of transducer at 30 PSI
const int preasureTransducerMaxPSI = 30; //Max PSI
const int baudRate = 9600; //Serial moniter
const int sensorReadDelay = 250; //delay in millliseconds

float preasureValue = 0; //varible for storing the preasure from the transducer
 
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
  Serial.begin(28800);
  // 1 revolution Motor 1 CW
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(100.0);
  stepper1.setSpeed(400);
  while(homeSeq1 == false){
    stepper1.moveTo(-625); 
    stepper1.run();
    Serial.println(stepper1.currentPosition());
    
    if(stepper1.currentPosition() == -625){
      homeSeq1 = true;
    }
  }
  
  stepper1.setCurrentPosition(0);
  Serial.println("Set 0 Pos");
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(100.0);
  stepper1.setSpeed(400);
}
 
void loop()
{
  //targetPosition = Serial.read();
  //Change direction at the limits
  stepper1.run();
  if (stepper1.currentPosition() == targetPositionPSI){ 
     preasureValue = analogRead(preasureInput); //reads the tranducer
       preasureValue = ((preasureValue - preasureZero)*preasureTransducerMaxPSI)/(preasureMax - preasureZero); //Converts from anolog to
       targetPositionPSI = preasureValue;
       Serial.println(preasureValue);
       //delay(sensorReadDelay);
    // Will check if the TargetPosition is greater or equal to then zero to make it take the appropriate number of steps
    if(targetPositionPSI >= 0){
      targetPositionPSI = abs(targetPositionPSI);
      targetPositionPSI = targetPositionPSI * upStepps;
      // takes the absoluete value and adds it to the base position for zero so it goes to the right place.
      targetPositionPSI = abs(targetPositionPSI) + gaugeZero;
    }
    // Will check if the TargetPosition is less then zero to make it take the appropriate number of steps
    if(targetPositionPSI < 0){
      targetPositionPSI = abs(targetPositionPSI);
      targetPositionPSI = targetPositionPSI * downStepps;
      // takes the absoluete value and subtracts it to the base position for zero so it goes to the right place.
      targetPositionPSI = gaugeZero - targetPositionPSI ;
    }
    //base number of steps: 217
    stepper1.moveTo(targetPositionPSI);//stops completely at 0 fix later
  }

}
