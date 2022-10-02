#include <TimerOne.h>

//int ir = 13;
int enablePin = 11;
int in1Pin = 10;
int in2Pin = 9;
int switchPin = 7;
int potPin = A0;
bool oldVal;
long toggles = 0;
const int numberOfBlades = 3;
const long calculateRPMdelay = 1000000; //delay between each RPM calculation in microseconds
const byte interruptPin = 2;

int debugCount = 0;

void setup()
{
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(enablePin, OUTPUT);  
  //pinMode(ir, INPUT);
  pinMode(switchPin, INPUT_PULLUP);
  oldVal = HIGH;
  Serial.begin(9600);  
  toggles = 0;
  
  //Timer1.initialize(calculateRPMdelay);
  //Timer1.attachInterrupt(calculateRPM);
  attachInterrupt(digitalPinToInterrupt(interruptPin), incrementToggle, CHANGE);
}

void loop()
{
  int speed = analogRead(potPin) / 4;    
  boolean spin = digitalRead(switchPin);
  setMotor(speed, spin);

  debugCount++;
  if(debugCount % 10000000 == 0){
    Serial.println((String)"Millis: " + millis());
    long elapsedSeconds = millis() / 1000;
    Serial.println((String)"Seconds: " + elapsedSeconds);
    Serial.println((String)"Toggles: " + toggles);
    int averageTogglesPerSecond = (toggles / elapsedSeconds);
    Serial.println((String)"Toggles Per Second: " + averageTogglesPerSecond);
    int rpm = averageTogglesPerSecond*60/6;
    Serial.println((String)"RPM: " + rpm);
  }  
}

void setMotor(int speed, boolean spin)
{
  analogWrite(enablePin, speed);  
  digitalWrite(in1Pin, !spin);
  digitalWrite(in2Pin, spin);
}

//void calculateRPM(){
  //int rpm = toggles*60/numberOfBlades;
  //toggles = 0;
  //Serial.println(rpm);  
//}
void incrementToggle(){  
  toggles++;
}
