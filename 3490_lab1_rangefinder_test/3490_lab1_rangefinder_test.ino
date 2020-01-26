#define NUM_SAMPLES 40
#define DELAY 50


/* By: Spencer Ploeger and Lucas Dasoivc
 *  ENGG*3490, Lab1
 *  January 26 2020
 *  
 * This code is used to develop and test a sensor value -> distance in mm function for the rangefinder.
 */

int sensor = A1;
int sample_num = 0;
unsigned long counter = 0;
unsigned long sum = 0;
int value = 0;

double getDistance(int val);

void setup() {

  pinMode(sensor, INPUT);
  Serial.begin(9600);
  delay(500);

}

void loop() {

  Serial.println(getDistance());

}

/*
 * Function: getDistance()
 * Parameters: none
 * Returns: distance in mm (float)
 * 
 * Range of sensor is 4 - 30 cm 
 * If the range is out of these bounds, return a disance of 3 and 31 respectively

*/
double getDistance()
{
  float val = 0; //calculated distance
  double sum = 0; //sum for averaging
  for (int x = 0; x < 4; x++) { //average 4 samples each time
    sum = sum + analogRead(sensor);
    delay(20); //20ms delay between sampling
  }
  val = (float)(sum / 4); //calculate average sensor data
  if (val > 480) { //if below min range, return min range
    return 30;
  }
  else if (val < 75) { //if above max range, return max range
    return 310;
  }
  else { //if in range, calulate distance
    double distance = (-1E-5 * pow(val, 3)) + (0.0103 * pow(val, 2)) + (-3.7462 * val) + 530.23;
    return distance;
  }
}
