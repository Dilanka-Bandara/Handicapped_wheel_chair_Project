#define enA 9
#define in1 6
#define in2 7
#define button 4

boolean buttonState =LOW;
int rotDirection =0;
int pressed = false;




void setup() {
  // put your setup code here, to run once:

  pinMode(enA,OUTPUT);
  pinMode(in1,INPUT);
  pinMode(in2,INPUT);
  pinMode(button,INPUT);

  //Set the initial rotation direction

  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  int potValue = analogRead(A0); // read the potentio meter value
  int pmwOutput = map(potValue,0,1023,0,255);
  analogWrite(enA,pmwOutput);

  //Read botton -debounce 
  if(digitalRead(button)==true)
  {
    pressed=!pressed;
  }

  while(digitalRead(button)==true)
  {
    delay(20);
  }

  //if button pressed - chanfge the direction 

  if(pressed == true & rotDirection ==0)
  {
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    rotDirection =1;
    delay(20);
  }

  if(pressed == false & rotDirection ==1)
  {
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    rotDirection =1;
    delay(20);
  }



}
