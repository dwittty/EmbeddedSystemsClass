

const int ditDelay = 200;
const int dahDelay = ditDelay * 3;
const int betweenCharacterDelay = ditDelay * 3;
const int wordDelay = ditDelay * 7;
const int sentinel = 33;
const int ledPin = 12;
const int buzzerPin = 11;
String morseCodeLetters[26]={
    // A to G
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", 
    // H to N
    "....", "..", ".---", "-.-", ".-..", "--", "-.",
    // O to U
     "---", ".--.", "--.-", ".-.", "...", "-", "..-",
    // V to Z
     "...-", ".--", "-..-", "-.--", "--..",
};
String morseCodeNumbers[10] = {
    //0 through 9
    "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."
};

boolean running = true;
int nextByte = 0; //for reading data coming from serial

void setup() {
  // put your setup code here, to run once:  
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);  
  Serial.begin(9600);
  Serial.print("Welcome, please enter a string to convert to morse code: ");    
}

void loop() {
    String currentMorseCode = "";
    if(running){
        if(Serial.available() > 0){
            nextByte = Serial.read();            
            //convert lowercase letters to upper, then handle those together
            if(nextByte >= 97 && nextByte <= 122){
                nextByte -= 32;
            }
      
            if(nextByte >= 65 && nextByte <= 90){
                currentMorseCode = morseCodeLetters[nextByte-65];
                processMorseCode(currentMorseCode);
            }
            else if(nextByte >= 48 && nextByte <= 57){
                currentMorseCode = morseCodeNumbers[nextByte-48];
                processMorseCode(currentMorseCode);
            }            
            else if(nextByte == 32){
                processMorseCode(" ");
            }
            else if(nextByte == sentinel){
                running = false;
                digitalWrite(ledPin, LOW);   
                digitalWrite(buzzerPin, LOW);
            }
            else{
                //ignore non alphanumeric, non-sentinel characters
            }
            
        }
    }   
}

void processMorseCode(String code){
    if(code == " "){
        //delay of 7 dits between words
        delay(wordDelay);
    }    
    else{
       //introduce a 3 dit delay between letters         
       delay(betweenCharacterDelay);
       for(int i = 0; i < code.length(); i++){
            //delay for the duration of one dit between each sound within a character
            delay(ditDelay);

            if(code[i] == '.'){
                //brighten LED for one dit duration, then send back to low
                digitalWrite(ledPin, HIGH);
                digitalWrite(buzzerPin, HIGH);
                delay(ditDelay);                
                digitalWrite(ledPin, LOW);
                digitalWrite(buzzerPin, LOW);
            }
            else if(code[i] == '-'){
                //brighten LED for one dah duration, then send back to low
                digitalWrite(ledPin, HIGH);
                digitalWrite(buzzerPin, HIGH);
                delay(dahDelay);
                digitalWrite(ledPin, LOW);
                digitalWrite(buzzerPin, LOW);
            }
        }
    }
}
