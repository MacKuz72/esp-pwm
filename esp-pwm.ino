#include <Wire.h>
#include <RTClib.h>
#include <time.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <EEPROM.h>
#include "BluetoothSerial.h"
#include "lampy.h"




RTC_DS3231 rtc;
char daysOfTheWeek[7][5] = {"NIE", "PON", "WTO", "ŚRO", "CZW", "PIĄ", "SOB"};
char daysOfTheWeekAll[7][15] = {"Niedziela", "Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota"};
int pl_week[7] = {1, 2, 3, 4, 5, 6, 0};
DateTime now;

#define EEPROM_SIZE 200
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
BluetoothSerial SerialBT;

#define LEDPin1 12
#define LEDPin2 13
#define LEDPin3 14
#define LEDPin4 27
#define LEDPin5 26
#define LEDPin6 25
#define LEDPin7 33 // panel tło

#define RGB_red   16
#define RGB_green 17
#define RGB_red   18

int dutyCycle;
/* Setting PWM Properties */
const int PWMFreq = 1000; /* 1 KHz */

#define PWMChannel1 0
#define PWMChannel2 1
#define PWMChannel3 2
#define PWMChannel4 3
#define PWMChannel5 4
#define PWMChannel6 5
#define PWMChannel7 6

const int PWMResolution = 10;
const int MAX_DUTY_CYCLE = (int)(pow(2, PWMResolution) - 1);
const int change_time = 1000;
bool newData = false;
int parsing;
const byte dataByte = 255;
char dataRec[dataByte];
char tempChar[dataByte];
char dataBT[dataByte] = {0};

Lampa *wskLampa1 = 0;

Lampa Lampa1(LEDPin1, PWMChannel1, EE_L1_ON_G_START, EE_L1_ON_M_START, EE_L1_ON_G_STOP, EE_L1_ON_M_STOP, EE_L1_OFF_G_START, EE_L1_OFF_M_START, EE_L1_OFF_G_STOP, EE_L1_OFF_M_STOP, EE_L1_NAT_MAX, EE_L1_NAT_MAN, EE_L1_TRYB);
Lampa Lampa2(LEDPin2, PWMChannel2, EE_L2_ON_G_START, EE_L2_ON_M_START, EE_L2_ON_G_STOP, EE_L2_ON_M_STOP, EE_L2_OFF_G_START, EE_L2_OFF_M_START, EE_L2_OFF_G_STOP, EE_L2_OFF_M_STOP, EE_L2_NAT_MAX, EE_L2_NAT_MAN, EE_L2_TRYB);
Lampa Lampa3(LEDPin3, PWMChannel3, EE_L3_ON_G_START, EE_L3_ON_M_START, EE_L3_ON_G_STOP, EE_L3_ON_M_STOP, EE_L3_OFF_G_START, EE_L3_OFF_M_START, EE_L3_OFF_G_STOP, EE_L3_OFF_M_STOP, EE_L3_NAT_MAX, EE_L3_NAT_MAN, EE_L3_TRYB);
Lampa Lampa4(LEDPin4, PWMChannel4, EE_L4_ON_G_START, EE_L4_ON_M_START, EE_L4_ON_G_STOP, EE_L4_ON_M_STOP, EE_L4_OFF_G_START, EE_L4_OFF_M_START, EE_L4_OFF_G_STOP, EE_L4_OFF_M_STOP, EE_L4_NAT_MAX, EE_L4_NAT_MAN, EE_L4_TRYB);
Lampa Lampa5(LEDPin5, PWMChannel5, EE_L5_ON_G_START, EE_L5_ON_M_START, EE_L5_ON_G_STOP, EE_L5_ON_M_STOP, EE_L5_OFF_G_START, EE_L5_OFF_M_START, EE_L5_OFF_G_STOP, EE_L5_OFF_M_STOP, EE_L5_NAT_MAX, EE_L5_NAT_MAN, EE_L5_TRYB);
Lampa Lampa6(LEDPin6, PWMChannel6, EE_L6_ON_G_START, EE_L6_ON_M_START, EE_L6_ON_G_STOP, EE_L6_ON_M_STOP, EE_L6_OFF_G_START, EE_L6_OFF_M_START, EE_L6_OFF_G_STOP, EE_L6_OFF_M_STOP, EE_L6_NAT_MAX, EE_L6_NAT_MAN, EE_L6_TRYB);
Lampa Lampa7(LEDPin7, PWMChannel7, EE_L7_ON_G_START, EE_L7_ON_M_START, EE_L7_ON_G_STOP, EE_L7_ON_M_STOP, EE_L7_OFF_G_START, EE_L7_OFF_M_START, EE_L7_OFF_G_STOP, EE_L7_OFF_M_STOP, EE_L7_NAT_MAX, EE_L7_NAT_MAN, EE_L7_TRYB);

int setDataTime()
{
  char *strtokIndx;
  int rr = 256, mc = 256, dd = 256, gg = 256, mm = 256, ss = 256;
  char *token;
  int i = 0;

  token = strtok(tempChar, "|");

  if (token == NULL)
  {
    return 1;
  }

  while (token)
  {
    i++;
    if (i == 1)
    {
      rr = atoi(token);
    }
    if (i == 2)
    {
      mc = atoi(token);
    }
    if (i == 3)
    {
      dd = atoi(token);
    }
    if (i == 4)
    {
      gg = atoi(token);
    }
    if (i == 5)
    {
      mm = atoi(token);
    }
    if (i == 6)
    {
      ss = atoi(token);
    }
    token = strtok(NULL, "|");
  }

  if (i != 6)
  {
    return 1;
  }
  if (rr < 2000 || rr > 2099)
  {
    return 1;
  }
  if (mc < 1 || mc > 12)
  {
    return 1;
  }
  if (dd < 1 || dd > 31)
  {
    return 1;
  }
  if (gg < 0 || gg > 23)
  {
    return 1;
  }
  if (mm < 0 || dd > 59)
  {
    return 1;
  }
  if (ss < 0 || dd > 59)
  {
    return 1;
  }
  rtc.adjust(DateTime(rr, mc, dd, gg, mm, ss));
  return 0;
}

int setLampa(Lampa *Lampa0)
{
  char *token;
  int i = 0;
  int akt = 256; // czy aktywna
  int onGGstart = 256;
  int onMMstart = 256;
  int onGGstop = 256;
  int onMMstop = 256;
  int offGGstart = 256;
  int offMMstart = 256;
  int offGGstop = 256;
  int offMMstop = 256;
  int nat_max = 2560;
  int nat_manual = 2560;

  // @1|10|10|12|12|18|18|19|19|1020|300>

  Serial.println(tempChar);

  token = strtok(tempChar, "|");

  if (token == NULL)
  {
    return 1;
  }
  while (token)
  {
    Serial.println(token);
    i++;
    if (i == 1)
    {
      akt = atoi(token);
    }
    if (i == 2)
    {
      onGGstart = atoi(token);
    }
    if (i == 3)
    {
      onMMstart = atoi(token);
    }
    if (i == 4)
    {
      onGGstop = atoi(token);
    }
    if (i == 5)
    {
      onMMstop = atoi(token);
    }
    if (i == 6)
    {
      offGGstart = atoi(token);
    }
    if (i == 7)
    {
      offMMstart = atoi(token);
    }
    if (i == 8)
    {
      offGGstop = atoi(token);
    }
    if (i == 9)
    {
      offMMstop = atoi(token);
    }
    if (i == 10)
    {
      nat_max = atoi(token);
    }
    if (i == 11)
    {
      nat_manual = atoi(token);
    }

    token = strtok(NULL, "|");
  }

  if (akt > 1)
  {
    return 1;
  }
  if (onGGstart < 0 || onGGstart > 23)
  {
    return 1;
  }
  if (onMMstart < 0 || onMMstart > 59)
  {
    return 1;
  }
  if (onGGstop < 0 || onGGstop > 23)
  {
    return 1;
  }
  if (onMMstop < 0 || onMMstop > 59)
  {
    return 1;
  }
  if (offGGstart < 0 || offGGstart > 23)
  {
    return 1;
  }
  if (offMMstart < 0 || offMMstart > 59)
  {
    return 1;
  }
  if (offGGstop < 0 || offGGstop > 23)
  {
    return 1;
  }
  if (offMMstop < 0 || offMMstop > 59)
  {
    return 1;
  }
  if (nat_max < 0 || nat_max > MAX_DUTY_CYCLE)
  {
    return 1;
  }
  if (nat_manual < 0 || nat_max > MAX_DUTY_CYCLE)
  {
    return 1;
  }

  Lampa0->tryb = akt;
  Lampa0->on_g_start = onGGstart;
  Lampa0->on_m_start = onMMstart;
  Lampa0->on_g_stop = onGGstop;
  Lampa0->on_m_stop = onMMstop;
  Lampa0->off_g_start = offGGstart;
  Lampa0->off_m_start = offMMstart;
  Lampa0->off_g_stop = offGGstop;
  Lampa0->off_m_stop = offMMstop;
  Lampa0->natezenie_manual = nat_manual;
  Lampa0->natezenie_max = nat_max;

  return 0;
}

void recData()
{
  rec();
  if (newData == true)
  {
    strcpy(tempChar, dataRec);
    Serial.println(tempChar);
    if (parsing == 1)
    {
      setDataTime();
    }
    else if (parsing == 2)
    {
      if (!setLampa(&Lampa1))
      {
        Lampa1.saveLampa();
      }
    }
    else if (parsing == 3)
    {
      if (!setLampa(&Lampa2))
      {
        Lampa2.saveLampa();
      }
    }
    else if (parsing == 4)
    {
      if (!setLampa(&Lampa3))
      {
        Lampa3.saveLampa();
      }
    }
    else if (parsing == 5)
    {
      if (!setLampa(&Lampa4))
      {
        Lampa4.saveLampa();
      }
    }
    else if (parsing == 6)
    {
      if (!setLampa(&Lampa5))
      {
        Lampa5.saveLampa();
      }
    }
    else if (parsing == 7)
    {
      if (!setLampa(&Lampa6))
      {
        Lampa6.saveLampa();
      }
    }
    else if (parsing == 8)
    {
      if (!setLampa(&Lampa7))
      {
        Lampa7.saveLampa();
      }
    }
    else if (parsing == 9)
    {
      if (!setLampa(&Lampa7))
      {
        Lampa7.saveLampa();
      }
    }

    newData = false;
  }
}

void rec()
{
  static bool recData = false;
  static byte ndx;
  char endline = '>';
  char c;

  while (SerialBT.available() > 0 && newData == false)
  {
    c = SerialBT.read();

    if (recData == true)
    {
      if (c != endline)
      {
        dataRec[ndx] = c;
        ndx++;
        if (ndx >= dataByte)
        {
          ndx = dataByte - 1;
        }
      }
      else
      {
        dataRec[ndx] = '\0';
        recData = false;
        ndx = 0;
        newData = true;
      }
    }
    else if (c == '!')
    {
      recData = true;
      parsing = 1;
      // Parse data i czas
    }
    else if (c == '@')
    {
      // @1|10|10|12|12|18|18|19|19|1020|300>
      recData = true;
      parsing = 2;
      // Parse Lampa1
    }
    else if (c == '#')
    {
      // #1|10|10|12|12|18|18|19|19|1020|300>
      recData = true;
      parsing = 3;
      // Parse Lampa2
    }
    else if (c == '$')
    {
      // $1|10|10|12|12|18|18|19|19|1020|300>
      recData = true;
      parsing = 4;
      // Parse Lampa3
    }
    else if (c == '^')
    {
      // ^1|10|10|12|12|18|18|19|19|1020|300>
      recData = true;
      parsing = 5;
      // Parse Lampa4
    }
    else if (c == '/')
    {
      // /1|10|10|12|12|18|18|19|19|1020|300>
      recData = true;
      parsing = 6;
      // Parse Lampa5
    }
    else if (c == '&')
    {
      // &1|10|10|12|12|18|18|19|19|1020|300>
      recData = true;
      parsing = 7;
      // Parse Lampa6
    }
    else if (c == '_')
    {
      // _1|10|10|12|12|18|18|19|19|1020|300>
      recData = true;
      parsing = 8;
      // Parse Lampa7
    }
    else if (c == '+')
    {
      // +1|10|10|12|12|18|18|19|19|1020|300>
      recData = true;
      parsing = 9;
      // Parse ustawienia globalne
    }
  }
}

void setup()
{

  Serial.begin(115200);
  SerialBT.begin("ESP32");

  EEPROM.begin(EEPROM_SIZE);

  if (!rtc.begin())
  {
    Serial.println("Could not find RTC! Check circuit.");
    while (1)
      ;
  }

  if (rtc.lostPower())
  {
    Serial.println("RTC power failure, resetting the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  display.clearDisplay();

  Lampa1.readLampa();
  Lampa1.printLampa();
  Lampa2.readLampa();
  Lampa2.printLampa();
  Lampa3.readLampa();
  Lampa3.printLampa();
  Lampa4.readLampa();
  Lampa4.printLampa();
  Lampa5.readLampa();
  Lampa5.printLampa();
  Lampa6.readLampa();
  Lampa6.printLampa();
  Lampa7.readLampa();
  Lampa7.printLampa();

  ledcSetup(Lampa1.pPWMChannel, PWMFreq, PWMResolution);
  ledcSetup(Lampa2.pPWMChannel, PWMFreq, PWMResolution);
  ledcSetup(Lampa3.pPWMChannel, PWMFreq, PWMResolution);
  ledcSetup(Lampa4.pPWMChannel, PWMFreq, PWMResolution);
  ledcSetup(Lampa5.pPWMChannel, PWMFreq, PWMResolution);
  ledcSetup(Lampa6.pPWMChannel, PWMFreq, PWMResolution);
  ledcSetup(Lampa7.pPWMChannel, PWMFreq, PWMResolution);

  ledcAttachPin(Lampa1.ppin, Lampa1.pPWMChannel);
  ledcAttachPin(Lampa2.ppin, Lampa2.pPWMChannel);
  ledcAttachPin(Lampa3.ppin, Lampa3.pPWMChannel);
  ledcAttachPin(Lampa4.ppin, Lampa4.pPWMChannel);
  ledcAttachPin(Lampa5.ppin, Lampa5.pPWMChannel);
  ledcAttachPin(Lampa6.ppin, Lampa6.pPWMChannel);
  ledcAttachPin(Lampa7.ppin, Lampa7.pPWMChannel);

  now = rtc.now();
  Serial.println(now.timestamp(DateTime::TIMESTAMP_TIME));
  Serial.println(now.timestamp(DateTime::TIMESTAMP_DATE));

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print(now.timestamp(DateTime::TIMESTAMP_TIME));
  display.setCursor(0, 20);
  display.print(now.timestamp(DateTime::TIMESTAMP_DATE));
}
void loop()
{

  recData();

  static long last_loop_time = 0;
  long loop_time = millis();
  if (loop_time - last_loop_time > change_time)
  {
    now = rtc.now();

    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.print(now.timestamp(DateTime::TIMESTAMP_TIME));
    display.setCursor(0, 20);
    display.print(now.timestamp(DateTime::TIMESTAMP_DATE));

    display.setCursor(0, 40);
    display.print("N");
    display.setCursor(10, 40);
    display.print(String(dutyCycle));
    display.setCursor(0, 60);
    display.print("G");
    display.setCursor(65, 60);
    display.print(String(gamma_20[dutyCycle]));

    display.display();

    //  Serial.print( dutyCycle );
    //  Serial.print( "/" );
    //  Serial.println( gamma_20[dutyCycle] );

    SerialBT.println(now.timestamp(DateTime::TIMESTAMP_TIME));

    last_loop_time = millis();
  }


  ledcWrite(Lampa1.pPWMChannel, Lampa1.setPWM());
  ledcWrite(Lampa2.pPWMChannel, Lampa2.setPWM());
  ledcWrite(Lampa3.pPWMChannel, Lampa3.setPWM());
  ledcWrite(Lampa4.pPWMChannel, Lampa4.setPWM());
  ledcWrite(Lampa5.pPWMChannel, Lampa5.setPWM());
  ledcWrite(Lampa6.pPWMChannel, Lampa6.setPWM());
  ledcWrite(Lampa7.pPWMChannel, Lampa7.setPWM());

  /* Increasing the LED brightness with PWM */
  for (dutyCycle = 0; dutyCycle < MAX_DUTY_CYCLE; dutyCycle++)
  {
    ledcWrite(Lampa1.pPWMChannel, dutyCycle);
    ledcWrite(Lampa2.pPWMChannel, gamma_20[dutyCycle]);
    delay(1);
    // delayMicroseconds(100);
  }
  /* Decreasing the LED brightness with PWM */
  for (dutyCycle = MAX_DUTY_CYCLE; dutyCycle >= 0; dutyCycle--)
  {
    ledcWrite(Lampa1.pPWMChannel, dutyCycle);
    ledcWrite(Lampa2.pPWMChannel, gamma_20[dutyCycle]);
    delay(1);
    // delayMicroseconds(100);
  }
}
