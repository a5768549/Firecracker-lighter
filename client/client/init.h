void init_begin()
{
  Serial.begin(115200);
  
  pinMode(trigger,OUTPUT);      //設置腳位的模式為輸出
  pinMode(button ,INPUT);       //設置腳位的模式為輸出

  timer0.begin();
  timer0.start(1000, LTIMER_REPEAT_MODE, _callback0, NULL);
  rtc.clockEnable(true);
  irrecv.enableIRIn();

  Serial.println("Wi-Fi開始連線");
}
