#include <Keypad.h>  //library needed
const byte numRows= 4; //number of rows on the keypad
const byte numCols= 3; //number of columns on the keypad 
//keymap defines the key pressed according to the row and columns just as appears on the keypad
char keymap[numRows][numCols]= 
{
{'1', '2', '3'}, 
{'4', '5', '6'}, 
{'7', '8', '9'},         //array initialisation
{'*', '0', '#'}
};
byte rowPins[numRows] = {3, 2, 1, 0}; //Rows 0 to 4 //if you modify your pins you should modify this too
byte colPins[numCols]= {4, 5, 6}; //Columns 0 to 3
char keypressed;
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);
void setup() {
  for(int i=7; i<=13; i++)
  pinMode(i,OUTPUT);
}

void loop() {
  keypressed = myKeypad.getKey();
  if (keypressed != NO_KEY){
    for(int i=7; i<=13; i++)
    digitalWrite(i,LOW); 
    if (keypressed == '1'){
      digitalWrite(8,HIGH); digitalWrite(12,HIGH);
    }
    if (keypressed == '2'){
      for(int i=7; i<=11; i++) if (i!=12 && i!=13)
      digitalWrite(i,HIGH);
    }
    if (keypressed == '3'){
      for(int i=7; i<=13; i++) if (i!=13 && i!=10)
      digitalWrite(i,HIGH);
    }
    if (keypressed == '4'){
      digitalWrite(8,HIGH); digitalWrite(9,HIGH); digitalWrite(12,HIGH); digitalWrite(13,HIGH);
    }
    if (keypressed == '5'){
      for(int i=7; i<=13; i++) if (i!=8 && i!=10)
      digitalWrite(i,HIGH);
    }
    if (keypressed == '6'){
      for(int i=7; i<=13; i++) if (i!=8)
      digitalWrite(i,HIGH);
    }
    if (keypressed == '7'){
      digitalWrite(7,HIGH); digitalWrite(8,HIGH); digitalWrite(12,HIGH);
    }
    if (keypressed == '8'){
      for(int i=7; i<=13; i++)
      digitalWrite(i,HIGH);
    }
    if (keypressed == '9'){
      for(int i=7; i<=13; i++) if (i!=10 && i!=11)
      digitalWrite(i,HIGH);
    }
    if (keypressed == '0'){
      for(int i=7; i<=13; i++) if (i!=9)
      digitalWrite(i,HIGH);
    }
    if (keypressed == '*' || keypressed == '#'){
      for(int i=7; i<=13; i++){
      digitalWrite(i,HIGH); delay(100); }
    }
  }
} 
