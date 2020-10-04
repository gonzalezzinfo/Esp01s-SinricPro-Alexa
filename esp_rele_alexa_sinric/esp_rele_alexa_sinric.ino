#include <ESP8266WiFi.h>   
#include "SinricPro.h"
#include "SinricProSwitch.h"

#define WIFI_SSID         "Coloque_Aqui_o_nome_do_seu_WiFi"    
#define WIFI_PASS         "A_Senha_do_seu_WiFi"
#define APP_KEY           "Coloque aqui a chave do app, que você acha lá no site do Sinric Pro"    // O seu App Key é algo como "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "Coloque o senha do app, está na parte de credenciais"   // O seu App Secret é algo como "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
  

#define Ventilador_ID       "Copie e cole aqui O ID do seu dispositivo"    // Algo como "5dc1564130xxxxxxxxxxxxxx"
#define Ventilador_Pin 0  // O pino fisico onde está ligado
#define BAUD_RATE         9600                // Se precisar, pode trocar o baud rate
  
void setupWiFi();
void setupSinricPro();
bool VentiladorState(const String &deviceId, bool &state);
  
// main setup function
void setup() {
  setupWiFi();
  setupSinricPro(); 
  pinMode(Ventilador_Pin, OUTPUT);
  digitalWrite(Ventilador_Pin, HIGH);
}
 
void loop() {
  SinricPro.handle();
}
 
bool VentiladorState(const String &deviceId, bool &state) {
  digitalWrite(Ventilador_Pin, !state);
  return true; // request handled properly
}
 
// setup das conexões Wifi
void setupWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
  }
}
 
// setup das funções para o SinricPro
void setupSinricPro() {
  // add devices and callbacks to SinricPro
  SinricProSwitch &mySwitch1 = SinricPro[Ventilador_ID];
  mySwitch1.onPowerState(VentiladorState);
 
  // setup SinricPro
  SinricPro.onConnected([](){  }); 
  SinricPro.onDisconnected([](){  });
  SinricPro.begin(APP_KEY, APP_SECRET);
}
