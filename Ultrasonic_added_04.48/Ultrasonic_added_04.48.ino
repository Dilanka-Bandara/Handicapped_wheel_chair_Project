// Define pins for the ultrasonic sensor
const int trigPin = 12;
const int echoPin = 13; 

// Define pin for the buzzer
const int buzzer = 2;

// defines variables
long duration;
int distance;
int safetyDistance;

//Joystick signal pins
double x_pin = A0;  
double y_pin = A1;  

//Right motor driver pins
int R_PWM_right = 3; //PWM pin
int L_PWM_right = 5; //PWM pin

//Left motor driver pins
int R_PWM_left = 6; //PWM pin
int L_PWM_left = 9; //PWM pin

// ---**---   x threshold values
//FWD_BACK
int x_start_Fwd = 535;
int x_End_Fwd = 1023;
//BACK
int x_start_Bac = 490;
int x_End_Bac = 0;

// ---**---   y threshold values
//LEFT_RIGHT
int y_start_right = 535;
int y_End_right = 1023;
//RIGHT
int y_start_left = 490;
int y_End_left = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT); 
  pinMode(9,OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);

}

void loop()
{
//Receive analog pins data
double x_data = analogRead(x_pin);
double y_data = analogRead(y_pin);

Serial.print("x: ");
Serial.println(x_data);
Serial.print("         \t");
Serial.print("y: ");
Serial.print(y_data);
Serial.println("");

//Speed mapping based on x
int spdFwd_RightLeft = map(x_data, x_start_Fwd, x_End_Fwd, 0, 255);   
int spdBac_RightLeft = map(x_data, x_start_Bac, x_End_Bac, 0, 255); 

//Speed mapping based on y
int spdFwd_RightLeft_y = map(y_data, y_start_right, y_End_right, 0, 255);   
int spdBac_RightLeft_y = map(y_data, y_start_left, y_End_left, 0, 255); 

//FWD
if(x_data>x_start_Fwd)
{  delay(250);   
analogWrite(R_PWM_right,0);
analogWrite(L_PWM_right,spdBac_RightLeft); 
analogWrite(R_PWM_left,0);
analogWrite(L_PWM_left,spdBac_RightLeft); 
  //.......

  
  // Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;

safetyDistance = distance;
if (safetyDistance <= 150){
  digitalWrite(buzzer, HIGH);
  //digitalWrite(ledPin, HIGH);
}
else{
  digitalWrite(buzzer, LOW);
  //digitalWrite(ledPin, LOW);
}

// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
  
  //.......
}
//RIGHT
else if(y_data>y_start_right)
{ delay(250);
analogWrite(R_PWM_right,0);
analogWrite(L_PWM_right,spdFwd_RightLeft_y);
analogWrite(R_PWM_left,spdFwd_RightLeft_y);
analogWrite(L_PWM_left,0);
}
//LEFT
else if(y_data<y_start_left)
{ delay(250);    
analogWrite(R_PWM_right,spdBac_RightLeft_y);
analogWrite(L_PWM_right,0);
analogWrite(R_PWM_left,0);
analogWrite(L_PWM_left,spdBac_RightLeft_y);
}
//BACK
else if(x_data<x_start_Bac)
{ delay(250) ;
analogWrite(R_PWM_right,spdFwd_RightLeft);
analogWrite(L_PWM_right,0);
analogWrite(R_PWM_left,spdFwd_RightLeft);
analogWrite(L_PWM_left,0); 
}
else
{     
analogWrite(R_PWM_right,0);
analogWrite(L_PWM_right,0);
analogWrite(R_PWM_left,0);
analogWrite(L_PWM_left,0);
}

}