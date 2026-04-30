//C++
// Ohmmeter Better

const int analogInPin = A0;   // measure voltage
const int pinCount = 4;       // Number of ref resistors
int refPins[pinCount] = {4, 5, 6, 7}; // Pins for ref resistors
float refValues[pinCount] = {1000.0, 10000.0, 100000.0, 1000000.0, }; // Values in Ohms

void setup() {
  Serial.begin(9600);                
  for (int i = 0; i < pinCount; i++) {
    pinMode(refPins[i], INPUT); // Set as input
  }
}

void loop() {
  for (int i = 0; i < pinCount; i++) {
    // 1. Activate one ref resistor
    pinMode(refPins[i], OUTPUT);
    digitalWrite(refPins[i], HIGH);
    delay(10); // Settle time

    // 2. Read Voltage
    int rawValue = analogRead(analogInPin);
    float vOut = (5.0 * rawValue) / 1023.0;

    // 3. Calculate Resistance if within valid range (avoiding too low/high)
    if (vOut > 0.8 && vOut < 4.2) {
      float rX = refValues[i] * (vOut / (5.0 - vOut));
      Serial.print("Ref: "); Serial.print(refValues[i]);
      Serial.print(" Ohms - R_unknown: "); Serial.print(rX);
      Serial.println(" Ohms");
    }

    // 4. Deactivate ref resistor
    digitalWrite(refPins[i], LOW);
    pinMode(refPins[i], INPUT);
    delay(100);
  }
  Serial.println("---");
  delay(1000);
}
