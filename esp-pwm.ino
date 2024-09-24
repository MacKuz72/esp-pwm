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
char daysOfTheWeekAll[7][15] = {"Niedziela", "Poniedzialek", "Wtorek", "Sroda", "Czwartek", "Piatek", "Sobota"};
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
#define LEDPin4 26
#define LEDPin5 25
#define LEDPin6 33
#define LEDPin7 32 // panel tło

#define RGB_red   16
#define RGB_green 17
#define RGB_blue   18

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
int ekran = 0;


Lampa *wskLampa1 = 0;

Lampa Lampa1(LEDPin1, PWMChannel1, EE_L1_ON_G_START, EE_L1_ON_M_START, EE_L1_ON_G_STOP, EE_L1_ON_M_STOP, EE_L1_OFF_G_START, EE_L1_OFF_M_START, EE_L1_OFF_G_STOP, EE_L1_OFF_M_STOP, EE_L1_NAT_MAX, EE_L1_NAT_MAN, EE_L1_TRYB);
Lampa Lampa2(LEDPin2, PWMChannel2, EE_L2_ON_G_START, EE_L2_ON_M_START, EE_L2_ON_G_STOP, EE_L2_ON_M_STOP, EE_L2_OFF_G_START, EE_L2_OFF_M_START, EE_L2_OFF_G_STOP, EE_L2_OFF_M_STOP, EE_L2_NAT_MAX, EE_L2_NAT_MAN, EE_L2_TRYB);
Lampa Lampa3(LEDPin3, PWMChannel3, EE_L3_ON_G_START, EE_L3_ON_M_START, EE_L3_ON_G_STOP, EE_L3_ON_M_STOP, EE_L3_OFF_G_START, EE_L3_OFF_M_START, EE_L3_OFF_G_STOP, EE_L3_OFF_M_STOP, EE_L3_NAT_MAX, EE_L3_NAT_MAN, EE_L3_TRYB);
Lampa Lampa4(LEDPin4, PWMChannel4, EE_L4_ON_G_START, EE_L4_ON_M_START, EE_L4_ON_G_STOP, EE_L4_ON_M_STOP, EE_L4_OFF_G_START, EE_L4_OFF_M_START, EE_L4_OFF_G_STOP, EE_L4_OFF_M_STOP, EE_L4_NAT_MAX, EE_L4_NAT_MAN, EE_L4_TRYB);
Lampa Lampa5(LEDPin5, PWMChannel5, EE_L5_ON_G_START, EE_L5_ON_M_START, EE_L5_ON_G_STOP, EE_L5_ON_M_STOP, EE_L5_OFF_G_START, EE_L5_OFF_M_START, EE_L5_OFF_G_STOP, EE_L5_OFF_M_STOP, EE_L5_NAT_MAX, EE_L5_NAT_MAN, EE_L5_TRYB);
Lampa Lampa6(LEDPin6, PWMChannel6, EE_L6_ON_G_START, EE_L6_ON_M_START, EE_L6_ON_G_STOP, EE_L6_ON_M_STOP, EE_L6_OFF_G_START, EE_L6_OFF_M_START, EE_L6_OFF_G_STOP, EE_L6_OFF_M_STOP, EE_L6_NAT_MAX, EE_L6_NAT_MAN, EE_L6_TRYB);
Lampa Lampa7(LEDPin7, PWMChannel7, EE_L7_ON_G_START, EE_L7_ON_M_START, EE_L7_ON_G_STOP, EE_L7_ON_M_STOP, EE_L7_OFF_G_START, EE_L7_OFF_M_START, EE_L7_OFF_G_STOP, EE_L7_OFF_M_STOP, EE_L7_NAT_MAX, EE_L7_NAT_MAN, EE_L7_TRYB);

void startLamp()
{  
  int i = 0;
  int ii = 0;
  int l1 = 0;
  int l2 = 0;
  int l3 = 0;
  int l4 = 0;
  int l5 = 0;
  int l6 = 0;
  int l7 = 0;
  l1= Lampa1.setPWM();
  l2= Lampa2.setPWM();
  l3= Lampa3.setPWM();
  l4= Lampa4.setPWM();
  l5= Lampa5.setPWM();
  l6= Lampa6.setPWM();
  l7= Lampa7.setPWM();
  l1=Lampa1.stanPWM;
  l2=Lampa2.stanPWM;
  l3=Lampa3.stanPWM;
  l4=Lampa4.stanPWM;
  l5=Lampa5.stanPWM;
  l6=Lampa6.stanPWM;
  l7=Lampa7.stanPWM;
  
  char tmp20[20];
  //gamma_22[1023-iPWM];
  for (i == 0; i<=1023; i++)  
  {    
    if (l1 >= i)
    {
      ledcWrite(Lampa1.pPWMChannel, gamma_22[i]);
    }
    if (l2 >= i)
    {
      ledcWrite(Lampa2.pPWMChannel, gamma_22[i]);
    }
    if (l3 >= i)
    {
      ledcWrite(Lampa3.pPWMChannel, gamma_22[i]);
    }
    if (l4 >= i)
    {
      ledcWrite(Lampa4.pPWMChannel, gamma_22[i]);
    }
    if (l5 >= i)
    {
      ledcWrite(Lampa5.pPWMChannel, gamma_22[i]);
    }
    if (l6 >= i)
    {
      ledcWrite(Lampa6.pPWMChannel, gamma_22[i]);
    }
    if (l7 >= i)
    {
      ledcWrite(Lampa7.pPWMChannel, gamma_22[i]);
    }
    delay(20);
    ii++;
    // Serial.println(ii);
    if ( ii > 10 )
    {
      display.clearDisplay();
      display.setTextColor(WHITE);
      display.setTextSize(2);
      display.setCursor(0, 0);
      display.print("Start lamp");
      display.setCursor(0, 20);
      sprintf(tmp20, "%04d/%04d", i,1023);
      display.print(tmp20);
      display.display();
      ii = 0;
    }
  }

 return;

}


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

//  ledcSetup(Lampa1.pPWMChannel, PWMFreq, PWMResolution);
//  ledcSetup(Lampa2.pPWMChannel, PWMFreq, PWMResolution);
//  ledcSetup(Lampa3.pPWMChannel, PWMFreq, PWMResolution);
//  ledcSetup(Lampa4.pPWMChannel, PWMFreq, PWMResolution);
//  ledcSetup(Lampa5.pPWMChannel, PWMFreq, PWMResolution);
//  ledcSetup(Lampa6.pPWMChannel, PWMFreq, PWMResolution);
//  ledcSetup(Lampa7.pPWMChannel, PWMFreq, PWMResolution);
//
//  ledcAttachPin(Lampa1.ppin, Lampa1.pPWMChannel);
//  ledcAttachPin(Lampa2.ppin, Lampa2.pPWMChannel);
//  ledcAttachPin(Lampa3.ppin, Lampa3.pPWMChannel);
//  ledcAttachPin(Lampa4.ppin, Lampa4.pPWMChannel);
//  ledcAttachPin(Lampa5.ppin, Lampa5.pPWMChannel);
//  ledcAttachPin(Lampa6.ppin, Lampa6.pPWMChannel);
//  ledcAttachPin(Lampa7.ppin, Lampa7.pPWMChannel);

  //ledcAttachChannel(uint8_t pin, uint32_t freq, uint8_t resolution, int8_t channel);
  ledcAttachChannel(Lampa1.ppin, PWMFreq, PWMResolution, Lampa1.pPWMChannel);
  ledcAttachChannel(Lampa2.ppin, PWMFreq, PWMResolution, Lampa2.pPWMChannel);
  ledcAttachChannel(Lampa3.ppin, PWMFreq, PWMResolution, Lampa3.pPWMChannel);
  ledcAttachChannel(Lampa4.ppin, PWMFreq, PWMResolution, Lampa4.pPWMChannel);
  ledcAttachChannel(Lampa5.ppin, PWMFreq, PWMResolution, Lampa5.pPWMChannel);
  ledcAttachChannel(Lampa6.ppin, PWMFreq, PWMResolution, Lampa6.pPWMChannel);
  ledcAttachChannel(Lampa7.ppin, PWMFreq, PWMResolution, Lampa7.pPWMChannel);

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

  startLamp();

}


void dajEkran()
{
  String tmpS = "";
  char tmp20[20];
  //char tmp5[5];
  
  switch (ekran)
  {
  case 0:
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.print(now.timestamp(DateTime::TIMESTAMP_TIME));
    display.setCursor(0, 20);
    display.print(now.timestamp(DateTime::TIMESTAMP_DATE));
    display.setTextSize(1);
    display.setCursor(0, 40);
    display.print(daysOfTheWeekAll[now.dayOfTheWeek()]);
    display.setTextSize(2);

    break;
  case 1:
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0,0);
    display.print("Lampa 1");    
    display.setCursor(90,0);
    if ( Lampa1.run == 0)
    {
      display.print("OFF");
    }
    else
    {
      display.print("ON");
    }  
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    sprintf(tmp20, "%02d:%02d-%02d:%02d", Lampa1.on_g_start, Lampa1.on_m_start, Lampa1.on_g_stop, Lampa1.on_m_stop);
    display.setTextSize(1);
    display.setCursor(0,20);
    display.print(tmp20);
    display.setCursor(0,30);
    sprintf(tmp20, "%02d:%02d-%02d:%02d", Lampa1.off_g_start, Lampa1.off_m_start, Lampa1.off_g_stop, Lampa1.off_m_stop);
    display.print(tmp20);
    sprintf(tmp20, "%04d,max:%04d", Lampa1.stanPWM,Lampa1.natezenie_max);
    display.setCursor(0,40);
    display.print(tmp20);

    display.setTextSize(2);
    
  break;

  case 2:
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0,0);
    display.print("Lampa 2");    
    display.setCursor(90,0);
    if ( Lampa2.run == 0)
    {
      display.print("OFF");
    }
    else
    {
      display.print("ON");
    }  
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    sprintf(tmp20, "%02d:%02d-%02d:%02d", Lampa2.on_g_start, Lampa2.on_m_start, Lampa2.on_g_stop, Lampa2.on_m_stop);
    display.setTextSize(1);
    display.setCursor(0,20);
    display.print(tmp20);
    display.setCursor(0,30);
    sprintf(tmp20, "%02d:%02d-%02d:%02d", Lampa2.off_g_start, Lampa2.off_m_start, Lampa2.off_g_stop, Lampa2.off_m_stop);
    display.print(tmp20);
    sprintf(tmp20, "%04d,max:%04d", Lampa2.stanPWM,Lampa2.natezenie_max);
    display.setCursor(0,40);
    display.print(tmp20);

    display.setTextSize(2);
    
  break;

  case 3:
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0,0);
    display.print("Lampa 3");    
    display.setCursor(90,0);
    if ( Lampa3.run == 0)
    {
      display.print("OFF");
    }
    else
    {
      display.print("ON");
    }  
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    sprintf(tmp20, "%02d:%02d-%02d:%02d", Lampa3.on_g_start, Lampa3.on_m_start, Lampa3.on_g_stop, Lampa3.on_m_stop);
    display.setTextSize(1);
    display.setCursor(0,20);
    display.print(tmp20);
    display.setCursor(0,30);
    sprintf(tmp20, "%02d:%02d-%02d:%02d", Lampa3.off_g_start, Lampa3.off_m_start, Lampa3.off_g_stop, Lampa3.off_m_stop);
    display.print(tmp20);
    sprintf(tmp20, "%04d,max:%04d", Lampa3.stanPWM,Lampa3.natezenie_max);
    display.setCursor(0,40);
    display.print(tmp20);

    display.setTextSize(2);
    
  break;

  case 4:
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0,0);
    display.print("Lampa 4");    
    display.setCursor(90,0);
    if ( Lampa3.run == 0)
    {
      display.print("OFF");
    }
    else
    {
      display.print("ON");
    }  
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    sprintf(tmp20, "%02d:%02d-%02d:%02d", Lampa4.on_g_start, Lampa4.on_m_start, Lampa4.on_g_stop, Lampa4.on_m_stop);
    display.setTextSize(1);
    display.setCursor(0,20);
    display.print(tmp20);
    display.setCursor(0,30);
    sprintf(tmp20, "%02d:%02d-%02d:%02d", Lampa4.off_g_start, Lampa4.off_m_start, Lampa4.off_g_stop, Lampa4.off_m_stop);
    display.print(tmp20);
    sprintf(tmp20, "%04d,max:%04d", Lampa4.stanPWM,Lampa4.natezenie_max);
    display.setCursor(0,40);
    display.print(tmp20);

    display.setTextSize(2);
    
  break;

  case 5:
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0,0);
    display.print("Lampa 5");    
    display.setCursor(90,0);
    if ( Lampa3.run == 0)
    {
      display.print("OFF");
    }
    else
    {
      display.print("ON");
    }  
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    sprintf(tmp20, "%02d:%02d-%02d:%02d", Lampa5.on_g_start, Lampa5.on_m_start, Lampa5.on_g_stop, Lampa5.on_m_stop);
    display.setTextSize(1);
    display.setCursor(0,20);
    display.print(tmp20);
    display.setCursor(0,30);
    sprintf(tmp20, "%02d:%02d-%02d:%02d", Lampa5.off_g_start, Lampa5.off_m_start, Lampa5.off_g_stop, Lampa5.off_m_stop);
    display.print(tmp20);
    sprintf(tmp20, "%04d,max:%04d", Lampa5.stanPWM,Lampa5.natezenie_max);
    display.setCursor(0,40);
    display.print(tmp20);

    display.setTextSize(2);
    
  break;

  case 6:
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0,0);
    display.print("Lampa 6");    
    display.setCursor(90,0);
    if ( Lampa3.run == 0)
    {
      display.print("OFF");
    }
    else
    {
      display.print("ON");
    }  
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    sprintf(tmp20, "%02d:%02d-%02d:%02d", Lampa6.on_g_start, Lampa6.on_m_start, Lampa6.on_g_stop, Lampa6.on_m_stop);
    display.setTextSize(1);
    display.setCursor(0,20);
    display.print(tmp20);
    display.setCursor(0,30);
    sprintf(tmp20, "%02d:%02d-%02d:%02d", Lampa6.off_g_start, Lampa6.off_m_start, Lampa6.off_g_stop, Lampa6.off_m_stop);
    display.print(tmp20);
    sprintf(tmp20, "%04d,max:%04d", Lampa6.stanPWM,Lampa6.natezenie_max);
    display.setCursor(0,40);
    display.print(tmp20);

    display.setTextSize(2);
    
  break;

  case 7:
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0,0);
    display.print("Tlo  ");    
    display.setCursor(90,0);
    if ( Lampa3.run == 0)
    {
      display.print("OFF");
    }
    else
    {
      display.print("ON");
    }  
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    sprintf(tmp20, "%02d:%02d-%02d:%02d", Lampa7.on_g_start, Lampa7.on_m_start, Lampa7.on_g_stop, Lampa7.on_m_stop);
    display.setTextSize(1);
    display.setCursor(0,20);
    display.print(tmp20);
    display.setCursor(0,30);
    sprintf(tmp20, "%02d:%02d-%02d:%02d", Lampa7.off_g_start, Lampa7.off_m_start, Lampa7.off_g_stop, Lampa7.off_m_stop);
    display.print(tmp20);
    sprintf(tmp20, "%04d,max:%04d", Lampa7.stanPWM,Lampa7.natezenie_max);
    display.setCursor(0,40);
    display.print(tmp20);

    display.setTextSize(2);
    
  break;



  default:
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.print(now.timestamp(DateTime::TIMESTAMP_TIME));
    display.setCursor(0, 20);
    display.print(now.timestamp(DateTime::TIMESTAMP_DATE));
    display.setTextSize(1);
    display.setCursor(0, 40);
    display.print(daysOfTheWeekAll[now.dayOfTheWeek()]);
    display.setTextSize(2);

    break;
  }
  display.display();
  
  delay(2000);
  
  if (ekran < 8)
  {
    ekran ++;
  }
  else
  {
    ekran = 0;
  }
}


void loop()
{

  recData();

  static long last_loop_time = 0;
  long loop_time = millis();
  if (loop_time - last_loop_time > change_time)
  {
    now = rtc.now();

    dajEkran();

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

}
