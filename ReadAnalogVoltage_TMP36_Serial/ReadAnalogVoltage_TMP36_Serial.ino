/*
  ReadAnalogVoltage
  Reads an analog input on pin 0, converts it to voltage, and prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

 This example code is in the public domain.
 */

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(A0, OUTPUT);
  pinMode(A2, OUTPUT);
  digitalWrite(A0, HIGH);
  digitalWrite(A2, LOW);
  
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
      int sensorValue = analogRead(A1);
      int VoltageValue = analogRead(A3);
      // convert the reading to millivolts:
      float voltage = sensorValue *  (5000 / 1024);
      // convert the millivolts to temperature celsius:
      float temperature = (voltage - 500) / 10;
  // print out the value you read:
  Serial.print(temperature);
  Serial.print("°C ");
  Serial.println(VoltageValue*(5000 / 1024));
  delay(1000);
}
