#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,16,2);

int IN1 = 9;  // Motor 1
int IN2 = 10;
int ENA = 4;   // Motor 1 speed control (PWM)

int buttonPin1 = 12; // Botão 1 para Motor 1
int pulsePin = 7;    // Entrada de pulsos

volatile int pulseCount = 0;   // Contador de pulsos
bool pulseReady = false;
unsigned long lastPulseTime = 0;
unsigned long pulseDebounceTime = 100; // Tempo mínimo entre pulsos (ms)

void countPulse() {
  unsigned long currentTime = millis();
  if (currentTime - lastPulseTime > pulseDebounceTime) { // Evita ruídos
    pulseCount++;
    lastPulseTime = currentTime;
    Serial.print("Pulsos contados: ");
    Serial.println(pulseCount);
    if (pulseCount >= 12) { // Ajustado para 4 pulsos
      pulseReady = true;
      Serial.println("4 pulsos recebidos! Pronto para ativar o motor.");
    }
  }
}

void setup() {
  Serial.begin(9600); // Ativa comunicação serial para depuração
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
 
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(pulsePin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pulsePin), countPulse, FALLING);

  lcd.init();
  lcd.setBacklight(HIGH);
}

void loop() {
  
  lcd.setCursor(0,0);
  lcd.print(" Valor R$ 3,00");
  float valor = pulseCount * 0.25; // Calcula o valor monetário
  lcd.setCursor(0,1);
  lcd.print("Creditos:R$ ");
  lcd.print(valor, 2); // Exibe com duas casas decimais

  if (!pulseReady) return; // Se não recebeu 12 pulsos, não faz nada

  if (digitalRead(buttonPin1) == LOW) {
    Serial.println("Botão 1 pressionado, ativando Motor 1");
    analogWrite(ENA, 200);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    delay(5000);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    pulseReady = false;
    pulseCount = 0;
    Serial.println("Motor 1 desligado, esperando novos pulsos");
  }
}
