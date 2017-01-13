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
const int redLEDPin = 11;     // LED connected to digital pin 10
const int blueLEDPin = 9;    // LED connected to digital pin 11
const int greenLEDPin = 10;
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
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(redLEDPin, LOW);
  digitalWrite(greenLEDPin, LOW);
  digitalWrite(blueLEDPin, LOW);
  digitalWrite(2, HIGH);
}

//int lowLight = 400;   // the light sensor reading when it's covered
//int highLight = 1023; // the maximum light sensor reading
//int minGreen = 0;     // minimum brightness of the green LED
//int maxGreen = 100;   // maximum brightness of the green LED

void loop() {
  char tab[40];
  //char c = 'R';
  // read the sensors into variables:
 // int mic = Esplora.readMicrophone();
 // int light = Esplora.readLightSensor();
 // int slider = Esplora.readSlider();

  // convert the sensor readings to light levels:
 // byte red   = constrain(mic, 0, 255);
 // byte green = constrain(
 //                map(light, lowLight, highLight, minGreen, maxGreen),
 //                0, 255);
 // byte blue  = slider / 4;

  // print the light levels (to see what's going on):
 // Serial.print(red);
 // Serial.print(' ');
 // Serial.print(green);
 // Serial.print(' ');
 // Serial.println(blue);

  // write the light levels to the LED.
  // note that the green value is always 0:
 // Esplora.writeRGB(red, green, blue);

  // add a delay to keep the LED from flickering:
  //if ((Serial.available()))
  //{
  digitalWrite(2, LOW);
  char c = Serial.read();
  
  if (c == 'R') // Wait for the beginning character
  {
    RED = Read_UART_Parameter('G');
  }
  
  if (RX_char == 'G') // Wait for the beginning character
  {
    GREEN = Read_UART_Parameter('B');
  }
  
  if (RX_char == 'B') // Wait for the beginning character
  {
    BLUE = Read_UART_Parameter('E');
  }
  tab[j] = c;  
      
  j++;
  //Serial.print("Value is:");
  //Serial.println(i%10);
  Serial.print("RED: ");
  Serial.print(RED);
  Serial.print(" GREEN: ");
  Serial.print(GREEN);
  Serial.print(" BLUE: ");
  Serial.print(BLUE); 
  //Esplora.writeRGB(RED, GREEN, BLUE);
  //analogWrite(redLEDPin, RED);
  //analogWrite(greenLEDPin, GREEN);
  //analogWrite(blueLEDPin, BLUE);
  //Serial.println();
 
  
  //}
  //c = 'R';
  j=0;
    for (i=0; i<RED; i++)
  {
  digitalWrite(redLEDPin, HIGH);
  digitalWrite(greenLEDPin, LOW);
  digitalWrite(blueLEDPin, LOW);
  }
  
  for (i=0; i<GREEN; i++)
  {
  digitalWrite(redLEDPin, LOW);
  digitalWrite(greenLEDPin, HIGH);
  digitalWrite(blueLEDPin, LOW); 
  }

  for (i=0; i<BLUE; i++)
  {
  digitalWrite(redLEDPin, LOW);
  digitalWrite(greenLEDPin, LOW);
  digitalWrite(blueLEDPin, HIGH);  
  }
  //Serial.println(tab);
  //Serial.print(c);
  //delay(100);
}

int Read_UART_Parameter(unsigned char end_char)
{
			unsigned int k;
			unsigned int i;
	
				k = 0;
				for (i=0; i<10; i++)
				{ 
					RX_string[i]='\0';
				}                				
		   		while (Serial.available() == 0)	  // Wait for COMRX buffer empty bit to be set
	      		{
	      		}				
				RX_char = Serial.read();
				while (RX_char != end_char)
				{ 					
					if ((RX_char == '0')||(RX_char == '1')||(RX_char == '2')||(RX_char == '3')||(RX_char == '4')||(RX_char == '5')||(RX_char == '6')||(RX_char == '7')||(RX_char == '8')||(RX_char == '9'))
					RX_string[k] = RX_char;	
					k++;
					while (Serial.available() == 0)
					{
					}
					RX_char = Serial.read();					
				}
				//READ_int = atoi(RX_string);
				//PWM0COM0 = PWM0COM1 + READ_int*2;	
	return atoi(RX_string);
}
