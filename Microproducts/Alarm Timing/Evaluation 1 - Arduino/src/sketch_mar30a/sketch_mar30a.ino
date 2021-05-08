#include <RTClib.h>
RTC_DS1307 rtc;
int set_button = 13;
int data_button = 12;
int mode_button = 11;
int alarm_LED = 10;
int mode = 0;
int data = 0;
int set = 0;int isAlarm = 0;int isTime = 0;
int h1 = 0;int h2 = 0;int m1 = 0;int m2 = 0;int s1 = 0;int s2 = 0;
int alarmHour = 0;int alarmMinute = 0;int alarmSecond= 0;
void setup() {
  Serial.begin(9600);
  showRealTime();
  pinMode(mode_button,INPUT);digitalWrite(mode_button,HIGH);
  pinMode(data_button,INPUT);digitalWrite(data_button,HIGH);
  pinMode(set_button,INPUT);digitalWrite(set_button,HIGH);
  pinMode(alarm_LED,OUTPUT);
}

void loop() {
  DateTime now = rtc.now();
  if (!digitalRead(set_button) and !mode==0){
    set = set + 1;
    data = 0;
  }
  data = data + !digitalRead(data_button);
  if (!digitalRead(mode_button)){
    mode = mode + 1;
    set = 0;
    clearVariables();
  }
  if (set == 0){showRealTime();}
  if (set == 1){h1 = data;addTime();}
  if (set == 2){h2 = data;addTime();}
  if (set == 3){m1 = data;addTime();}
  if (set == 4){m2 = data;addTime();}
  if (set == 5){s1 = data;addTime();}
  if (set == 6){s2 = data;addTime();}
  if (set == 7){
    if (mode==1){
      isAlarm = 1;
    }
    if (mode==2){
      isTime = 1;
    }
    mode = 0;set = 0;
  }

  if (isAlarm){
      if (((h1*10+h2) == now.hour() and m1*10+m2 == now.minute()) and s1*10+s2 == now.second()){
        digitalWrite(alarm_LED,HIGH);
      }
      else if (((h1*10+h2) == now.hour() and m1*10+m2+1 == now.minute()) and s1*10+s2 == now.second()){
        digitalWrite(alarm_LED,LOW);
        isAlarm = 0;
        clearVariables();
      }
  }
   if (isTime){
      rtc.adjust(DateTime(now.year(), now.month(), now.day(), h1*10+h2,m1*10+m2,s1*10+s2));
      isTime=0;
      clearVariables();
    }
  
  delay(200);
}
void showRealTime(){
  DateTime now = rtc.now();
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
}
void addTime(){
  Serial.print(h1*10+h2, DEC);
  Serial.print(':');
  Serial.print(m1*10+m2, DEC);
  Serial.print(':');
  Serial.print(s1*10+s2, DEC);
  Serial.println();
}
void clearVariables(){
  h1 = 0;h2 = 0;m1 = 0;m2 = 0;s1 = 0;s2 = 0;
}
