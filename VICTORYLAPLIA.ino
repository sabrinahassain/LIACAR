// VICTORY LAP CODE, in this code the robot will turn around the table and return to it's starting point.

const int pinA = 5; // control the speed range 0 to 255 motor A  
const int pinB = 6; // control the speed range 0 to 255 motor B  
const int pinC = 7; // control the direction for motor A  
const int pinD = 8; // control the direction for motor B  
const int pinE = 3; // standby to make the whole car stop  
int carState = 1; // controls if car is on or off  
 
 
void setup() {  
pinMode(pinA, OUTPUT);  
pinMode(pinB, OUTPUT);  
pinMode(pinC, OUTPUT);  
pinMode(pinD, OUTPUT);  
pinMode(pinE, OUTPUT);  
}  
 
 
void loop() {  
forward(); // Move forward 
delay(3700); // Move forward for 3 seconds 
turnRight(); // Turn right 
delay(4000); // Turn right for 1 second 
forward();  //forward
delay(4000); //for 4 seconds 
turnRight(); //the car turns right
delay(4000); //for 4 seconds
forward(); 
delay(4000); 
turnLeft(); //the car will turn left 
delay(4500); //for 4,5 seconds
forward(); 
delay(3700); 
turnRight(); // Turn right 
delay(4000); // Turn right for 1 second 
 
} 
 
 
// Function to move the car forward 
void forward() {  
digitalWrite(pinC, LOW); // Motor A moves forward  
analogWrite(pinA, 50); // Motor A speed  
digitalWrite(pinD, LOW); // Motor B moves forward  
analogWrite(pinB, 50); // Motor B speed  
digitalWrite(pinE, carState); // Enable the car (standby pin)  
}  
 
 
// Function to move the car backward 
void backward() {  
digitalWrite(pinC, HIGH); // Motor A moves backward  
analogWrite(pinA, 50); // Motor A speed  
digitalWrite(pinD, HIGH); // Motor B moves backward  
analogWrite(pinB, 50); // Motor B speed  
digitalWrite(pinE, carState); // Enable the car (standby pin)  
}  
 
 
// Function to turn the car left 
void turnLeft() { 
digitalWrite(pinC, LOW); // Motor A moves forward 
analogWrite(pinA, 50); // Motor A speed 
digitalWrite(pinD, LOW); // Motor B stops (doesn't move) 
analogWrite(pinB, 0); // Motor B speed = 0 (stop) 
digitalWrite(pinE, carState); // Enable the car 
} 
 
 
// Function to turn the car right 
void turnRight() { 
digitalWrite(pinC, LOW); // Motor A stops (doesn't move) 
analogWrite(pinA, 0); // Motor A speed = 0 (stop) 
digitalWrite(pinD, HIGH); // Motor B moves forward 
analogWrite(pinB, 50); // Motor B speed 
digitalWrite(pinE, carState); // Enable the car 
} 
 
 

