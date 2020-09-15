/*
 * Firecracker-lighter
 * Copyright 2020 a5768549
 *
 * GitHub Project：https://github.com/a5768549/Firecracker-lighter
 */
 
#include "config.h"
#include "init.h"
#include "post.h"

void setup()
{
  init_begin();
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED)
  {
    delay(100); 
  }
  Serial.println("Wi-Fi連線成功");

  timer0.begin();
  timer0.start(1000, LTIMER_REPEAT_MODE, _callback0, NULL);
  rtc.clockEnable(true);
  irrecv.enableIRIn();

  while (!rtc.begin()) 
  {
    delay(100);
  }
  Serial.println("RTC讀取成功");
}


void loop()
{
  get_time();
  
  if (digitalRead(button) == LOW || flag == 1)
  {
    digitalWrite(trigger,HIGH);  
    delay(2000);
    digitalWrite(trigger,LOW);
    delay(5000);
    flag = 0;
    post_status(1);
  }

  //IR觸發(此處沒設定接收到什麼訊號，接收到紅外線訊號就啟用)
  if (irrecv.decode(&results)) 
  {
    flag = 1;
    Serial.println("IR 觸發");
    irrecv.resume();
  }

  while (client.connected() || client.available()) 
  {
    char thisChar = client.read();
    inData += thisChar;
    
    if (thisChar == '\n')
    {
      inData = "";          
    }

    MatchState ms;

    char buf[50];
    inData.toCharArray(buf, 50);
    ms.Target(buf);

    char result = ms.Match ("(%d+)-(%d+)-(%d+) (%d+):(%d+):(%d+)", 0);
    if (result == REGEXP_MATCHED)
    {
      Serial.println("data time:" + inData); 
      client.stop();

      char buf2[50];
      inData.toCharArray(buf2, 50);

      char buf3[50];
      format_time.toCharArray(buf3, 50);

      if(inData == "0000-00-00 00:00:0")
      {
        Serial.println("未設定時間");
      }
      else if(inData == "2000-01-01 00:00:0")
      {
        Serial.println("網站觸發");
        flag = 1;
      }
      else if(strcmp(buf2, buf3) < 0) 
      {
        Serial.println("時間已到！");
        flag = 1;
      }

      inData = "";
    }
      
  }

  delay(500);
}
