
/*
  Web client

 This sketch connects to a Raspberry Pi
 using a WiFi shield (with a Arduino Yun mini using as an access point).

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * WiFi shield attached

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified April 2016
 
 */


#include <SPI.h>
#include <WiFi.h>

char ssid[] = "Arduino Yun-B4218AF5003A"; //  network SSID of Arduino Yun mini(name)
//char pass[] = "secretPassword";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
IPAddress server(192,168,240,171);  // numeric IP for Google (no DNS)
cost
//char server[] = "raspberrypi";    // name address for Raspberry Pi 3 (using DNS from OpenWRT installed on Arduino YUN)

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient client;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  // using A0 and A2 as vcc and gnd for the TMP36 sensor:
  pinMode(A0, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(9, OUTPUT);      // set the LED pin mode;
  digitalWrite(A0, HIGH);
  digitalWrite(A2, LOW);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if ( fv != "1.1.0" )
    Serial.println("Please upgrade the firmware");

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWifiStatus();

  Serial.print("\nStarting connection to server: ");
  Serial.println(server);
  // if you get a connection, report back via serial:
  if (client.connect(server, 5000)) {
    // Serial.println("connected to server");
    // Make a HTTP request:
    // client.print("temperature from WIFI shield: ");
    // client.print(temperature);
    // client.println("°C");
    //client.println("Connection: close");
    // client.println();
  }
}

void loop() 
{
  
  int sensorValue = analogRead(A1);
  float voltage = sensorValue *  (5000 / 1024);
  // convert the millivolts to temperature celsius:
  float temperature = (voltage - 500) / 10;
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) 
  {
    char c = client.read();
    Serial.write(c);
    if (c == 'H')
    {
      digitalWrite(9, HIGH);
    }
    else if (c == 'L')
    {
      digitalWrite(9, LOW);
    }
    
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) 
  {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }
  //if (client.connect(server, 5000)) 
  //{
  client.print("temperature from WIFI shield:;");
  client.print(temperature);
  client.print(";");
  client.println("°C");
  delay(2000);
  //}
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}





