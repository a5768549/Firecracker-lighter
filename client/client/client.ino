/*
 * Firecracker-lighter
 * Copyright 2020 a5768549
 *
 * GitHub Project：https://github.com/a5768549/Firecracker-lighter
 */
 
#include "config.h"
#include "init.h"
#include "post.h"
#include "timer_callback.h"

void setup()
{
  init_begin();
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED)
  {
    delay(100); 
  }
  Serial.println("Wi-Fi連線成功");

  timer_init();
  
  starttime = millis();  //get the current time;
  rtc.clockEnable(true);
  irrecv.enableIRIn();
  dht.begin();

  while (!rtc.begin()) 
  {
    delay(100);
  }
  Serial.println("RTC讀取成功");
  
  digitalWrite(trigger,HIGH);
  display.setBrightness(0x0f);
}


void loop()
{
  //get_time();   //向伺服器取得目前設定點燃時間or指令(測試時請註解)
  count += 1;

  float t = dht.readTemperature();
  float h = dht.readHumidity();
  
  if(count == 20)
  {
    send_dht_temp(t);           //上傳溫度 濕度 pm2.5(dust)至中華電信IOT大平台
    send_dht_humi(h);
    send_pm25(concentration);
    count = 0;
  }
  
  if (digitalRead(button) == LOW || flag == 1)
  {
    if(btn_timer > 0)
    {
      btn_timer_enable = 1;
      btn_timer_sec = btn_timer * 60;
    }
    else
    {
      digitalWrite(trigger,LOW);  
      delay(8000);
      digitalWrite(trigger,HIGH);
      delay(2000);
      flag = 0;
      post_status(1);     //上傳「已點燃」狀態
    }
  }

  if (digitalRead(button2) == LOW)
  {
    uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
    data[2] = display.encodeDigit(0);
    data[3] = display.encodeDigit(0);
    btn_timer += 1;

    if(btn_timer > 9)
    {
      int num = btn_timer / 10;
      int num_mod = btn_timer % 10;
      data[0] = display.encodeDigit(num);
      data[1] = display.encodeDigit(num_mod); 
    }
    else
    {
      data[0] = display.encodeDigit(0);
      data[1] = display.encodeDigit(btn_timer); 
    }
    
    display.setSegments(data);
  }

  //IR觸發(此處沒設定接收到什麼訊號，接收到紅外線訊號就啟用)
  if (irrecv.decode(&results)) 
  {
    flag = 1;
    Serial.println("IR 觸發");
    irrecv.resume();
  }

  //網站觸發or網路設定時間觸發
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
    //為了使用模糊搜尋(REGEXP)，有另外安裝函式庫
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
