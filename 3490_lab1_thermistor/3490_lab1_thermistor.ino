#define NUM_SAMPLES 5
#define DELAY 50


/* By: Spencer Ploeger and Lucas Dasoivc
 *  ENGG*3490, Lab1
 *  January 26 2020
 *  
 * This code is used to take a certain number of samples from the thermistor, and return the average. This is used to generate a response curve to various temperatures.
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
    Serial.println((double)sum/NUM_SAMPLES);
    delay(100000);
  }
}
