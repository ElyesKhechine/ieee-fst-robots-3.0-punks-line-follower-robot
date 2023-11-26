
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
void setup() {

  //Encodeur left
  Serial.begin(9600);

  pinMode(2, INPUT);
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
  
  //Motor left
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);   
  //Motor right
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT); 

  //digitalWrite(10, LOW);
  //digitalWrite(11, LOW);
}
void loop() {
  digitalWrite(10,100);
    digitalWrite(11,0);
  
}
