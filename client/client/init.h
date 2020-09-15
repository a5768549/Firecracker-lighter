void init_begin()
{
  Serial.begin(115200);
  
  pinMode(trigger,OUTPUT);      //設置腳位的模式為輸出
  pinMode(button ,INPUT);       //設置腳位的模式為輸出

  Serial.println("Wi-Fi開始連線");
}
