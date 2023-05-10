#include "DHT.h"

const int pino_dht = 9; // pino onde o sensor DHT está conectado
float temperatura; // variável para armazenar o valor de temperatura
float umidade; // variável para armazenar o valor de umidade

const int pinoLDR = A0; // pino onde o LDR está conectado

int leitura = 0; // variável para armazenar o valor lido pelo ADC
float tensao = 0.0; // variável para armazenar a tensão

DHT dht(pino_dht, DHT11); // define o pino e o tipo de DHT

int GREEN_LED_PIN = 2;   // pino digital do led verde
int YELLOW_LED_PIN = 3;  // pino digital do led amarelo
int RED_LED_PIN = 4;     // pino digital do led vermelho
void setup() {
 
  Serial.begin(9600); // 9600bps
  pinMode(pinoLDR, INPUT);
  dht.begin(); // inicializa o sensor DHT
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
}

void loop() {
  // Aguarda alguns segundos entre uma leitura e outra
  delay(2000); // 2 segundos (Datasheet)
 
  // A leitura da temperatura ou umidade pode levar 250ms
  // O atraso do sensor pode chegar a 2 segundos
  temperatura = dht.readTemperature(); // lê a temperatura em Celsius
  umidade = dht.readHumidity(); // lê a umidade

  // Se ocorreu alguma falha durante a leitura
  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("Falha na leitura do Sensor DHT!");
  }
  else { // Se não
    // Imprime o valor de temperatura  
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.print(" *C ");
    
    Serial.print("\t"); // tabulação
  
    // Imprime o valor de umidade
    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.print(" %\t"); 
    // imprime valor lido pelo arduino (0 a 1023)
    Serial.print("Leitura: ");
    Serial.print(leitura);
    Serial.print("\t"); // tabulacao

    // converte e imprime o valor em tensão elétrica
    tensao = leitura * 5.0 / 1024.0;
    Serial.print("Tensão: ");
    Serial.print(tensao);
    Serial.print("V");

    Serial.println(); // nova linha

  }

  leitura = analogRead(pinoLDR);
  if ((leitura <= 650 && leitura>=400)||(temperatura>=15 && temperatura<=25)) {
    // Luminosidade média - liga led amarelo e desliga verde
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
    
  } else if ((leitura >= 650 )||(temperatura>=25 || temperatura<=0)) {
    // Luminosidade alta - liga led vermelho e desliga verde e amarelo
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
  } else if(temperatura>=10 && temperatura<=15){
    // Luminosidade baixa - liga led verde e desliga os outros
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
  }
  
}
