// Pin Definitions for Motor Control 
int pinC = 7; // Left motor direction 
int pinD = 8; // Right motor direction 
int pinA = 5; // Left motor speed (PWM) 
int pinB = 6; // Right motor speed (PWM) 
int pinE = 3; // Standby pin to stop the whole car 
 
 
void setup() {  
Serial.begin(9600);  
// Set motor control pins as outputs 
pinMode(pinC, OUTPUT);  
pinMode(pinD, OUTPUT);  
pinMode(pinE, OUTPUT);  
// Set motor speed control pins as outputs 
pinMode(pinA, OUTPUT); 
pinMode(pinB, OUTPUT); 
}  
 
 
void loop() {  
// Read sensor values 
int rightSensor = analogRead(A0);  
int middleSensor = analogRead(A1);  
int leftSensor = analogRead(A2);  
 
 
// Check if all sensors are off the line (no line detected) 
if (rightSensor == 41 && middleSensor == 39 && leftSensor == 43) {  
stopMotors(0);  
}  
// Move backward if the middle sensor detects the line 
if (middleSensor >= 500 && middleSensor <= 1500) {  
moveBackward(50);  
}  
// Turn left if the right sensor detects the line 
if (rightSensor >= 500 && rightSensor <= 1500) {  
turnLeft(50);  
}  
// Turn right if the left sensor detects the line 
if (leftSensor >= 500 && leftSensor <= 1500) {  
turnRight(50);  
}  
// If all sensors are off the line, perform a U-turn 
if (middleSensor < 39 && rightSensor < 41 && leftSensor < 43) {  
makeUTurn(100);  
}  
 
 
// Debugging output to Serial Monitor 
Serial.print("Right Sensor = "); 
Serial.print(rightSensor); 
Serial.print("\t"); 
Serial.print("Middle Sensor = "); 
Serial.print(middleSensor); 
Serial.print("\t"); 
Serial.print("Left Sensor = "); 
Serial.println(leftSensor); 
}  
 
 
// Stop motors 
void stopMotors(int speedValue) {  
digitalWrite(pinC, HIGH); // Left motor stop 
digitalWrite(pinD, HIGH); // Right motor stop 
analogWrite(pinA , speedValue); // Set left motor speed to 0 
analogWrite(pinB, speedValue); // Set right motor speed to 0 
digitalWrite(pinE, HIGH); // Enable the motors 
}  
 
 
// Perform a U-turn 
void makeUTurn(int speedValue) {  
digitalWrite(pinC, HIGH);  
analogWrite(pinA, speedValue);  
digitalWrite(pinD, LOW);  
analogWrite(pinB, speedValue / 2);  
digitalWrite(pinE, HIGH);  
} 
 
 
// Move backward (now switched with forward) 
void moveBackward(int speedValue) { 
digitalWrite(pinC, LOW); // Left motor backward 
digitalWrite(pinD, LOW); // Right motor backward 
analogWrite(pinA, speedValue); // Set left motor speed 
analogWrite(pinB, speedValue); // Set right motor speed 
digitalWrite(pinE, HIGH); // Enable the motors 
}  
 
 
// Turn left 
void turnLeft(int speedValue) { 
digitalWrite(pinC, LOW); // Left motor backward 
digitalWrite(pinD, HIGH); // Right motor forward 
analogWrite(pinA, speedValue); // Set left motor speed 
analogWrite(pinB, speedValue); // Set right motor speed 
digitalWrite(pinE, HIGH); // Enable the motors 
} 
 
 
// Turn right 
void turnRight(int speedValue) { 
digitalWrite(pinC, HIGH); // Left motor forward 
digitalWrite(pinD, LOW); // Right motor backward 
analogWrite(pinA, speedValue); // Set left motor speed 
analogWrite(pinB, speedValue); // Set right motor speed 
digitalWrite(pinE, HIGH); // Enable the motors 
} 
 
 
LINETRACKING1.ino