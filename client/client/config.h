/*
 * Firecracker-lighter
 * Copyright 2020 a5768549
 *
 * GitHub Project：https://github.com/a5768549/Firecracker-lighter
 */
 
//7697沒有包進snprintf指令，所以必須使用Erriez的lib，不能用平常的lib。
#include <TM1637Display.h>
#include <IRremote.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include "ESP32TimerInterrupt.h"
#include "DHT.h"
#include "time.h"

#define trigger   21            //電熱絲觸發腳
#define button    25            //按鈕
#define button2   26            //按鈕2
#define RECV_PIN  35            //IR
#define DHTPIN             5  //DHT
#define DHTTYPE            DHT11
#define Seg7_CLK           22  //SEG7
#define Seg7_DIO           23
#define dust_sensor        17   //Dust_Sensor

const char* ssid     = "MaxPro";
const char* password = "12345678";

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
