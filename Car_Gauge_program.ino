/*
 * Author: Fernando Matias
 * Made for car metter gauge
 */
// #include <Stepper.h>
//  const float stepsPerRev = 32;
//  const float gearRatio = 64;
//  const float gearedOutputRotation = stepsPerRev * gearRatio;
//  int stepsRequired;

#include <AccelStepper.h>

//define step constants 
#define fullStep 4
#define halfStep 8

//define motor pins
#define motorPin1 8
#define motorPin2 9
#define motorPin3 10
#define motorPin4 11

 // const varaible needed for calculations and comletetion of cuircuts
 const int preasureInput = A1; //PIN A1
 const double preasureZero = 102.4; //Anlog reading of transducer at 0 PSI
 const double preasureMax = 921.6; //Anlog reading of transducer at 30 PSI
 const int preasureTransducerMaxPSI = 30; //Max PSI
 const int baudRate = 9600; //Serial moniter
 const int sensorReadDelay = 100; //delay in millliseconds

 float preasureValue = 0; //varible for storing the preasure from the transducer

  //The pins used are d8, d9, d10, d11
  //connected to in1, in2, in3, in4
  //for proper sequencing use 1-3-2-4

  //Stepper steppermotor(stepsPerRev, 8, 10, 9, 11);

  //define motor objects 
  AccelStepper stepper1(fullStep, motorPin1, motorPin3, motorPin2, motorPin4); 
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(baudRate); //starts the serial moniter
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(50.0);
  stepper1.setSpeed(200);
  stepper1.moveTo(-2048);

}

void loop() {
  // put your main code here, to run repeatedly:
  preasureValue = analogRead(preasureInput); //reads the tranducer
  preasureValue = ((preasureValue - preasureZero)*preasureTransducerMaxPSI)/(preasureMax - preasureZero); //Converts from anolog to PSI
  Serial.print(preasureValue, 1);
  Serial.println("PSI");
  delay(sensorReadDelay);

}
