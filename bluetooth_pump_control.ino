//Code written by Sumukh Anil Purohit
//Licenced under GNU GPL v2
//
//Arduino 4 relay bluetooth shield for UNO and MEGA 2560
//the 4 relay bluetooth shield is available for sale on tindie https://www.tindie.com/products/sumukh208/4-relay-bluetooth-shield-for-arduino/


// This code is written for my home pump automation which has a panel with ON switch and OFF switch, thus users have to customize it for their applications.
// the pump panel contains the ON switch with 2 elements which are N/O. and OFF switch with 1 element which is N/C.
//2 relays are engaged simultaneously for ON and 1 relay for OFF. bluetooth module HC 05 or 06 can be used
//Ultrasound sensor for Arduino is used for sensing water level and turning off the pumps correspondingly
//Code is well tested and the unit I hve made is in operation at my home since January 2017.

// the app development is done in MIT app inventor.

String voice;
const int trigPin = 2;
const int echoPin = 3;
long duration;
int distanceCm;
float level;
float parts;
const int levelHigh = 4;
const int subOff = 9;
const int subOn = 11;
const int tankOn = 8;
const int subOnn = 10;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(levelHigh, INPUT);
  pinMode(subOff, OUTPUT);
  pinMode(subOnn, OUTPUT);
  pinMode(subOn, OUTPUT);
  pinMode(tankOn, OUTPUT);
  digitalWrite(levelHigh, HIGH);
  digitalWrite(subOff, HIGH);
  digitalWrite(subOnn, HIGH);
  digitalWrite(subOn, HIGH);
  digitalWrite(tankOn, HIGH);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;
  level = float(distanceCm) / 16.0;
  parts = 5.50 - float(level);
  delay(10);
  if (float(distanceCm) == 20.00)
  {
    digitalWrite(tankOn, HIGH);
    digitalWrite(subOff, LOW);
    delay(200);
    digitalWrite(subOff, HIGH);
  }
  while (Serial.available())
  {
    delay(10);
    char c = Serial.read();
    voice += c;
  }
  if (voice.length() > 0)
  {
    Serial.println(voice);
    if (voice == "SUBON")
    {
      digitalWrite(subOn, LOW);
      digitalWrite(subOnn, LOW);
      delay(200);
      digitalWrite(subOn, HIGH);
      digitalWrite(subOnn, HIGH);
    }
    if (voice == "SUBOFF")
    {
      digitalWrite(subOff, LOW);
      delay(200);
      digitalWrite(subOff, HIGH);
    }
    if (voice == "TANKON")
    {
      digitalWrite(tankOn, LOW);
    }
    if (voice == "TANKOFF")
    {
      digitalWrite(tankOn, HIGH);
    }
    if (voice == "LEVEL")
    {
      Serial.println(parts);
      delay(100);
    }
    voice = "";
  }
}
