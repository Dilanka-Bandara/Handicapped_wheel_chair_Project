#include<Servo.h>
Servo servo;


#define enB 10
#define in3 6
#define in4 7


int motorSpeedB = 0;

void setup() {
  
  pinMode(enB, OUTPUT);
  
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  servo.attach(2);
}

void loop() {
  int xAxis = analogRead(A0); // Read Joysticks X-axis
  int yAxis = analogRead(A1); // Read Joysticks Y-axis
  int angle =map(xAxis,0,1023,0,180);
  servo.write(angle);
  // Y-axis used for forward and backward control
  if (yAxis < 470) {
    
    // Set Motor B backward
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
    
    motorSpeedB = map(yAxis, 470, 0, 0, 255);
  }
  else if (yAxis > 550) {
    
    // Set Motor B forward
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
    
    motorSpeedB = map(yAxis, 550, 1023, 0, 255);
  }
  // If joystick stays in middle the motors are not moving
  else {
    
    motorSpeedB = 0;
  }
  
  
  analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
}