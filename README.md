# Arduino Project: Pulse-Based Motor Control with LCD Display

## Description
This Arduino-based project controls a **12V water pump** using pulse counting and a push button. It displays credit values on an I2C LCD screen and activates the pump when a specific amount is reached.

## Components Used
- **Arduino Micro** – Microcontroller to handle logic and control
- **L298N Motor Driver** – Controls the 12V water pump
- **12V Water Pump** – Activated when sufficient credits are collected
- **Push Button** – Used to manually trigger the pump
- **LCD Display (16x2) with I2C Module** – Displays credit balance
- **Coin Selector** – Generates pulses based on inserted coins
- **Resistors and Wires** – Additional electronic components for connections

## How It Works
1. The system continuously monitors pulses received from the **coin selector**.
2. Each pulse corresponds to **R$ 0.25**, and after **12 pulses (R$ 3.00)**, the system becomes ready to activate the pump.
3. The accumulated credit is displayed on the LCD.
4. When the **push button** is pressed after collecting **R$ 3.00**, the **pump** activates for **5 seconds**.
5. After activation, the pulse counter resets to zero, and the system waits for new pulses.

## Code Breakdown

### Libraries and LCD Initialization
```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); // Initialize LCD with I2C address 0x27
```

### Pin Definitions
```cpp
int IN1 = 9;  // Motor 1 (Pump)
int IN2 = 10;
int ENA = 4;  // Pump speed control (PWM)

int buttonPin1 = 12; // Push button for activation
int pulsePin = 7;    // Coin selector pulse input pin
```

### Variables for Pulse Counting
```cpp
volatile int pulseCount = 0;   // Pulse counter
bool pulseReady = false;
unsigned long lastPulseTime = 0;
unsigned long pulseDebounceTime = 100; // Minimum time between pulses (ms)
```

### Pulse Counting Function
```cpp
void countPulse() {
  unsigned long currentTime = millis();
  if (currentTime - lastPulseTime > pulseDebounceTime) { // Debounce filter
    pulseCount++;
    lastPulseTime = currentTime;
    Serial.print("Pulses counted: ");
    Serial.println(pulseCount);
    if (pulseCount >= 12) { // 12 pulses equal R$ 3.00
      pulseReady = true;
      Serial.println("12 pulses received! Ready to activate the pump.");
    }
  }
}
```

### Setup Function
```cpp
void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
 
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(pulsePin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pulsePin), countPulse, FALLING);

  lcd.init();
  lcd.setBacklight(HIGH);
}
```

### Main Loop
```cpp
void loop() {
  lcd.setCursor(0,0);
  lcd.print(" Value R$ 3.00");
  float value = pulseCount * 0.25; // Convert pulses to monetary value
  lcd.setCursor(0,1);
  lcd.print("Credits:R$ ");
  lcd.print(value, 2); // Display with two decimal places

  if (!pulseReady) return; // Do nothing if 12 pulses are not reached

  if (digitalRead(buttonPin1) == LOW) {
    Serial.println("Button pressed, activating Pump");
    analogWrite(ENA, 200);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    delay(5000);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    pulseReady = false;
    pulseCount = 0;
    Serial.println("Pump deactivated, waiting for new pulses");
  }
}
```

## Summary
- The system **counts pulses** from the **coin selector** and converts them into **monetary credit**.
- When **R$ 3.00 is reached**, the system **allows pump activation** through a push button.
- Pressing the **button activates the 12V water pump** for **5 seconds**.
- The system **resets** and waits for new pulses.

This setup can be used for **coin/token-based water dispensing machines, vending machines, or prepaid systems** that require pulse-based credit tracking.

---
## Wiring Diagram
![Untitled Sketch 2_bb](https://github.com/user-attachments/assets/6b9ea321-5a88-4253-b4b1-5511f0c7b89d)

## Demonstration
To see the system in action, add a GIF here showing the **coin selector, LCD updates, and pump activation**.
![1](https://github.com/user-attachments/assets/1d0164c1-843c-4a76-8cd8-6f109b94f0af)

