/*********************
CONFIGURATION BEGIN
*********************/
const int TRIGGER_PIN = 9; //Ultrasonic sensor trigger pin
const int ECHO_PIN = 10; //Ultrasonic sensor echo pin
const int MAX_DISTANCE = 40; //Maximum range for ultrasonic sensor, in cm

const int LEFT_MOTOR_PIN = 2; //Left motor forward pin, to be hooked up to the correct pin on the brainboard
const int LEFT_MOTOR_REVERSE_PIN = 3; //Left motor reverse pin
const int RIGHT_MOTOR_PIN = 4; //Right motor forward pin
const int RIGHT_MOTOR_REVERSE_PIN = 5; //Right motor reverse pin

const int DELAY = 100; //Main loop delay, in ms

/*********************
CONFIGURATION END
*********************/

boolean isLine = false;

//Setup sonar
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup(){
  //Open pins for output
  pinMode(LEFT_MOTOR_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_REVERSE_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_REVERSE_PIN, OUTPUT);
  
  //Open serial port for debugging with 57600 baud
  Serial.begin(57600);
}

void loop() {
  //Ping ultrasound
  int distance = ping();
  Serial.println("Distance: " + String(distance) + "cm");
  
  //No obstacle ahead, full speed ahead!
  if (distance > COLLISION_THRESHOLD || distance == 0){
    motor(1, 1); //Both motors forward
  }
  else { //Obstacle within threshold, rotate
    do { //Keep rotating left until cleared obstacle
      distance = ping();
      Serial.println("Collision, rotating, distance: " + String(distance) + "cm");
      motor(1, -1); //Left motor forward, right reverse
      delay(DELAY);
    } while (distance != 0 && distance < 20);
  }
  delay(DELAY);
}

/*
* Call function motor(left motor, right motor)
* 1  - forward
* 0  - stop
* -1 - reverse
* 
* Move foward - motor(1, 1)
* Move backward - motor(-1, -1)
* 
* Turn left - motor(0, 1)
* Turn right - motor(1, 0)
* 
* Rotate left - motor(-1, 1)
* Rotate right - motor(1, -1)
*/
void motor(int left, int right){
  digitalWrite(LEFT_MOTOR_PIN, left >= 1 ? HIGH : LOW);
  digitalWrite(LEFT_MOTOR_REVERSE_PIN, left <= -1 ? HIGH : LOW);
  
  digitalWrite(RIGHT_MOTOR_PIN, right >= 1 ? HIGH : LOW);
  digitalWrite(RIGHT_MOTOR_REVERSE_PIN, right <=-1 ? HIGH : LOW);
}

//Ping ultrasound, returns distance in cm
int ping(){
  return sonar.ping() / US_ROUNDTRIP_CM;
}
