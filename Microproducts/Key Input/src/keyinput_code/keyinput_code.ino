
#include <Keypad.h>  //library needed
char Key[4][3] ={
  {'1', '2', '3'},
  {'4', '5', '6'},       //Array initialisation
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte row_pin[4] ={3, 2, 1, 0};
byte col_pin[3] ={4, 5, 6};
Keypad mykeypad = Keypad(makeKeymap(Key), row_pin, col_pin, 4, 3);


void setup() {
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  // put your setup code here, to run once:

}

void loop() {
  int Key = mykeypad.getKey();
  if (Key!='\0'){
    if (Key=='7'){
      digitalWrite(13,HIGH);  //when 7 key pressed led13 on
      delay(1000);
      digitalWrite(13,LOW);
     }
    else{
      digitalWrite(12,HIGH);  //for keys other than 7 led12 on
      delay(1000);
      digitalWrite(12,LOW);
    }
  }
  // put your main code here, to run repeatedly:

}
