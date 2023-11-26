const int captDroit=7;
const int captGauche=4;
const int captExtDroit=;
const int captExtGauche=;
const int U1=;
const int U2=;
const int U3=;

int val=0;
int checkk=0;

const int moteurDroitAvant=;
const int moteurDroitDeriere=;


const int moteurGaucheAvant=;
const int moteurGaucheDeriere=;

bool etatCaptDroit;
bool etatCaptGauche;
bool etatCaptExtDroit;
bool etatCaptExtGauche;
bool etatU1;
bool etatU2;
bool etatU3;

//Encodeur
unsigned long int counterL = 0;
unsigned long int counterR = 0;

void ISRtrackAL() {
  int A = digitalRead(2);
  int B = digitalRead(3);

  if ((B && !A) || (A && !B)) {
    ++counterL;
  } else {
    --counterL;
  }
}
void ISRtrackCR() {
  int C = digitalRead(0);
  int D = digitalRead(1);

  if ((C && !D) || (C && !D)) {
    ++counterR;
  } else {
    --counterR;
  }
}
void ISRtrackBL() {
  int A = digitalRead(2);
  int B = digitalRead(3);

  if ((A && B) || (!A && !B)) {
    ++counterL;
  } else {
    --counterL;
  }
}
void ISRtrackDR() {
  int C = digitalRead(0);
  int D = digitalRead(1);

  if ((C && D) || (!C && !D)) {
    ++counterR;
  } else {
    --counterR;
  }
}
void Avancer()
{
analogWrite(moteurDroitAvant,100);
analogWrite(moteurGaucheAvant,100);
analogWrite(moteurDroitDeriere,0);
analogWrite(moteurGaucheDeriere,0);
}
void Droite()
{
analogWrite(moteurDroitAvant,0);
analogWrite(moteurGaucheAvant,100);
analogWrite(moteurDroitDeriere,100);
analogWrite(moteurGaucheDeriere,0);

}
void Gauche()
{
analogWrite(moteurDroitAvant,100);
analogWrite(moteurGaucheAvant,0);
analogWrite(moteurDroitDeriere,0);
analogWrite(moteurGaucheDeriere,100);

}
void setup() {
  Serial.begin(9600);
  //capteur
  pinMode(captDroit, INPUT);
  pinMode(captGauche, INPUT);
  pinMode(captCentre, INPUT);
  pinMode(captExtDroit, INPUT);
  pinMode(captExtGauche, INPUT);
  //Encodeur left
 /* pinMode(2, INPUT);
  pinMode(3, INPUT);  
  pinMode(0, INPUT);
  pinMode(1, INPUT); 
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(0, HIGH);
  digitalWrite(1, HIGH);
  attachInterrupt(digitalPinToInterrupt(2), ISRtrackAL, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), ISRtrackBL, CHANGE);
  attachInterrupt(digitalPinToInterrupt(0), ISRtrackCR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(1), ISRtrackDR, CHANGE);
  */
  //Motor Gauche
  pinMode(moteurGaucheAvant, OUTPUT);
  pinMode(moteurGaucheDeriere, OUTPUT);   
  //Motor Droite
  pinMode(moteurDroitAvant, OUTPUT);
  pinMode(moteurDroitDeriere, OUTPUT); 
}
void loop() {
etatCaptDroit=digitalRead(captDroit);
etatCaptGauche=digitalRead(captGauche);
etatCaptExtDroit=digitalRead(captExtDroit);
etatCaptExtGauche=digitalRead(captExtGauche);

if(checkk==0)
{
  switch (val=c3*1000+c1*100+c2*10+c4){
    case 0: 
    case 1:
    case 10:
    case 11:
    case 100:
    case 101:
    case 110:
    case 111:
    case 1000:
    case 1001:
    case 1010:
    case 1011:
    case 1100:
    case 1101:
    case 1110:
    case 1111:
default: delay(10);
  }
if(((etatcaptDroit && etatcaptGauche)))
Avancer();
}
if (!etatcaptExtGauche && !etatcaptExtDroit))  {
  Avancer();
}
if ((!etatcaptGauche && !etatcaptDroit) && etatcaptExtGauche)){
  Avancer();
}
else if((etatcaptGauche && !etatcaptDroit)||(etatcaptExtGauche && etatcaptExtDroit))
Droite();
else if((!etatcaptGauche && etatcaptDroit)||(!etatcaptExtGauche && etatcaptExtDroite))
{
Gauche();
}
}
checkk++;
if (checkk==1)
{if((etatcaptDroit && etatcaptGauche) && (etatU1 && etatU2))
Avancer();
}
checkk++;
if (checkk==2)
{
  if(!etatcaptGauche && !etatcaptDroit)
  Avancer();
  else if(etatcaptDroit && !etatcaptGauche)
  Droite();
  else if (!etatcaptDroit && etatcaptGauche)
  Gauche();
}
checkk++;
if(checkk==3)
{
}
}
