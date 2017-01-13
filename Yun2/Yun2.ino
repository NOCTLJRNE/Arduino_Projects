
#include <Bridge.h>
#include <BridgeSSLClient.h>
#include <ArduinoCloud.h>


// Arduino Cloud settings and credentials
const char userName[]   = "NOCTLJRNE";
const char thingName[] = "Yun2";
const char thingId[]   = "93dee55a-e676-4213-9b76-5d7d2f1b93b4";
const char thingPsw[]  = "5cdb0ee0-f401-4869-8229-00d353506289";


BridgeSSLClient sslClient;


// build a new object "Yun2"
ArduinoCloudThing Yun2;


void setup() {
  Serial.begin (9600);

  Serial.println("Starting Bridge");
  Bridge.begin();
  Serial.println("Done");


  Yun2.begin(thingName, userName, thingId, thingPsw, sslClient);
  Yun2.enableDebug();
  // define the properties
  Yun2.addProperty("String2", CHARSTRING, R, TIMED, 3);
  Serial.println("Setup done");
}

void loop() {
  Serial.println("loop");
  Yun2.poll();

  Yun2.writeProperty("String2", "oh...");
  
  delay(1000);
  Yun2.writeProperty("String2", "yeah!");
  
  delay(1000);
}
