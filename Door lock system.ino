#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myservo;
const int ROW_NUM = 4; 
const int COLUMN_NUM = 4; 

LiquidCrystal_I2C lcd(0x27, 16, 2);

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; 
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; 

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );
String password = "1234";
String mypassword;
int redled = 11;
int greenled = 12;

int counter = 0;
int attempts = 0;
int max_attempts = 5;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.init();
  lcd.backlight();
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  myservo.attach(10);
  digitalWrite(redled, LOW);
  digitalWrite(greenled, LOW);
  myservo.write(90);
  Serial.println("enter password");
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
}

void loop() {
  keypadfunction();
}


void keypadfunction()
{
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
    counter = counter + 1;
    lcd.setCursor(counter, 1);
    lcd.print("*");
  }
  if (key == '1')
  {
    mypassword = mypassword + 1;
  }
  if (key == '2')
  {
    mypassword = mypassword + 2;
  }
  if (key == '3')
  {
    mypassword = mypassword + 3;
  }
  if (key == '4')
  {
    mypassword = mypassword + 4;
  }

  if (key == '5')
  {
    mypassword = mypassword + 5;
  }
  if (key == '6')
  {
    mypassword = mypassword + 6;
  }

  if (key == '7')
  {
    mypassword = mypassword + 7;
  }

  if (key == '8')
  {
    mypassword = mypassword + 8;
  }
  if (key == '9')
  {
    mypassword = mypassword + 9;
  }
  if (key == '0')
  {
    mypassword = mypassword + 0;
  }

  if (key == '*')
  {
    Serial.println(mypassword);
    if (password == mypassword)
    {
      Serial.println("Correct");
      lcd.setCursor(0, 0);
      lcd.println("Correct!!       ");
      lcd.setCursor(0, 1);
      lcd.println("Welcome Home    ");
      digitalWrite(greenled, HIGH);
      myservo.write(0);
      delay(1000);
      digitalWrite(greenled, LOW);
      myservo.write(90);
      mypassword = "";
      counter = 0;
      lcd.setCursor(0, 0);
      lcd.println("Enter Password  ");
      lcd.setCursor(0, 1);
      lcd.println("                ");
    }
    else
    {
      Serial.println("wrong");
      digitalWrite(greenled, LOW);
      myservo.write(90);
      attempts = attempts + 1;
      if (attempts >= max_attempts )
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Locked Out");
        lcd.setCursor(0, 1);
        lcd.print("Max Attempts");
        digitalWrite(redled, HIGH);
        delay(5000);
        digitalWrite(redled, LOW);
        attempts = 0;
      }
      mypassword = "";
      counter = 0;
      lcd.setCursor(0, 0);
      lcd.print("Wrong Password  ");
      lcd.setCursor(0, 1);
      lcd.print("Count Attempts");
      lcd.setCursor(15, 1);
      lcd.print(attempts);
      digitalWrite(redled, HIGH);
      delay(1000);
      digitalWrite(redled, LOW);

      lcd.setCursor(0, 0);
      lcd.print("Enter Password  ");
      lcd.setCursor(0, 1);
      lcd.println("                ");
    }
  }
}
