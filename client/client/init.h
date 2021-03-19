/*
 * Firecracker-lighter
 * Copyright 2020 a5768549
 *
 * GitHub Project：https://github.com/a5768549/Firecracker-lighter
 */
 
void init_begin()
{
  Serial.begin(115200);
  
  pinMode(trigger     ,OUTPUT);      //設置腳位的模式為輸出
  pinMode(button      ,INPUT);       //設置腳位的模式為輸出
  pinMode(button2     ,INPUT);
  pinMode(dust_sensor ,INPUT);
  Serial.println("Wi-Fi開始連線");
}

IRrecv         irrecv(RECV_PIN);               //IR init
decode_results results;                        //IR_results init
DHT            dht(DHTPIN, DHTTYPE);           //DHT init
TM1637Display  display(Seg7_CLK, Seg7_DIO);    //Seg7 init

//Dust_Sensor init
unsigned long starttime;
unsigned long duration;
unsigned long sampletime_ms = 30000;//sample 30s ;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

//timer flag init
int count = 0;
int count2= 0;
int btn_timer = 0;
int btn_timer_enable = 0;
int btn_timer_sec = 0;

String format_time = "";
String Setting_time = "";

int flag = 0;
