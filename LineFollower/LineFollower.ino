#define IR_SENSOR_RIGHT A1
#define IR_SENSOR_LEFT A3
#define IR_SENSOR_MID A2

#define MOTOR_SPEED  180

//Right motor
int enableRightMotor = 6;
int rightMotorPin1 = 7;
int rightMotorPin2 = 8;


//Left motor
int enableLeftMotor = 5;
int leftMotorPin1 = 9;
int leftMotorPin2 = 10;

//SENSORS
int leftIRSensorValue;
int rightIRSensorValue;
int midIRSensorValue;


//obstacle detection
int trigPin = 3;    // TRIG pin
int echoPin = 11;    // ECHO pin
float duration, distance;


void setup()
{


  Serial.begin(9600);
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);
  rotateMotor(0, 0);




  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}


void loop()
{

  obstacl();
  if (distance < 10) {
    rotateMotor(0, 0);
  }
  else {

    rightIRSensorValue = analogRead(IR_SENSOR_RIGHT);
    leftIRSensorValue = analogRead(IR_SENSOR_LEFT);
    midIRSensorValue = analogRead(IR_SENSOR_MID);

    // Serial.println(midIRSensorValue);
    //If none of the sensors detects black line, then go straight
    if (midIRSensorValue > 500 ) {



      //If none of the sensors detects black line, then go straight
      if (rightIRSensorValue < 500 && leftIRSensorValue < 500)
      {
        rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
      }
      //If right sensor detects black line, then turn right
      else if (rightIRSensorValue > 500 && leftIRSensorValue < 500 )
      {
        rotateMotor(MOTOR_SPEED, -MOTOR_SPEED);
      }
      //If left sensor detects black line, then turn left
      else if (rightIRSensorValue < 500 && leftIRSensorValue > 500 )
      {
        rotateMotor(-MOTOR_SPEED, MOTOR_SPEED);
      }
      else if (rightIRSensorValue > 500 && leftIRSensorValue > 500 )
      {
        rotateMotor(-MOTOR_SPEED, - MOTOR_SPEED);
      }
    }

    else {
      if (rightIRSensorValue < 500 && leftIRSensorValue < 500 ) {
        rotateMotor(0, 0);
      }
      else {
        rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
      }
    }
  }
}









void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{

  if (rightMotorSpeed < 0)
  {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
  }
  else if (rightMotorSpeed > 0)
  {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  }
  else
  {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
  }

  if (leftMotorSpeed < 0)
  {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
  }
  else if (leftMotorSpeed > 0)
  {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
  }
  else
  {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
  }
  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));
}

void obstacl() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
}
