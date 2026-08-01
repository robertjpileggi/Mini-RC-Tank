#include <Bluepad32.h>
#include <ESP32Servo.h>
#include <AccelStepper.h>

ControllerPtr myController = nullptr;

// Car motor pins
const int IN1 = 25;
const int IN2 = 26;
const int IN3 = 27;
const int IN4 = 14;

// Servo pin
const int SERVO_PIN = 13;

// Flywheel motor pins
const int FLY1_IN1 = 16;
const int FLY1_IN2 = 17;
const int FLY2_IN1 = 21;
const int FLY2_IN2 = 22;

// Stepper pins
const int STP1 = 32;
const int STP2 = 33;
const int STP3 = 18;
const int STP4 = 19;

// For 28BYJ-48 + ULN2003 driver
AccelStepper stepper(
  AccelStepper::HALF4WIRE,
  STP1,
  STP3,
  STP2,
  STP4
);

Servo myServo;

const int DEADZONE = 80;

// Trigger must be above this value to activate
const int TRIGGER_THRESHOLD = 20;

void onConnectedController(ControllerPtr ctl) {
  myController = ctl;
  Serial.println("Controller connected!");
}

void onDisconnectedController(ControllerPtr ctl) {
  myController = nullptr;

  stopCar();
  stopFlywheels();

  myServo.write(90);
  stepper.setSpeed(0);

  Serial.println("Controller disconnected!");
}

void setup() {
  Serial.begin(115200);

  // Car motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Flywheel motor pins
  pinMode(FLY1_IN1, OUTPUT);
  pinMode(FLY1_IN2, OUTPUT);
  pinMode(FLY2_IN1, OUTPUT);
  pinMode(FLY2_IN2, OUTPUT);

  // Servo setup
  myServo.attach(SERVO_PIN);
  myServo.write(90);

  // Stepper setup
  stepper.setMaxSpeed(800);
  stepper.setAcceleration(400);

  stopCar();
  stopFlywheels();

  BP32.setup(
    &onConnectedController,
    &onDisconnectedController
  );

  Serial.println("Ready. Connect Xbox controller.");
}

void loop() {
  BP32.update();

  if (myController && myController->isConnected()) {

    // --------------------------------
    // Left stick controls the car
    // --------------------------------

    int x = myController->axisX();
    int y = myController->axisY();

    if (abs(x) < DEADZONE) {
      x = 0;
    }

    if (abs(y) < DEADZONE) {
      y = 0;
    }

    int forward = -y;
    int turn = x;

    int leftSpeed =
      constrain(forward + turn, -512, 512);

    int rightSpeed =
      constrain(forward - turn, -512, 512);

    leftSpeed =
      map(leftSpeed, -512, 512, -255, 255);

    rightSpeed =
      map(rightSpeed, -512, 512, -255, 255);

    driveMotors(leftSpeed, rightSpeed);

    // --------------------------------
    // RT controls the servo
    // --------------------------------

    int rightTrigger = myController->throttle();

    if (rightTrigger > TRIGGER_THRESHOLD) {
      myServo.write(135);
    } else {
      myServo.write(90);
    }

    // --------------------------------
    // LT controls both flywheel motors
    // --------------------------------

    int leftTrigger = myController->brake();

    if (leftTrigger > TRIGGER_THRESHOLD) {
      runFlywheels();
    } else {
      stopFlywheels();
    }

    // --------------------------------
    // Right stick X controls stepper
    // --------------------------------

    int rx = myController->axisRX();

    if (abs(rx) < DEADZONE) {
      rx = 0;
    }

    int stepperSpeed =
      map(rx, -512, 512, -600, 600);

    stepper.setSpeed(stepperSpeed);

  } else {
    stopCar();
    stopFlywheels();

    myServo.write(90);
    stepper.setSpeed(0);
  }

  stepper.runSpeed();
}

void driveMotors(int leftSpeed, int rightSpeed) {
  setMotor(IN1, IN2, leftSpeed);
  setMotor(IN3, IN4, rightSpeed);
}

void setMotor(int pin1, int pin2, int speedVal) {
  if (abs(speedVal) < 20) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    return;
  }

  if (speedVal > 0) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
  } else {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
  }
}

void runFlywheels() {
  // Motor 1 forward
  digitalWrite(FLY1_IN1, HIGH);
  digitalWrite(FLY1_IN2, LOW);

  // Motor 2 forward
  digitalWrite(FLY2_IN1, HIGH);
  digitalWrite(FLY2_IN2, LOW);
}

void stopFlywheels() {
  digitalWrite(FLY1_IN1, LOW);
  digitalWrite(FLY1_IN2, LOW);

  digitalWrite(FLY2_IN1, LOW);
  digitalWrite(FLY2_IN2, LOW);
}

void stopCar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}