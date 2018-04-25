#include <Wire.h>
#include <SoftwareSerial.h>
#define BLYNK_PRINT DebugSerial
#include <elapsedMillis.h>
SoftwareSerial DebugSerial(0, 1); // RX, TX

#include <BlynkSimpleStream.h>

const int ledPin = 13;    // take 13Pin and Ground
const int inputSoundPin = A2;  // take Ground, A2 and V5
//const int lightPin = A3;  // take A3 and Ground
const int potentiometerPin = A0;  // take Ground, A0  and V3-3


#define SOUND_THRESHOLD 400

bool flag = true;

char auth[] = "yourTocken";

void setup() 
{
  Wire.begin(); // for the 2 arduinos communication
  Serial.begin(9600);
  DebugSerial.begin(9600);
  
  pinMode(ledPin, OUTPUT);
  pinMode(inputSoundPin, INPUT);
  //pinMode(lightPin, INPUT);

  Blynk.begin(Serial, auth);
  Blynk.run();
}

void loop() 
{
  char c = 'Z';
  
  // Wait for start-game action
  while(c != 'A') // 'A' is the character for starting the game
  {
    Blynk.run();
    Wire.requestFrom(5,1);
    while(Wire.available())
    {
      Blynk.run();
      c = Wire.read();
    }
  }
  elapsedMillis timeElapsed;

  Blynk.virtualWrite(V0, 0);
  Blynk.virtualWrite(V1, 0);
  Blynk.virtualWrite(V2, 0); 
  Blynk.virtualWrite(V5, 0);

  flag = true;
  delay(1200);
  // Sound sensor
  while(flag)
  {
    Blynk.run();
    soundFunc(); //blocking call - run until high sound is made
    Wire.beginTransmission(5);
    Wire.write('S'); // high sound test passed
    Wire.endTransmission();
    delay(200);

    Wire.requestFrom(5,1);
    getResponse(); // checks if the sound was made in the appropriate time
  }

  flag = true;
  delay(1200);

  // Light Sensor
  Blynk.virtualWrite(V5, 1); 
  while(flag)
  {
    Blynk.run();
    /*lightFunc(); //blocking call - run until low light
    Wire.beginTransmission(5);
    Wire.write('L'); // low light was made
    Wire.endTransmission();
    delay(200);*/

    Wire.requestFrom(5,1);
    getResponse(); //checks if low light is in the appropriate time
  }
  
  int x1 = timeElapsed/60000;
  timeElapsed = 0;

  flag = true;
  delay(1200);

  // NOTE TO SELF - might want to just let the LED to transmit the morse code indefinitly
  Blynk.virtualWrite(V5, 2); 
  while(flag)
  {
    Blynk.run();
    ledFunc();

    Wire.requestFrom(5,1);
    getResponse();
    delay(3000);
  }

  flag = true;
  delay(1200);

  // pontention
  int x2 = timeElapsed/60000;
  Blynk.virtualWrite(V5, 3); 
  while(flag)
  {
    Blynk.run();
    potentFunc(); //blocking call - wait until right value was entered
    Wire.beginTransmission(5);
    Wire.write('R'); // asking if it is the right time
    Wire.endTransmission();
    delay(200);

    Wire.requestFrom(5,1);
    getResponse();
  }

  int x3 = timeElapsed/60000;
  Blynk.virtualWrite(V0, x1);
  Blynk.virtualWrite(V1, x2);
  Blynk.virtualWrite(V2, x3);
  Blynk.virtualWrite(V5, 4);
  timeElapsed = 0;
}



// Potentiometer function
void potentFunc()
{
  int sensorValue = 0;
  int value = 24;

  while(sensorValue != 24)
  {
    Blynk.run();
    sensorValue = analogRead(potentiometerPin);
    Blynk.virtualWrite(V3, sensorValue); 
    
    delay(500);
  }
}


/*
// LightSensor
void lightFunc()
{
  int count = 0;
  int sensorValue = 0;
  
  while(count < 4)
  {
    Blynk.run();
    sensorValue = analogRead(lightPin);
    if(sensorValue > 0)
      count++;

    else
      count = 0;
      
    delay(200);
  }
}
*/


// LED function
void ledFunc()
{
  // 9
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  
  delay(200);
  if(!flag)
    return;
  
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  
  delay(200);
  if(!flag)
    return;
  
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  
  delay(200);
  if(!flag)
    return;
  
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  
  delay(200);
  if(!flag)
    return;
  
  digitalWrite(ledPin, HIGH);
  delay(200);
  digitalWrite(ledPin, LOW);

  if(!flag)
    return;
  delay(2000);
  if(!flag)
    return;

  // 7
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  
  delay(200);
  if(!flag)
    return;
  
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  
  delay(200);
  if(!flag)
    return;
  
  digitalWrite(ledPin, HIGH);
  delay(200);
  digitalWrite(ledPin, LOW);
  
  delay(200);
  if(!flag)
    return;
  
  digitalWrite(ledPin, HIGH);
  delay(200);
  digitalWrite(ledPin, LOW);
  
  delay(200);
  if(!flag)
    return;
  
  digitalWrite(ledPin, HIGH);
  delay(200);
  digitalWrite(ledPin, LOW);
  
  if(!flag)
    return;
  delay(2000);
  if(!flag)
    return;

  // 2
  digitalWrite(ledPin, HIGH);
  delay(200);
  digitalWrite(ledPin, LOW);
  
  delay(200);
  if(!flag)
    return;
  
  digitalWrite(ledPin, HIGH);
  delay(200);
  digitalWrite(ledPin, LOW);
  
  delay(200);
  if(!flag)
    return;
  
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  
  delay(200);
  if(!flag)
    return;
  
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  
  delay(200);
  if(!flag)
    return;
  
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  
  delay(200);
  if(!flag)
    return;
}



// SoundSensor function
void soundFunc()
{
  int count = 0;
  int sensorValue = 0;
  
  while(count < 2)
  {
    Blynk.run();
    sensorValue = analogRead(inputSoundPin);

    if(sensorValue > SOUND_THRESHOLD)
      count++;

    else
      count = 0;

    delay(100);
  }
}


void getResponse()
{ 
  while(Wire.available())
  {
    Blynk.run();
    char c = Wire.read();
      
    if(c == 'Y') // right time
      flag = false;

    else if(c == 'O') // right time
      flag = false;
    
    else
      flag = true;
  }
}


