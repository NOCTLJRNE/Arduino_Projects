// Process.h gives us access to the Process class, which lets
// us communicate with the shell
#include <Bridge.h>
#include <Process.h>
#include "DHT.h"

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#define DHTPIN 4     // what digital pin we're connected to
////////////////////////////
// Initial State Streamer //
////////////////////////////
// URL to IS Bucket API
String ISBucketURL = "https://groker.initialstate.com/api/buckets";
// URL to IS Event API
String ISEventURL = "https://groker.initialstate.com/api/events";
// Access key (the one you find in your account settings):
String accessKey = "ATjyrSjPOtEX2U6emwF43haxAJBa7bvl";
// Bucket key (hidden reference to your bucket that allows appending):
String bucketKey = "X5Y9PXLBFPBU";
// Bucket name (name your data will be associated with in Initial State):
String bucketName = "Test_Bucket_2";
// How many signals are in your stream? You can have as few or as many as you want
const int NUM_SIGNALS = 3;
// What are the names of your signals (i.e. "Temperature", "Humidity", etc.)
String signalName[NUM_SIGNALS] = {"Signal 1", "Signal 2", "Signal 3" };//, "Signal 4", "Signal 5", "Signal 6"};
// This array is to store our signal data later
String signalData[NUM_SIGNALS];
//enum emoji {:sunny:, :partly_sunny:, :cloud:, :cloud_rain:, :cloud_snow:};
String emoji[5] = {":sunny:", ":partly_sunny:", ":cloud:", ":cloud_rain:", ":cloud_snow:"};
// This only runs once at the very beginning
int sensorValue = 0;
DHT dht(DHTPIN, DHTTYPE);
void setup() 
{
  Bridge.begin();
  Serial.begin(9600);
  dht.begin();
  delay(10);
  // Initialize random number generation for our example signals
  randomSeed (millis());

  // while (!Serial);
    // Post Bucket
    delay(5000);
    Serial.println("Posting Bucket!");
    // The postBucket() function creates a bucket 
    // (unnecessary if the bucket already exists)
    postBucket();
}

// This repeats
void loop()
{  
  // Gather Data
  // Read from a port for input or output or generate your own values/messages
  // These signals are random numbers for the sake of example
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  float hic = dht.computeHeatIndex(t, h, false);
  // Read temperature as Fahrenheit (i
  sensorValue = analogRead(A0);
  signalData[0] = String(t);
  //signalData[1] = String(random(1,100));
  if (sensorValue > 200)
  signalData[1] = ":bulb:";
  else if (sensorValue < 20) 
  signalData[1] = ":black_large_square:";  
  unsigned char k = random(0, 4);
  signalData[2] = emoji[k];//signalData[2] = String("Alert");
  //signalData[3] = String(h);
  //signalData[4] = String(t);
  //signalData[5] = String(hic);
  // Post Data
  Serial.println("Posting Data!");
  // The postData() function streams our events
  postData(); 
  // Wait for 5 seconds before collecting and sending the next batch
  delay(3000);
}



// Here are the data bucket creation and posting functions
// They do not need to be edited - everything you would need to change for 
// your situation can be found above

void postBucket()
{
  // Initialize the process
  Process isbucket;

  isbucket.begin("curl");
  isbucket.addParameter("-k");
  isbucket.addParameter("-v");
  isbucket.addParameter("-X");
  isbucket.addParameter("POST");
  isbucket.addParameter("-H");
  isbucket.addParameter("Content-Type:application/json");
  isbucket.addParameter("-H");
  isbucket.addParameter("Accept-Version:0.0.1");

  // IS Access Key Header
  isbucket.addParameter("-H");
  isbucket.addParameter("X-IS-AccessKey:" + accessKey);

  // IS Bucket Key Header
  isbucket.addParameter("-d");
  isbucket.addParameter("{\"bucketKey\": \"" + bucketKey + "\", \"bucketName\": \"" + bucketName + "\"}");
  
  isbucket.addParameter("https://groker.initialstate.com/api/buckets");
  
  // Run the process
  isbucket.run();

  Serial.flush();
}

void postData()
{
  // Initialize the process
  Process isstreamer;

  isstreamer.begin("curl");
  isstreamer.addParameter("-k");
  isstreamer.addParameter("-v");
  isstreamer.addParameter("-X");
  isstreamer.addParameter("POST");
  isstreamer.addParameter("-H");
  isstreamer.addParameter("Content-Type:application/json");
  isstreamer.addParameter("-H");
  isstreamer.addParameter("Accept-Version:0.0.1");

  // IS Access Key Header
  isstreamer.addParameter("-H");
  isstreamer.addParameter("X-IS-AccessKey:" + accessKey);

  // IS Bucket Key Header
  // Note that bucketName is not needed here
  isstreamer.addParameter("-H");
  isstreamer.addParameter("X-IS-BucketKey:" + bucketKey);

  isstreamer.addParameter("-d");

  // Initialize a string to hold our signal data
  String jsonData;

  jsonData = "[";

  for (int i=0; i<NUM_SIGNALS; i++)
  {
    jsonData += "{\"key\": \"" + signalName[i] + "\", \"value\": \"" + signalData[i] + "\"}";

    if (i != NUM_SIGNALS - 1)
    {
      jsonData += ",";
    }
  }

  jsonData += "]";

  isstreamer.addParameter(jsonData);

  isstreamer.addParameter("https://groker.initialstate.com/api/events");

  // Print posted data for debug
  Serial.print("Sending data: ");
  Serial.println(jsonData);

  // Run the process
  isstreamer.run();

  Serial.flush();
}

