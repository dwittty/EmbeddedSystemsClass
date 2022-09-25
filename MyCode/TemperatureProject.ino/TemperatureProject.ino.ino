#include <AnalogReader.h>
#include <Thermistor.h>


// Pin Definitions
#define THERMISTOR_PIN_CON1  A10

// Global variables and defines

// object initialization
Thermistor thermistor(THERMISTOR_PIN_CON1);


// define vars for testing menu
const int readTempDelay = 10;
const int arraySize = 200;
const int nextIndex = 0;
const int interruptPin = 2; 

volatile byte state = HIGH;

int currIndex = 0;
char menuOption = 0;
long time0;


float temps[arraySize];


// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    pinMode(interruptPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(interruptPin), outputSerial, LOW);
    
    Serial.begin(9600);
    //while (!Serial) ; // wait for serial port to connect. Needed for native USB    

    for(int i = 0; i < arraySize; i++){
      temps[i] = -1;
    }    
    Serial.print("Welcome. Please enter 1 when you are ready to retrieve the stored temperature data.\n");
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    //Serial.print("This is a test.\n");
    // NTC Thermistor 10k - Test Code
    //delay for some duration between temperature reads while reading user input. If input value 1 is received, trigger interrupt and write temp data to serial
    for(int i = 0; i < readTempDelay; i++){
      char checkInterrupt = Serial.read();       
      if(checkInterrupt == '1') {        
        state = !state;
        digitalWrite(interruptPin, state);        
        checkInterrupt = '0'; //set to some value other than 1 when interrupt concludes
      }  
      else{
        delay(1000);
      }      
    }
    //stop collecting data if the array is full.
    if(currIndex < arraySize){
      //Get Measurment from Thermistor temperature sensor.
      float thermistorTempF = thermistor.getTempF();   
      temps[currIndex] = thermistorTempF;
      currIndex++;    
    }
}


void outputSerial(){    
  for(int i = 0; i < currIndex; i++){
    float currVal = temps[i];
    if(currVal == -1){
      break;
    }
    else{
      Serial.print(currVal);
      Serial.print(",");
      temps[i] = -1; //set back to -1 in case we wanted to continue collecting data for another run. 
    }
  }
  currIndex = 0;  //reset temp array index
  state = !state; //reset state of interrupt pin
  digitalWrite(interruptPin, state);        
}
