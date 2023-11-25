//Ultrason
const byte TRIGGERleft = 8; // broche TRIGGER
const byte ECHOleft= A1; // broche ECHO

const byte TRIGGERright = 7; // broche TRIGGER
const byte ECHOright= A0; // broche ECHO

const byte TRIGGERfront = 4; // broche TRIGGER
const byte ECHOfront= 9; // broche ECHO

const unsigned long MEASURE_TIMEOUT = 25000UL;
const float SOUND_SPEED = 340.0 / 1000;

//PDUltrason
float distL,distR,kpULTRA=1,kdULTRA=0,erreurancien,erreur,PD=0,P,D;


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

float right = 0.00;
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

float distanceleft() {
  digitalWrite(TRIGGERleft, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGERleft, LOW);
  long measure = pulseIn(ECHOleft, HIGH, MEASURE_TIMEOUT);
  float distance_mm = measure / 2.0 * SOUND_SPEED;
  return(distance_mm);
}
float distanceright() {
  digitalWrite(TRIGGERright, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGERright, LOW);
  long measure = pulseIn(ECHOright, HIGH, MEASURE_TIMEOUT);
  float distance_mm = measure / 2.0 * SOUND_SPEED;
  return(distance_mm);
}
float distancefront() {
  digitalWrite(TRIGGERfront, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGERfront, LOW);
  long measure = pulseIn(ECHOfront, HIGH, MEASURE_TIMEOUT);
  float distance_mm = measure / 2.0 * SOUND_SPEED;
  return(distance_mm);
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
  float rightPD= rightPD+p + d;

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
  float leftPD= leftPD+ p + d;

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
void PdUltrason(){
  float erreurancien=erreur ; 
  float erreur=distL-distR;
  float P=kpULTRA*erreur;
  float D=kdULTRA*(erreurancien-erreur);
  float PD=PD+P+D;
  if (PD>255)
    PD=255;
  if (PD<-255)
    PD=-255;
  if (PD>=0){
    
  }
  if (PD<=0){
    
  }
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
  distL=distanceleft();
  distR=distanceright();

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
  analogWrite(ECHOleft, 0);
  
  pinMode(TRIGGERright, OUTPUT);
  digitalWrite(TRIGGERright, LOW);
  pinMode(ECHOright, INPUT);
  analogWrite(ECHOright, 0);
    
  pinMode(TRIGGERfront, OUTPUT);
  digitalWrite(TRIGGERfront, LOW);
  pinMode(ECHOfront, INPUT);
  digitalWrite(ECHOfront, LOW);
 
}

//Checkpoint1
int t = 0;
int checkpoint1=0;
float test1=0,test2=0;

void loop() {
  c1 = digitalRead(captExtDroit);
  c2 = digitalRead(captDroit);
  c3 = digitalRead(captGauche);
  c4 = digitalRead(captExtGauche);
  
  etatcapteur = c1 * 1000 + c2 * 100 + c3 * 10 + c4;
  test1=millis();
if (t==1)
  if (test1-test2>=500)
      checkpoint1=1;
if (checkpoint1==0)
  switch (etatcapteur) {
    case 0:
    if ( t== 0){
      test2=millis();
      t=1;
    }
      Avancer(90);
      break;
    case 1:
      Gauche(90);
      break;
    case 10:
      Gauche(90);
      break;
    case 11:
      Avancer(90);
      break;
    case 100:
      Droite(90);
      break;
    case 101:
      Gauche(90);
      break;
    case 110:
      Avancer(90);
      break;
    case 111:
      Gauche(90);
      break;
    case 1000:
      Droite(90);
      break;
    case 1001:
      Avancer(90);
      break;
    case 1010:
      Droite(90);
      break;
    case 1011:
      Avancer(90);
      break;
    case 1100:
      Avancer(90);
      break;
    case 1101:
      Avancer(90);
      break;
    case 1110:
      Droite(90);
      break;
    case 1111:
      Avancer(90);
      break;
    default:
      Stop();
        break;
}
if (checkpoint1==1)
  switch (etatcapteur) {
    case 0:
      Gauche(90);
      break;
    case 1:
      Gauche(90);
      break;
    case 10:
      Gauche(90);
      break;
    case 11:
      Avancer(90);
      break;
    case 100:
      Droite(90);
      break;
    case 101:
      Gauche(90);
      break;
    case 110:
      Avancer(90);
      break;
    case 111:
      Gauche(90);
      break;
    case 1000:
      Droite(90);
      break;
    case 1001:
      Avancer(90);
      break;
    case 1010:
      Droite(90);
      break;
    case 1011:
      Avancer(90);
      break;
    case 1100:
      Avancer(90);
      break;
    case 1101:
      Avancer(90);
      break;
    case 1110:
      Droite(90);
      break;
    case 1111:
      Avancer(90);
      break;
    default:
      Stop();
        break;
}
}
