/*
  Arduino Starter Kit example
 Project 4  - Color Mixing Lamp

 This sketch is written to accompany Project 3 in the
 Arduino Starter Kit

 Parts required:
 1 RGB LED
 three 10 kilohm resistors
 3 220 ohm resistors
 3 photoresistors
 red green and blue colored gels

 Created 13 September 2012
 Modified 14 November 2012
 by Scott Fitzgerald
 Thanks to Federico Vanzati for improvements

 http://arduino.cc/starterKit

 This example code is part of the public domain
 */

const int cyanLEDPin = 11;    // LED connected to digital pin 9
const int magentaLEDPin = 7;     // LED connected to digital pin 10
const int yellowLEDPin = 9;    // LED connected to digital pin 11
const int greenLEDPin = 12;    // LED connected to digital pin 9
const int redLEDPin = 8;     // LED connected to digital pin 10
const int blueLEDPin = 10;    // LED connected to digital pin 11
const int greenLEDPin_fade = 5;    // LED connected to digital pin 9
const int redLEDPin_fade = 4;     // LED connected to digital pin 10
const int blueLEDPin_fade = 6; 

const int redSensorPin = A2;  // pin with the photoresistor with the red gel
const int LDRSensorPin = A0;   // pin with the photoresistor with the green gel
const int blueSensorPin = A1;   // pin with the photoresistor with the blue gel

int redValue = 0; // value to write to the red LED
int greenValue = 0; // value to write to the green LED
int blueValue = 0; // value to write to the blue LED

int redSensorValue = 0; // variable to hold the value from the red sensor
int LDRSensorValue = 0; // variable to hold the value from the green sensor
int blueSensorValue = 0; // variable to hold the value from the blue sensor
int i = 0;
int k = 0;
int j = 0;
void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  // set the digital pins as outputs
  pinMode(cyanLEDPin, OUTPUT);
  pinMode(magentaLEDPin, OUTPUT);
  pinMode(yellowLEDPin, OUTPUT);
  pinMode(redLEDPin_fade, OUTPUT);
  pinMode(greenLEDPin_fade, OUTPUT);
  pinMode(blueLEDPin_fade, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
}

void loop() {
  const int pwm_time=13;
  const int period_time=10;// 10 for 16 MHz
  // Read the sensors first:

  // read the value from the red-filtered photoresistor:
  //redSensorValue = analogRead(redSensorPin);
  // give the ADC a moment to settle
  /*delay(5);
  // read the value from the green-filtered photoresistor:
  //greenSensorValue = analogRead(greenSensorPin);
  // give the ADC a moment to settle
  delay(5);
  // read the value from the blue-filtered photoresistor:
  //blueSensorValue = analogRead(blueSensorPin);

  // print out the values to the serial monitor
  Serial.print("raw sensor Values \t red: ");
  Serial.print(redSensorValue);
  Serial.print("\t green: ");
  Serial.print(greenSensorValue);
  Serial.print("\t Blue: ");
  Serial.println(blueSensorValue);

  
  //In order to use the values from the sensor for the LED,
  //you need to do some math. The ADC provides a 10-bit number,
  //but analogWrite() uses 8 bits. You'll want to divide your
  //sensor readings by 4 to keep them in range of the output.
  
  redValue = redSensorValue / 4;
  greenValue = greenSensorValue / 4;
  blueValue = blueSensorValue / 4;

  //  print out the mapped values
  Serial.print("Mapped sensor Values \t red: ");
  Serial.print(redValue);
  Serial.print("\t green: ");
  Serial.print(greenValue);
  Serial.print("\t Blue: ");
  Serial.println(blueValue);

  
  //Now that you have a usable value, it's time to PWM the LED.
  
  */
  //if (i<period_time/3)
  //{
  //digitalWrite(magentaLEDPin, HIGH);
  //digitalWrite(cyanLEDPin, LOW);
  //digitalWrite(yellowLEDPin, HIGH);
  LDRSensorValue = analogRead(LDRSensorPin);
  Serial.print("raw sensor Values \t LDR: ");
  Serial.println(LDRSensorValue);
  if (LDRSensorValue<=500)
  {
      digitalWrite(magentaLEDPin, HIGH);
      digitalWrite(cyanLEDPin, HIGH);
      digitalWrite(yellowLEDPin, HIGH);
      digitalWrite(redLEDPin, HIGH);
      digitalWrite(greenLEDPin, HIGH);
      digitalWrite(blueLEDPin, HIGH);   
  } //there are 6 digital outputs, R, G & B ouputs will drive 3 RGB LEDs and M, C, Y will drive 3 RGB LEDs (pin connections are permutated for each LED)
  if (LDRSensorValue>500)
  {//divide into 3 sequence, in each sequence
  //SEQUENCE 1
  for (i=0; i<pwm_time; i=i+1) // each iteration of "i" will change the duty cycle of each output, thus changing the appearing color of each LED
  {
    LDRSensorValue = analogRead(LDRSensorPin);
  Serial.print("raw sensor Values \t LDR: ");
  Serial.println(LDRSensorValue); 
    if (LDRSensorValue<=500)// if environmental Light is on, then dont do anything
    {
    break;
    }
    for (k=0; k<period_time; k++) // this loop will hold each output on a constant duty cycle long enough so human eyes can perceive the RGB LEDs color clearly 
    {    
      for (j=0; j<pwm_time; j++)
      {

        if (j<pwm_time-i)
        {  
          digitalWrite(magentaLEDPin, HIGH);
          digitalWrite(cyanLEDPin, LOW);
          digitalWrite(yellowLEDPin, HIGH);
        }
        if (j>=pwm_time-i)
        {  
          digitalWrite(magentaLEDPin, HIGH);
          digitalWrite(cyanLEDPin, HIGH);
          digitalWrite(yellowLEDPin, LOW);    
        }
        if (((pwm_time/2)-i)>=0)
        {
          if (j>(pwm_time/2)-i)//increase pwm rate of low ouput
          {  
            digitalWrite(redLEDPin, HIGH);
            digitalWrite(greenLEDPin, LOW);
            digitalWrite(blueLEDPin, HIGH);
          }
          if (j<=(pwm_time/2)-i)//decrease pwm rate of low ouput
          {  
            digitalWrite(redLEDPin, HIGH);
            digitalWrite(greenLEDPin, HIGH);
            digitalWrite(blueLEDPin, LOW);
          }  
        }
        if (i-(pwm_time/2)>=0)
        {      
          if (j>i-(pwm_time/2))//decrease pwm rate of low ouput
          {  
            digitalWrite(redLEDPin, HIGH);
            digitalWrite(greenLEDPin, LOW);
            digitalWrite(blueLEDPin, HIGH);
          }
          if (j<=i-(pwm_time/2))//increase pwm rate of low ouput
          {  
            digitalWrite(redLEDPin, LOW);
            digitalWrite(greenLEDPin, HIGH);
            digitalWrite(blueLEDPin, HIGH);
          } 
        }
        delay(1);
      }
    }
  }
  //LDRSensorValue = analogRead(LDRSensorPin);
 
  //SEQUENCE 2
  for (i=0; i<pwm_time; i=i+1)
  {
    LDRSensorValue = analogRead(LDRSensorPin);
  Serial.print("raw sensor Values \t LDR: ");
  Serial.println(LDRSensorValue);     
    if (LDRSensorValue<=500)
    {
    break;
    } 
    for (k=0; k<period_time; k++)
    {    
    for (j=0; j<pwm_time; j++)
    {

      if (j<pwm_time-i)
      {  
      digitalWrite(magentaLEDPin, HIGH);
      digitalWrite(cyanLEDPin, HIGH);
      digitalWrite(yellowLEDPin, LOW);
      }
      if (j>=pwm_time-i)
      {  
      digitalWrite(magentaLEDPin, LOW);
      digitalWrite(cyanLEDPin, HIGH);
      digitalWrite(yellowLEDPin, HIGH);    
      }
      if (((pwm_time/2)-i)>=0)
      {
      if (j>(pwm_time/2)-i)
      {  
      digitalWrite(redLEDPin, LOW);
      digitalWrite(greenLEDPin, HIGH);
      digitalWrite(blueLEDPin, HIGH);
      }
      if (j<=(pwm_time/2)-i)
      {  
      digitalWrite(redLEDPin, HIGH);
      digitalWrite(greenLEDPin, LOW);
      digitalWrite(blueLEDPin, HIGH);
      }  
      }
      if (i-(pwm_time/2)>=0)
      {      
      if (j>i-(pwm_time/2))
      {  
      digitalWrite(redLEDPin, LOW);
      digitalWrite(greenLEDPin, HIGH);
      digitalWrite(blueLEDPin, HIGH);
      }
      if (j<=i-(pwm_time/2))
      {  
      digitalWrite(redLEDPin, HIGH);
      digitalWrite(greenLEDPin, HIGH);
      digitalWrite(blueLEDPin, LOW);
      } 
      }
      delay(1);
   }
   }
  }  
  //LDRSensorValue = analogRead(LDRSensorPin);
  //Serial.print("raw sensor Values \t LDR: ");
  //Serial.println(LDRSensorValue);  
  //SEQUENCE 3
  for (i=0; i<pwm_time; i=i+1)
  {
    LDRSensorValue = analogRead(LDRSensorPin);
   Serial.print("raw sensor Values \t LDR: ");
  Serial.println(LDRSensorValue);    
    if (LDRSensorValue<=500)
    {
    break;
    }  
    for (k=0; k<period_time; k++)
    {    
    for (j=0; j<pwm_time; j++)
    {

      if (j<pwm_time-i)
      {  
      digitalWrite(magentaLEDPin, LOW);
      digitalWrite(cyanLEDPin, HIGH);
      digitalWrite(yellowLEDPin, HIGH);
      }
      if (j>=pwm_time-i)
      {  
      digitalWrite(magentaLEDPin, HIGH);
      digitalWrite(cyanLEDPin, LOW);
      digitalWrite(yellowLEDPin, HIGH);    
      }
      if (((pwm_time/2)-i)>=0)
      {
      if (j>(pwm_time/2)-i)
      {  
      digitalWrite(redLEDPin, HIGH);
      digitalWrite(greenLEDPin, HIGH);
      digitalWrite(blueLEDPin, LOW);
      }
      if (j<=(pwm_time/2)-i)
      {  
      digitalWrite(redLEDPin, LOW);
      digitalWrite(greenLEDPin, HIGH);
      digitalWrite(blueLEDPin, HIGH);
      }  
      }
      if (i-(pwm_time/2)>=0)
      {      
      if (j>i-(pwm_time/2))
      {  
      digitalWrite(redLEDPin, HIGH);
      digitalWrite(greenLEDPin, HIGH);
      digitalWrite(blueLEDPin, LOW);
      }
      if (j<=i-(pwm_time/2))
      {  
      digitalWrite(redLEDPin, HIGH);
      digitalWrite(greenLEDPin, LOW);
      digitalWrite(blueLEDPin, HIGH);
      } 
      }
      delay(1);
   }
   }
  }  
 } 
  //delay(2000);
}

