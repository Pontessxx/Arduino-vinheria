#include <LiquidCrystal.h>

// Definindo as constantes dos pinos
const int temperatureSensorPin = A0;
const int humiditySensorPin = A1;
const int LDRPin = A2;
const int GREEN_LED_PIN = 2;
const int YELLOW_LED_PIN = 3;
const int RED_LED_PIN = 4;
const int BUZZER_PIN = 10;
const int LCD_RS = 12;
const int LCD_EN = 11;
const int LCD_D4 = 8;
const int LCD_D5 = 7;
const int LCD_D6 = 6;
const int LCD_D7 = 5;

// Inicialização do LCD
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void setup() {
  Serial.begin(9600);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  lcd.begin(16, 2);
}

void loop() {
  int temperature = readTemperature();
  int humidity = readHumidity();
  int lightLevel = readLightLevel();
  // Exibição dos valores no monitor serial
  Serial.print("Temperature: ");
  Serial.print(temperature, 1);
  Serial.print(" °C / ");
  Serial.println();

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
  Serial.print("Leitura: ");
  Serial.print(lightLevel);
  Serial.print("\t");

  // Verificar a condição do ambiente
  if (lightLevel >= 950 || temperature >= 15 || humidity > 70 ||temperature <=9) {
    // Ambiente ruim - LED vermelho aceso
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000);
    umiPrint();
    luzPrint();
    tempPrint();
  } else if (lightLevel >= 650 && lightLevel<=949) {
    // Ambiente mediano - LED amarelo aceso
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
    noTone(BUZZER_PIN);
    umiPrint();
    luzPrint();
    tempPrint();
    }else if (lightLevel<=649 && (temperature >= 10 && temperature <= 15 || humidity<50)){
    // Ambiente bom - LED verde aceso
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
    noTone(BUZZER_PIN);
    umiPrint();
    luzPrint();
    tempPrint();
  }

  delay(5000);  // Aguardar 5 segundos antes de atualizar os valores novamente
}
int readTemperature() {
  int rawValue = analogRead(temperatureSensorPin);
  double voltage = (rawValue / 1023.0) * 5000; // 5000 para obter milivolts
  double celsius = (voltage - 500) * 0.1; // 500 é o deslocamento
  return celsius;
}
int readHumidity() {
  int rawValue = analogRead(humiditySensorPin);
  int percentage = map(rawValue, 0, 1023, 0, 100);
  return percentage;
}
int readLightLevel() {
  int rawValue = analogRead(LDRPin);

  return rawValue;
}
int luzPrint(){
    
    int lightLevel = readLightLevel();
    if (lightLevel >= 950 ){
        lcd.setCursor(0, 0);
        lcd.print("Ambiente:  ");
        lcd.setCursor(0, 1);
        lcd.print("Muito claro    ");
        delay(2000);
        lcd.clear();
    }else if (lightLevel >= 650 && lightLevel<=949){
        lcd.setCursor(0, 0);
        lcd.print("Ambiente:  ");
        lcd.setCursor(0, 1);
        lcd.print("A meia Luz    ");
        delay(2000);
        lcd.clear();
    }else if (lightLevel<=649){
        lcd.setCursor(0, 0);
        lcd.print("Ambiente    ");
        lcd.setCursor(0, 1);
        lcd.print("Perfeito       ");
        delay(2000);
        lcd.clear();
    }
}
int tempPrint(){
    int temperature = readTemperature();
    
    if(temperature <=9 || temperature >=15){
        lcd.setCursor(0, 0);
        lcd.print("Temp. ALTA    ");
        lcd.setCursor(0, 1);
        lcd.print("Temp. = ");
        lcd.print(temperature);
        lcd.print(" C");
        delay(2000);
        lcd.clear();
    }else{
        lcd.setCursor(0, 0);
        lcd.print("Temp. OK    ");
        lcd.setCursor(0, 1);
        lcd.print("Temp. = ");
        lcd.print(temperature);
        lcd.print(" C");
        delay(2000);
        lcd.clear();
    }
}
int umiPrint(){
    int humidity = readHumidity();
    if (humidity>70){
        lcd.print("Umidade ALTA   ");
        lcd.setCursor(0, 1);
        lcd.print("Umid. = ");
        lcd.print(humidity);
        lcd.print(" %");
    }else{
        lcd.print("Umidade BAIXA   ");
        lcd.setCursor(0, 1);
        lcd.print("Umid. = ");
        lcd.print(humidity);
        lcd.print(" %");
        delay(2000);
        lcd.clear();
    }
}
