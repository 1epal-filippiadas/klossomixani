#include  <Wire.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);
#define DHTTYPE DHT21
#define dht_dpin 15
DHT dht(dht_dpin, DHTTYPE);
const int light =  33;
const int fan =  25;
const int buttonPinA = 32;   
const int buttonPinB = 12; 
const int ledPin1 =  26;      
const int ledPin2 =  27;
const int limitTemp =  37.5;
const int limitHum =  60;

int buttonStateA = 0;   
int buttonStateB = 0;  
int dir;
float day = 1;
void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init(); 
  lcd.backlight(); 
  pinMode(fan, OUTPUT); 
  pinMode(light, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(buttonPinA, INPUT_PULLUP);
  pinMode(buttonPinB, INPUT_PULLUP);
  
  digitalWrite(ledPin2, LOW);
 // digitalWrite(ledPin3, LOW);
 // digitalWrite(ledPin4, LOW);
  digitalWrite(ledPin1, LOW);
  digitalWrite(light, LOW);
  digitalWrite(fan, LOW);
}
  
 void loop() {
   
   buttonStateA = digitalRead(buttonPinA);
   buttonStateB = digitalRead(buttonPinB);
   
    Serial.print( buttonStateB);
     Serial.print("  ");
     Serial.print( buttonStateA );
     Serial.print("  ");
     Serial.println(dir);
 
     Serial.print("Day=  ");
     Serial.println(day);
     dir=0;
     kinisiarist();
   
     if (buttonStateB == 0&& dir==0) {
      stopMove();
      metriseis();
       dir=1;
       }
     
      
     if (buttonStateB == 0&& dir==1) {
      kinisiadexia();
      stopMove();
      metriseis();
     // dir=1;
      }
     
 }
 
  void stopMove() {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
   // digitalWrite(ledPin3, LOW);
  //  digitalWrite(ledPin4, LOW);
  }
  
 
 void kinisiarist(){
 if (buttonStateB == 1)
 {
  Serial.println("ARISTERA");
  digitalWrite(ledPin2, LOW);
 // digitalWrite(ledPin3, LOW);
 // digitalWrite(ledPin4, HIGH);
  digitalWrite(ledPin1, HIGH);
 }
 else
 {
  stopMove();
 }
 }
void kinisiadexia(){
int j=0;
 Serial.println("DEJIA");
 Serial.print( dir);
     Serial.print("  ");
     Serial.print( buttonStateB);
     Serial.print("  ");
     Serial.println( buttonStateA);
  digitalWrite(ledPin2, HIGH);
  //digitalWrite(ledPin3, HIGH);
  //digitalWrite(ledPin4, LOW);
  digitalWrite(ledPin1, LOW);

 for (j=1; j<=20000; j++){
   buttonStateA = digitalRead(buttonPinA);
  Serial.println( j);
  if (buttonStateA==0){
    j=1;
    break;
  }

 }
}

 void metriseis() {
   int i=1;
  for (i=1 ; i<=360;i++){
      Serial.print(i);
      Serial.print("  ");
      Serial.print(dht.readTemperature());
      Serial.print("  ");
      Serial.println(dht.readHumidity());
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Humidity:");
    lcd.setCursor(13,0);
    lcd.print(dht.readHumidity());
    lcd.setCursor(0,1);
    lcd.print("Temperature:");
    lcd.setCursor(13,1);
    lcd.print(dht.readTemperature());
    lcd.setCursor(0,2);
    lcd.print("start incub:");
    lcd.setCursor(13,2);
    lcd.print("3/5/22");
    lcd.setCursor(0,3);
    lcd.print("day:");
    lcd.setCursor(13,3);
    lcd.print(day);
      delay(60000);
   if (dht.readTemperature()>limitTemp)
    {   
    digitalWrite(light, HIGH);
    }
       else
    {   
      digitalWrite(light, LOW);
    } 
    if (dht.readHumidity()>limitHum)
    {   
    digitalWrite(fan, HIGH);
    }
       else
    {   
      digitalWrite(fan, LOW);
    } 
   
  }
   day=day+0.25; 
}
