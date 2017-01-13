/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 3
 * LCD Enable pin to digital pin 5
 * LCD D4 pin to digital pin 7
 * LCD D5 pin to digital pin 9
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 13
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(3, 5, 7, 9, 11, 13);
const int RS =  3;
const int EN =  5;
const int D4 =  7;
const int D5 =  9;
const int D6 =  11;
const int D7 =  13;
uint8_t function;
uint8_t control;
uint8_t mode;
void setup() {
  // set up the LCD's number of columns and rows:
  pinMode(RS, OUTPUT);
  pinMode(EN, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  
  //lcd.begin(16, 2);
   
  function = LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS; //0x00 | 0x08 | 0x00 | 0x20
  delayMicroseconds(50000); 
  // Now we pull both RS and R/W low to begin commands
  digitalWrite(RS, LOW);
  digitalWrite(EN, LOW);
  //if (RW != 255) { 
  //  digitalWrite(RW, LOW);
  //}
  // Print a message to the LCD.
  //lcd.print("hello, world!");

  lcd.command(function | LCD_FUNCTIONSET);// | 0x20
  delayMicroseconds(4500);
  lcd.command(function | LCD_FUNCTIONSET);
  delayMicroseconds(150);
  lcd.command(function | LCD_FUNCTIONSET);
  lcd.command(function | LCD_FUNCTIONSET);
  control = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF; //0x04 | 0x00 | 0x00
  
  //display
  control |= LCD_DISPLAYON;
  lcd.command(LCD_DISPLAYCONTROL | control);
  
  //clear
  lcd.command(LCD_CLEARDISPLAY); // 0x01
  delayMicroseconds(2000);
  
  mode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT; // 0x02 | 0x00
  lcd.command(LCD_ENTRYMODESET | mode); // 0x04
  //write character U
  digitalWrite(RS, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(D5, LOW);
  digitalWrite(D6, HIGH);
  digitalWrite(D7, LOW);
  digitalWrite(EN, LOW);
  delayMicroseconds(1);    
  digitalWrite(EN, HIGH);
  delayMicroseconds(1);    // enable pulse must be >450ns
  digitalWrite(EN, LOW);
  delayMicroseconds(100);   // commands need > 37us to settle
  delay(100);
  digitalWrite(RS, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(D5, LOW);
  digitalWrite(D6, HIGH);
  digitalWrite(D7, LOW);
  digitalWrite(EN, LOW);
  delayMicroseconds(1);    
  digitalWrite(EN, HIGH);
  delayMicroseconds(1);    // enable pulse must be >450ns
  digitalWrite(EN, LOW);
  delayMicroseconds(100);   // commands need > 37us to settle
  
  //lcd.setCursor(1, 0);
  //write character e
  digitalWrite(RS, HIGH);
  digitalWrite(D4, LOW);
  digitalWrite(D5, HIGH);
  digitalWrite(D6, HIGH);
  digitalWrite(D7, LOW);
  digitalWrite(EN, LOW);
  delayMicroseconds(1);    
  digitalWrite(EN, HIGH);
  delayMicroseconds(1);    // enable pulse must be >450ns
  digitalWrite(EN, LOW);
  delayMicroseconds(100);   // commands need > 37us to settle
  delay(100);
  digitalWrite(RS, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(D5, LOW);
  digitalWrite(D6, HIGH);
  digitalWrite(D7, LOW);
  digitalWrite(EN, LOW);
  delayMicroseconds(1);    
  digitalWrite(EN, HIGH);
  delayMicroseconds(1);    // enable pulse must be >450ns
  digitalWrite(EN, LOW);
  delayMicroseconds(100);   // commands need > 37us to settle
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  int com;
  //com = LCD_SETDDRAMADDR | (0 + 0x40);
  //lcd.command(com);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);
}

