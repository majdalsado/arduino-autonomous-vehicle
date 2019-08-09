#include <NewPing.h>
#include <Servo.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

int motorR=3;
int motorL=5;
int servoPin=9;
int pos;
int dist;
const int interval = 1000;
const int E=0;
const int NE=45;
const int N=90;
const int NW=135;
const int W = 180;
int distances[] = {0,0,0,0,0};
int runnum=0;
int max1;

Servo sonarServo;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(9600);
  pinMode(motorR, OUTPUT);
  pinMode(motorL, OUTPUT);
  sonarServo.attach(servoPin);
  sonarServo.write(90);
}

void loop() {
  int distances[] = {0,0,0,0,0};
  Serial.print("Run # ");
  Serial.println(runnum);
  for (pos = 0; pos <= 4; pos += 1) {
    // Set servo to position either E,NE,N,NW,W
   sonarServo.write(45*pos);
   // Wait for Servo
   delay(500);
   // Ping and save the ping in distances array
   dist = sonar.ping_cm();
   if (dist==0 || dist >50){
      distances[pos]=9999;
   } else {
       distances[pos]=dist;
   }
   
  }
  for (int i=0; i<= 4; i++){
    Serial.print(distances[i]);
    Serial.println(" ");
   }

   
  runnum++;
  max1=getIndexOfMaxValue(distances,4);
  Serial.print("Turn ");
  Serial.print(max1*45);
  Serial.println(" degrees");
  move(max1*45);
}

boolean move(int angle){
        digitalWrite(motorL, LOW);
      digitalWrite(motorR, LOW);
  switch(angle){
    case E:
      digitalWrite(motorL, HIGH);
      delay(interval);
      digitalWrite(motorL, LOW);
      break;
    case NE:
      digitalWrite(motorL, HIGH);
      digitalWrite(motorR, HIGH);
      delay(interval/2);
      digitalWrite(motorR, LOW);
      delay(interval/2);
      digitalWrite(motorL, LOW);
      break;
    case N:
      digitalWrite(motorL, HIGH);
      digitalWrite(motorR, HIGH);
      delay(interval);
      digitalWrite(motorL, LOW);
      digitalWrite(motorR, LOW);
      break;
    case NW:
      digitalWrite(motorL, HIGH);
      digitalWrite(motorR, HIGH);
      delay(interval/2);
      digitalWrite(motorL, LOW);
      delay(interval/2);
      digitalWrite(motorR, LOW);
      break;
    case W:
      digitalWrite(motorR, HIGH);
      delay(interval);
      digitalWrite(motorR, LOW);
      break;


  }
}

int getIndexOfMaxValue(int* array, int size){
 int maxIndex = 0;
 int max = array[maxIndex];
 for (int i=0; i<=size; i++){
   if (max<array[i]){
     max = array[i];
     maxIndex = i;
   }
 }
 return maxIndex;
}
