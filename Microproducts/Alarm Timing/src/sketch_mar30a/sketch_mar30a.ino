#include <RTClib.h>
RTC_DS1307 rtc;
void setup() {
  Serial.begin(9600);
  if (rtc.begin()){
    Serial.println("RTC is connected");
  }
  else{
    Serial.println("RTC is not connected");
  }
}

void loop() {
  
  DateTime now = rtc.now();
  Serial.print(now.year(),DEC);
  Serial.print("-");
  Serial.print(now.month(),DEC);
  Serial.print("-");
  Serial.print(now.day(),DEC);
  Serial.print("--");
  Serial.print(now.hour(),DEC);
  Serial.print("-");
  Serial.print(now.minute(),DEC);
  Serial.print("-");
  Serial.println(now.second(),DEC);

  delay(1000);
}
