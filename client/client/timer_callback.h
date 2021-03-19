/*
 * Firecracker-lighter
 * Copyright 2020 a5768549
 *
 * GitHub Project：https://github.com/a5768549/Firecracker-lighter
 */
 
ESP32Timer ITimer0(0);
ESP32Timer ITimer1(1);

#define TIMER0_INTERVAL_MS 1000
#define TIMER1_INTERVAL_MS 1000

void dust()
{
  duration = pulseIn(dust_sensor, LOW);
  lowpulseoccupancy = lowpulseoccupancy+duration;
  //Serial.println(concentration);
  if ((millis()-starttime) > sampletime_ms)//if the sample time == 30s
  {
    ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
    //Serial.println(concentration);
    lowpulseoccupancy = 0;
    starttime = millis();
  }
}

<<<<<<< Updated upstream
=======
<<<<<<< HEAD
>>>>>>> Stashed changes
void IRAM_ATTR TimerHandler0()
{
  printLocalTime();
  
  Serial.println("local time:" + format_time);
<<<<<<< Updated upstream
=======
=======
  String format_mon  = "";
  String format_day  = "";
  String format_hour = "";
  String format_min  = "";
  String format_sec  = "";
  int(mon)  < 10 ? format_mon  = "0"  + String(mon)  : format_mon  = String(mon);
  int(mday) < 10 ? format_day  = "0"  + String(mday) : format_day  = String(mday);
  int(hour) < 10 ? format_hour = "0"  + String(hour) : format_hour = String(hour);
  int(min)  < 10 ? format_min  = "0"  + String(min)  : format_min  = String(min);
  int(sec)  < 10 ? format_sec  = "0"  + String(sec)  : format_sec  = String(sec);

  format_time = String(year) + "-" + format_mon + "-" + format_day + " " + format_hour + ":" + format_min + ":" + format_sec;
  //Serial.println("local time:" + format_time);
>>>>>>> 60ed33e977b9032ed9f52b27f44795c55f1aac6f
>>>>>>> Stashed changes

  if(btn_timer_enable == 1)
  {
    btn_timer_sec -= 1;

    if(btn_timer_sec == 0)
    {
      flag = 1;
      uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
      data[0] = display.encodeDigit(0);
      data[1] = display.encodeDigit(0); 
      data[2] = display.encodeDigit(0);
      data[3] = display.encodeDigit(0);
      
      display.setSegments(data);
      btn_timer_enable = 0;
      btn_timer = 0;
    }

    int min1 = (btn_timer_sec / 60) / 10;
    int min2 = (btn_timer_sec / 60) % 10;
    int sec1 = (btn_timer_sec % 60) / 10;
    int sec2 = (btn_timer_sec % 60) % 10;

    uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };

    data[0] = display.encodeDigit(min1);
    data[1] = display.encodeDigit(min2); 
    data[2] = display.encodeDigit(sec1);
    data[3] = display.encodeDigit(sec2);
    
    display.setSegments(data);
  }
}

//void IRAM_ATTR TimerHandler1()
//{
//  duration = pulseIn(dust_sensor, LOW);
//  lowpulseoccupancy = lowpulseoccupancy+duration;
//  Serial.println(concentration);
//  if ((millis()-starttime) > sampletime_ms)//if the sample time == 30s
//  {
//    ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
//    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
//    Serial.println(concentration);
//    lowpulseoccupancy = 0;
//    starttime = millis();
//  }
//}

void timer_init()
{
  ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 1000, TimerHandler0);
  //ITimer1.attachInterruptInterval(TIMER1_INTERVAL_MS * 1000, TimerHandler1);
}
