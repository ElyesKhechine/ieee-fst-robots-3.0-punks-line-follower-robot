const int captDroit=7;
const int captGauche=4;
const int captCentre=3;
const int captExtDroit=;
const int captExtGauche=;

bool etatCaptDroit;
bool etatCaptGauche;
bool etatCaptCentre;
bool etatCaptExtDroit;
bool etatCaptExtGauche;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
pinMode(captDroit, INPUT);
pinMode(captGauche, INPUT);
pinMode(captCentre, INPUT);
pinMode(captExtDroit, INPUT);
pinMode(captExtGauche, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
etatCaptDroit=digitalRead(captDroit);
etatCaptGauche=digitalRead(captGauche);
etatCaptCentre=digitalRead(captCentre);
etatCaptExtDroit=digitalRead(captExtDroit);
etatCaptExtGauche=digitalRead(captExtGauche);

/*if (!captDroit && !captGauche)
{
  if(!captExtGauche && captExtDroit)
  Serial.println("Tourner à gauche");
  else if(captExtGauche && !captExtDroit)
  Serial.println("Tourner à droite");
  else 
  Serial.println("Continuer tout droit");
}

else if(captDroit && captGauche)
{
if(!captExtGauche && captExtDroit)
  Serial.println("Tourner à gauche");
  else if(captExtGauche && !captExtDroit)
  Serial.println("Tourner à droite");
  else 
  Serial.println("Continuer tout droit");
}
else if (captDroit)
Serial.println("Tourner à gauche");
else 
Serial.println("Tourner à droite");
*/




}
