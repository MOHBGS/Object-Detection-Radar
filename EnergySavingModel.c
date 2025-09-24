int ir1 = 2;        // IR sensor 1 connected to pin 2 (placed at entry side)
int ir2 = 3;        // IR sensor 2 connected to pin 3 (placed at exit side)
int relay = 8;      // Relay (or LED bulb) connected to pin 8
int ledPin = 4;     // Extra LED indicator 1
int ledPin1 = 5;    // Extra LED indicator 2
int ledPin2 = 6;    // Extra LED indicator 3
int personCount = 0; // Counter to keep track of number of people inside

void setup() {
  // Define input/output pins
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  // Keep light OFF initially
  digitalWrite(relay, LOW);

  // Start Serial Monitor for debugging
  Serial.begin(9600);
}

void loop() {
  // ========== Detect ENTRY (Person going inside) ==========
  // If IR1 is blocked first, then IR2 gets blocked → means entry
  if (digitalRead(ir1) == LOW) {            // IR1 blocked
    while (digitalRead(ir2) == HIGH);       // Wait until IR2 also gets blocked
    personCount++;                          // Increase count
    Serial.print("Person Entered, Count = ");
    Serial.println(personCount);
    delay(500);  // Small delay to avoid multiple counts
  }

  // ========== Detect EXIT (Person going outside) ==========
  // If IR2 is blocked first, then IR1 gets blocked → means exit
  if (digitalRead(ir2) == LOW) {            // IR2 blocked
    while (digitalRead(ir1) == HIGH);       // Wait until IR1 also gets blocked
    personCount--;                          // Decrease count
    if (personCount < 0) personCount = 0;   // Avoid negative value
    Serial.print("Person Exited, Count = ");
    Serial.println(personCount);
    delay(500);  // Small delay to avoid multiple counts
  }

  // ========== Control Lights Based on People Count ==========
  if (personCount > 0) {
    digitalWrite(relay, HIGH);  // Turn ON the relay (light)
    digitalWrite(ledPin, HIGH); // Turn ON LED 1
    digitalWrite(ledPin1, HIGH);// Turn ON LED 2
    digitalWrite(ledPin2, LOW); // Turn OFF LED 3
  } else {
    digitalWrite(relay, LOW);   // Turn OFF the relay (light)
    digitalWrite(ledPin, LOW);  // Turn OFF LED 1
    digitalWrite(ledPin1, LOW); // Turn OFF LED 2
    digitalWrite(ledPin2, HIGH);// Turn ON LED 3 (indicating empty room)
  }
}
