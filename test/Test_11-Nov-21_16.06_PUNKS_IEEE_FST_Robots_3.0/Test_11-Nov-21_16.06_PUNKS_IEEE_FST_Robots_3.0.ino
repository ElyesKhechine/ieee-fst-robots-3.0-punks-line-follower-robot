
// Capteurs IR
const int captExtDroit=10;
const int captDroit=11;
const int captGauche=12;
const int captExtGauche=13;
bool c1;
bool c2;
bool c3;
bool c4;
int etatcapteur = 0;

//Moteurs
const int moteurDroitAvant=9;
const int moteurDroitDeriere=6;
const int moteurGaucheAvant=5;
const int moteurGaucheDeriere=3;

const float vitesse = 300.00;
float kp = 1.0;
float ki = 0.001;
float kd = 1.0;


int checkk=0;

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
void Stop() 
{
analogWrite(moteurDroitAvant,0);
analogWrite(moteurGaucheAvant,0);
analogWrite(moteurDroitDeriere,0);
analogWrite(moteurGaucheDeriere,0);
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
c2=digitalRead(captDroit);
c3=digitalRead(captGauche);
c1=digitalRead(captExtDroit);
c4=digitalRead(captExtGauche);
etatcapteur = c1 * 1000 + c2 * 100 + c3 * 10 + c4;
//Serial.println(etatcapteur);
if(checkk==0){ 
  Serial.println(etatcapteur);
  switch(etatcapteur) {
      case 0:
            Avancer();
    break; 
      case 1:
            Gauche();
    break; 
      case 10:
            Gauche();
    break; 
      case 11:
            Gauche();
    break; 
      case 100:
            Droite();
    break; 
      case 101:
            Gauche();
    break; 
      case 110:
            Avancer();
    break; 
      case 111:
            Gauche();
    break; 
      case 1000:
            Droite();
    break; 
      case 1001:
            Avancer();
    break; 
      case 1010:
            Droite();
    break; 
      case 1011:
            Droite();
    break; 
      case 1100:
            Droite();
    break; 
      case 1101:
            Droite();
    break; 
      case 1110:
            Droite();
    break; 
      case 1111:
            Droite
            
            ();
    break; 
    default: 
      Stop();
      break;
  }
}
}
/*
if(((etatCaptDroit && etatCaptGauche) || (!etatCaptExtGauche && !etatCaptExtDroit)) || ((!etatCaptGauche && !etatCaptDroit) && etatCaptExtGauche))
{
Avancer();
}
else if((etatCaptGauche && !etatCaptDroit)||(etatCaptExtGauche && etatCaptExtDroit))
{Droite();}
else if((!etatCaptGauche && etatCaptDroit)||(!etatCaptExtGauche && etatCaptExtDroit))
{Gauche();}
}
}*/
/*
checkk++;
if (checkk==1)
{if((etatcaptDroit && etatcaptGauche) && (etatU1 && etatU2))
Avancer();
}
checkk++;
if (checkk==2)
{
  if(!etatCaptGauche && !etatCaptDroit)
  Avancer();
  else if(etatCaptDroit && !etatCaptGauche)
  Droite();
  else if (!etatCaptDroit && etatCaptGauche)
  Gauche();
}
checkk++;
//MAZE CODE
if(checkk==3)
{
}
}*/

 
