int ir1 = 2;        // First IR sensor connected to pin 2
int ir2 = 3;        // Second IR sensor connected to pin 3
int relay = 8;      // Relay (or you can use LED) connected to pin 8
int ledPin = 4;     // First extra LED on pin 4
int ledPin1 = 5;    // Second extra LED on pin 5
int ledPin2 = 6;    // Third extra LED on pin 6
int personCount = 0; // Variable to keep track of number of people

void setup() {
  pinMode(ir1, INPUT);      // Set IR sensor 1 as input
  pinMode(ir2, INPUT);      // Set IR sensor 2 as input
  pinMode(relay, OUTPUT);   // Relay pin as output
  pinMode(ledPin, OUTPUT);  // LED 1 pin as output
  pinMode(ledPin1, OUTPUT); // LED 2 pin as output
  pinMode(ledPin2, OUTPUT); // LED 3 pin as output

  digitalWrite(relay, LOW); // Keep relay/light OFF when starting
  Serial.begin(9600);       // Start serial monitor to print data
}
