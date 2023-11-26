
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

void ISRtrackBL() {
  int A = digitalRead(2);
  int B = digitalRead(3);

  if ((A && B) || (!A && !B)) {
    ++counterL;
  } else {
    --counterL;
  }
}
void setup() {

  //Encodeur left
  Serial.begin(9600);

  pinMode(2, INPUT);
  pinMode(3, INPUT);  

  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  attachInterrupt(digitalPinToInterrupt(2), ISRtrackAL, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), ISRtrackBL, CHANGE);

  
  //Motor left
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);   

  //digitalWrite(10, LOW);
  //digitalWrite(11, LOW);
}
void loop() {
  digitalWrite(10,100);
    digitalWrite(11,0);
  
}
