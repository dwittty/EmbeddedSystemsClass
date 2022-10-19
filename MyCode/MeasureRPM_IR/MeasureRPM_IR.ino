int enablePin = 11;
int in1Pin = 10;
int in2Pin = 9;
int potPin = A0;
long toggles = 0;

const int arrSize = 5;
int rollingAverage[arrSize];

const int numberOfBlades = 3;
const long calculateRPMdelay = 1000000; //delay between each RPM calculation in microseconds
const byte interruptPin = 2;

static const unsigned long REFRESH_INTERVAL = 1000; // ms
static unsigned long lastRefreshTime = 0;
  
  

void setup()
{
  for(int i = 0; i < arrSize; i++){
    rollingAverage[i] = 0;
  }
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(enablePin, OUTPUT);      
  Serial.begin(9600);  
  toggles = 0;
  
  //Timer1.initialize(calculateRPMdelay);
  //Timer1.attachInterrupt(calculateRPM);
  attachInterrupt(digitalPinToInterrupt(interruptPin), incrementToggle, CHANGE);
}

void loop()
{
  int speed = analogRead(potPin) / 4;      
  setMotor(speed);

  if(millis() - lastRefreshTime >= REFRESH_INTERVAL)
  {
    lastRefreshTime += REFRESH_INTERVAL;
    int currentRPM = computeRPM();
    storeRPMInRollingArray(currentRPM);
    printAverage();    
  }  
}

void setMotor(int speed)
{
  analogWrite(enablePin, speed);  
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
}

void incrementToggle(){  
  toggles++;
}


//call every second; calculate rpm using number of toggles
int computeRPM(){          
    noInterrupts();    
    int rpm = toggles*60/6; //times 60 for sixty seconds a minute; divide by 6 because there are 3 blades and 2 toggles per blade
    toggles = 0;
    interrupts();
    storeRPMInRollingArray(rpm);             
    return rpm;
}

//keep track of most recent RPM recordings 
void storeRPMInRollingArray(int newRPM){
    int prev = rollingAverage[0];
    rollingAverage[0] = newRPM;
    for(int i = 1; i < arrSize; i++){
      int temp = rollingAverage[i];
      rollingAverage[i] = prev;
      prev = temp;      
    }
}

//print out the average RPM value by averaging all RPM values stored in array
void printAverage(){
  long average = 0;
  for(int i = 0; i < arrSize; i++){
    average += rollingAverage[i];
  }
  average = average/arrSize;  
  Serial.println(average);
}
