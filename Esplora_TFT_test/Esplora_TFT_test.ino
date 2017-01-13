/*

 Esplora TFT Graph

 This example for the Esplora with an Arduino TFT reads
 the value of the light sensor, and graphs the values on
 the screen.

 This example code is in the public domain.

 Created 15 April 2013 by Scott Fitzgerald

 http://arduino.cc/en/Tutorial/EsploraTFTGraph

 */

#include <Esplora.h>
#include <TFT.h>  // Arduino LCD library
#include <SPI.h>

// position of the line on screen
int xPos = 0;

void setup() {

  // initialize the screen
  EsploraTFT.begin();

  // clear the screen with a nice color
  EsploraTFT.background(50, 50, 50);
}

void loop() {

  // read the sensor value
  int sensor = Esplora.readMicrophone();
  // map the sensor value to the height of the screen
  //int graphHeight = map(sensor, 0, 1023, 0, EsploraTFT.height());
  int graphHeight = map(sensor, 0, 255, 0, 2*EsploraTFT.height()); //speaker
  byte blue   = constrain(sensor, 0, 255);
  // draw the line in a pretty color
  EsploraTFT.stroke(0, 255, 255);
  //EsploraTFT.line(xPos, EsploraTFT.height() - graphHeight, xPos, EsploraTFT.height());
  EsploraTFT.line(xPos, EsploraTFT.height() - graphHeight*3 - 1, xPos, 128);
  // if the graph reaches the edge of the screen
  // erase it and start over from the other side
  if (xPos >= 160) {
    xPos = 0;
    EsploraTFT.background(50, 50, 50);
  }
  else {
    // increment the horizontal position:
    xPos++;
  }
  Esplora.writeRGB(0, 0, blue);
  delay(16);
}
