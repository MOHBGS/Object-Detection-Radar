#include <Servo.h>       // Servo motor control library include

// Pin definitions
const int trigPin = 8;   // Ultrasonic sensor TRIG pin connected to pin 8
const int echoPin = 9;   // Ultrasonic sensor ECHO pin connected to pin 9
int buzzer = 7;          // Buzzer connected to pin 7

// Variables for ultrasonic sensor
long duration;           // Time taken by ultrasonic pulse to return
int distance;            // Calculated distance in centimeters

Servo myServo;           // Create a Servo object to control servo motor

// --------------------- SETUP ---------------------
void setup() {
  pinMode(trigPin, OUTPUT);   // trigPin will send pulse → OUTPUT
  pinMode(echoPin, INPUT);    // echoPin will receive pulse → INPUT
  pinMode(buzzer, OUTPUT);    // buzzer pin is OUTPUT
  Serial.begin(9600);         // Start serial communication at 9600 baud
  myServo.attach(10);         // Attach servo motor signal pin to pin 10
}

// --------------------- LOOP ---------------------
void loop() {
  // Rotate servo from 15° to 165° (left to right)
  for(int i = 15; i <= 165; i++) {    
    myServo.write(i);         // Move servo to current angle
    delay(30);                // Small delay for smooth movement

    distance = calculateDistance();  // Measure distance at this angle

    // If object detected within 40 cm → buzzer ON, else OFF
    if(distance > 0 && distance <= 40) {  
      digitalWrite(buzzer, HIGH);
    } else {
      digitalWrite(buzzer, LOW);
    }

    // Print angle and distance on Serial Monitor
    Serial.print(i);   
    Serial.print(",");   
    Serial.print(distance);   
    Serial.println(" cm");  
  }

  // Rotate servo back from 165° to 15° (right to left)
  for(int i = 165; i > 15; i--) {    
    myServo.write(i);  
    delay(30);  

    distance = calculateDistance();  

    if(distance > 0 && distance <= 40) {  
      digitalWrite(buzzer, HIGH);
    } else {
      digitalWrite(buzzer, LOW);
    }

    Serial.print(i);  
    Serial.print(",");  
    Serial.print(distance);  
    Serial.println(" cm");  
  }  
}

// --------------------- FUNCTION ---------------------
// Function to calculate distance using Ultrasonic sensor
int calculateDistance(){   
  digitalWrite(trigPin, LOW);       // Clear the trigPin
  delayMicroseconds(2);  

  digitalWrite(trigPin, HIGH);      // Send 10µs HIGH pulse to trigger the sensor
  delayMicroseconds(10);  
  digitalWrite(trigPin, LOW);       // End pulse

  duration = pulseIn(echoPin, HIGH);    // Read the time for echo to return
  distance = duration * 0.034 / 2;      // Convert time → distance (cm)
  return distance;  
}