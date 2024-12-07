
#include <Servo.h> // Include Servo library for servo control  
// Pin Definitions  
const int trigPIN = 13; // Ultrasonic sensor trigger pin  
const int echoPIN = 12; // Ultrasonic sensor echo pin  
const int AIN = 7; // Motor A direction pin  
const int LEFT_BIN = 8; // Motor B direction pin  
const int PWMA = 5; // Motor A PWM pin  
const int PWMB = 6; // Motor B PWM pin  
const int STBY = 3; // Standby pin for motor driver  
Servo myservo; // Servo object for scanning  
// Global Variables  
float distance = 0; // Distance from ultrasonic sensor  
const int threshold = 35; // Obstacle distance threshold in cm  
int pos = 90; // Initial servo position (center)  
// Function Prototypes  
void sensor();  
void forward(int speed);  
void stopped();  
void backward(int speed);  
void turnLeft(int speed);  
void turnRight(int speed);  
void setup() {  
Serial.begin(9600); // Initialize serial communication  
pinMode(trigPIN, OUTPUT); // Set ultrasonic trigger pin as output  
pinMode(echoPIN, INPUT); // Set ultrasonic echo pin as input  
pinMode(AIN, OUTPUT); // Motor control pins  
pinMode(LEFT_BIN, OUTPUT);  
pinMode(STBY, OUTPUT);  
myservo.attach(10); // Attach servo to pin 10  
myservo.write(90); // Center servo  
delay(500); // Wait for servo to stabilize  
}  
void loop() {  
sensor(); // Check distance using ultrasonic sensor  
delay(500);  
if (distance > threshold) {  
forward(60); // Move forward if no obstacle  
} else {  
stopped(); // Stop the car if obstacle detected  
 
 
// Check left  
myservo.write(180); // Turn servo to left  
delay(500);  
sensor();  
 
 
if (distance > threshold) {  
turnLeft(120); // Turn left if no obstacle on the left  
myservo.write(90); // Reset servo to center  
delay(500);  
forward(70); // Move forward  
} else {  
// Check right  
myservo.write(0); // Turn servo to right  
delay(500);  
sensor();  
 
 
if (distance > threshold) {  
turnRight(120); // Turn right if no obstacle on the right  
myservo.write(90); // Reset servo to center  
delay(500);  
forward(60); // Move forward  
} else {  
// Reverse and re-evaluate  
myservo.write(90); // Turn servo backward  
delay(500);  
sensor();  
 
 
backward(70); // Move backward  
delay(1000); // Reverse for 1 second  
turnRight(200);  
stopped(); // Stop to re-evaluate  
}  
}  
}  
}  
void sensor() {  
// Send ultrasonic pulse  
digitalWrite(trigPIN, LOW);  
delayMicroseconds(2);  
digitalWrite(trigPIN, HIGH);  
delayMicroseconds(10);  
digitalWrite(trigPIN, LOW);  
 
 
// Measure pulse duration  
float duration = pulseIn(echoPIN, HIGH);  
 
 
// Calculate distance in cm  
distance = (duration / 2) * 0.0343;  
 
 
// Print distance to Serial Monitor  
Serial.print("Distance: ");  
if (distance >= 400 || distance <= 2) {  
Serial.println("Out of Range");  
distance = 400; // Treat out-of-range as max distance  
} else {  
Serial.print(distance);  
Serial.println(" cm");  
}  
}  
// Motor Control Functions  
void forward(int speed) {  
digitalWrite(AIN, LOW); // Reverse motor A 
digitalWrite(STBY, HIGH);  
analogWrite(PWMA, speed);  
digitalWrite(LEFT_BIN, LOW); // Reverse motor B 
analogWrite(PWMB, speed);  
}  
void stopped() {  
digitalWrite(AIN, LOW);  
digitalWrite(STBY, HIGH);  
analogWrite(PWMA, 0);  
digitalWrite(LEFT_BIN, LOW);  
analogWrite(PWMB, 0);  
}  
void backward(int speed) {  
digitalWrite(AIN, HIGH); // Forward motor A  
digitalWrite(STBY, HIGH);  
analogWrite(PWMA, speed);  
digitalWrite(LEFT_BIN, HIGH); // Forward motor B  
analogWrite(PWMB, speed);  
}  
void turnRight(int speed) {  
digitalWrite(AIN, LOW); // Reverse motor A  
digitalWrite(STBY, HIGH);  
analogWrite(PWMA, speed);  
digitalWrite(LEFT_BIN, HIGH); // Forward motor B  
analogWrite(PWMB, speed);  
delay(500); // Turn duration  
stopped();  
}  
void turnLeft(int speed) {  
digitalWrite(AIN, HIGH); // Forward motor A  
digitalWrite(STBY, HIGH);  
analogWrite(PWMA, speed);  
digitalWrite(LEFT_BIN, LOW); // Reverse motor B  
analogWrite(PWMB, speed);  
delay(500); // Turn duration  
stopped();  
}  
 
 
 