
#include <AccelStepper.h>

#define M1_STEP 2
#define M1_DIR  5

#define M2_STEP 3
#define M2_DIR  6

#define LIMIT1 9
#define LIMIT2 10

#define ENABLE_PIN 8

AccelStepper motor1(AccelStepper::DRIVER, M1_STEP, M1_DIR);
AccelStepper motor2(AccelStepper::DRIVER, M2_STEP, M2_DIR);

const long RETURN_POSITION = 7240;

const unsigned long CHARGE_TIME = 30000;

bool motor1Stopped = false;
bool motor2Stopped = false;

enum State {
  MOVING_FORWARD,
  CHARGING,
  MOVING_BACKWARD,
  FINISHED
};

State state = MOVING_FORWARD;

unsigned long chargeStart = 0;

void setup() {

  Serial.begin(9600);

  pinMode(LIMIT1, INPUT_PULLUP);
  pinMode(LIMIT2, INPUT_PULLUP);

  pinMode(ENABLE_PIN, OUTPUT);

  digitalWrite(ENABLE_PIN, LOW);

  motor1.setMaxSpeed(800);
  motor1.setAcceleration(500);

  motor2.setMaxSpeed(800);
  motor2.setAcceleration(500);

  motor1.setCurrentPosition(0);
  motor2.setCurrentPosition(0);

  Serial.println("Base Station Started");

  startForward();
}

void loop() {

  switch (state) {

    case MOVING_FORWARD:

      if (digitalRead(LIMIT1) == LOW &&
          !motor1Stopped) {

        motor1.stop();
        motor1Stopped = true;

        Serial.println("Motor 1 Limit Reached");
      }

      if (digitalRead(LIMIT2) == LOW &&
          !motor2Stopped) {

        motor2.stop();
        motor2Stopped = true;

        Serial.println("Motor 2 Limit Reached");
      }

      if (!motor1Stopped) {
        motor1.run();
      }

      if (!motor2Stopped) {
        motor2.run();
      }

      if (motor1Stopped && motor2Stopped) {

        Serial.println("Both Motors Reached");
        Serial.println("Charging Started");

        chargeStart = millis();

        state = CHARGING;
      }

      break;


    case CHARGING:

      if (millis() - chargeStart >= CHARGE_TIME) {

        Serial.println("Charging Complete");

        startBackward();
      }

      break;


    case MOVING_BACKWARD:

      motor1.run();
      motor2.run();

      if (motor1.distanceToGo() == 0 &&
          motor2.distanceToGo() == 0) {

        Serial.println("Both Motors Returned");

        digitalWrite(ENABLE_PIN, HIGH);

        state = FINISHED;
      }

      break;


    case FINISHED:

      break;
  }
}


void startForward() {

  motor1Stopped = false;
  motor2Stopped = false;

  digitalWrite(ENABLE_PIN, LOW);

  motor1.moveTo(-100000);
  motor2.moveTo(-100000);

  state = MOVING_FORWARD;

  Serial.println("Forward Movement Started");
}


void startBackward() {

  digitalWrite(ENABLE_PIN, LOW);

  motor1.moveTo(RETURN_POSITION);
  motor2.moveTo(RETURN_POSITION);

  state = MOVING_BACKWARD;

  Serial.println("Returning Motors");

}
