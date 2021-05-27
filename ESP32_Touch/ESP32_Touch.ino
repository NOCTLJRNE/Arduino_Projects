/*
  ESP8266 Blink by Simon Peter
  Blink the blue LED on the ESP-01 module
  This example code is in the public domain

  The blue LED on the ESP-01 module is connected to GPIO1
  (which is also the TXD pin; so we cannot use Serial.print() at the same time)

  Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/
/*
 Arduino - ESP8266
 TX - TX
 RX - RX
 GND - D8
 GND - D3
 3V3 - D4
 remove the pin connection once done
 */
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:
  Serial.println(touchRead(4));
  delay(500);
}
