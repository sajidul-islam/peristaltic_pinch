#include <Arduino.h>

#include <Servo.h>


const int motor_pwm = 3; 
const int servoPin = 9;
const int potmotorPin = A0; 
const int potServoSpeedPin = A1; 
int angle = 0;
// Initialize the servo motor
Servo myServo;

int intervalMillis;      
unsigned long previousMillis = 0;  
bool increasing = true; 
void setup() {


  pinMode(motor_pwm,OUTPUT);
  
  myServo.attach(servoPin);


intervalMillis = 1000;

}

void loop() 
{


int sspeed = analogRead(potServoSpeedPin);
 

 intervalMillis = map(sspeed, 0, 1023, 5, 30);

  unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= intervalMillis) {
    previousMillis = currentMillis;

    if (increasing) {
      angle++;
      if (angle >= 90) {
        increasing = false;
      }
    } else {
      angle--;
      if (angle <= 40) {
        increasing = true;
      }
    }

    myServo.write(angle);
  }
}