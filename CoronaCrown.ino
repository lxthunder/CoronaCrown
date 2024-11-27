/**************************************************************************************************************
 * Distance measuring with four ultrasonic sensors.
Sensors are built from on top of HCHC-SR04 sensors with an extra LED attached.
Wiring of the sensor:
Green  -> LED
White  -> GND
Gray   -> Echo
Yellow -> Trigger
Copper -> VIN 
 **************************************************************************************************************/



const int trigPin = 8;                    // Trigger can be one common signal, echo must be separated
const int echopin[] = { 9, 10, 11, 12 };  // Digital echo pin array
const int LED[] = { 7, 6, 5, 4 };         // LED pin array
const int Buzzer = 2;                     // Buzzer
const int Sensors = 2;                    // Number of sensors
float duration, distance;
float alarmdistance = 10;  // Distance at which alarm is triggered
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
const long buzztime = 500;  // Minimum time to buzz
int i = 0;
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echopin[0], INPUT);
  pinMode(echopin[1], INPUT);
  pinMode(echopin[2], INPUT);
  pinMode(echopin[3], INPUT);
  pinMode(LED[0], OUTPUT);
  pinMode(LED[1], OUTPUT);
  pinMode(LED[2], OUTPUT);
  pinMode(LED[3], OUTPUT);
  pinMode(Buzzer, OUTPUT);
  Serial.begin(9600);
  digitalWrite(LED[0], LOW);
  digitalWrite(LED[1], LOW);
  digitalWrite(LED[3], LOW);
  digitalWrite(LED[4], LOW);
  digitalWrite(Buzzer, LOW);

  //System ready beep
  for (int i = 0; i < Sensors; i++) {
    digitalWrite(Buzzer, HIGH);
    digitalWrite(LED[i], HIGH);
    delay(100);
    digitalWrite(Buzzer, LOW);
    digitalWrite(LED[i], LOW);
    delay(100);
  }
  int i = 0;
}



void loop() {

  digitalWrite(LED[i], HIGH);  // Indicator which Sensor is
  digitalWrite(trigPin, LOW);  // Trigger the sensor
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echopin[i], HIGH);  //read sensor echo
  distance = (duration * .0343) / 2;
  Serial.print("\n");
  Serial.print(i);
  Serial.print("\n");
  Serial.print(distance);
  currentMillis = millis();
  digitalWrite(LED[i], LOW);
  if (distance < alarmdistance) {
    digitalWrite(LED[i], HIGH);
    digitalWrite(Buzzer, HIGH);
    previousMillis = currentMillis;
  } else {
    digitalWrite(LED[i], LOW);
    if (currentMillis - previousMillis >= buzztime) {  //buzz at least 2 sec when positive signal, independant from signal time
      digitalWrite(Buzzer, LOW);
      previousMillis = currentMillis;
    }
  }

  delay(10);  // Needed to clear the echo in the environment
  if (i < Sensors - 1) {
    i++;
  } else {
    i = 0;
  }
}
