#include <Wire.h>  
#include <LiquidCrystal_I2C.h> // Using version 1.2.1

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  

int sensorVal = 0;
int sensorPin = A0;
int motorTrig = 13;
volatile int pumpState = 0;

void setup() {
  lcd.begin(16,2); // sixteen characters across - 2 lines
  lcd.backlight();
  // first character - 1st line
  lcd.setCursor(0,0);
  lcd.print("Water Level:");
  lcd.setCursor(1,1);
  lcd.print("--LOADING--");
  
  pinMode(motorTrig, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  sensorVal = analogRead(sensorPin);
  Serial.print(pumpState);
  Serial.print(" ");
  Serial.println(sensorVal);
  lcd.setCursor(0,1);
  lcd.print(sensorVal);
  delay(50);
  lcd.setCursor(3,1);
  lcd.print("------>");
  delay(200);
  //dry = 1023 wet = 0
  if (sensorVal > 700)  { // EDIT SENSORVAL BASED ON YOUR PLANT. 
    digitalWrite(motorTrig,HIGH);
    pumpState = 1;
    lcd.print("ON");
    delay(200);
  }
  else if (sensorVal <= 600)  {
    digitalWrite(motorTrig,LOW);
    pumpState = 0;
    lcd.print("OFF");
    delay(200);
  }
}
