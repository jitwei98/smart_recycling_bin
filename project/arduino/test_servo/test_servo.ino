#include <Servo.h>
Servo servo;
int angle = 90;
void setup() {
  // put your setup code here, to run once:
servo.attach(8);
  servo.write(angle);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (angle = 90; angle < 180; angle++) {
    servo.write(angle);
    delay(15);
  }
  for (angle = 180; angle > 90; angle--) {
    servo.write(angle);
    delay(15);
  }
}
