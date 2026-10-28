#include <WiFi.h>
#include <ArduinoWebsockets.h>
#include <ESPmDNS.h>

using namespace websockets;
WebsocketsServer server;

typedef char* cptr;
cptr ssid = "your_ssid";
cptr password = "your_password";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  if(!MDNS.begin("robot")){
    Serial.println("MDNS failed !!");
  }
  else{
    Serial.println("MDNS started");
  }
  Serial.println();
  Serial.println(WiFi.localIP());

  server.listen(80);
}

void loop() {
  // put your main code here, to run repeatedly:
  WebsocketsClient client = server.accept();
  
  if(client.available()){
    Serial.println("BROWSER CONNECTED");
    client.send("hello from ESP32");
    

    client.onMessage([](WebsocketsMessage message) {
            Serial.print("Client: ");
            Serial.println(message.data());
        });

    while(client.available()){
      client.poll();
    }
  }
}
