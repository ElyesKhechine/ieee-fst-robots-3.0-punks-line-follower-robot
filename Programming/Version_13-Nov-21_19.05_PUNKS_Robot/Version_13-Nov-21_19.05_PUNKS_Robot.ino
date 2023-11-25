/Ultrason
const byte TRIGGERleft = 8; // broche TRIGGER
const byte ECHOleft= A1; // broche ECHO

const byte TRIGGERright = 7; // broche TRIGGER
const byte ECHOright= A0; // broche ECHO

const byte TRIGGERfront = 4; // broche TRIGGER
const byte ECHOfront= 9; // broche ECHO

const unsigned long MEASURE_TIMEOUT = 25000UL;
const float SOUND_SPEED = 340.0 / 1000;

//PDUltrasoN
float kpULTRA=0.01,kdULTRA=0,erreurancien,erreur,PD=0,P,D;

long distL=0,distR=0,distF=0;

// Echantillonnage
const float periode = 20.00;

// Capteurs IR
const int captExtDroit = A2;
const int captDroit = A3;
const int captGauche = A4;
const int captExtGauche = A5;
bool c1;
bool c2;
bool c3;
bool c4;
int etatcapteur = 0;

// PID vitesse
const float vitesseMax = 300.00;
const float accelerationMax = 5000.00;

float kp = 1.0;
float ki = 0.001;
float kd = 1.0;

float erreurAVR = 0.00;
float erreurAVL = 0.00;

float rightPD = 0.00;
float leftPD = 0.00;

// Moteurs
const int moteurDroitAvant = 11;
const int moteurDroitDeriere = 10;
const int moteurGaucheAvant = 5;
const int moteurGaucheDeriere = 6;

// Encodeurs
long int counterL = 0;
long int counterR = 0;

long int previousCounterL = 0;
long int previousCounterR = 0;

int resolution = 400;
float diametreRoue = 70.00;


const int pinAR=2;
const int pinBR=12;
const int pinAL=3;
const int pinBL=13;

void distanceleft() {
  digitalWrite(TRIGGERleft, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGERleft, LOW);
  long measure = pulseIn(ECHOleft, HIGH, MEASURE_TIMEOUT);
  distL = measure / 2.0 * SOUND_SPEED;
}
void distanceright() {
  digitalWrite(TRIGGERright, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGERright, LOW);
  long measure = pulseIn(ECHOright, HIGH, MEASURE_TIMEOUT);
  distR = measure / 2.0 * SOUND_SPEED;
  //Serial.println(distR);
}
float distancefront() {
  digitalWrite(TRIGGERfront, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGERfront, LOW);
  long measure = pulseIn(ECHOfront, HIGH, MEASURE_TIMEOUT);
  distF = measure / 2.0 * SOUND_SPEED;
}
void ISRtrackAR() {
  int A = digitalRead(pinAR);
  int B = digitalRead(pinBR);

  if ((B && !A) || (A && !B)) {
    ++counterL;
  } else {
    if ((B && A) || (!A && !B)) {
      --counterL;
    }
  }
}

void ISRtrackAL() {
  int A = digitalRead(pinAL);
  int B = digitalRead(pinBL);

  if ((B && !A) || (A && !B)) {
    ++counterL;
  } else {
    if ((B && A) || (!A && !B)) {
      --counterL;
    }
  }
}

void vitesseDroit(float consigne) {
  float vitesseActuel = (((counterR - previousCounterR) * diametreRoue * PI ) / resolution) / (periode / 1000);
  float erreur = consigne - vitesseActuel;
  if ((erreur * 1000) / periode) {
    erreur = accelerationMax;
  }
  float p = kp * erreur;
  float d = kd * (erreur - erreurAVR);
  rightPD += p + d;

  if (rightPD >= 0) {
    if (rightPD > 255) {
      rightPD = 255;
    }
    analogWrite(moteurDroitAvant, rightPD);
    analogWrite(moteurDroitDeriere, 0);
  } else {
    if (rightPD < - 255) {
      rightPD = - 255;
    }
    analogWrite(moteurDroitAvant, abs(rightPD));
    analogWrite(moteurDroitDeriere, 0);
  }
}

void vitesseGauche(float consigne) {
  float vitesseActuel = (((counterL - previousCounterL) * diametreRoue * PI ) / resolution) / (periode / 1000);
  float erreur = consigne - vitesseActuel;
   if ((erreur * 1000) / periode) {
    erreur = accelerationMax;
  }
  float p = kp * erreur;
  float d = kd * (erreur - erreurAVL);
  leftPD += p + d;

  if (leftPD >= 0) {
    if (leftPD > 255) {
      leftPD = 255;
    }
    analogWrite(moteurDroitAvant, leftPD);
    analogWrite(moteurDroitDeriere, 0);
  } else {
    if (leftPD < - 255) {
      leftPD = - 255;
    }
    analogWrite(moteurDroitAvant, abs(leftPD));
    analogWrite(moteurDroitDeriere, 0);
  }
}
float testFront = 0.00;
float pdultrason = 0;
void PdUltrason(){
 
  float erreurancien=erreur ; 
  float erreur=distL-distR;
  float P=kpULTRA*erreur;
  float D=kdULTRA*(erreurancien-erreur);
  pdultrason+=P+D;
  
  if (pdultrason>150)
    pdultrason=150;
  if (pdultrason<-150)
    pdultrason=-150;
  if (erreur >60) 
  {
    Gauche(pdultrason) ;
    }
    if(erreur<60) {
      Droite(pdultrason) ;
    }
   else {
     Avancer(70);
    }
  
  testFront += 110 - kpULTRA;
  if (testFront>80)
    testFront=80;
  if (testFront<-80)
    testFront=-80;

  testFront = abs(testFront);
  
  if (pdultrason>=0){   
  analogWrite(moteurDroitAvant,   testFront + pdultrason);
  if ( testFront - pdultrason < 0)
  analogWrite(moteurGaucheAvant, 0);
  else 
    analogWrite(moteurGaucheAvant, testFront - pdultrason);
  analogWrite(moteurDroitDeriere, 0);
  analogWrite(moteurGaucheDeriere, 0); 
  }
  if (pdultrason<=0){
  if ( testFront - abs(pdultrason) < 0)
    analogWrite(moteurDroitAvant, 0);
  else 
  analogWrite(moteurDroitAvant, testFront - abs(pdultrason));
  analogWrite(moteurGaucheAvant, testFront + abs(pdultrason));
  analogWrite(moteurDroitDeriere, 0);
  analogWrite(moteurGaucheDeriere, 0);
  }
  Serial.println(testFront + abs(pdultrason));
}
void Avancer(int pwm)
{
  analogWrite(moteurDroitAvant, pwm);
  analogWrite(moteurGaucheAvant, pwm);
  analogWrite(moteurDroitDeriere, 0);
  analogWrite(moteurGaucheDeriere, 0);
}
void Droite(int pwm)
{
  analogWrite(moteurDroitAvant, 0);
  analogWrite(moteurGaucheAvant, pwm);
  analogWrite(moteurDroitDeriere, pwm);
  analogWrite(moteurGaucheDeriere, 0);

}
void Gauche(int pwm)
{
  analogWrite(moteurDroitAvant, pwm);
  analogWrite(moteurGaucheAvant, 0);
  analogWrite(moteurDroitDeriere, 0);
  analogWrite(moteurGaucheDeriere, pwm);
}
void Stop()
{
  analogWrite(moteurDroitAvant, 0);
  analogWrite(moteurGaucheAvant, 0);
  analogWrite(moteurDroitDeriere, 0);
  analogWrite(moteurGaucheDeriere, 0);
}
void setup() {
  Serial.begin(9600);

  // Capteurs IR
  pinMode(captDroit, INPUT);
  pinMode(captGauche, INPUT);

  pinMode(captExtDroit, INPUT);
  pinMode(captExtGauche, INPUT);

  digitalWrite(captDroit, HIGH);
  digitalWrite(captDroit, HIGH);

  digitalWrite(captExtDroit, HIGH);
  digitalWrite(captExtGauche, HIGH);

  // Encodeurs
 

  pinMode(pinAR, INPUT);
  pinMode(pinAL, INPUT);

  pinMode(pinBR, INPUT);
  pinMode(pinBL, INPUT);

  digitalWrite(pinAR, INPUT);
  digitalWrite(pinAL, INPUT);

  digitalWrite(pinBR, INPUT);
  digitalWrite(pinBL, INPUT);

  attachInterrupt(digitalPinToInterrupt(pinAR), ISRtrackAR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinAL), ISRtrackAL, CHANGE);

  //Moteurs
  pinMode(moteurGaucheAvant, OUTPUT);
  pinMode(moteurGaucheDeriere, OUTPUT);

  pinMode(moteurDroitAvant, OUTPUT);
  pinMode(moteurDroitDeriere, OUTPUT);

  digitalWrite(moteurGaucheAvant, LOW);
  digitalWrite(moteurGaucheDeriere, LOW);

  digitalWrite(moteurDroitAvant, LOW);
  digitalWrite(moteurDroitDeriere, LOW);

//Ultrason
  pinMode(TRIGGERleft, OUTPUT);
  digitalWrite(TRIGGERleft, LOW);
  pinMode(ECHOleft, INPUT);
  //analogWrite(ECHOleft, 0);
  
  pinMode(TRIGGERright, OUTPUT);
  digitalWrite(TRIGGERright, LOW);
  pinMode(ECHOright, INPUT);
  //analogWrite(ECHOright, 0);
    
  pinMode(TRIGGERfront, OUTPUT);
  digitalWrite(TRIGGERfront, LOW);
  pinMode(ECHOfront, INPUT);
  //digitalWrite(ECHOfront, LOW);

}

int checkpoint1=0;

void loop() {
  distanceright();
  distanceleft();
  distancefront();
  PdUltrason();
/*
//  PdUltrason();
  c1 = digitalRead(captExtDroit);
  c2 = digitalRead(captDroit);
  c3 = digitalRead(captGauche);
  c4 = digitalRead(captExtGauche);
  
  etatcapteur = c4 * 1000 + c3 * 100 + c2 * 10 + c1;
if (checkpoint1==0)
  switch (etatcapteur) {
    case 0:
      Avancer(80);
      checkpoint1=1;
      break;
    case 1:
      Droite(80);
      break;
    case 10:
      Droite(80);
      break;
    case 11:
      Droite(80);
      break;
    case 100:
      Gauche(80);
      break;
    case 101:
      Avancer(80);
      break;
    case 110:
      Avancer(80);
      break;
    case 111:
      Droite(80);
      break;
    case 1000:
      Gauche(80);
      break;
    case 1001:
      Avancer(80);
      break;
    case 1010:
      Droite(80);
      break;
    case 1011:
      Avancer(80);
      break;
    case 1100:
      Gauche(80);
      break;
    case 1101:
      Avancer(80);
      break;
    case 1110:
      Gauche(80);
      break;
    case 1111:
      Avancer(80);
      break;
    default:
      Stop();
        break;
  }       
if (checkpoint1==1)
   switch (etatcapteur) {
    case 0:
      Avancer(140);
      break;
    case 1:
      Droite(140);
      break;
    case 10:
      Droite(140);
      break;
    case 11:
      Droite(140);
      break;
    case 100:
      Gauche(140);
      break;
    case 101:
      Avancer(140);
      break;
    case 110:
      Avancer(140);
      break;
    case 111:
      Gauche(140);
      break;
    case 1000:
      Gauche(140);
      break;
    case 1001:
      Avancer(140);
      break;
    case 1010:
      Droite(140);
      break;
    case 1011:
      Avancer(140);
      break;
    case 1100:
      Gauche(140);
      break;
    case 1101:
      Avancer(140);
      break;
    case 1110:
      Gauche(140);
      break;
    case 1111:
      Avancer(140);
      break;
    default:
      Stop();
        break;
  }
  */
  
  
}
