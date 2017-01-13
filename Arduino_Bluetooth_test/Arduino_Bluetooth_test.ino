/*
  Esplora Led/Microphone

  This simple sketch reads the microphone, light sensor, and slider.
  Then it uses those readings to set the brightness of red, green and blue
  channels of the RGB LED. The red channel will change with the loudness
  "heared" by the microphone, the green channel changes as the
  amount of light in the room and the blue channel will change
  with the position of the slider.

  Created on 22 november 2012
  By Enrico Gueli <enrico.gueli@gmail.com>
  Modified 24 Nov 2012
  by Tom Igoe
*/

//#include <Esplora.h>

unsigned char j = 0;
unsigned char i = 0;
unsigned char RED = 0;

unsigned char GREEN = 0;
unsigned char BLUE = 0;
char RX_string[10] ="";
unsigned char RX_char = 0;
void setup() {
  // initialize the serial communication:
  Serial.begin(38400);

  pinMode(2, OUTPUT);

  digitalWrite(2, HIGH);
}



void loop() {
  
 
  Serial.print("Value is:");
  //Serial.println(i%10);



  //for (i=0; i<10; i++)
  //{
    //Serial.write(i);
   delay(1000); 
  //}
//digitalWrite(2, LOW);
  //Serial.println(tab);
  //Serial.print(c);
  //delay(100);
}


