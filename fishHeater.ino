#include "Timer.h"
#include "DHT.h"

#define DHTPIN 3     // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);




int portaPino = 2;
int led = 13;
int botao = 12;
Timer t;
int qt = 0;
int state = HIGH;

void setup()
{

	Serial.begin(9600);
	pinMode(portaPino, OUTPUT);
	pinMode(led, OUTPUT);
	pinMode(botao, INPUT_PULLUP);
	t.every(60000 * 60 * 2, callback, (void*)0);
	dht.begin();
	chamaAoInicializar();
}

void alternaRele()
{
	float t = getTemperatura();
	Serial.println("Temperatura: ");
	Serial.println(t);
	if (t <= 20){
		digitalWrite(portaPino, LOW);
		digitalWrite(led, LOW);
		Serial.println("Rele ligado");
		return;
	}
	
	state = digitalRead(led) ^ 1;
	digitalWrite(portaPino, !state);
	digitalWrite(led, state);
}

void callback(void *context)
{
	alternaRele();
}

void chamaAoInicializar() // aciona o relé ao inicializar para fins de demonstração.
{
	state = HIGH;
	digitalWrite(led, state);
	digitalWrite(portaPino, state);
}

float getTemperatura()
{
	float t = dht.readTemperature();
	float h = dht.readHumidity();
	if (isnan(t) || isnan(h))
	{
		Serial.println("Failed to read from DHT sensor!");
		return 0;
	}
	float f = dht.convertCtoF(t);

	float hic = dht.computeHeatIndex(f, h);
	Serial.print("Humidity: ");
	Serial.print(h);
	Serial.print(" %\n");
	Serial.print("Temperature: ");
	Serial.print(t);
	Serial.print(" *C \n");
	Serial.print("Heat index: ");
	Serial.print(hic);
	Serial.print(" *C \n");
	return t;
}

void loop()
{
	t.update();
	int buttonState = digitalRead(botao);
	if (buttonState != HIGH)
	{
		alternaRele();
		while(buttonState == HIGH)
		{
			delay(50);
		};

	}

	delay(300);
}
