#include <Arduino.h>

/* Read Jostick
    ------------
    REMEMBER, FOR SERVO, BROWN OUT
    Reads two analog pins that are supposed to be
    connected to a jostick made of two potentiometers

    We send three bytes back to the comp: one header and two
    with data as signed bytes, this will take the form:
       Jxy\r\n

    x and y are integers and sent in ASCII
*/
//#include <Adafruit_MotorShield.h>
#include <Servo.h>
int ledPin = 13;
int joyPin1 = 0;                 // slider variable connecetd to analog pin 0 - x
int joyPin2 = 1;                 // slider variable connecetd to analog pin 1 - y
int joyPin3 = 2;                 // slider variable connecetd to analog pin 2 - z
int value1;
int value2;
int value3;
double speedX = 0;                  // variable to read the value from the analog pin 0 - x
double speedY = 0;                  // variable to read the value from the analog pin 1 - y
int onoff = 0;                      // variable to read the value from the analog pin 1 - y
double zeroX = 612;
double zeroY = 612;
int MAX_SPEED = 255;
Servo servo1;
Servo servo2;
int enA = 10;
int in1 = 9;
int in2 = 8;
// motor two
int enB = 5;
int in3 = 7;
int in4 = 6;




void setup() {
  pinMode(ledPin, OUTPUT);              // initializes digital pins 0 to 7 as outputs
  Serial.begin(9600);
  //calibrate
  delay(100);
  zeroX = analogRead(joyPin1);
  zeroY = analogRead(joyPin2);
  Serial.println();
  Serial.print("zero X:"); Serial.print(zeroX);
  Serial.print( "zero Y:"); Serial.print(zeroY);

}

double calcSpeed(double data, double zero) {
  double cf = (data - zero) / zero;
  if (data > zero)
    return MAX_SPEED * cf;
  else
    return MAX_SPEED - MAX_SPEED * abs(1 - cf);
}

void loop() {
  // reads the value of the variable resistor
  value1 = analogRead(joyPin1);
  delay(10);
  // this small pause is needed between reading
  // analog pins, otherwise we get the same value twice
  // reads the value of the variable resistor
  value2 = analogRead(joyPin2);
  delay(10);
  value3 = analogRead(joyPin3);
  speedX = calcSpeed(value1, zeroX);
  speedY = calcSpeed(value2, zeroY);
  //Seriac11l.print(treatValue(value1));
  Serial.print("Raw:");
  Serial.print(" X:"); Serial.print(value1);
  Serial.print(" Y:"); Serial.print(value2);
  Serial.print(" Z:"); Serial.print(value3);
  Serial.println();
  Serial.print("Calculated Speed:");
  Serial.print(" X:"); Serial.print(speedX);
  Serial.print(" Y:"); Serial.print(speedY);
  Serial.println();
  int i;
for (i=0; i<255; i++) {
    servo1.write(map(i, 0, 255, 0,  90));}

  if (speedX > 0){
 for (i=0; i<255; i++) {
    servo1.write(i);
  }
 }    
 else 
    for (i=254; i>=0; i--) {
    servo1.write(i);
 }
 
  
  
  if (speedY > 0){
  for (i=0; i<255; i++) {
    servo2.write(i);
  }
  }
else
  for (i=0; i<255; i--) {
    servo2.write(i);
  }
}
  

