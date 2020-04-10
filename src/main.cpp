#include <Arduino.h>
#include <ESP8266WiFi.h>

//Parâmetros do WiFi
const char* wifi_ssid = "nome do seu wifi";
const char* wifi_pass = "senha do seu wifi";

//Lista de servidores ntp:
const char* pool_server = "pool.ntp.org";
const char* google_server = "time.google.com";
const char* time_server = "time.nist.gov";

//Constante para auxiliar no ajuste de fuso horário
#define GMT 3600

void setup() {
  Serial.begin(115200);
  WiFi.begin(wifi_ssid, wifi_pass);
  while (WiFi.status() != WL_CONNECTED)
  {
      Serial.println("Aguardando conexão com WiFi...");
      delay(500);
  }
  //A configuração do relógio RTC, deve ser chamada após a conexão com a rede WiFi:
  configTime(
    -3*GMT, 0, pool_server,     //Ajuste de fuso horário (-3GMT para o Brasil)
    google_server,              //Lista de links dos provedores ntp's a serem utilizados
    time_server                 ////Após essa configuração, a conexão com internet não é mais necessária.
  ); 
}

void loop() {
  time_t now = time(nullptr);        //Faz a leitura do valor do RTC
  String date = ctime(&now);         //Faz a leitura da data usando o valor do RTC
  Serial.print(date);                //Escreve na tela a data atual
  delay(1000);                       //Aguarda 1 segundo
}
