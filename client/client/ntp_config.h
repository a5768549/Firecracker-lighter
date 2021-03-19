const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 28800; //Taipei GMT+8 8*60*60
const int   daylightOffset_sec = 0;

void init_ntp()
{
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}
void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return;
  }

  String format_mon  = "";
  String format_day  = "";
  String format_hour = "";
  String format_min  = "";
  String format_sec  = "";
  timeinfo.tm_mon += 1;
  int(timeinfo.tm_mon)  < 10 ? format_mon  = "0"  + String(timeinfo.tm_mon)  : format_mon  = String(timeinfo.tm_mon);
  int(timeinfo.tm_mday) < 10 ? format_day  = "0"  + String(timeinfo.tm_mday) : format_day  = String(timeinfo.tm_mday);
  int(timeinfo.tm_hour) < 10 ? format_hour = "0"  + String(timeinfo.tm_hour) : format_hour = String(timeinfo.tm_hour);
  int(timeinfo.tm_min)  < 10 ? format_min  = "0"  + String(timeinfo.tm_min)  : format_min  = String(timeinfo.tm_min);
  int(timeinfo.tm_sec)  < 10 ? format_sec  = "0"  + String(timeinfo.tm_sec)  : format_sec  = String(timeinfo.tm_sec);

  format_time = String(timeinfo.tm_year + 1900) + "-" + format_mon + "-" + format_day + " " + format_hour + ":" + format_min + ":" + format_sec;
}
