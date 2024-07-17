#include<Keypad.h>
#include<LiquidCrystal.h>
#include<Servo.h>
Servo myservo;
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
#define Password_Length 6
int pos = 0;
char Data[Password_Length];
char Master[Password_Length] = "12345";
byte data_count = 0, master_count = 0;
char customKey;
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}};
bool door = true;
byte rowPins[ROWS] = {1, 2, 3, 4};
byte colPins[COLS] = {5, 6, 7};
Keypad customKeypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
void setup(){
  myservo.attach(9);
  ServoClose();
  lcd.begin(16, 2);
  lcd.print("Password Based");
  lcd.setCursor(0, 1);
  lcd.print("DoorLock project");
  delay(3000);
  lcd.clear();
}
void loop(){
  if(door == 0){
    customKey = customKeypad.getKey();
    if(customKey == '*'){
      lcd.clear();
      ServoClose();
      lcd.print("Door is close");
      delay(3000);
      door = 1;
    }
  }
  else Open();
}
void clearData(){
  while(data_count!=0){
    Data[data_count--] = 0;
  }
  return;
}
void ServoOpen(){
  for(pos = 180; pos>=0; pos-=5){
    myservo.write(pos);
    delay(15);
  }
}
void ServoClose(){
  for(pos=0; pos<=180; pos+=5){
    myservo.write(pos);
    delay(15);
  }
}
void Open(){
  lcd.setCursor(0, 0);
  lcd.print("Enter Password");
  customKey = customKeypad.getKey();
  if(customKey){
    Data[data_count] = customKey;
    lcd.setCursor(data_count, 1);
    lcd.print(Data[data_count]);
    data_count++;
  }
  if(data_count == Password_Length-1){
    if(!strcmp(Data, Master)){
      lcd.clear();
      ServoOpen();
      lcd.print("Door is Open");
      door = 0;
    }
    else{
      lcd.clear();
      lcd.print("Wrong Password");
      delay(1000);
      door = 1;
    }
    clearData();
  }
}
