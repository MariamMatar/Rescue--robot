#include <NewPing.h>
#include<Servo.h>
#include <AFMotor.h>
#define lefts A4
#define rights A3
#define TRIG_PIN A0
#define ECHO_PIN A1
#define objectIR A5
NewPing ultrasonic(TRIG_PIN, ECHO_PIN, maxDistance);
Servo myservo;
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
const int MIN_DISTANCE_FROM_OBJECT = 20;
int pos = 180;
const int maxDistance = 200;
int sensitivity_offset = 30;
int LEFT;
int RIGHT;
int Object;
int flag = 0;
int flag2 = 0;
int flagEnd = 0;
void setup() {
pinMode(lefts, INPUT);
pinMode(rights, INPUT);
pinMode(objectIR, INPUT);
myservo.attach(10);
Serial.begin(9600);
}
void loop() {
motor1.setSpeed(100);
motor2.setSpeed(100);
motor3.setSpeed(100);
motor4.setSpeed(100);
if (flag == 0) { //flags for opening and closing the gripper
openServo();
}
if (flag == 1) {
flagEnd = 2;
}
LEFT = (analogRead(lefts));
RIGHT = (analogRead(rights));
Object = (analogRead(objectIR));
if (!hasObstacle()) { //greater than 400 on black less than 400 on white
if (foundObject() && flag2 == 0) {
stopMoving();
delay(15);
closeServo();
if (LEFT < 400 && RIGHT > 400) { // turn left // right on black an left on white.
turnLeft();
}
else if (LEFT > 400 && RIGHT < 400) { //turn right
turnRight();
}
else if (LEFT >= 400 && RIGHT >= 400) { // both on black
stopMoving();
if (flagEnd == 2) {
openServo(); //reached the end
flag = 2;
flagEnd = 3;
}
}
else if (LEFT < 400 && RIGHT < 400) { // both on white
moveForward();
}
}
else
{
if (LEFT < 400 && RIGHT > 400) { // turnleft // right on black an left on white.
turnLeft();
}
else if (LEFT > 400 && RIGHT < 400) { //turn right
turnRight();
}
else if (LEFT >= 400 && RIGHT >= 400) { // both on black
stopMoving();
if (flagEnd == 2) {
openServo(); //reached the end
flag = 2;
flagEnd = 3;
}
}
else if (LEFT < 400 && RIGHT < 400) { // both on white
moveForward();
}
}
}
else { //el ultrasonic shayef obstacle ba3ade menha
for (int i = 0; i <= 2; i++) {
stopMoving();
delay(200);
}
for (int i = 0; i <= 3; i++) {
turnLeft();
delay(200);
}
stopMoving();
delay(200);
for (int i = 0; i <= 2; i++) {
moveForward();
delay(200);
}
stopMoving();
delay(200);
for (int i = 0; i <= 2; i++) {
turnRight();
delay(200);
}
for (int i = 0; i <= 1; i++) {
moveForward();
delay(200);
}
stopMoving();
for (int i = 0; i <= 1; i++) {
turnRight();
delay(200);
}
stopMoving();
for (int i = 0; i <= 1; i++) {
moveForward();
delay(200);
}
stopMoving();
for (int i = 0; i <= 2; i++) {
turnLeft();
delay(200);
}
for (int i = 0; i <= 2; i++) {
stopMoving();
delay(200);
}
motor1.setSpeed(90);
motor2.setSpeed(90);
motor3.setSpeed(90);
motor4.setSpeed(90);
}
}
boolean hasObstacle() {
int distance = ultrasonic.ping_cm();
// Check if distance different of 0, because NewPing library returns 0 if
// the distance is greater than the specified
return distance > 0 && distance <= MIN_DISTANCE_FROM_OBJECT;
}
void moveBack() {
motor1.run(BACKWARD); // move back
motor2.run(BACKWARD);
motor3.run(BACKWARD);
motor4.run(BACKWARD);
}
void moveForward() {
motor1.run(FORWARD);
motor2.run(FORWARD); //forward
motor3.run(FORWARD);
motor4.run(FORWARD);
}
void turnLeft() {
motor3.run(FORWARD); // turn left
motor4.run(FORWARD);
motor1.run(BACKWARD);
motor2.run(BACKWARD);
}
void turnRight() {
motor1.run(FORWARD); // turn right
motor2.run(FORWARD);
motor3.run(BACKWARD);
motor4.run(BACKWARD);
}
void stopMoving() {
motor1.run(RELEASE); //stop
motor2.run(RELEASE);
motor3.run(RELEASE);
motor4.run(RELEASE);
}
boolean foundObject()
{
if (!hasObstacle() && Object <= 500 ) { //found the object
return true;
}
else {
return false;
}
}
void openServo() {
flag = 1;
flagEnd = 1;
for (pos = 30; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
// in steps of 1 degree
myservo.write(pos); // tell servo to go to position in variable 'pos'
delay(15); // waits 15ms for the servo to reach the position
}
}
void closeServo() {
flag2 = 1;
for (pos = 180; pos >= 30; pos -= 1) { // goes from 180 degrees to 0 degrees
myservo.write(pos); // tell servo to go to position in variable 'pos'
delay(15); // waits 15ms for the servo to reach the position
}
}