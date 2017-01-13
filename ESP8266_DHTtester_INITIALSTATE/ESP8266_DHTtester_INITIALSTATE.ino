// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain
// last mod Sep 9 2016
#include "DHT.h"
#include <ESP8266WiFi.h>
#define DHTPIN 2     // what digital pin we're connected to
#define ISDestURL "insecure-groker.initialstate.com"
#define bucketKey "RX7RB7CJLQM9"
#define accessKey "ATjyrSjPOtEX2U6emwF43haxAJBa7bvl"
// Uncomment whatever type you're using!

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321


// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
#define period_sec 120

const char* ssid     = "hongtrang";
const char* password = "trang123456";

const int NUM_SIGNALS = 4;
String signalName[NUM_SIGNALS] = {"H", "T", "I", "L"};
String signalData[NUM_SIGNALS];

DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;
int LDRValue = 0;
void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");

  dht.begin();
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("ESP8266 Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(5000);
}

void loop() 
{
  // Wait a few seconds between measurements.
  //delay(period_sec*1000);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  LDRValue = analogRead(A0);
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.print(h);
    Serial.print(t);
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  /*
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
  */
  signalData[0] = h;
  signalData[1] = t;
  signalData[2] = hic;
  signalData[3] = String(LDRValue);
  //Serial.print("connecting to ");
  //Serial.println(ISDestURL);
  
  // Use WiFiClient class to create TCP connections
  
  const int httpPort = 80;
  if (!client.connect(ISDestURL, httpPort)) 
  {
    Serial.println("connection failed");
    return;
  }
  else
  {
    Serial.println("connected !");
  }
  while(!postData()); 
  
    // Read all the lines of the reply from server and print them to Serial

  
  Serial.println();
  Serial.println("closing connection");
  delay(period_sec*1000); // Send data every 10 minutes
}

boolean postData() 
{  
  // Must be connected to your destination URL
  // if (!connectService(ISDestURL,80)) return false;
 
  // Get connection status 
  // if (!echoCommand("AT+CIPSTATUS", "OK", CONTINUE)) return false;
 
  // Build HTTP request.
  for (int i=0; i<NUM_SIGNALS; i++)
  {
    // Shorten signalName and signalData if toSend will be over 290 characters
    // truncateString(i);
    
    String toSend = "POST /api/events HTTP/1.1\r\n";
    toSend += "Host: "ISDestURL"\r\n";
    toSend += "Content-Type: application/json\r\n";
    toSend += "User-Agent: Arduino\r\n";
    toSend += "Accept-Version: ~0\r\n";
    toSend += "X-IS-AccessKey:  "accessKey"\r\n";
    toSend += "X-IS-BucketKey:  "bucketKey"\r\n";
    String payload ="[{\"key\": \"" + signalName[i] + "\", "; 
    payload +="\"value\": \"" + signalData[i] + "\"}]";
    payload +="\r\n"; 
    toSend += "Content-Length: "+String(payload.length())+"\r\n";
    toSend += "\r\n";
    toSend += payload;
 
    //Serial.println(toSend);
 
    // Ready the module to receive raw data
    /*if (!echoCommand("AT+CIPSEND="+String(toSend.length()), ">", CONTINUE))
    {
      echoCommand("AT+CIPCLOSE", "", CONTINUE);
      Serial.println("Connection timeout.");
      return false;
    }
    
    // Send the raw HTTP request
    // POST
    if(!echoCommand(toSend,"204", CONTINUE)) return false;
    */
    client.print(toSend); 
    while(client.available())
    {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
    String toPrint = "Data batch ";
    toPrint += i;
    toPrint += " posted!";
    Serial.println(toPrint);
  }
 
  return true;
}
