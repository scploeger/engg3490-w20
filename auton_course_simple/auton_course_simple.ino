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

   Last Modified: March 28, 2020

   About: This is a simpler version of the original code that autonomously controls the robot.
          This revision is what was used to take the videos posted to youtube and works well.
          In practice, it should allow the robot to make it through the maze.
*/
#include <Servo.h> //include servo library

#define START_POS 90 //servo starting pos (in degrees)
#define DRV_SPD 80 //drive speed (PWM value 0-255)
#define FST_SPD 100 //fast speed  (PWM value 0-255)

//digital pins for motor control
//these pins connect to PWM+/- pins on the L293 IC
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
int servo_int = 20; //how often the servo changes position
int timer_1 = 100; //timer used multiple times throughout the code

//timers used to timer different events during execution of code
unsigned long servo_tmr = 0; //used for timing servo position
unsigned long time_1 = 0; //used to time robot movements

//servo position and direction global variable
int pos = START_POS; //initial position
int servo_dir = 'r'; //the servo will be initialized to 'START_POS' and will begin moving right

int dist[] = {15, 15, 15, 15, 15, 15, 15}; //initialize all the distances in distance array to 15 inches

//timer_on initialization
int timer_on[] = {0, 0, 0, 0, 0, 0}; //initialize all "timer on" array elements

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
  go("f", DRV_SPD); //start robot going forward
}

void loop() {

  if (millis() - servo_tmr > servo_int) { //move the servo and record position
    servo_tmr = millis();
    myservo.write(move_servo());

    //get distance from sensor and place in correct distance array element
    //based on where the servo is, get the distance from rangefinder and add to correct array element
    if (pos == 34) {
      dist[0] = getDist();
      timer_on[0] = 1; //used to know what measurement was taken most recently
    }                  //current servo position will be 1, rest will be 0 (used below)
    else if (pos == 46) {
      dist[1] = getDist();
      timer_on[1] = 1;
    }
    else if (pos == 68) {
      dist[2] = getDist();
      timer_on[2] = 1;
    }
    else if (pos == 90) {
      dist[3] = getDist();
      timer_on[3] = 1;
    }
    else if (pos == 112) {
      dist[4] = getDist();
      timer_on[4] = 1;
    }
    else if (pos == 134) {
      dist[5] = getDist();
      timer_on[5] = 1;
    }
    else if (pos == 146) {
      dist[6] = getDist();
      timer_on[6] = 1;
    }
  }

  //****Main control loop****
  //block 1
  if (dist[6] < 12 || dist[0] < 12 || dist[5] < 12 || dist[1] < 12) { //if farthest left or right distances < 12" away
    if (dist[6] < 12 && timer_on[6] == 1) { //if farthest right distance < 12" AND the servo is current pointing in correct direction
      timer_1 = millis();
      go("l", FST_SPD); //turn left
      timer_on[6] = 0;
    }
    else if (dist[0] < 12 && timer_on[0] == 1) { 
      timer_1 = millis();
      go("r", FST_SPD);
      timer_on[0] = 0;
    }
    else if (dist[5] < 12 && timer_on[5] == 1) { 
      timer_1 = millis();
      go("l", FST_SPD);
      timer_on[5] = 0;
    }
    else if (dist[1] < 12 && timer_on[1] == 1) { 
      timer_1 = millis();
      go("r", FST_SPD);
      timer_on[1] = 0;
    }
    if (millis() - timer_1 > 100) { //after desired interval, reset to forward
      go("f", DRV_SPD);
    }
  }
  //block 2
  if (dist[4] < 12 || dist[2] < 12) { //if middle lefr or right distance 12"
    if (dist[4] < 12 && timer_on[4] == 1) { //if middle right distance < 12" AND the servo is current pointing in correct direction
      timer_1 = millis();
      go("l", FST_SPD); //turn left
      timer_on[4] = 0;
    }
    else if (dist[2] < 12 && timer_on[2] == 1) { //if middle right distance < 12" AND the servo is current pointing in correct direction
      timer_1 = millis();
      go("r", FST_SPD); //turn right
      timer_on[2] = 0;
    }
    if (millis() - timer_1 > 200) { //after desired interval, reset to forward
      go("f", DRV_SPD);
    }
  }
  //block 3
  if (dist[3] < 13) {//if fwd distance < 13"
    if (dist[3] < 13 && timer_on[3] == 1) { //if fwd distance < 13" AND the servo is current pointing in correct direction
      timer_1 = millis(); //start the timer
      go("b", FST_SPD); //reverse
      timer_on[3] = 0; //set to zero
    }
    if (millis() - timer_1 > 300) { //after desired interval, reset to forward
      go("f", DRV_SPD);
    }
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
