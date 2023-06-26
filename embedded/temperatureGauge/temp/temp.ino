#include <AccelStepper.h>
#include <Thermistor.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecureBearSSL.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define PIN4 D4
#define PIN5 D5
#define PIN6 D6
#define PIN7 D7
#define STEPS 32

AccelStepper motor(AccelStepper::FULL4WIRE, PIN4, PIN6, PIN5, PIN7);
Thermistor temp(A0);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

const char *ssid = "CASADOJOARES_2.4";
const char *password = "32380958";

const char *hostEstado = "http://192.168.0.25:8090/estado";
const char *hostTemperatura = "http://192.168.0.25:8080/log";

int tempAtual = 0;
int tempAntg = 0;

void setup()
{
	Serial.begin(9600);

	motor.setMaxSpeed(200.0);
	motor.setAcceleration(50.0);
	motor.setSpeed(30);
	motor.setCurrentPosition(0);

	conexao();

	timeClient.begin();
	timeClient.setTimeOffset(-3 * 3600);

	delay(1000);
}

void loop()
{

	if (getStatus())
	{
		Serial.println("Ligado");
		timeClient.update();
		String hour = timeClient.getFormattedTime();

		tempAtual = temp.getTemp();
		postTemperature(tempAtual, hour);
		if (tempAtual != tempAntg) {
			moverPonteiro();
		}
	}
	else
	{
		Serial.println("Desligado");
	}

	delay(2000);
}

void moverPonteiro()
{

	Serial.print("Temperatura: ");
	Serial.print(tempAntg);
	Serial.print(" vs. ");
	Serial.println(tempAtual);

	motor.moveTo(TempToPos(tempAtual));

	motor.run();

	while (motor.isRunning())
	{
		motor.run();
		yield();
	}

	motor.stop();

	tempAntg = tempAtual;
}

long TempToPos(long tempAtual)
{
	return -map(tempAtual - 5, 30, 70, 0, 512);
}

void conexao()
{
	WiFi.begin(ssid, password);
	Serial.print("Conectando com o WiFi ..");
	while (WiFi.status() != WL_CONNECTED)
	{
		Serial.print(".");
		delay(1000);
	}
	Serial.println("\n Conectado");
}

int getStatus()
{
	if (WiFi.status() == WL_CONNECTED){
		WiFiClient client;
		HTTPClient http;
		http.begin(client, hostEstado);
		int httpCode = http.GET();
		if (httpCode == HTTP_CODE_OK)
		{
			String payload = http.getString();
			Serial.println(httpCode);
			Serial.println(payload);
			if (payload == "on")
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			Serial.println("GET ERROR");
			Serial.println(httpCode);
		}
		http.end();
	}
	return 0;
}

void postTemperature(int temperature, String date_time)
{
	char content[50];
	sprintf(content, "temperature=%d&date_time=%s", temperature, date_time);
	if (WiFi.status() == WL_CONNECTED)
	{
		WiFiClient client;
		HTTPClient http;
		http.begin(client, hostTemperatura);
		http.addHeader("Content-Type", "application/x-www-form-urlencoded");
		int httpCode = http.POST(content);
		if (httpCode == HTTP_CODE_OK)
		{
			Serial.println("POST OK");
			String payload = http.getString();
			Serial.println(httpCode);
			Serial.println(payload);
		}
		else
		{
			Serial.println("POST ERROR");
			Serial.println(httpCode);
		}
		http.end();
	}
	else
	{
		Serial.println("Error in WiFi connection");
	}
}
