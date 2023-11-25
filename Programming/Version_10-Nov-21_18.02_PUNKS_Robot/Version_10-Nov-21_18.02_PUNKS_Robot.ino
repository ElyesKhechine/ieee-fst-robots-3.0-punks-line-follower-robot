const int captDroit=12;
const int captGauche=11;
const int captExtDroit=13;
const int captExtGauche=10;
//const int U1=;
//const int U2=;
//const int U3=;

int checkK=0;

const int moteurDroitAvant = 6;
const int moteurDroitDeriere = 9;

const int moteurGaucheAvant = 5;
const int moteurGaucheDeriere = 3;

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
digitalWrite(moteurDroitAvant,150);
digitalWrite(moteurGaucheAvant,150);
digitalWrite(moteurDroitDeriere,0);
digitalWrite(moteurGaucheDeriere,0);
}
void Droite()
{
digitalWrite(moteurDroitAvant,0);
digitalWrite(moteurGaucheAvant,100);
digitalWrite(moteurDroitDeriere,100);
digitalWrite(moteurGaucheDeriere,0);

}
void Gauche()
{
digitalWrite(moteurDroitAvant,100);
digitalWrite(moteurGaucheAvant,0);
digitalWrite(moteurDroitDeriere,0);
digitalWrite(moteurGaucheDeriere,100);

}
void setup() {
  Serial.begin(9600);
  //capteur
  pinMode(captDroit, INPUT);
  pinMode(captGauche, INPUT);
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
/*
if(checkk=0)
{
if(((etatcaptDroit && etatcaptGauche) || (!etatcaptExtGauche && !etatcaptExtDroit)) || ((!etatcaptGauche && !etatcaptDroit) && etatcaptExtGauche))
{
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
}*/
Serial.println(etatCaptExtDroit);
}
