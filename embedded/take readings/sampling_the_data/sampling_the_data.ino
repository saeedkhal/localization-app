#include <ESP8266WiFi.h>

int AvailableNetworks;
String routers_ssid[13] = {"El-lab","El-modarag","Redmi","youssef","Farouk","hamdy","Ramadan","STUDBME2","CMP_LAB1","CMP_LAB2","CMP_LAB3","CMP_LAB4","ReahabLab"};

void setup() 
{
  Serial.begin(9600);
  AvailableNetworks = WiFi.scanNetworks();
  Serial.println("");
  for (int i = 0; i < 13; i++)
  {
    Serial.print(routers_ssid[i]);
    Serial.print(',');
  }
  Serial.println("");
}
void loop() 
{
  AvailableNetworks = WiFi.scanNetworks();
  int routers_strength[13] = {-100,-100,-100,-100,-100,-100,-100,-100,-100 ,-100 ,-100,-100,-100};
  
  for (int j=0;j<13;j++)
  {
    for (int i = 0; i < AvailableNetworks; i++)
    {  
        if(routers_ssid[j] == WiFi.SSID(i))
        {
          routers_strength[j] = WiFi.RSSI(i);
        }
    }
    Serial.print(routers_strength[j]);
    Serial.print(',');
  }
  
  Serial.println("");

  delay(500);
}
