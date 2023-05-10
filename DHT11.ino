#include "DHT.h"
#include <LiquidCrystal.h>

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
int BUZZER_PIN = 5;
LiquidCrystal lcd(12, 11, 8, 7, 6, 5);

const int NUM_LEITURAS = 5; // número de leituras para a média
const int INTERVALO_LEITURAS = 5000; // intervalo entre leituras (em milissegundos)

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600); // 9600bps
  pinMode(pinoLDR, INPUT);
  dht.begin(); // inicializa o sensor DHT
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  lcd.begin(16, 2);
}

void loop() {
  float temperaturaMedia = 0.0;
  float umidadeMedia = 0.0;
  int leituraMedia = 0;

  // Realiza a média de leituras
  for (int i = 0; i < NUM_LEITURAS; i++) {
    // Aguarda o intervalo entre as leituras
    delay(INTERVALO_LEITURAS);

    // Lê a temperatura e umidade
    temperatura = dht.readTemperature();
    umidade = dht.readHumidity();
    leitura = analogRead(pinoLDR);

    // Verifica se ocorreu alguma falha durante a leitura
    if (isnan(umidade) || isnan(temperatura)) {
      Serial.println("Falha na leitura do Sensor DHT!");
      continue;
    }

    // Soma os valores para calcular a média posteriormente
    temperaturaMedia += temperatura;
    umidadeMedia += umidade;
    leituraMedia += leitura;
  }

  // Calcula a média dos valores lidos
  temperaturaMedia /= NUM_LEITURAS;
  umidadeMedia /= NUM_LEITURAS;
  leituraMedia /= NUM_LEITURAS;

  // Exibe as informações no monitor serial
  Serial.print("Temperatura: ");
  Serial.print(temperaturaMedia);
  Serial.print(" *C\t");

  Serial.print("Umidade: ");
  Serial.print(umidadeMedia);
  Serial.print(" %\t");

  Serial.print("Leitura: ");
  Serial.print(leituraMedia);
  Serial.print("\t");

  tensao = leituraMedia * 5.0 / 1024.0;
  Serial.print("Tensão: ");
  Serial.print(tensao);
  Serial.print("V");
  Serial.println();

  // Controle do LED e do Buzzer com base nas condições do ambiente
  if (leituraMedia <= 650 && leituraMedia >= 400) {
    // Ambiente escuro - liga LED verde
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
    noTone(BUZZER_PIN);
  } else if (leituraMedia > 650) {
    // Ambiente a meia luz - liga LED amarelo e exibe mensagem no display
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
    noTone(BUZZER_PIN);
    lcd.setCursor(0, 0);
    lcd.print("Ambiente a meia luz");
  } else {
    // Ambiente totalmente iluminado - liga LED vermelho, buzzer contínuo e exibe mensagem no display
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000); // toca um som de 1kHz no buzzer
    lcd.setCursor(0, 0);
    lcd.print("Ambiente muito claro");
  }

  // Exibição da temperatura no display
  if (temperaturaMedia >= 10 && temperaturaMedia <= 15) {
    lcd.setCursor(0, 1);
    lcd.print("Temperatura OK  ");
  } else if (temperaturaMedia > 15) {
    lcd.setCursor(0, 1);
    lcd.print("Temp. Alta      ");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Temp. Baixa     ");
  }
  lcd.setCursor(12, 1);
  lcd.print(temperaturaMedia);
  lcd.print("*C");

  // Exibição da umidade no display
  if (umidadeMedia >= 50 && umidadeMedia <= 70) {
    lcd.setCursor(0, 0);
    lcd.print("Umidade OK      ");
  } else if (umidadeMedia > 70) {
    lcd.setCursor(0, 0);
    lcd.print("Umidade Alta    ");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Umidade Baixa   ");
  }
  lcd.setCursor(13, 0);
  lcd.print(umidadeMedia);
  lcd.print("%");

  lcd.clear();
}
  
}
