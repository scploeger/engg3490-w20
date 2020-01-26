#define NUM_SAMPLES 40 //number of samples to average
#define DELAY 50 //delay between samples

/* By: Spencer Ploeger and Lucas Dasoivc
 *  ENGG*3490, Lab1
 *  January 26 2020
 *  
 * This code is used to generate an output curve for the rnagefinder. At each distance, the code is run and an average sensor value is obtained.
 * This value is put into a spreadsheet program. This process is repeated for all distanced within the sensor range.
 */

int sensor = A1;
int sample_num = 0;
unsigned long counter = 0;
unsigned long sum = 0;
int value = 0;


void setup() {
  pinMode(sensor, INPUT);
  Serial.begin(9600);
  delay(500);
  Serial.println("BEGIN");
  counter = millis();
}

void loop() {

  //for NUM_SAMPLES print sample #, time of sample, and sensor value
  if (sample_num < NUM_SAMPLES)
  {
    if (millis() - counter > DELAY)
    {
      counter = millis();

      Serial.print(sample_num);
      Serial.print(",");
      Serial.print(millis());
      Serial.print(",");
      value = analogRead(sensor);
      Serial.println(value);
      sum = sum + value;
      sample_num++;
    }
  }
  else {
    Serial.println("END");
    Serial.print("**AVERAGE: ");
    Serial.println((double)sum/NUM_SAMPLES); //print the averaged sensor value
    delay(100000);
  }
}
