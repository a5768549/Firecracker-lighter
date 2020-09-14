//7697沒有包進snprintf指令，所以必須使用Erriez的lib，不能用平常的lib。
#include <ErriezDS1302.h>
#include <IRremote.h>
#include <Regexp.h>
#include <LWiFi.h>
#include "LTimer.h"

#define trigger   3       //電熱絲觸發腳
#define button    4       //按鈕
#define RECV_PIN  9       //IR
#define DS1302_CLK_PIN     7
#define DS1302_DAT_PIN     6
#define DS1302_RST_PIN     8

uint8_t  hour;
uint8_t  min;
uint8_t  sec;
uint8_t  mday;
uint8_t  mon;
uint16_t year;
uint8_t  wday;

LTimer timer0(LTIMER_0);
IRrecv irrecv(RECV_PIN);
decode_results results;

ErriezDS1302 rtc = ErriezDS1302(DS1302_CLK_PIN, DS1302_DAT_PIN, DS1302_RST_PIN);

struct tm dt;

char _lwifi_ssid[] = "MaxPro";
char _lwifi_pass[] = "12345678";

String format_time = "";
int flag = 0;

void _callback0(void *usr_data)
{
  if (!rtc.getDateTime(&hour, &min, &sec, &mday, &mon, &year, &wday)) 
  {
    Serial.println(F("Read date/time failed"));
    return;
  }

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
  Serial.println("local time:" + format_time);
}


/**********************************
 * IR 數值
 * 1 FFA25D
 * 2 FF629D
 * 3 FFE21D
 * 4 FF22DD
 * 5 FF02FD
 * 6 FFC23D
 * 7 FFE01F
 * 8 FFA857
 * 9 FF906F
 * 0 FF9867
 * * FF6897
 * # FFB04F
 *             
 * up    FF18E7
 * down  FF4AB5
 * left  FF10EF
 * right FF5AA5
 * ok    FF38C7
 **********************************/
