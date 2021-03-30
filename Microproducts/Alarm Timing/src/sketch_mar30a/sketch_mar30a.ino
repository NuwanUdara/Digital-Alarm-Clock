#include <RTClib.h>
RTC_DS1307 rtc;
int set_button = 13;
int data_button = 12;
int set_mode = 0; 
void setup() {
  Serial.begin(9600);
  if (rtc.begin()){
    Serial.println("RTC is connected");
  }
  else{
    Serial.println("RTC is not connected");
  }
  //rtc.adjust(DateTime(2017, 7, 16, 16, 35, 20));
  showRealTime();
  pinMode(set_button,INPUT);
  digitalWrite(set_button,HIGH);
  pinMode(data_button,INPUT);
  digitalWrite(data_button,HIGH);
}

void loop() {
  set_mode = set_mode + !digitalRead(set_button);
  if (set_mode == 0){
    showRealTime();
  }
  if (set_mode == 1){
    showGivenTime(2017,2,23,8,12,23);
  }
  if (set_mode == 2){
    showGivenTime(2016,2,23,8,12,23);
  }
  delay(300);
}
void showRealTime(){
  DateTime now = rtc.now();
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print('-');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
}
void showGivenTime(int y,int M,int d,int h,int m,int s){
  Serial.print(y, DEC);
  Serial.print('/');
  Serial.print(M, DEC);
  Serial.print('/');
  Serial.print(d, DEC);
  Serial.print('-');
  Serial.print(h, DEC);
  Serial.print(':');
  Serial.print(m, DEC);
  Serial.print(':');
  Serial.print(s, DEC);
  Serial.println();
}
