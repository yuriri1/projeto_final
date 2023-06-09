#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

// Informações da rede Wi-Fi
const char* ssid = "CASADOJOARES_5.8";
const char* password = "32380950";

// Endereço IP do servidor
const char* serverIP = "192.168.0.25";
const int serverPort = 8080; // Porta do servidor HTTP

// Dados a serem enviados na requisição POST
const char* postData = "40";

void setup() {
  Serial.begin(115200);
  
  // Conexão com a rede Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  Serial.println("Conectando à rede Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(2000);
  }
  
  Serial.println("Conectado à rede Wi-Fi!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
  
    // Conexão com o servidor
    if (client.connect(serverIP, serverPort)) {
      Serial.println("Conectado ao servidor!");

      // Envia a requisição POST
      client.println("POST /caminho_do_recurso HTTP/1.1");
      client.println("Host: " + String(serverIP));
      client.println("Content-Type: application/x-www-form-urlencoded");
      client.print("Content-Length: ");
      client.println(strlen(postData));
      client.println();
      client.println(postData);

      delay(500); // Aguarda a resposta do servidor

      // Exibe a resposta do servidor
      while (client.available()) {
        String responseLine = client.readStringUntil('\r');
        Serial.print(responseLine);
      }
      
      Serial.println("\nRequisição enviada!");

      // Fecha a conexão
      client.stop();
    }
    else {
      Serial.println("Falha na conexão com o servidor!");
    }
    
    // Aguarda um intervalo antes de fazer a próxima requisição
    delay(5000);
  }
}
