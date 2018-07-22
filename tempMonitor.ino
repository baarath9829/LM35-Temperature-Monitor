#include <LiquidCrystal.h>
#define rs 13   
#define en 12
#define d0 5     //data pins 
#define d1 4
#define d2 3
#define d3 2
#define tempPin 1    //analog pin for LM35
#define buzzer 9     //digital pin for buzzer
#define motor 2      //analog pin for DC motor
#define buttonin 1     //digital pin for override button
#define buttonout 6    //digital pin
#define pumpRelay 7    //digital pin for relay to use water pump
int val;
float lowTemp = 25.0;
float midTemp = 30.0;
float highTemp = 32.0;
float cel;

LiquidCrystal lcd(rs,en,d0,d1,d2,d3);

void alarm(){
  tone(buzzer, 1000); 
  delay(1000);       
  noTone(buzzer);     
  delay(1000); 
}
void LCDdisplay(){
  lcd.clear();
  lcd.print("Tire temperature has exceeded 25*C ");
}
void waterPump(){
  digitalWrite(pumpRelay, HIGH);
  delay(5000);   //5sec delay
  digitalWrite(pumpRelay, LOW);
}
void slow(){
  analogWrite(motor, 255/2);  // half speed
}
void disableSlow(){
  analogWrite(motor, 255);   //full speed
}
void setup()
{
  pinMode(buzzer, OUTPUT);
  pinMode(motor, OUTPUT);
  pinMode(tempPin, INPUT);
  pinMode(buttonin, INPUT);
  pinMode(buttonout, OUTPUT);
  pinMode(pumpRelay, OUTPUT);
  digitalWrite(buttonout, HIGH);
  digitalWrite(pumpRelay, LOW);
  lcd.clear();
  lcd.print("Tire Temperature is calculating");
  analogWrite(motor, 255);   //full speed
}
void loop()
{
val = analogRead(tempPin);
float mv = ( val/1024.0)*5000; 
cel = mv/10;
if (cel > highTemp){
  waterPump();
}
else if(cel > midTemp){
   slow();
}
else if(cel > lowTemp){
  alarm();
  LCDdisplay();
}
if (digitalRead(buttonin) == HIGH){
  disableSlow();
}
}
