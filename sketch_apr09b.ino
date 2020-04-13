
// Motor pins L298N motor driver board
const uint8_t rightMotorPinA = 10; //Right motor => IN1 pin 8
const uint8_t rightMotorPinB = 9; //Right motor => IN2 pin 9
const uint8_t leftMotorPinA = 12; // Left Motor => IN3 pin 10
const uint8_t leftMotorPinB = 11; //Left Motor IN4 pin 11

// Button pin (configured so that on is LOW)
const uint8_t buttonPin = 5; //was 12

// Transmit and receive pins for distance sensor
const uint8_t tPin = A0;//was 2
const uint8_t rPin = A1;//was 4

// Pin for status LED (turns on when nose touch neurons stimulated)
const uint8_t statusPin = 13;

// Pins for speaker
const uint8_t speaker = 7;
const uint8_t speakerMin = 6;

 const  uint8_t spdBoost = 0;
 const  uint8_t turnTime = 0;



void rightMotorForward(uint8_t spd) {
  analogWrite(rightMotorPinA, spd);
  digitalWrite(rightMotorPinB, LOW);
}

void rightMotorBackward(uint8_t spd) {
  digitalWrite(rightMotorPinA, LOW);
  analogWrite(rightMotorPinB, spd);
}

void rightMotorOff() {
  digitalWrite(rightMotorPinA, LOW);
  digitalWrite(rightMotorPinB, LOW);
}

void leftMotorForward(uint8_t spd) {
  analogWrite(leftMotorPinA, spd);
  digitalWrite(leftMotorPinB, LOW);
}

void leftMotorBackward(uint8_t spd) {
  digitalWrite(leftMotorPinA, LOW);
  analogWrite(leftMotorPinB, spd);
}

void leftMotorOff() {
  digitalWrite(leftMotorPinA, LOW);
  digitalWrite(leftMotorPinB, LOW);
}





void setup() {
  // put your setup code here, to run once:
  pinMode(leftMotorPinA, OUTPUT);
  pinMode(leftMotorPinB, OUTPUT);
  pinMode(rightMotorPinA, OUTPUT);
  pinMode(rightMotorPinB, OUTPUT);
  pinMode(tPin, OUTPUT);
  pinMode(rPin, INPUT);
  pinMode(speaker, OUTPUT);
  pinMode(speakerMin, OUTPUT);

}



void loop() {
  // put your main code here, to run repeatedly:

  uint8_t leftSpdMotor;
  uint8_t rightSpdMotor;



   int16_t leftSpd;
   int16_t rightSpd;
  
  // Send sound pulse
  digitalWrite(tPin, LOW);
  delayMicroseconds(2);
  digitalWrite(tPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(tPin, LOW);

  // Read off length
  long pulseWidth = pulseIn(rPin, HIGH);

  // Calculate distance
  long distance = (pulseWidth/29.1) / 2;
  
  if (distance <= 25 && distance >= 0)
  {
  rightMotorOff();
  tone(speaker, 220, 500);  
    
  }
  
  else
  { 

     // Left forward
  if(leftSpd >= 0) {
    leftSpd += spdBoost;
    if(leftSpd > 255) {
      leftSpdMotor = 255;
    }
    else {
      leftSpdMotor = leftSpd;
    }
    leftMotorForward(leftSpdMotor);
  }
  
  if(rightSpd <= 0) {
    rightSpd -= spdBoost;
    if(abs(rightSpd) > 255) {
      rightSpdMotor = 255;
    }
    else {
      rightSpdMotor = abs(rightSpd);
    }
    rightMotorBackward(rightSpdMotor);
  }

    
  }
}
