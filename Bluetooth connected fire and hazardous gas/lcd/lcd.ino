#include <LiquidCrystal_I2C.h> // Include the LiquidCrystal_I2C library

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD I2C address and dimensions (change the address if necessary)

int Buttonpin = 2;
int outPin1 = 4;

int sensorPin1 = A0;
int lm35_pin = A1;
int sensorValue1 = 0;
int sensorValue2 = 0;

int greenLED1 = 7;
int redLED1 = 6;
int buzzar = 11;

int ONValue1 = 390;
int ONValue2 = 100;

boolean buttonState;
boolean lastState;
boolean state = LOW;

void setup() {
  analogReference(DEFAULT);
  lcd.init(); // Initialize the LCD
  lcd.backlight();
  //lcd.print("Safety System"); // Display initial message
  delay(2000);
  lcd.clear(); // Clear the LCD

  pinMode(Buttonpin, INPUT);
  pinMode(outPin1, OUTPUT);
  pinMode(13, OUTPUT); // Power on indicator

  pinMode(greenLED1, OUTPUT);
  pinMode(redLED1, OUTPUT);
  pinMode(buzzar, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int reading = digitalRead(Buttonpin);
  if (reading == LOW && lastState == HIGH) {
    delay(10);
    if (digitalRead(Buttonpin) == LOW)
      state = !state;
  }
  digitalWrite(outPin1, state);

  if (state == HIGH) {
    digitalWrite(13, HIGH);
    delay(10);

    int sensorValue1 = analogRead(A0);
    int sensorValue2 = analogRead(A1);
    Serial.print("SensorValue1 =  ");
    Serial.print(sensorValue1);

    float temp_val;
    sensorValue2 = analogRead(lm35_pin); /* Read Temperature */
    temp_val = (sensorValue2 * 4.8828125); /* Convert adc value to equivalent voltage */
    temp_val = (temp_val / 10); /* LM35 gives output of 10mv/°C */
    Serial.print("     Temperature = ");
    Serial.print(temp_val);
    Serial.print(" Degree Celsius\n");
    delay(1000);

    if ((sensorValue1 < ONValue1) && (temp_val < ONValue2)) {
      digitalWrite(greenLED1, HIGH);
      digitalWrite(redLED1, LOW);
      digitalWrite(buzzar, LOW);
      Serial.println("Safe");

      // Display safe message on the LCD
      lcd.setCursor(0, 0);
      //lcd.print(temp_val);
      lcd.print("     Safe");
    } else {
      digitalWrite(greenLED1, LOW);
      digitalWrite(redLED1, HIGH);
      digitalWrite(buzzar, HIGH);
      delay(300);
      digitalWrite(buzzar, LOW);
      delay(300);
      digitalWrite(buzzar, HIGH);
      delay(300);
      digitalWrite(buzzar, LOW);
      delay(1000);

      Serial.println("Danger");

      // Display danger message on the LCD
      lcd.setCursor(0, 0);
      //lcd.print(temp_val);
      lcd.print("    Danger");
    }
  }

  if (state == LOW) {
    Serial.println("Off");
    digitalWrite(13, LOW);
    digitalWrite(greenLED1, LOW);
    digitalWrite(redLED1, LOW);
    digitalWrite(buzzar, LOW);

    // Display off message on the LCD
    lcd.setCursor(0, 0);
    lcd.print("Off");
  }
  lastState = reading;
}
