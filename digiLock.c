#include <Keypad.h>
#include <LiquidCrystal.h>
#include<Servo.h>

Servo myservo;

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

#define Password_Lenght 7 

int pos = 0;    

char Data[Password_Lenght]; 
char Master[Password_Lenght] = "123A45";
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
bool door = true;

byte rowPins[ROWS] = {1, 2, 3, 4}; 
byte colPins[COLS] = {5, 6, 7, 8}; 

Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); 

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

  else Open();
}

void clearData()
{
  while (data_count != 0)
  { 
    Data[data_count--] = 0; 
  }
  return;
}

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
