#include <LiquidCrystal.h>
int GREEN_LED_PIN = 2;   // pino digital do led verde
int YELLOW_LED_PIN = 3;  // pino digital do led amarelo
int RED_LED_PIN = 4;     // pino digital do led vermelho
int BUZZER_PIN = 5;      // pino digital do buzzer

int lightValue = 0;    // variavel para armazenar a leitura do LDR
int greenState = LOW;  // estado do led verde
int yellowState = LOW; // estado do led amarelo
int redState = LOW;    // estado do led vermelho

const int LDR_PIN = A0; // variavel para armazenar o valor lido pelo ADC
const int sensorPin = A5;
float valorSensor;
float temperaturaC, temperaturaF;
float tensao = 0.0;    // variavel para armazenar a tensao
float tensao_ms = 0.0; 
LiquidCrystal lcd(12,11,9,8,7,6);
void setup() {
  Serial.begin(9600);
  pinMode(LDR_PIN, INPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(sensorPin, INPUT);
  lcd.begin(16, 2);
}
void loop() {
  // Leitura do valor do LDR
  lightValue = analogRead(LDR_PIN);
  valorSensor = analogRead(sensorPin);
  tensao = valorSensor * 5.0 / 1024.0; // encontra a tensao do sensor
  temperaturaC = ((tensao - 0.5) * 100.0); // converte para temperatura em graus Celsius

  if ((lightValue <= 935 && lightValue>=755) && (temperaturaC>=16 && temperaturaC<=25)) {
    // Luminosidade media - liga led amarelo e desliga verde
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
    noTone(BUZZER_PIN); // para o som do buzzer
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LUZ: MEDIA");
    lcd.setCursor(0, 1);
    lcd.print("TEMP: MEDIA");
    delay(2000);
} else if ((lightValue >= 935) || (temperaturaC<=0 ||temperaturaC>=26)) {
    // Luminosidade alta - liga led vermelho e desliga verde e amarelo
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000);// toca um som de 1kHz no buzzer
    delay(1000);
    tone(BUZZER_PIN, 2000);
    noTone(BUZZER_PIN);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ALERTA!!!");
    lcd.setCursor(0, 1);
    lcd.print("Condicoes ruins");
    delay(2000);
	}
else{
  // Luminosidade baixa - liga led verde e desliga os outros
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  noTone(BUZZER_PIN); // para o som do buzzer
  lcd.clear();
  lcd.setCursor(0, 0);
  if (lightValue < 755) {
    lcd.print("LUZ: BOA");
  } else {
    lcd.print("LUZ: BOA");
  }
    lcd.setCursor(0, 1);
  if (temperaturaC < 16) {
    lcd.print("TEMP: BOA");
  } else if (temperaturaC > 25) {
    lcd.print("TEMP: ALTA");
  } else {
    lcd.print("TEMP: MEDIA");
  }
    delay(2000);
}
  lcd.setCursor(0, 1);
  lcd.print("TEMP: "); // imprime o texto "Temperatura:"
  lcd.print(temperaturaC);
  lcd.print("C");
  lcd.setCursor(0, 0);
  lcd.print("LUZ: ");
  lcd.print(lightValue);
  delay(2000);
  // imprime valor lido pelo arduino (0 a 1023)
  tensao_ms = (lightValue * 5.0) / 1024.0;
  Serial.print("Leitura: ");
  Serial.print(lightValue);
  Serial.print("\t"); // tabulacao
  Serial.print("Temperatura atual (°C): "); // Printando em graus Celsius
  Serial.print(temperaturaC);
  Serial.print("\t");
  Serial.print("Voltagem: ");
  Serial.print(tensao_ms);
  Serial.println("V");
  delay(1000);
}
