#include <Arduino.h>

#include <Servo.h>


const int motor_pwm = 5; 
const int motor1 = 6; 
const int motor2 = 7; 

const int servoPin = 9;
const int potmotorPin = A0; 
const int potServoSpeedPin = A1; 
int angle = 0;
// Initialize the servo motor
Servo myServo;

   
unsigned long previousMillis = 0;  
bool increasing = true; 
void setup() 
{
  pinMode(motor_pwm,OUTPUT);
  pinMode(motor1,OUTPUT);
  pinMode(motor2,OUTPUT);
  myServo.attach(servoPin);
}

void servocontrol();
void dc_motor_control();

void loop() 
{
  servocontrol();
  dc_motor_control();
  
}


void servocontrol()
{
  int sspeed = analogRead(potServoSpeedPin);
  int intervalMillis = map(sspeed, 0, 1023, 5, 30);

  unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= intervalMillis) {
    previousMillis = currentMillis;

    if (increasing) {
      angle++;
      if (angle >= 65) {
        increasing = false;
      }
    } else {
      angle--;
      if (angle <= 30) {
        increasing = true;
      }
    }

    myServo.write(angle);
  }
}



void dc_motor_control()
{
  digitalWrite(motor1,LOW);
  digitalWrite(motor2,HIGH);
  int dc_analog_value = analogRead(A0);
  int speed = map(dc_analog_value,0,1023,10,250);
  analogWrite(motor_pwm,speed); 
}