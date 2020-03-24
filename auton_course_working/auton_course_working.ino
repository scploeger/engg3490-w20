/* Final Robot Code
   For: ENGG*3490, Final Project
   Winter 2020

   By: Spencer Ploeger (0969141)

   On behalf of group:
   Matthew Bolan (0962361)
   Iain Bulmer (0957153)
   Devin Catt (0922742)
   Lucas Dasovic (0963516)
   Jacob Highgate (0981246)

   Last Modified: March 24, 2020

   About: This is the code that autonomously controls the robot.
*/
#include <Servo.h> //include servo library

#define START_POS 90 //servo starting pos
#define DRV_SPD 80 //drive speed
#define FST_SPD 90 //fast speed 

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
int servo_int = 20;
int timer_1 = 100;

//timers
unsigned long servo_tmr = 0;
unsigned long time_1 = 0;

//servo position and direction global variable
int pos = START_POS; //initial position
int servo_dir = 'r'; //the servo will be initialized to 'START_POS' and will begin moving right

int dist[] = {15, 15, 15, 15, 15, 15, 15}; //initialize all the distanced to 15 inches

void setup() {

  //servo setup
  myservo.attach(3);  // attaches the servo on pin 3 to the servo object
  myservo.write(START_POS); //set the servo to center position, it will start moving right

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

  //start button. wait until button pushed to leave setup loop
  while (digitalRead(button) == LOW) {
    delay(50);
  }
  delay(100);
}

void loop() {

  if (millis() - servo_tmr > servo_int) { //move the servo and record position
    servo_tmr = millis();
    myservo.write(move_servo());

    //get distance from sensor and place in correct distance array element
    if (pos == 34) {
      dist[0] = getDist();
    }
    else if (pos == 46) {
      dist[1] = getDist();
    }
    else if (pos == 68) {
      dist[2] = getDist();
    }
    else if (pos == 90) {
      dist[3] = getDist();
    }
    else if (pos == 112) {
      dist[4] = getDist();
    }
    else if (pos == 134) {
      dist[5] = getDist();
    }
    else if (pos == 146) {
      dist[6] = getDist();
    }
  }

  //****Main control loop****
  if (dist[6] < 4) { //if farthest right is about to hit, steer left fast
    timer_1 = millis();
    while (millis() - timer_1 < 200) { //left fast for 200ms
      go("l", FST_SPD);
    }
  }
  else if (dist[0] < 4) { //if farthest left is about to hit, steer right fast
    timer_1 = millis();
    while (millis() - timer_1 < 200) { //right fast for 200ms
      go("r", FST_SPD);
    }
  }
  else if (dist[2] < 6 && dist[0] > 9) { //if centre < 6" but left is clear, strafe left
    //strafe left
    go("sl", DRV_SPD);
  }
  else if (dist[2] < 6 && dist[6] > 9) { //if centre < 6" but right is clear, strafe right
    //strafe right
    go("sr", DRV_SPD);
  }
  else if (dist[2] < 9 || dist[1] < 9) { //if either of the two middle left positions sense obstacle < 8" away
    //go right
    go("r", DRV_SPD);
  }
  else if (dist[4] < 9 || dist[5] < 9) { //if either of the two middle right positions sense obstacle < 8" away
    //go left
    go("l", DRV_SPD);
  }
  else if (dist[3] < 8) { //if centre sense obstacle < 6" away
    timer_1 = millis();
    while (millis() - timer_1 < 800) { //reverse for 400ms
      go("b", DRV_SPD);
    }
    if (dist[1] < dist[5]) { //if left middle dist less than right, go right
      while (millis() - timer_1 < 1100) { //turn right for 300ms
        go("r", DRV_SPD);
      }
    }
    else { //else means right middle dist less than left, so go left
      while (millis() - timer_1 < 1100) { //turn left for 300ms
        go("l", DRV_SPD);
      }
    }
    pos = 90; //check to see if conflcit resolved
    myservo.write(pos);//set servo back to 90
    dist[3] = getDist();//update centre distance
  }
  else { //if not obstacles present, go forward
    go("f", DRV_SPD);
  }


}
/*
   function: go
   parameters: char* dir (desired direction to move), int spd (pwm value 0-255) desired speed
   return: none
   brief: moves robot in desired direction at desired speed
*/
void go(char *dir, int spd) {
  if (dir == "f") {
    analogWrite(pwmB1, 0); //front left fwd
    analogWrite(pwmB2, spd);

    analogWrite(pwmC1, 0); //back right fwd
    analogWrite(pwmC2, spd);

    analogWrite(pwmA1, 0); //back left fwd
    analogWrite(pwmA2, spd);

    analogWrite(pwmD1, 0); //front right fwd
    analogWrite(pwmD2, spd);
  }

  if (dir == "b") {
    analogWrite(pwmB1, spd); //front left bwd
    analogWrite(pwmB2, 0);

    analogWrite(pwmC1, spd); //back right bwd
    analogWrite(pwmC2, 0);

    analogWrite(pwmA1, spd); //back left bwd
    analogWrite(pwmA2, 0);

    analogWrite(pwmD1, spd); //front right bwd
    analogWrite(pwmD2, 0);
  }

  if (dir == "l") {
    analogWrite(pwmB1, spd); //front left bwd
    analogWrite(pwmB2, 0);

    analogWrite(pwmC1, 0); //back right fwd
    analogWrite(pwmC2, spd);

    analogWrite(pwmA1, spd); //back left bwd
    analogWrite(pwmA2, 0);

    analogWrite(pwmD1, 0); //front right fwd
    analogWrite(pwmD2, spd);
  }

  if (dir == "r") {
    analogWrite(pwmB1, 0); //front left fwd
    analogWrite(pwmB2, spd);

    analogWrite(pwmC1, spd); //back right bwd
    analogWrite(pwmC2, 0);

    analogWrite(pwmA1, 0); //back left fwd
    analogWrite(pwmA2, spd);

    analogWrite(pwmD1, spd); //front right bwd
    analogWrite(pwmD2, 0);
  }

  if (dir == "sr") { //strafe right
    analogWrite(pwmB1, 0); //front left fwd
    analogWrite(pwmB2, spd);

    analogWrite(pwmC1, 0); //back right fwd
    analogWrite(pwmC2, spd);

    analogWrite(pwmA1, spd); //back left bwd
    analogWrite(pwmA2, 0);

    analogWrite(pwmD1, spd); //front right bwd
    analogWrite(pwmD2, 0);
  }

  if (dir == "sl") { //strafe left
    analogWrite(pwmB1, spd); //front left bwd
    analogWrite(pwmB2, 0);

    analogWrite(pwmC1, spd); //back right bwd
    analogWrite(pwmC2, 0);

    analogWrite(pwmA1, 0); //back left fwd
    analogWrite(pwmA2, spd);

    analogWrite(pwmD1, 0); //front right fwd
    analogWrite(pwmD2, spd);
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
   function: move_servo()
   parameters: none
   return: none
   brief: adjust pos variable (servo position) sequentially, allowing the servo to 'sweep'
*/
int move_servo() {
  if (pos == 34) {
    servo_dir = 'r';
    pos = 46;
    return 46;
  }
  else if (pos == 46 && servo_dir == 'r') {
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
    pos = 134;
    return 134;
  }
  else if (pos == 134 && servo_dir == 'r') {
    servo_dir = 'l';
    pos = 146;
    return 146;
  }
  else if (pos == 146) {
    pos = 134;
    return 134;
  }
  else if (pos == 134 && servo_dir == 'l') {
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
  else if (pos == 46 && servo_dir == 'l') {
    pos = 34;
    return 34;
  }
}

/*
   function: getDist
   parameters: none
   return: double (distance in inches)
   brief: calculates distance from rangefinder value based off of second degree interpolation function
*/
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
  else { //if in range, calulate distance based on interpolation function
    double distance = ((9E-05 * pow(val, 2)) + (-0.0911 * val) + 27.407);
    return distance;
  }
}
