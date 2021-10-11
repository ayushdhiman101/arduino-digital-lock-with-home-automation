## DESIGN

###### VIDEO IMPLEMENTAION
[LINK](https://drive.google.com/drive/folders/1itetbOOLUXKuYhQi7NM1tFrftVyEgeVY?usp=sharing)

![image](https://user-images.githubusercontent.com/61506157/136735199-8bd7a996-8116-4d4c-9f3f-fb628e5ccc9f.png)

###### CIRCUIT DIAGRAM
[LINK](https://www.tinkercad.com/things/hDJkfGfHuxg-arduino-door)

![image](https://user-images.githubusercontent.com/61506157/136735205-d5eddf7b-5723-4884-b68a-1b006086a6c0.png)

## HARDWARE COMPONENTS 
1. Arduino Uno
2. 16*2 Lcd Display
3. 4*4 matrix keypad 
4. TowerPro SG 90 Micro Servo Motor
5. 10k Ohm Potentiometer Single Variable Resistor 
6. 330ohm Resistor
7. Universal Buzzer
8. LED
9. Some jumper wire

## CODING & ANALYSIS
After inserting all the header and library files, assign all the pin for LCD and define the password length and set the initial position of the servo to 0. After that, take a “char” datatype for declaring the number that can hold it including the null character.
###### Header files:
Keypad.h => Required for handling the 4x4 Keypad
LiquidCrystal.h =>Required for handling the LCD
Servo.h =>Required to handle the Servo Motor
`#include <Keypad.h>`
`#include <LiquidCrystal.h>`
`#include<Servo.h>`

With this piece of code (char Master[Password_Lenght] = "123456";) -- under the Char Master, I declare the password of the door lock, then assign the number of rows and columns in the keyboard and declare keyMaps and connect with rows and columns. 
```
Servo myservo;
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
#define Password_Lenght 7 
int pos = 0;
char Data[Password_Lenght]; 
char Master[Password_Lenght] = "123A45";
```

#### Setup Function
Under the void setup, initialize the servo signal pin D9, servo status closed and print the name of the project/device/company with 3 seconds of delay on LCD time of starting the device.

```
void setup()
{
  myservo.attach(9);
  ServoClose();
  lcd.begin(16, 2);
  lcd.print(" Arduino Door");
  lcd.setCursor(3, 1);
  lcd.print("-CSE2006-");
  delay(3000);
  lcd.clear();
  pinMode(13, OUTPUT);
}
```
#### Loop Function
Under the loop function, the simple if-else condition is there. The loop function is executed again and again in a loop. There are 3 conditions: - When,
Door Closed(door=1), which leads to entering the custom key (“*”) for closing the lights or Open () where we have to enter the password.
Door Open(door=0), which leads to entering the custom key (“#”) for closing the Door or Open () where we have to enter the password.
Default choice, leads to the Open () where we have to enter the password.
````
void loop()
{
  if(door ==1){
    if (customKey == '*'){
      lcd.clear();
       digitalWrite(13, LOW);
      lcd.print("  Lights closed");
      delay(3000);
    }
  }
  if (door == 0)
  {
    customKey = customKeypad.getKey();

    if (customKey == '#')

    {
      lcd.clear();
      ServoClose();
      lcd.print("  Door is close");
      tone(12, 1500, 500); 
      delay(3000);

      door = 1;
    }
  }
````
We have used 2 functions for controlling the Door using the servo motor. 
`ServoOpen()`, rotates the servo to open position as it goes from 180 degrees to 90 degrees , door data count as 1 otherwise door locker remains open and data count 0.
`ServoClose()`, rotates the servo to close position as it goes from 90 degrees to 180 degrees. 
The servo open and servo close functions are shown below.
```
void ServoOpen()
{
  for (pos = 180; pos >= 90; pos -= 5) { 

    myservo.write(pos);
    delay(15);
  }
}
void ServoClose()
{
  for (pos = 90; pos <= 180; pos += 5) { 
    myservo.write(pos);
    delay(15);
  }
}
```

Write the position of the servo with 15 seconds of delay to reach the servo position. Under the void open function, print on LCD “Enter Password” then the condition specifies that the entered password should be same with custom key, within this body data counted and stores char into the data array, incremented and input password printed on LCD if the data length (number of key) and input password matches with Data Master (where the pre-defined keys are present). 

Then as an action LCD clear, servo drive, print on LCD “Door is open” and the data counter is reset to 0. If the input key does not match with Data Master, as an action on LCD clear print on LCD “Wrong Password “ to notify with 1 second of delay and remains in its lock position with data counter sets to 1 and continue this process in a loop.
```
void Open()
{
  lcd.setCursor(0, 0);
  lcd.print(" Enter Password");

  customKey = customKeypad.getKey();
  if (customKey) 
  {
    Data[data_count] = customKey; 
    lcd.setCursor(data_count, 1); 
    lcd.print(Data[data_count]); 
    data_count++;
  }

  

if (data_count == Password_Lenght - 1) 
  {
    if (!strcmp(Data, Master)) 
    {
      lcd.clear();
      ServoOpen();
      lcd.print("  Door is Open");
      door = 0;
      tone(12, 1000, 500);
      digitalWrite(13, HIGH);
      delay(1000);

    }

    else
    {
      lcd.clear();
      lcd.print("  Wrong Password");
      door = 1;
      tone(12, 2000, 500);

      delay(1000);

    }
    clearData();
  }
}
```
