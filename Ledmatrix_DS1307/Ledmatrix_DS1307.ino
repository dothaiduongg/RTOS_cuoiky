// #include <Time.h>
// #include <TimeLib.h>

// Header file includes
// #include <WiFi.h>
#include <time.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <RTClib.h>
#include "Font_Data.h"

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 8

#define CLK_PIN   18 // or SCK
#define DATA_PIN  19 // or MOSI
#define CS_PIN    5 // or SS




#include "DHT.h"
#define DHTPIN 23   
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);

// Arbitrary output pins
MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

#define SPEED_TIME  65
#define PAUSE_TIME  0
#define MAX_MESG  75

int timezone = 7;
int dst = 0;

char Message[MAX_MESG+1] = { "GIA HUY" };
char WeatherTh[MAX_MESG+1] = "";

uint16_t  h, m, s;
uint8_t dow;
int  day;
uint8_t month;
String  year;
// Global variables
char szTime[9];    // mm:ss\0
char szsecond[4];    // ss
char szMesg[MAX_MESG+1] = "";
RTC_DS1307 rtc;
uint8_t degC[] = { 6, 3, 3, 56, 68, 68, 68 }; // Deg C


// HÀM HIỂN THỊ THÁNG
char *mon2str(uint8_t mon, char *psz, uint8_t len)
// Get a label from PROGMEM into a cha r array
{DateTime now = rtc.now();
  static const char str[][4] PROGMEM =
  {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
  };
  
  *psz = '\0';
  if ((now.month()-1) < 12)
  {
    strncpy_P(psz, str[now.month()-1], len);
    psz[len] = '\0';
  }

  return(psz);
}

char *dow2str(uint8_t code, char *psz, uint8_t len)
{
  static const char str[][10] PROGMEM =
  {
    "Sunday", "Monday", "Tuesday", "Wednesday",
    "Thursday", "Friday", "Saturday"
  };
DateTime now = rtc.now();
  *psz = '\0';
  code--;
  if (code < 7)
  {
    strncpy_P(psz, str[now.dayOfTheWeek()], len);
    psz[len] = '\0';
  }

  return(psz);
}
void getsec(char *psz)
// Code for reading clock date
{
  sprintf(psz, "%02d", s);
}
void getTime(char *psz, bool f = true)
// Code for reading clock time
{
  DateTime now = rtc.now();
      h = now.hour();
      m = now.minute();
      s = now.second();
  sprintf(psz, "%02d%c%02d", h, (f ? ':' : ' '), m);
}

void getDate(char *psz)
// Code for reading clock date
{DateTime now = rtc.now();
  char  szBuf[10];

      dow = now.dayOfTheWeek();
      day = now.day();
      month = now.month();
  sprintf(psz, "%d %s %04d", day, mon2str(now.month(), szBuf, sizeof(szBuf)-1),now.year());
}
void getHumidit(char *psz)
// Code for reading clock date
{
        float h = dht.readHumidity();
        strcpy(szMesg, "Humidity : ");
          dtostrf(h, 3, 1, WeatherTh);
          strcat(szMesg, WeatherTh);
          strcat(szMesg, " % RH");
}
void getTemperatur(char *psz)
// Code for reading clock date
{
        float t = dht.readTemperature();
        strcpy(szMesg, "Temperature : ");
          dtostrf(t, 3, 1, WeatherTh);
          strcat(szMesg, WeatherTh);
          strcat(szMesg, " $");
}

void setup(void)
{
    Serial.begin(9600);
    delay(10);

    // We start by connecting to a WiFi network

    if (! rtc.begin()) {
    Serial.println("RTC module is NOT found");
    Serial.flush();
    while (1);
  }

  // automatically sets the RTC to the date & time on PC this sketch was compiled
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));


  delay(3000);
  getTimentp();
  P.begin(3);
  P.setInvert(false);

  P.setZone(0, 0, 3);
  P.setZone(1, 4, 4);
  P.setZone(2, 5, 7);
  P.setFont(1, numeric7Seg);
  P.setFont(2, numeric7Se);
  P.displayZoneText(0, szMesg, PA_CENTER, SPEED_TIME, 0, PA_PRINT, PA_SCROLL_LEFT);
  P.displayZoneText(1, szsecond, PA_LEFT, SPEED_TIME, 0, PA_PRINT, PA_NO_EFFECT);
  P.displayZoneText(2, szTime, PA_CENTER, SPEED_TIME, PAUSE_TIME, PA_PRINT, PA_NO_EFFECT);

  P.addChar('$', degC);
  dht.begin();
  getDate(szMesg);
  getTime(szTime);
}

void loop(void)
{
  static uint32_t lastTime = 0; // millis() memory
  static uint8_t  display = 0;  // current display mode
  static bool flasher = false;  // seconds passing flasher

  String dulieu = "";
  while(Serial.available()>0)
  {
    char c =Serial.read();
    dulieu += c;
    delay(5);
  }
  dulieu.trim();
  Message

  P.displayAnimate();

  if (P.getZoneStatus(0))
  {
    switch (display)
    {
      case 0: // Day of the week
        P.setTextEffect(0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
        display++;
        dow2str(dow, szMesg, MAX_MESG);
        break;

      case 1: // Calendar
        P.setTextEffect(0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
        display++;
        getDate(szMesg);
        break;

      case 2: // Temperature deg C
        P.setTextEffect(0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
        display++;
        getTemperatur(szMesg);
        break;

      case 3:  // Relative Humidity
        P.setTextEffect(0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
        display++;
        getHumidit(szMesg);
        break;

      default: // Text
        P.setTextEffect(0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);

        strcpy(szMesg, Message);
        display = 0;
        break;
    }

    P.displayReset(0);
  }

  // Finally, adjust the time string if we have to
  if (millis() - lastTime >= 1000)
  {
    lastTime = millis();
    getsec(szsecond);
    getTime(szTime, flasher);
    flasher = !flasher;

    P.displayReset(1);
    P.displayReset(2);
  }
}

void getTimentp()
{

  configTime(timezone * 3600, dst, "pool.ntp.org","time.nist.gov");

  while(!time(nullptr)){
        delay(500);
        Serial.print(".");
  }
        Serial.print("Time Update");
}

