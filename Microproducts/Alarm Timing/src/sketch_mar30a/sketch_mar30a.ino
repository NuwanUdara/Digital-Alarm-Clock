#include <RTClib.h>
RTC_DS1307 rtc;
int mode_button = 13;
int data_button = 12;
int set_button = 11;
int alarm_LED = 10;
int mode = 0;
int data = 0;
int set = 0;
int h1 = 0;int h2 = 0;int m1 = 0;int m2 = 0;int s1 = 0;int s2 = 0;
int alarmHour = 0;int alarmMinute = 0;int alarmSecond= 0;
void setup() {
  Serial.begin(9600);
  showRealTime();
  pinMode(mode_button,INPUT);
  digitalWrite(mode_button,HIGH);
  pinMode(data_button,INPUT);
  digitalWrite(data_button,HIGH);
  pinMode(set_button,INPUT);
  digitalWrite(set_button,HIGH);
  pinMode(alarm_LED,OUTPUT);
}

void loop() {
  DateTime now = rtc.now();
  if (!digitalRead(mode_button)){
    mode = mode + 1;
    data = 0;
  }
  data = data + !digitalRead(data_button);
  if (mode == 0){showRealTime();}
  if (mode == 1){h1 = data;setAlarm();}
  if (mode == 2){h2 = data;setAlarm();}
  if (mode == 3){m1 = data;setAlarm();}
  if (mode == 4){m2 = data;setAlarm();}
  if (mode == 5){s1 = data;setAlarm();}
  if (mode == 6){s2 = data;setAlarm();}
  if (mode == 7){mode = 0;}
  if (((h1*10+h2) == now.hour() and m1*10+m2 == now.minute()) and s1*10+s2 == now.second()){
    digitalWrite(alarm_LED,HIGH);
  }
  if (((h1*10+h2) == now.hour() and m1*10+m2+1 == now.minute()) and s1*10+s2 == now.second()){
    digitalWrite(alarm_LED,LOW);
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
void setAlarm(){
  Serial.print(h1*10+h2, DEC);
  Serial.print(':');
  Serial.print(m1*10+m2, DEC);
  Serial.print(':');
  Serial.print(s1*10+s2, DEC);
  Serial.println();
}
