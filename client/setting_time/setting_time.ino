#include <ErriezDS1302.h>

#define DS1302_CLK_PIN      7
#define DS1302_DAT_PIN       6
#define DS1302_RST_PIN       8

ErriezDS1302 rtc = ErriezDS1302(DS1302_CLK_PIN, DS1302_DAT_PIN, DS1302_RST_PIN);

struct tm dt;

void rtcInit()
{
    while (!rtc.begin()) 
    {
        Serial.println(F("RTC not found"));
        delay(3000);
    }

    rtc.clockEnable(true);
}

bool getBuildTime(const char *str)
{
    int hour;
    int minute;
    int second;

    if (sscanf(str, "%d:%d:%d", &hour, &minute, &second) != 3) {return false;}

    dt.tm_hour = hour;
    dt.tm_min  = minute;
    dt.tm_sec  = second;

    return true;
}

bool getBuildDate(const char *str)
{
    const char *monthName[] = 
    {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    uint8_t monthIndex;
    char month[12];
    int  dayMonth;
    int  year;
    time_t t;

    if (sscanf(str, "%s %d %d", month, &dayMonth, &year) != 3) {return false;}

    for (monthIndex = 0; monthIndex < 12; monthIndex++) 
    {
        if (strcmp(month, monthName[monthIndex]) == 0) {break;}
    }
    if (monthIndex >= 12) {return false;}

    // Set date
    dt.tm_mday = dayMonth;
    dt.tm_mon  = monthIndex;
    dt.tm_year = year - 1900;

    t = mktime(&dt);
    dt.tm_wday = localtime(&t)->tm_wday;

    return true;
}

bool rtcSetDateTime()
{
    if (!getBuildDate(__DATE__) || !getBuildTime(__TIME__)) 
    {
        Serial.print(F("Build date/time error"));
        return false;
    }

    // Print build date/time
    Serial.print(F("Build date time: "));
    Serial.println(asctime(&dt));

    // Set new date time
    Serial.print(F("Set RTC date time..."));
    if (!rtc.write(&dt)) 
    {
        Serial.println(F("FAILED"));
    } 
    else 
    {
        Serial.println(F("OK"));
    }

    return true;
}

void setup()
{
    delay(500);
    
    Serial.begin(115200);
    while (!Serial) {;}
    
    Serial.println(F("\nErriez DS1302 RTC Set Time example\n"));
    rtcInit();

    if (!rtcSetDateTime()) 
    {
        while(1) 
        {
            delay(1000);
        }
    }
}

void loop()
{
    if (!rtc.read(&dt)) 
    {
        Serial.println(F("RTC read failed"));
    } 
    else 
    {
        Serial.println(asctime(&dt));
    }
    
    delay(1000);
}
