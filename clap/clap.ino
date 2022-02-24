/*
 * Programme arduino qui permet d'allumer une lampe de chevet
 * avec une application android développée sous App inventor
 * 
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
  
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); // Initialisation de l'objet Leds
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

/******************************** Fonctions **************************************/

void drawLedOn() {
  // Allume le bandeau de Led
  FastLED.clear();
  for (int i=0; i< NUM_LEDS; i++) {
    leds[i].setRGB(255,255,255) ;
  }
  FastLED.show();
}

void drawLedOff() {
  // Eteint le Bandeau de Led
  FastLED.clear();
  for (int i=0; i< NUM_LEDS; i++) {
    leds[i].setRGB(0,0,0) ;
  }
  FastLED.show();
}

void buzzerAlarm() {
  // Allume le buzzer pendant 150 ms
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW);
}
