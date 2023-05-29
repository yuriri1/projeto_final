#include <AccelStepper.h>
#include <Thermistor.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecureBearSSL.h>

#define PIN4 D4
#define PIN5 D5
#define PIN6 D6
#define PIN7 D7
#define STEPS 32

AccelStepper motor(AccelStepper::FULL4WIRE, PIN4, PIN6, PIN5, PIN7);
Thermistor temp(A0);

const char* ssid = "YuriFi";
const char* password = "12345678";



int tempAtual = 0;
int tempAntg = 0;

void setup() {
	Serial.begin(9600);

  // Setando o motor
	motor.setMaxSpeed(500.0);
	motor.setAcceleration(100.0);
	motor.setSpeed(50);
  motor.setCurrentPosition(0);

  conexao();
  getHTTPS();

	delay(1000);
}

void loop() {

	tempAtual = temp.getTemp();
	if (tempAtual != tempAntg) {
		moverPonteiro();
	}
	delay(5000);
}

void moverPonteiro() {

	Serial.print("Temperatura: ");
	Serial.print(tempAntg);
	Serial.print(" vs. ");
	Serial.println(tempAtual);

	motor.moveTo(TempToPos(tempAtual));

	motor.run();

	while (motor.isRunning()) {
		motor.run();
    yield();
	}

	motor.stop();

	tempAntg = tempAtual;
}

long TempToPos(long tempAtual) {
 return -map(tempAtual-5 , 30, 70, 0, 512);
}

void conexao(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Conectando com o WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println("\n Conectado");
}

void getHTTPS(){
  if((WiFi.status() == WL_CONNECTED)){
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    client -> setInsecure();
    
    HTTPClient https;

    if (https.begin(*client, "https://mocki.io/v1/68d5a59f-0ae3-4c5d-8c3a-8121947d14c9")) {
      int httpCode = https.GET();

      if (httpCode > 0) {
        Serial.printf("[HTTPS] GET... codigo: %d\n", httpCode);
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          Serial.println(payload);
        }
      }else{
        Serial.printf("\nErro %d", httpCode);
      }
    }
    https.end();
  }
}
