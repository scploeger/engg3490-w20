#include <Servo.h> //include servo library

//pins for motor control
#define pwmA1 6 //back left
#define pwmA2 7

#define pwmB1 4 //front left
#define pwmB2 5

#define pwmC1 10 //back right
#define pwmC2 11

#define pwmD1 8 //front right
#define pwmD2 9

//pushbutton pin
#define button 12

//sensor pin
#define sensor A1

Servo myservo;  // create servo object to control a servo

//timing periods
int servo_int = 30;
int timer_1 = 100;

//timers
unsigned long servo_tmr = 0;
unsigned long time_1 = 0;

//servo position and direction global variable
int pos = 46; //initial position is all the way left
int servo_dir = 'r'; //the servo will be initialized all the way left and will be moving right

int dist[] = {15, 15, 15, 15, 15};

void setup() {
  Serial.begin(9600);

  //servo setup
  myservo.attach(3);  // attaches the servo on pin 3 to the servo object
  myservo.write(46); //set the servo to leftmost position, it will start moving right

  //pinmode for button
  pinMode(button, INPUT);

  //pinmode for sensor
  pinMode(sensor, INPUT);

  //pinmode for motor control
  pinMode(pwmA1, OUTPUT);
  pinMode(pwmA2, OUTPUT);

  pinMode(pwmB1, OUTPUT);
  pinMode(pwmB2, OUTPUT);

  pinMode(pwmC1, OUTPUT);
  pinMode(pwmC2, OUTPUT);

  pinMode(pwmD1, OUTPUT);
  pinMode(pwmD2, OUTPUT);

  while (digitalRead(button) == LOW) {
    delay(50);
  }
  delay(100);

}

void loop() {
  //  go('f', 100);
  //  delay(1000);
  //  halt();
  //  delay(500);
  //  go('b', 100);
  //  delay(1000);
  //  halt();
  //  delay(500);
  //  go('l', 100);
  //  delay(1000);
  //  halt();
  //  delay(500);
  //  go('r', 100);
  //  delay(1000);
  //  halt();
  //  delay(500);

  if (millis() - servo_tmr > servo_int) { //move the servo and record position
    servo_tmr = millis();
    myservo.write(move_servo());
    if (pos == 46) {
      dist[0] = getDist();
    }
    else if (pos == 68) {
      dist[1] = getDist();
    }
    else if (pos == 90) {
      dist[2] = getDist();
    }
    else if (pos == 112) {
      dist[3] = getDist();
    }
    else if (pos == 134) {
      dist[4] = getDist();
    }
  }

    if (dist[0] < 7 || dist[1] < 7) { //if either of the two left positions sense obstacle < 12" away
      //go right
      go('r', 70);
    }
    else if (dist[4] < 7 || dist[3] < 7) { //if either of the two right positions sense obstacle < 12" away
      //go left
      go('l', 70);
    }
    else if (dist[3] < 8) { //if either of the two right positions sense obstacle < 12" away
      timer_1 = millis();
      while(millis() - timer_1 < 500){
        go('b', 100);
      }
      while(millis() - timer_1 < 700){
        go('l', 70);
      }
    }
    else {
      go('f', 70);
    }

  Serial.print(dist[0]);
  Serial.print(",");
  Serial.print(dist[1]);
  Serial.print(",");
  Serial.print(dist[2]);
  Serial.print(",");
  Serial.print(dist[3]);
  Serial.print(",");
  Serial.println(dist[4]);
}
/*
   function: go
   parameters: char dir (desired direction to move), int spd (pwm value 0-255) desired speed
   return: none
   brief: moves robot in desired direction at desired speed
*/
void go(char dir, int spd) {
  if (dir == 'f') {
    analogWrite(pwmB1, 0); //front left fwd
    analogWrite(pwmB2, spd);

    analogWrite(pwmC1, 0); //back right fwd
    analogWrite(pwmC2, spd);

    analogWrite(pwmA1, 0); //back left fwd
    analogWrite(pwmA2, spd);

    analogWrite(pwmD1, 0); //front right fwd
    analogWrite(pwmD2, spd);
  }

  if (dir == 'b') {
    analogWrite(pwmB1, spd); //front left bwd
    analogWrite(pwmB2, 0);

    analogWrite(pwmC1, spd); //back right bwd
    analogWrite(pwmC2, 0);

    analogWrite(pwmA1, spd); //back left bwd
    analogWrite(pwmA2, 0);

    analogWrite(pwmD1, spd); //front right bwd
    analogWrite(pwmD2, 0);
  }

  if (dir == 'l') {
    analogWrite(pwmB1, spd); //front left bwd
    analogWrite(pwmB2, 0);

    analogWrite(pwmC1, 0); //back right fwd
    analogWrite(pwmC2, spd);

    analogWrite(pwmA1, spd); //back left bwd
    analogWrite(pwmA2, 0);

    analogWrite(pwmD1, 0); //front right fwd
    analogWrite(pwmD2, spd);
  }

  if (dir == 'r') {
    analogWrite(pwmB1, 0); //front left fwd
    analogWrite(pwmB2, spd);

    analogWrite(pwmC1, spd); //back right bwd
    analogWrite(pwmC2, 0);

    analogWrite(pwmA1, 0); //back left fwd
    analogWrite(pwmA2, spd);

    analogWrite(pwmD1, spd); //front right bwd
    analogWrite(pwmD2, 0);
  }
}

/*
   function: halt()
   parameters: none
   return: none
   brief: stops the robot moving by stopping all motors
*/
void halt() {
  analogWrite(pwmB1, 0); //front left stop
  analogWrite(pwmB2, 0);

  analogWrite(pwmC1, 0); //back right stop
  analogWrite(pwmC2, 0);

  analogWrite(pwmA1, 0); //back left stop
  analogWrite(pwmA2, 0);

  analogWrite(pwmD1, 0); //front right stop
  analogWrite(pwmD2, 0);
}

/*
   46 = dist[0]
   68 = dist[1]
   90 = dist[2]
   112 = dist[3]
   134 = dist [4]
*/
int move_servo() {
  if (pos == 46) {
    servo_dir = 'r';
    pos = 68;
    return 68;
  }
  else if (pos == 68 && servo_dir == 'r') {
    pos = 90;
    return 90;
  }
  else if (pos == 90 && servo_dir == 'r') {
    pos = 112;
    return 112;
  }
  else if (pos == 112 && servo_dir == 'r') {
    servo_dir = 'l';
    pos = 134;
    return 134;
  }
  else if (pos == 134) {
    pos = 112;
    return 112;
  }
  else if (pos == 112 && servo_dir == 'l') {
    pos = 90;
    return 90;
  }
  else if (pos == 90 && servo_dir == 'l') {
    pos = 68;
    return 68;
  }
  else if (pos == 68 && servo_dir == 'l') {
    pos = 46;
    return 46;
  }
}

double getDist()
{
  float val = 0; //calculated distance
  double sum = 0; //sum for averaging
  for (int x = 0; x < 4; x++) { //average 4 samples each time
    sum = sum + analogRead(sensor);
    delay(20); //20ms delay between sampling
  }
  val = (float)(sum / 4); //calculate average sensor data
  if (val > 540) { //if below min range, return min range
    return 4;
  }
  else if (val < 173) { //if above max range, return max range
    return 15;
  }
  else { //if in range, calulate distance
    double distance = ((9E-05 * pow(val, 2)) + (-0.0911 * val) + 27.407);
    return distance;
  }
}
