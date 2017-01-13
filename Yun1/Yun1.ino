
#include <Bridge.h>
#include <BridgeSSLClient.h>
#include <ArduinoCloud.h>


// Arduino Cloud settings and credentials
const char userName[]   = "NOCTLJRNE";
const char thingName[] = "Yun1";
const char thingId[]   = "45d1297c-1968-43c5-bbd0-4809f89fbdf1";
const char thingPsw[]  = "d594c9be-6dda-4eec-aaa4-67f899d5a9b0";


BridgeSSLClient sslClient;


// build a new object "Yun1"
ArduinoCloudThing Yun1;


void setup() {
  Serial.begin (9600);

  Serial.println("Starting Bridge");
  Bridge.begin();
  Serial.println("Done");


  Yun1.begin(thingName, userName, thingId, thingPsw, sslClient);
  Yun1.enableDebug();
  // define the properties
  Yun1.addProperty("cloudLedStatus", INT, R, TIMED, 3);
  
}

void loop() {
  Yun1.poll();

  Yun1.writeProperty("cloudLedStatus", "oh...");
  
  delay(1000);
  Yun1.writeProperty("cloudLedStatus", "yeah!");
  
  delay(1000);
}
