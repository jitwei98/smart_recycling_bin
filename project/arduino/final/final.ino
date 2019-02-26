#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

Servo servo;
const int left_button = 12, right_button = 11, green_light = 6, red_light = 7;
volatile int left_button_state = 0, right_button_state = 0;
String drt;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  Serial.begin(9600);
  servo.attach(8);
  servo.write(90);
  pinMode(left_button, INPUT);
  pinMode(right_button, INPUT);
  pinMode(red_light, OUTPUT);
  pinMode(green_light, OUTPUT);
  lcd.begin(16, 2); //Defining 16 columns and 2 rows of lcd display
  lcd.backlight();//To Power ON the back light
  Serial.print("Hello World!\n");
}

void turnleft() {
  int angle = 90;
  servo.write(angle);
  for (angle = 90; angle < 180; angle++) {
    servo.write(angle);
    delay(15);
  }
  for (angle = 180; angle > 90; angle--) {
    servo.write(angle);
    delay(15);
  }
}

void turnright() {
  int angle = 90;
  servo.write(angle);
  for (angle = 90; angle > 0; angle--) {
    servo.write(angle);
    delay(15);
  }
  for (angle = 0; angle < 90; angle++) {
    servo.write(angle);
    delay(15);
  }
}

void correct_LED() {
  for ( int i = 0 ; i < 3 ; i ++ ) {
    digitalWrite(green_light, HIGH);
    delay(300);
    digitalWrite(green_light, LOW);
    delay(150);
  }
  digitalWrite(green_light, HIGH);
  lcd.clear();//Clean the screen
  lcd.setCursor(0, 0);
  lcd.print("   Correct!!!   ");
  lcd.setCursor(0, 1);
  lcd.print("    GOOD BOY    ");
}

void wrong_LED() {
  for ( int i = 0 ; i < 3 ; i ++ ) {
    digitalWrite(red_light, HIGH);
    delay(300);
    digitalWrite(red_light, LOW);
    delay(150);
  }
  digitalWrite(red_light, HIGH);
  lcd.clear();//Clean the screen
  lcd.setCursor(0, 0);
  lcd.print("    Wrong!!!    ");
  lcd.setCursor(0, 1);
  lcd.print("    BAD BOY     ");
}

void loading() {
  lcd.clear();//Clean the screen
  lcd.setCursor(0, 0);
  lcd.print("    Loading    ");
  lcd.setCursor(0, 1);
  lcd.print("      .");
  delay(100);
  lcd.setCursor(0, 1);
  lcd.print("      ..");
  delay(100);
  lcd.setCursor(0, 1);
  lcd.print("      ...");
  delay(100);
  lcd.setCursor(0, 1);
  lcd.print("       ..");
  delay(100);
  lcd.setCursor(0, 1);
  lcd.print("        .");
  delay(100);
  lcd.setCursor(0, 1);
  lcd.print("       ..");
  delay(100);
  lcd.setCursor(0, 1);
  lcd.print("      ...");
  delay(100);
  lcd.setCursor(0, 1);
  lcd.print("      ..");
  delay(100);
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("  Welcome to   ");
  lcd.setCursor(0, 1);
  lcd.print("  EnlighteNUS  ");

  left_button_state = digitalRead(left_button);
  right_button_state = digitalRead(right_button);

  if (left_button_state == HIGH) {

    Serial.print("s");

    while (1) {
      loading();
      if (Serial.available()) break;
    }
    lcd.clear();//Clean the screen
    lcd.setCursor(0, 0);
    lcd.print("I pressed left");

    //    while(Serial.available()){
    //    drt = Serial.read();
    //    if(drt == "l" || drt == "r") break;
    //    }
    drt = Serial.readString();
    Serial.print((String) drt);
    if ( drt == "l\n" ) { //0 is left
      correct_LED();
      turnleft();
      
    } else if (drt == "r\n") {
      wrong_LED();
      turnright();

    }



  } else if (right_button_state == HIGH) {

    Serial.print("s");

    while ( 1 ) {
      loading();
      if (Serial.available()) break;
    }
    lcd.clear();//Clean the screen
    lcd.setCursor(0, 0);
    lcd.print("I pressed right");

    drt = Serial.readString();
    //
    //    while(Serial.available()){
    //      drt = Serial.read();
    //      if(drt == "l" || drt == "r") break;
    //    }


    if ( drt == "r\n" ) { //right
      correct_LED();
      turnright();
      
    } else if ( drt == "l\n") {
      wrong_LED();
      turnleft();

    }
  }
  digitalWrite(green_light, LOW);
  digitalWrite(red_light, LOW);
}
