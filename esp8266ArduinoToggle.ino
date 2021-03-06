#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
const char* ssid = "thorhammer";
const char* password = "thorthor";


ESP8266WebServer server(80);
 
const int led = 4;

int state = 0;
 
void handle_root() {

  digitalWrite(led, state);
  String s = "<html>";
  if (state == 1) {
    s += "OUTPUT IS OFF<br>";
  }
  if (state == 0) {
    s += "OUTPUT IS ON<br>";
  }
  s += "<button style='font-size: 2em;' onclick='javascript:location.reload();'>Toggle</button>";
  s += "</html>";
  server.send(200, "text/html", s);
  Serial.println("Toggled state!");
  delay(100);

  if (state == 1) {
     Serial.println("LED is now off!");
     
     state = 0;
     return;    
  }
  if (state == 0) {
     Serial.println("LED is now on!");

     state = 1;
     return;
  }
}
 
void setup(void)
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);

  // Connect to WiFi network
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  Serial.println("");

  Serial.println("");
  Serial.print("Access Point SSID: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
   
  server.on("/", handle_root);
  server.begin();
  
  Serial.println("HTTP server started");
}
 
void loop(void)
{
  server.handleClient();
} 
