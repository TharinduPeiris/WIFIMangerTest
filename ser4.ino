#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>    
#include "index.h"
ESP8266WebServer server(80);
WiFiManager wm;
#define PIN_RESET_BUTTON 4        
int RESET = 0; 
void handle_root();
void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    pinMode(PIN_RESET_BUTTON, INPUT);
    //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    
    //reset saved settings
    //wm.resetSettings();
    
    //Assign fixed IP
    //wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));
    //Try to connect WiFi, then create AP
    wm.autoConnect("ESP8266_AP", "esp8266_pwd");
    //Idem avec nom automatique de la forme ESP + ChipID et sans mot de passe
    //wifiManager.autoConnect();
    //the library is blocking. Once connected, the program continues
    Serial.println("ESP8266 is connected to Wi-Fi network");
    
    // Display an HTML interface to the project from a browser on esp8266_ip_address /
    server.on("/", handle_root);
    server.begin();
    Serial.println("HTTP server started");
    delay(100); 
}
void loop() {
    server.handleClient();
    
    RESET = digitalRead(PIN_RESET_BUTTON);
    if( RESET == HIGH) {                                 
      Serial.println("Erase settings and restart ...");
      delay(1000);
      wm.resetSettings();  
      ESP.restart();  
    }
}

// Handle root url (/)
void handle_root() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
