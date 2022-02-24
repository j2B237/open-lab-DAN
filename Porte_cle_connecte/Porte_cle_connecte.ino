/*
 * Programme arduino qui permet de faire sonner un dispositif
 * placé sur un porte-clé lorsque l'utilisateur appuie 
 * sur un bouton depuis une application Android
 */
#include <FastLED.h>
#define NUM_LEDS 4
#define DATA_PIN 12

// Declaration de variables
int buzzerPin = 7;
int ledPin = 4;
int buttonPin = 8;
char incomingValue = 0;

// Variables for leds
CRGB leds[NUM_LEDS];

void setup() {
  // Initialisation de la communication entre arduino et le module HC-05
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(100);
  pinMode(buzzerPin, OUTPUT);     // Definit la broche connecté au buzzer en mode sortie
  pinMode(ledPin, OUTPUT);        // Définit la broche connectée à la led en mode sortie
  pinMode(buttonPin, INPUT_PULLUP);   // Définit le type de péripherie pour le bouton
  digitalWrite(buttonPin, HIGH);
  FastLED.clear();
  drawLedOff();
 
}

void loop() {
  // Boucle infinie
  if (Serial.available() > 0 ){
    incomingValue = Serial.read();    
    Serial.println(incomingValue);   

    if (incomingValue == '1')
    {
      digitalWrite(ledPin, HIGH);
      buzzerAlarm();
      drawLedOn();
      
    }
    // Lorsqu'il appuie sur OFF coupe le son et éteint la led
    else if(incomingValue == '0')
    {
      digitalWrite(ledPin, LOW);
      drawLedOff(); 
    }
  }
}


void drawLedOn() {
  FastLED.clear();
  for (int i=0; i< NUM_LEDS; i++) {
    leds[i].setRGB(255,255,255) ;
  }
  FastLED.show();
}

void drawLedOff() {
  FastLED.clear();
  for (int i=0; i< NUM_LEDS; i++) {
    leds[i].setRGB(0,0,0) ;
  }
  FastLED.show();
}

void buzzerAlarm() {
  digitalWrite(buzzerPin, HIGH);
  delay(150);
  digitalWrite(buzzerPin, LOW);
}
