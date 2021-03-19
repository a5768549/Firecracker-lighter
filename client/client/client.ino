/*
 * Firecracker-lighter
 * Copyright 2020 a5768549
 *
 * GitHub Project：https://github.com/a5768549/Firecracker-lighter
 */

#include "config.h"
#include "init.h"
#include "post.h"
#include "ntp_config.h"
#include "timer_callback.h"

void setup()
{
  init_begin();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");

  timer_init();
  
  starttime = millis();  //get the current time;
  irrecv.enableIRIn();
  dht.begin();

  init_ntp();

  Serial.println("RTC讀取成功");
  
  digitalWrite(trigger,HIGH);
  display.setBrightness(0x0F);
}


void loop()
{
  count += 1;
  count2+= 1;
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  Serial.println(digitalRead(button));
  if(count == 20)
  {
    send_dht_temp(t,h,concentration);           //上傳溫度 濕度 pm2.5(dust)至中華電信IOT大平台
    count = 0;
    Serial.println("data post");
  }
  dust();
  if(count2 == 10)
  {
    get_time();   //向伺服器取得目前設定點燃時間or指令(測試時請註解)

    char buf[50];
    Setting_time.toCharArray(buf, 50);

    char buf2[50];
    format_time.toCharArray(buf2, 50);

    if(Setting_time == "0000-00-00 00:00:0")
    {
      Serial.println("未設定時間");
    }
    else if(Setting_time == "2000-01-01 00:00:0")
    {
      Serial.println("網站觸發");
      flag = 1;
    }
    else if(strcmp(buf, buf2) < 0) 
    {
      Serial.println("時間已到！");
      flag = 1;
    }
    Setting_time = "";
    
    count2 = 0;
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
      Serial.print("burn");
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
//  if (irrecv.decode()) 
//  {
//    flag = 1;
//    Serial.println(flag);
//    Serial.println("IR 觸發");
//    irrecv.resume();
//  }
  

  delay(500);
}
