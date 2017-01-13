//i2c Master Code(UNO)
#include <Wire.h>

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Wire.begin();
  digitalWrite(13, LOW);
}

void loop()
{
  while(Serial.available())
  {
    char c = Serial.read();
    
    if(c == 'H')
    {
      Serial.print("char:");
      Serial.println(c);
      Wire.beginTransmission(1);
      Wire.write('H');
      Wire.endTransmission();
      digitalWrite(13, HIGH);
    }
    else if(c == 'L')
    {
      Serial.print("char:");
      Serial.println(c);
      Wire.beginTransmission(1);
      Wire.write('L');
      Wire.endTransmission();
      digitalWrite(13, LOW);
    }
  }
}
