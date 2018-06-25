#include <Wire.h>  
#include <LiquidCrystal_I2C.h> // Using version 1.2.1
 
// The LCD constructor - address shown is 0x27 - may or may not be correct for yours
// Also based on YWRobot LCM1602 IIC V1
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  

int sensorValue = 0;
int countOn;
int countOff;
int flag;
int timer;
int timer2;

void setup()
{
  lcd.begin(16,2); // sixteen characters across - 2 lines
  lcd.backlight();
  // first character - 1st line
  lcd.setCursor(0,0);
  lcd.print("Machine Status:");
  // 8th character - 2nd line 
  lcd.setCursor(1,1);
  lcd.print("--LOADING--");

  Serial.begin(9600);
}
 
 
void loop()
{
  sensorValue = analogRead(A0);
  //Serial.println(sensorValue);
  if (sensorValue < 200){
    countOn++;
    flag = 1;
    if (countOn > 50){
      lcd.setCursor(1,1);
      lcd.print("-- IN USE --");
    }
    timer = millis();
  }
  if (sensorValue > 200){
    countOff++;
    flag = 2;
    if (countOff > 50){
      lcd.setCursor(1,1);
      lcd.print("- AVAILABLE -");
    }
    timer2 = millis();
  }
  int value = timer2 - timer;
  if (value < 0)
    value = value*-1;
  Serial.print(flag);
  Serial.print("   ");
  Serial.println(value);
  if (value < 600){
    lcd.setCursor(1,1);
    lcd.print("- FINISHING -");
    countOn = 0;
    countOff = 0;
  }

}




