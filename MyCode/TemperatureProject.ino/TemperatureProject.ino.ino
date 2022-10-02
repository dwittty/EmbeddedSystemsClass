#include <AnalogReader.h>
#include <Thermistor.h>
#include <TimerOne.h>

// Pin Definitions
#define THERMISTOR_PIN_CON1  A10

// object initialization
Thermistor thermistor(THERMISTOR_PIN_CON1);

// Global variables and defines
const long readTempDelay = 10000000; //delay for interrupt in microseconds
const int arraySize = 200; 

volatile byte state = HIGH;
int currIndex = 0;
long time0;
float temps[arraySize];

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{    
  Timer1.initialize(readTempDelay);
  Timer1.attachInterrupt(saveNextTemperatureReading);  
  Serial.begin(9600);  

  //initialize array that holds temperature data to -1. Values of -1 will not be read when downloading data. 
  for(int i = 0; i < arraySize; i++){
    temps[i] = -1;
  }    
  Serial.print("Welcome. Please enter 1 when you are ready to retrieve the stored temperature data.\n");
    
}

void saveNextTemperatureReading(){      
  float thermistorTempF = thermistor.getTempF(); //Get Measurment from Thermistor temperature sensor.
  temps[currIndex] = thermistorTempF; //store temperature value at currIndex
  currIndex++; //increment currIndex
}

//prints out all the collected data across the serial bus
void download(){
  for(int i = 0; i < currIndex; i++){
    float currVal = temps[i];
    if(currVal == -1){
      break;
    }
    else{
      Serial.println((String) currVal + ",");      
      temps[i] = -1; //set back to -1 in case we wanted to continue collecting data for another run. 
    }
  }
  currIndex = 0;  //reset temp array index  
}

//main loop checks for user input requesting download. Enter '1' to download collected temperature data. 
void loop() 
{     
  
  char userRequestedDownload = Serial.read();       
  if(userRequestedDownload == '1') {   
    noInterrupts();   
    download(); 
    userRequestedDownload = '0'; //set to some value other than 1 when download concludes               
    interrupts();
  }    
}
