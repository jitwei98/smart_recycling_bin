#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  // put your setup code here, to run once:
    lcd.begin(16, 2); //Defining 16 columns and 2 rows of lcd display
  lcd.backlight();//To Power ON the back light
}

void loop() {
  // put your main code here, to run repeatedly:
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
