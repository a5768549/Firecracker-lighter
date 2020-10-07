/*
 * Firecracker-lighter
 * Copyright 2020 a5768549
 *
 * GitHub Project：https://github.com/a5768549/Firecracker-lighter
 */
 
//7697沒有包進snprintf指令，所以必須使用Erriez的lib，不能用平常的lib。
#include <ErriezDS1302.h>
#include <TM1637Display.h>
#include <IRremote.h>
#include <Regexp.h>
#include <LWiFi.h>
#include "LTimer.h"
#include "DHT.h"

#define trigger   3            //電熱絲觸發腳
#define button    5            //按鈕
#define button2   4            //按鈕2
#define RECV_PIN  9            //IR
#define DS1302_CLK_PIN     7   //RTC
#define DS1302_DAT_PIN     6
#define DS1302_RST_PIN     8
#define DHTPIN             12  //DHT
#define DHTTYPE            DHT11
#define Seg7_CLK           13  //SEG7
#define Seg7_DIO           14
#define dust_sensor        2   //Dust_Sensor

char _lwifi_ssid[] = "MaxPro";
char _lwifi_pass[] = "12345678";

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
