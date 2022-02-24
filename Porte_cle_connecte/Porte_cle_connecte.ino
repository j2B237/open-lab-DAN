/*
 * Programme arduino qui permet de faire sonner un dispositif
 * placé sur un porte-clé lorsque l'utilisateur appuie 
 * sur un bouton depuis une application Android
 */

 #include <ArduinoBLE.h>
 

 // Declaration de variables
 int buzzerPin = 5;
 int ledPin = 4;
 int buttonPin = 8;
 char incomingValue = 0;
 
void setup() {
  // Initialisation de la communication entre arduino et le module HC-05
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);     // Definit la broche connecté au buzzer en mode sortie
  pinMode(ledPin, OUTPUT);        // Définit la broche connectée à la led en mode sortie
  pinMode(buttonPin, INPUT_PULLUP);   // Définit le type de péripherie pour le bouton
  digitalWrite(buttonPin, HIGH);
 
}

void loop() {
  // Boucle infinie
  if (Serial.available() > 0 ){
    incomingValue = Serial.read();    
    Serial.println(incomingValue);   

    if (incomingValue == '1')
    {
      digitalWrite(ledPin, HIGH);
      digitalWrite(buzzerPin, HIGH);
      
    }
    // Lorsqu'il appuie sur OFF coupe le son et éteint la led
    else if(incomingValue == '0')
    {
      digitalWrite(buzzerPin, LOW);
      digitalWrite(ledPin, LOW); 
    }

    
  }

}
