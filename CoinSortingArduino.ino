/* Project: Coin sorting
 * Student: Circiu Delia Maria
 
Pins descriptions:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V*/

#include <LiquidCrystal.h>

//define const variables
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int button_pin = 7;
const int buzzer = 9;

//define variables
int value_sensor_1 = 0,value_sensor_2 = 0; 
int counter_sensor_1 = 0, counter_sensor_2 = 0;  
int flag_detection_1 =0, flag_detection_2 = 0;
int current_button_state;
int last_button_state = LOW;
float total_money = 0;
int display_state = 0;
int buzzer_counter = 0;

//LCD initialization
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() 
{
  //set analog pin as digital inputs
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  
 // set up the LCD's number of columns and rows:
 lcd.begin(16, 2);

 // initialize the pushbutton pin as an input:
 pinMode(button_pin, INPUT);

 pinMode(buzzer, OUTPUT);

 lcd.setCursor(0,1);
 lcd.print("  CIRCIU DELIA  ");
 lcd.setCursor(0,0);
 lcd.print("  COIN COUNTER  ");
 delay(3000);
 lcd.clear();
}

void loop() 
{
  //process data
  if((digitalRead(A1) == LOW) && (flag_detection_1 == 0))
  {
    counter_sensor_1++;
    total_money += 0.1;
    flag_detection_1 = 1;
    tone(buzzer, 500);
  }
  else if((digitalRead(A1) == HIGH) && (flag_detection_1 == 1))
  {
    //reset flag detection
    flag_detection_1 = 0;
  }
  
    if((digitalRead(A2) == LOW) && (flag_detection_2 == 0))
  {
    counter_sensor_2++;
    total_money += 0.5;
    flag_detection_2 = 1;
    tone(buzzer, 1000);
  }
  else if((digitalRead(A2) == HIGH) && (flag_detection_2 == 1))
  {
    //reset flag detection
    flag_detection_2 = 0;
  }

  // read the button:
  current_button_state = digitalRead(button_pin);
 
if((last_button_state != current_button_state) && (current_button_state == LOW))
  {
    display_state = ~display_state; 

    // reset LCD text
    lcd.clear();
  }
  last_button_state = current_button_state;

  
 //display data
  if(display_state == 0)
  {
  lcd.setCursor(0,0);
  lcd.print("  C10      C50   ");
 
  lcd.setCursor(3,1);
  lcd.print(counter_sensor_1);

  lcd.setCursor(12,1);
  lcd.print(counter_sensor_2);
  }
  else
  {
  lcd.setCursor(0,1);
  lcd.print("TOTAL:       RON");
  
  lcd.setCursor(6,1);
  lcd.print(total_money,2);
  }
  
  //delay 1ms
  delay(10);
  buzzer_counter++;
  
  //delay 200ms for buzzer
  if(buzzer_counter >= 20)
  {
  //stop buzzer
  noTone(buzzer);

  //reset counter
  buzzer_counter = 0;
  }
}
