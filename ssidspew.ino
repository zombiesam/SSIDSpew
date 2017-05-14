#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>

extern "C" {
#include "user_interface.h"
}

char* baseSSID[] = {"comhem_", "TN_24GHz_", "COMHEM_"};
char* fixedSSID[] = {"default", "NETGEAR", "linksys", "dlink", "D-LINK", 
                     "FreeWifi", "hpsetup", "eduroam", "Home", "Guest", 
                     "asus", "WLAN", "internet", "dd-wrt", "wifi", "office", 
                     "MSHOME", "DIRECT-", "mobile", "virus", "THOMSON", 
                     "NetWork", "My ASUS", "Visitor", "Linksys-G", "netis"};  // 26 at netis
long randNumber;
byte mac[6] = {0, 0, 0, 0, 0, 0} ;
const byte brand[21][3]   = {0x10, 0x1C, 0x0C,          /* Apple */
                             0x12, 0x1E, 0x0D,          /* Apple */
                             0x13, 0x24, 0x12,          /* Apple */
                             0x00, 0x10, 0xFA,          /* Apple */ 
                             0x00, 0x21, 0xE9,          /* Apple */
                             0x28, 0xE7, 0xCf,          /* Apple */
                             0x44, 0xA6, 0x60,          /* Apple */
                             0xB8, 0xC7, 0x5D,          /* Apple */
                             0x40, 0xb3, 0x95,          /* Apple */
                             0xa8, 0xfa, 0xd8,          /* Apple */
                             0x34, 0xFC, 0xEF,          /* LG Electronics */
                             0xE8, 0x11, 0x32,          /* Samsung Electronics CO., LTD */
                             0x84, 0x4B, 0xF5,          /* Hon Hai Precision Ind. CO., LTD. */
                             0x28, 0x47, 0xAA,          /* Nokia Corporation */
                             0x84, 0x8E, 0xDF,          /* Sony Mobile Communications AB */
                             0xa4, 0xdb, 0x30,          /* Liteon Technology Corporation */
                             0x54, 0x8c, 0xa0,          /* Liteon Technology Corporation */
                             0x44, 0x6d, 0xa0,          /* Liteon Technology Corporation */
                             0xac, 0xb5, 0x7d,          /* Liteon Technology Corporation */
                             0x70, 0xf1, 0xa1,          /* Liteon Technology Corporation */
                             0xd0, 0xdf, 0x9a           /* Liteon Technology Corporation */
                             };        
void setup() {}

void loop() {                                           
  WiFi.mode(WIFI_STA); 
  int c;
  c = random(2);
  if (c == 0) {
    String finalSSID = baseSSID[random(3)];
    for (int x = 0; x < 3; x++) {
      finalSSID.concat(String(random(255), HEX));
      }
    WiFi.begin(finalSSID.c_str());
  } if (c == 1) {
    WiFi.begin(fixedSSID[random(26)]);
  }
  
  int currBrand = random(21);
  for (int x = 0; x < 3; x++) {             
    mac[x] = brand[currBrand][x];
  }
    
  for (int x = 3; x < 6; x++) {
    mac[x] = random(255);                               
  }
  
  wifi_set_macaddr(STATION_IF, mac);                   
  int numSsid = WiFi.scanNetworks();
} 
