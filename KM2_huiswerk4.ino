#include <Servo.h>
#define PIN_LED 11
#define STEP_FORWARD 10
#define STEP_BACK -10
#define buttonPIN 2

volatile byte state = LOW;

Servo myServo;

int ledState = LOW;
long ledChangeTime = 0L;
int buttonState = 0;

int servoState = STEP_FORWARD;
int servoPos = 0;
long servoStepTime = 0L;

void setup() {
  Serial.begin(9600);
  myServo.attach(9);

  pinMode(11, OUTPUT);
  pinMode(buttonPIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), buttonISR, CHANGE);
  
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(A0);
  Serial.print("value=");
  Serial.println(value);  

  long currentTimeMS = millis();

  digitalWrite(11, state);

  
    
  if (currentTimeMS - servoStepTime > 200) {
    myServo.write(servoPos);
    servoStepTime = currentTimeMS;
    if (servoState == STEP_FORWARD) {
      servoPos +=80;
    } else {
      servoPos -=80;
    }
  }

  if (servoPos > 180) {
    servoPos = 180;
    servoState = STEP_BACK;
  } 
  if (servoPos < 0) {
    servoPos = 0;
    servoState = STEP_FORWARD;
  }
  
}

void buttonISR() {
  state = !state;
}



