#include <Servo.h>

#define TRIG_PIN 10
#define ECHO_PIN 11
#define SERVO_PIN 12

bool opened = false;
Servo servo;


void setup() {
  Serial.begin (115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  servo.attach(SERVO_PIN);
  delay(1);
  servo.write(0);
  delay(500);
  servo.detach();
}


void loop() {
  if (distance() < 50) {
    if (!opened) {
      Serial.println("Opening");
      servo.attach(SERVO_PIN);
      delay(1);
      servo.write(120);
      delay(500);
      servo.detach();
      opened = true;
    }
  } else {
    if (opened) {
      delay(50);
      if (distance() < 50) { // re-check to avoid false positives
        Serial.println("Closing");
        delay(1000);
        servo.attach(SERVO_PIN);
        delay(1);
        servo.write(0);
        delay(500);
        servo.detach();
        opened = false;
      }
    }
  }
  delay(100);
}


long distance() {
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration/2) / 29.1;
  return distance;
}
