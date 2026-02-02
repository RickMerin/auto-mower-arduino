#include <Servo.h>

// ================= MOTOR PINS =================
#define ENA 5
#define IN1 2
#define IN2 3

#define ENB 6
#define IN3 4
#define IN4 7

// ================= ULTRASONIC =================
#define TRIG 9
#define ECHO 10

// ================= SERVO ======================
#define SERVO_PIN 11
Servo scanner;

// ================= LOGIC FLAGS ================
bool isScanning = false;
bool hasScanned = false;

// ================= DISTANCE LOGIC =============
#define FAR_DISTANCE   30
#define NEAR_DISTANCE  20
#define SCAN_MIN       25

// ================= SPEEDS =====================
#define SPEED_FAST     180
#define SPEED_SLOW     110
#define SPEED_REVERSE  140

// ================= SERVO ANGLES ===============
#define LEFT_ANGLE     150
#define CENTER_ANGLE   90
#define RIGHT_ANGLE    30

// ================= MOTOR CONTROL ===============
void setSpeed(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

void moveForward(int speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  setSpeed(speed);
}

void moveBackward(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  setSpeed(speed);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  setSpeed(SPEED_SLOW);
  delay(450);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  setSpeed(SPEED_SLOW);
  delay(450);
}

void stopMotors() {
  setSpeed(0);
}

// ================= ULTRASONIC ==================
long getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);
  if (duration == 0) return 999;

  return duration * 0.034 / 2;
}

// ================= SERVO SCAN ==================
long scanAtAngle(int angle) {
  scanner.write(angle);
  delay(450);
  return getDistance();
}

void scanAndDecide() {
  if (isScanning) return;
  isScanning = true;

  stopMotors();

  long leftDist  = scanAtAngle(LEFT_ANGLE);
  long rightDist = scanAtAngle(RIGHT_ANGLE);

  scanner.write(CENTER_ANGLE);
  delay(300);

  if (leftDist >= SCAN_MIN && rightDist < SCAN_MIN) {
    turnLeft();
  }
  else if (rightDist >= SCAN_MIN && leftDist < SCAN_MIN) {
    turnRight();
  }
  else if (leftDist >= SCAN_MIN && rightDist >= SCAN_MIN) {
    if (leftDist > rightDist) {
      turnLeft();
    } else {
      turnRight();
    }
  }
  else {
    moveBackward(SPEED_REVERSE);
    delay(500);
    stopMotors();
  }

  isScanning = false;
}

// ================= SETUP =======================
void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  scanner.attach(SERVO_PIN);
  scanner.write(CENTER_ANGLE);

  Serial.begin(9600);
}

// ================= LOOP ========================
void loop() {
  long distance = getDistance();

  if (distance > FAR_DISTANCE) {
    hasScanned = false;
    moveForward(SPEED_FAST);
  }
  else if (distance > NEAR_DISTANCE) {
    hasScanned = false;
    moveForward(SPEED_SLOW);
  }
  else {
    stopMotors();

    if (!hasScanned) {
      scanAndDecide();   // 🔒 scan ONLY once per stop
      hasScanned = true;
    }
  }

  delay(120);
}
