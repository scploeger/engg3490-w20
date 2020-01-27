#define NUM_SAMPLES 40
#define DELAY 50


/* By: Spencer Ploeger and Lucas Dasoivc
 *  ENGG*3490, Lab1
 *  January 26 2020
 *  
 * This code is used to develop and test a thermistor value -> temperature in *C function
 * 
  */

int sensor = A1;
int sample_num = 0;
unsigned long counter = 0;
unsigned long sum = 0;
int value = 0;

double getTemp(int val);

void setup() {

  pinMode(sensor, INPUT);
  Serial.begin(9600);
  delay(500);

}

void loop() {

  Serial.println(getTemp());

}

/*
 * Function: getTemp()
 * Parameters: none
 * Returns: temp in *C (float)
 * 
 * Tested range of thermistor is 0-80 *C
 * If the range is out of these bounds, return a temp of 0 or 80 degrees respectively
*/
double getTemp()
{
  float val = 0; //calculated temperature
  double sum = 0; //sum for averaging
  for (int x = 0; x < 4; x++) { //average 4 samples each time
    sum = sum + analogRead(sensor);
    delay(20); //20ms delay between sampling
  }
  val = (float)(sum / 4); //calculate average sensor data
  if (val > 774) { //if below min range, return min range
    return 0;
  }
  else if (val < 133) { //if above max range, return max range
    return 80;
  }
  else { //if in range, calulate distance
    double temp = (-6.33287E-8 * pow(val, 3)) + (1.72024E-4 * pow(val, 2)) + (-2.27157E-1 * val) + 1.05585E2;
    return temp;
  }
}
