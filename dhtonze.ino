#include <LiquidCrystal.h>
#include <DHT.h>

int GREEN_LED_PIN = 2;    // pino digital do led verde
int YELLOW_LED_PIN = 3;   // pino digital do led amarelo
int RED_LED_PIN = 4;      // pino digital do led vermelho
int BUZZER_PIN = 5;       // pino digital do buzzer

int lightValue = 0;       // variável para armazenar a leitura do LDR
int greenState = LOW;     // estado do led verde
int yellowState = LOW;    // estado do led amarelo
int redState = LOW;       // estado do led vermelho

const int LDR_PIN = A0;   // variável para armazenar o valor lido pelo ADC
const int DHT_PIN = A1;   // pino digital conectado ao sensor DHT11
const int DHT_TYPE = DHT11;

DHT dht(DHT_PIN, DHT_TYPE);

LiquidCrystal lcd(12, 11, 9, 8, 7, 6);

void setup() {
  Serial.begin(9600);
  pinMode(LDR_PIN, INPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  dht.begin();

  lcd.begin(16, 2);
}

void loop() {
  // Leitura do valor do LDR
  lightValue = analogRead(LDR_PIN);
  float temperatura = 0.0;
  float umidade = 0.0;

  // Realiza a média de 5 leituras dos sensores
  for (int i = 0; i < 5; i++) {
    temperatura += dht.readTemperature();
    umidade += dht.readHumidity();
    delay(50);
  }

  temperatura /= 5.0;
  umidade /= 5.0;

  // Verifica as condições de luminosidade
  if (lightValue < 755) {
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LUZ: BOA");
    lcd.setCursor(0, 1);
    lcd.print("TEMP: ");
    lcd.print(temperatura);
    lcd.print("C");
  } else if (lightValue >= 755 && lightValue <= 935) {
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LUZ: MEIA LUZ");
    lcd.setCursor(0, 1);
    lcd.print("TEMP: ");
    lcd.print(temperatura);
    lcd.print("C");
  } else {
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LUZ: MUITO CLARO");
    lcd.setCursor(0, 1);
    lcd.print("TEMP: ");
    lcd.print(temperatura);
    lcd.print("C");
  }

  // Verifica as condições de temperatura
    if (temperatura >= 10 && temperatura <= 15) {
    lcd.setCursor(8, 0);
    lcd.print("TEMP: OK");
  } else if (temperatura > 15) {
    digitalWrite(YELLOW_LED_PIN, HIGH);
    tone(BUZZER_PIN, 2000);
    lcd.setCursor(0, 1);
    lcd.print("TEMP: ALTA ");
    lcd.setCursor(12, 1);
    lcd.print(temperatura);
    lcd.print("C");
  } else if (temperatura < 10) {
    digitalWrite(YELLOW_LED_PIN, HIGH);
    tone(BUZZER_PIN, 2000);
    lcd.setCursor(0, 1);
    lcd.print("TEMP: BAIXA");
    lcd.setCursor(12, 1);
    lcd.print(temperatura);
    lcd.print("C");
  }

  // Verifica as condições de umidade
  if (umidade >= 50 && umidade <= 70) {
    lcd.setCursor(0, 0);
    lcd.print("UMIDADE: OK     ");
  } else if (umidade > 70) {
    digitalWrite(RED_LED_PIN, HIGH);
    tone(BUZZER_PIN, 2000);
    lcd.setCursor(0, 1);
    lcd.print("UMIDADE: ALTA   ");
    lcd.setCursor(14, 1);
    lcd.print(umidade);
    lcd.print("%");
  } else if (umidade < 50) {
    digitalWrite(RED_LED_PIN, HIGH);
    tone(BUZZER_PIN, 2000);
    lcd.setCursor(0, 1);
    lcd.print("UMIDADE: BAIXA  ");
    lcd.setCursor(14, 1);
    lcd.print(umidade);
    lcd.print("%");
  }

  delay(5000);  // Aguarda 5 segundos antes de realizar a próxima leitura
}
