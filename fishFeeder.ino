#include <Stepper.h> 
#include "Timer.h"

const int stepsPerRevolution = 500; 
const int portaPino = 2;
const int led=13;
const int motor=9;
Timer t;
int qt=0;

Stepper myStepper(stepsPerRevolution, 7,5,6,4); 

void setup()
{
	Serial.begin(9600);
  	pinMode(portaPino,OUTPUT);
  	pinMode(motor,OUTPUT);
  	pinMode(led,OUTPUT);
	myStepper.setSpeed(60);
	//t.every(20000, callback,(void*)0);   //indica ao timer para executar o callback a cada 12 horas
    t.every(60000*60*8, callback,(void*)0);   //indica ao timer para executar o callback a cada 12 horas
    chamaAoInicializar();
    
}

void girar(int tempo){
	digitalWrite(motor,LOW);
	delay(tempo);
	digitalWrite(motor,HIGH);
	delay(tempo);	
}

void tremer(){
	girar(200);
}

void callback(void *context)
{   Serial.print(qt) ;
    qt++;
  	myStepper.step(120*60);
	digitalWrite(led,digitalRead(led)^1); //alterna o led interno do arduino para acompanhamento.
	tremer();
}

void chamaAoInicializar() // aciona o relé ao inicializar para fins de demonstração.
{
  //myStepper.step(80*60);
  tremer();
}

void loop()
{
  t.update();
}



  
