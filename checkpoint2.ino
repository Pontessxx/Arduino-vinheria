#include <LiquidCrystal.h>
int GREEN_LED_PIN = 2;   // pino digital do led verde
int YELLOW_LED_PIN = 3;  // pino digital do led amarelo
int RED_LED_PIN = 4;     // pino digital do led vermelho
int BUZZER_PIN = 5;      // pino digital do buzzer

int lightValue = 0;    // variável para armazenar a leitura do LDR
int greenState = LOW;  // estado do led verde
int yellowState = LOW; // estado do led amarelo
int redState = LOW;    // estado do led vermelho

const int LDR_PIN = A0; // variável para armazenar o valor lido pelo ADC
const int sensorPin = A5;
float valorSensor;
float temperaturaC, temperaturaF;
float tensao = 0.0;    // variável para armazenar a tensão

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
  tensao = valorSensor * 5.0 / 1024.0; // encontra a tensão do sensor
  temperaturaC = ((tensao - 0.5) * 100.0); // converte para temperatura em graus Celsius
  
  // Checagem do nível de luminosidade
  if (lightValue <= 935 && lightValue>=755) {
    // Luminosidade média - liga led amarelo e desliga verde
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
    noTone(BUZZER_PIN);   // para o som do buzzer
    
    //lcd.clear();
    //lcd.setCursor(0, 0);
    //lcd.print("LUZ e TEMP:");
    //lcd.setCursor(0, 1);
    //lcd.print("MEDIA");
    //delay(2000);
    
  } else if (lightValue >= 935) {
    // Luminosidade alta - liga led vermelho e desliga verde e amarelo
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000);// toca um som de 1kHz no buzzer
    	delay(1000);
    tone(BUZZER_PIN, 2000);
    noTone(BUZZER_PIN);
    
    //lcd.clear();
    //lcd.setCursor(0, 0);
    //lcd.print("CUIDADO!!!");
    //lcd.setCursor(0, 1);
    //lcd.print("Produto danificado");
    //delay(2000);
    
  } else {
    // Luminosidade baixa - liga led verde e desliga os outros
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
    noTone(BUZZER_PIN);   // para o som do buzzer
    
    //lcd.clear();
    //lcd.setCursor(0, 0);
    //lcd.print("LUZ e TEMP:");
    //delay(2000);
  }
  //lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("TEMP: "); // imprime o texto "Temperatura:"
  lcd.print(temperaturaC);
  lcd.print("C");
  lcd.setCursor(0, 1); 
  lcd.print("LUZ: ");
  lcd.print(lightValue);
  lcd.print(" UV  ");

  // imprime valor lido pelo arduino (0 a 1023)
  Serial.print("Leitura: ");
  Serial.print(lightValue);
  Serial.print("\t"); // tabulacao     

  Serial.print("Temperatura atual (°C): ");  // Printando em graus Celsius
  Serial.println(temperaturaC);
  delay(1000);
}