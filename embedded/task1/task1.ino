
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>

WebSocketsClient webSocket;
String wifi_strengths ;
char char_array_user[255];
char char_array_pass[255];
int network_number = 0 ;
char *data[]={char_array_user,char_array_pass};
unsigned long messageInterval = 100;
bool connected = false;

//String path = "192.168.1.7";

String path = "indoor-localization-sbme.herokuapp.com" ;
int port = 80;
String url = "/master" ;
#define DEBUG_SERIAL Serial
 
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case WStype_DISCONNECTED:
            DEBUG_SERIAL.printf("[WSc] Disconnected!\n");
            connected = false;
            break;
        case WStype_CONNECTED: 
            DEBUG_SERIAL.printf("[WSc] Connected to url: %s\n", payload);
            connected = true;
            break;
        //when we recieve data but we will not recievw any data 
        //case WStype_TEXT:
        //    DEBUG_SERIAL.printf("[WSc] RESPONSE: %s\n", payload);
        //    break;
    }
 
}
 
char* serial_tochar(int choose_data) {
    while(Serial.available()==0) { }
    String str =Serial.readString();
    str.toCharArray(data[choose_data], str.length());
    return data[choose_data];
}

void get_wifi_strength() {
  int network_number = WiFi.scanNetworks();
  const size_t CAPACITY = JSON_OBJECT_SIZE(20);
  StaticJsonDocument<CAPACITY> doc;

  // create an object
  JsonObject object = doc.to<JsonObject>();
  for (int i=0;i<network_number;i++){
    object[WiFi.SSID(i)] = WiFi.RSSI(i);
  }
  wifi_strengths = " " ;
  //wifi strength in json object
  serializeJson(doc, wifi_strengths);
} 
void connect_wifi() {
    char * username;
    Serial.println("Please enter the username: ");
    username = strtok(serial_tochar(0), " ");
    char * password;
    Serial.println("Please enter the password: ");
    password = strtok(serial_tochar(1), " ");
    WiFi.begin(username, password);

    uint8_t i = 0;
    while(WiFi.status() != WL_CONNECTED && i < 20) {
      Serial.print(".");
      delay(500);
      i++;
    }
}
void print_available_wifi () {
  network_number = WiFi.scanNetworks();
  Serial.print("number of network : ");
  Serial.println(network_number);
  for (int i=0;i<network_number;i++){
  Serial.print("WiFi name : ");
  Serial.println(WiFi.SSID(i));
  Serial.print("Signal Strenth : ");
  Serial.println(WiFi.RSSI(i));
  Serial.println("------------");
  }
}
void setup() {
  Serial.begin(9600);
  print_available_wifi(); 
  connect_wifi();
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
    // server address, port and URL
    //webSocket.begin("localization-hamdy-server.herokuapp.com", 8082, "/master","text");
  Serial.println("Trying to connect to web_socket  === " + path + ":" + String(port) + url );
  webSocket.begin(path, port, url ,"text");
    // event handler
  webSocket.onEvent(webSocketEvent);
}
 
unsigned long lastUpdate = millis();

void loop() {
    webSocket.loop();
    if (connected && lastUpdate+messageInterval<millis()){
        get_wifi_strength();
        webSocket.sendTXT(wifi_strengths);
        DEBUG_SERIAL.println("[WSc] SENT:" + wifi_strengths);
       lastUpdate = millis();
    }
}
