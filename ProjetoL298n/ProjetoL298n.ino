int IN1 = 9;  // Motor 1
int IN2 = 10; 
int ENA = 3;   // Motor 1 speed control (PWM)
int IN3 = 4;   // Motor 2
int IN4 = 5; 
int ENB = 6;   // Motor 2 speed control (PWM)

int buttonPin1 = 11; // Botão 1 para Motor 1
int buttonPin2 = 12; // Botão 2 para Motor 2

int buttonState1 = 0; // Estado do Botão 1
int buttonState2 = 0; // Estado do Botão 2
int lastButtonState1 = 0; // Último estado do Botão 1
int lastButtonState2 = 0; // Último estado do Botão 2

unsigned long lastDebounceTime1 = 0; // Tempo do último debounce Botão 1
unsigned long lastDebounceTime2 = 0; // Tempo do último debounce Botão 2
unsigned long debounceDelay = 50;    // Tempo de debounce

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(buttonPin1, INPUT_PULLUP);  // Botão 1
  pinMode(buttonPin2, INPUT_PULLUP);  // Botão 2
}

void loop() {
  int reading1 = digitalRead(buttonPin1); // Lê o estado do Botão 1
  int reading2 = digitalRead(buttonPin2); // Lê o estado do Botão 2

  // Verifica se houve uma mudança no Botão 1
  if (reading1 != lastButtonState1) {
    lastDebounceTime1 = millis(); // Registra o tempo da última mudança
  }

  // Verifica se houve uma mudança no Botão 2
  if (reading2 != lastButtonState2) {
    lastDebounceTime2 = millis(); // Registra o tempo da última mudança
  }

  // Debounce para Botão 1
  if ((millis() - lastDebounceTime1) > debounceDelay) {
    if (reading1 == LOW) { // Botão 1 pressionado
      buttonState1 = 1;
    } else {
      buttonState1 = 0;
    }
  }

  // Debounce para Botão 2
  if ((millis() - lastDebounceTime2) > debounceDelay) {
    if (reading2 == LOW) { // Botão 2 pressionado
      buttonState2 = 1;
    } else {
      buttonState2 = 0;
    }
  }

  // Se o Botão 1 for pressionado, aciona o Motor 1 por 5 segundos
  if (buttonState1 == 1) {
    analogWrite(ENA, 200);    // Controla a velocidade do Motor 1 (0-255)
    digitalWrite(IN1, HIGH);  // Motor 1 em frente
    digitalWrite(IN2, LOW);   
    delay(5000);              // Motor 1 roda por 5 segundos

    // Após os 5 segundos, o Motor 1 para
    digitalWrite(IN1, LOW);   // Desativa o Motor 1
    digitalWrite(IN2, LOW);   
    buttonState1 = 0;         // Reseta o estado do Botão 1
  }

  // Se o Botão 2 for pressionado, aciona o Motor 2 por 5 segundos
  if (buttonState2 == 1) {
    analogWrite(ENB, 200);    // Controla a velocidade do Motor 2 (0-255)
    digitalWrite(IN3, HIGH);  // Motor 2 em frente
    digitalWrite(IN4, LOW);   
    delay(5000);              // Motor 2 roda por 5 segundos

    // Após os 5 segundos, o Motor 2 para
    digitalWrite(IN3, LOW);   // Desativa o Motor 2
    digitalWrite(IN4, LOW);   
    buttonState2 = 0;         // Reseta o estado do Botão 2
  }

  lastButtonState1 = reading1; // Atualiza o estado do Botão 1
  lastButtonState2 = reading2; // Atualiza o estado do Botão 2
}
