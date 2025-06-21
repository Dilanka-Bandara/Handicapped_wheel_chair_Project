const int LRpin =A0;
const int UDpin =A1;

int LR;
int UD;


int LR_neutral;
int UD_neutral;


const int Rpin=11;
const int Ypin=10;
const int Gpin=6;
const int Bpin=9;


int R;
int Y;
int G;
int B;


const int deadZone =1;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

LR_neutral=analogRead(LRpin);
UD_neutral=analogRead(UDpin);
}

void loop() {
  // put your main code here, to run repeatedly:
  LR = analogRead(LRpin);
  UD = analogRead(UDpin);


  if(UD>=UD_neutral-deadZone)
  {
    B=0;
    R= map(UD,UD_neutral+deadZone,1023,0,255);


  }
  else if(UD<=UD_neutral-deadZone)
  {
    R=0;
    B=map(UD,UD_neutral,0,0,255);
  }
  else 
  {
    R=0;
    B=0;
  }



  if(LR>=LR_neutral+deadZone)
  {
    Y=0;
    G= map(LR,LR_neutral+deadZone,1023,0,255);


  }
  else if(LR<=LR_neutral-deadZone)
  {
    G=0;
    Y=map(LR,LR_neutral,0,0,255);
  }
  else 
  {
    G=0;
    Y=0;
  }


  analogWrite(Rpin,R);
  analogWrite(Ypin,Y);
  analogWrite(Bpin,B);
  analogWrite(Gpin,G);




  

}
