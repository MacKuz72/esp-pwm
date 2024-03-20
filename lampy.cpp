/*
 * gamma.c
 *
 *  Created on: 2 gru 2020
 *      Author: Maciej Kuźmiak
 */
#include "Arduino.h"
#include "lampy.h"
#include <time.h>
#include <RTClib.h>
#include <EEPROM.h>


extern DateTime now;
// extern Lampa lampa_biala;
// extern Lampa lampa_kolorowa;

Lampa::Lampa(int pin, int PWMChannel, uint8_t EE_on_g_start, uint8_t EE_on_m_start, uint8_t EE_on_g_stop, uint8_t EE_on_m_stop, uint8_t EE_off_g_start, uint8_t EE_off_m_start, uint8_t EE_off_g_stop, uint8_t EE_off_m_stop, uint8_t EE_natezenie_max, uint8_t EE_natezenie_manual, uint8_t EE_tryb)
{
  /* Setting PWM Properties */
  //const int PWMFreq = 1000; /* 1 KHz */
  //const int PWMChannel = 0;
  //const int PWMResolution = 10;
  //const int MAX_DUTY_CYCLE = (int)(pow(2, PWMResolution) - 1);

  //ledcSetup(PWMChannel, PWMFreq, PWMResolution);
  /* Attach the LED PWM Channel to the GPIO Pin */
  //ledcAttachPin(pin, PWMChannel);
  ppin = pin;
  pPWMChannel = PWMChannel;
  _pin = pin;
  _PWMChannel = PWMChannel;

  _EE_on_g_start = EE_on_g_start;   
  _EE_on_m_start = EE_on_m_start;
  _EE_on_g_stop = EE_on_g_stop;
  _EE_on_m_stop = EE_on_m_stop;
  _EE_off_g_start = EE_off_g_start;
  _EE_off_m_start = EE_off_m_start;
  _EE_off_g_stop = EE_off_g_stop;
  _EE_off_m_stop = EE_off_m_stop;
  _EE_natezenie_max = EE_natezenie_max;
  _EE_natezenie_manual = EE_natezenie_manual;
  _EE_tryb = EE_tryb; 
}

int Lampa::readLampa()
{
  on_g_start = EEPROM.read(_EE_on_g_start);   
  on_m_start = EEPROM.read(_EE_on_m_start);
  on_g_stop = EEPROM.read(_EE_on_g_stop);
  on_m_stop = EEPROM.read(_EE_on_m_stop);
  off_g_start = EEPROM.read(_EE_off_g_start);
  off_m_start = EEPROM.read(_EE_off_m_start);
  off_g_stop = EEPROM.read(_EE_off_g_stop);
  off_m_stop = EEPROM.read(_EE_off_m_stop);
  natezenie_max = EEPROM.readInt(_EE_natezenie_max);
  natezenie_manual = EEPROM.readInt(_EE_natezenie_manual);
  tryb = EEPROM.read(_EE_tryb); 
    
  return 0;

}


void Lampa::printLampa()
{
  Serial.print("ON_G_START=");
  Serial.println(on_g_start);   
  Serial.print("ON_M_START=");
  Serial.println(on_m_start);
  Serial.print("ON_G_STOP=");
  Serial.println(on_g_stop);
  Serial.print("ON_M_STOP=");
  Serial.println(on_m_stop);
  Serial.print("OFF_G_START=");
  Serial.println(off_g_start);
  Serial.print("OFF_M_START=");
  Serial.println(off_m_start);
  Serial.print("OFF_G_STOP=");
  Serial.println(off_g_stop);
  Serial.print("OFF_M_STOP=");
  Serial.println(off_m_stop);
  Serial.print("NAT_MAX=");
  Serial.println(natezenie_max);
  Serial.print("NAT_MAN=");
  Serial.println(natezenie_manual);
  Serial.print("TRYB=");
  Serial.println( tryb); 
  
  return;
}


int Lampa::saveLampa()
{
  EEPROM.write(_EE_on_g_start, on_g_start);   
  EEPROM.write(_EE_on_m_start, on_m_start);
  EEPROM.write(_EE_on_g_stop, on_g_stop);
  EEPROM.write(_EE_on_m_stop, on_m_stop);
  EEPROM.write(_EE_off_g_start, off_g_start);
  EEPROM.write(_EE_off_m_start, off_m_start);
  EEPROM.write(_EE_off_g_stop, off_g_stop);
  EEPROM.write(_EE_off_m_stop, off_m_stop);
  EEPROM.writeInt(_EE_natezenie_max, natezenie_max);
  EEPROM.writeInt(_EE_natezenie_manual, natezenie_manual);
  EEPROM.write(_EE_tryb, tryb); 
  EEPROM.commit();  
  return 0;
}

int Lampa::setPWM()
{
  int godz = now.hour();
  int min = now.minute();
  float roznica = 0;
  float minuty = 0;
  //  float sPWM = 1023;
  //   float sPWM = 65535;
  float fPWM = 0;

  //   // zamieniam pwm z poziomu 255 na procenty 100 a potem przeliczam na wartości od 0 do 65535 lepsza płynność
  //   int f_pwm_max =  map(EE_tab[pwm_max],  0, 100,  0, 65535);
  //   int f_pwm_kolor_max =  map(EE_tab[pwm_kolor_max],  0, 100,  0, 65535);

  if (tryb == 1)
  {
    float on_min;
    float off_min;
    int iPWM = 0;
    //   // Serial.println("dupa 5");

    on_min = (on_g_stop - on_g_start) * 60 - on_m_start + on_m_stop;
    off_min = (off_g_stop - off_g_start) * 60 - off_m_start + off_m_stop;

    //   ///////////////************************************************************************
    if (godz > on_g_stop && godz < off_g_start)
      iPWM = natezenie_max;
    if (godz == on_g_stop && min > on_m_stop)
      iPWM = natezenie_max;
    if (godz == off_g_start && min < off_m_start)
      iPWM = natezenie_max;

    if (godz >= off_g_stop)
    {
      if (min > off_m_stop)
      {
        iPWM = 0;
      }
    }

    if (godz <= on_g_start)
    {
      if (min > on_m_start)
      {
        iPWM = 0;
      }
    }

    //   ///////////////// rozpalanie ////////////////////////
    if (godz >= on_g_start && godz <= on_g_stop)
    {
      if (godz == on_g_start && min >= on_m_start)
      {
        minuty = min - on_m_start;
      }
      if (godz > on_g_start)
      {
        roznica = godz - on_g_start;
        minuty = (60 * roznica) + min - on_m_start;
      }
      if (godz == on_g_stop && min <= on_m_stop)
      {
        roznica = godz - on_g_start;
        minuty = (60 * roznica) + min - on_m_start;
        if (minuty < 0)
          minuty = 0;
      }

      fPWM = (natezenie_max * minuty) / on_min;
      iPWM = (unsigned int)(fPWM + 0.5);
      // cPWM = iPWM;
      if (iPWM > natezenie_max)
        iPWM = natezenie_max;
      // if ( cPWM > f_pwm_kolor_max ) cPWM = f_pwm_kolor_max;
    }

    //   //////////////// wygaszanie ///////////////////////////////
    if (godz >= off_g_start && godz <= off_g_stop)
    {
      if (godz == off_g_start && min >= off_m_start)
      {
        minuty = min - off_m_start;
      }
      if (godz > off_g_start)
      {
        roznica = godz - off_g_start;
        minuty = (60 * roznica) + min;
      }
      if (godz == off_g_stop && min <= off_m_stop)
      {
        minuty = off_min - off_m_stop + min;
        if (minuty < 0)
          minuty = 0;
      }
      fPWM = (natezenie_max * minuty) / off_min;
      iPWM = (unsigned int)(fPWM + 0.5);
      // cPWM = iPWM;
      iPWM = natezenie_max - iPWM;
      if (iPWM < 0)
        iPWM = 0;
      // cPWM = f_pwm_kolor_max - cPWM;
      // if ( cPWM < 0 ) cPWM = 0;
    }
    natezenie = gamma_22[iPWM];
    //ledcWrite(_PWMChannel, gamma_22[iPWM]);
    //     pwmWriteHR(P_PWM_B, iPWM);
    //     pwmWriteHR(P_PWM_K, cPWM);

    // Serial.print("AUTO setPWM=");
    // Serial.println(iPWM);
    // //  Serial.print("K=");
    // //  Serial.println( cPWM );
    // }
    return gamma_22[1023 - iPWM];
    //return 1023 - iPWM; 
  }
  else
  {
    //ledcWrite(_PWMChannel, gamma_22[natezenie_manual]);
     Serial.print("MANUAL setPWM=");
     Serial.println(natezenie_manual);
     Serial.println(_PWMChannel);
     Serial.println(ledcRead(_PWMChannel));
     return gamma_22[1023 - natezenie_manual];
     //return 1023 - natezenie_manual;
  }
}

// void saveLampy()
// {

//   StaticJsonDocument<1024> doc;

//   JsonObject lampa_kolor = doc.createNestedObject("lampa_kolor");
//   lampa_kolor["on_g_start"] = lampa_kolorowa.on_g_start;
//   lampa_kolor["on_m_start"] = lampa_kolorowa.on_m_start;
//   lampa_kolor["on_g_stop"] = lampa_kolorowa.on_g_stop;
//   lampa_kolor["on_m_stop"] = lampa_kolorowa.on_m_stop;
//   lampa_kolor["off_g_start"] = lampa_kolorowa.off_g_start;
//   lampa_kolor["off_m_start"] = lampa_kolorowa.off_m_start;
//   lampa_kolor["off_g_stop"] = lampa_kolorowa.off_g_stop;
//   lampa_kolor["off_m_stop"] = lampa_kolorowa.off_m_stop;
//   lampa_kolor["natezenie_max"] = lampa_kolorowa.natezenie_max;
//   lampa_kolor["tryb"] = lampa_kolorowa.tryb;
//   lampa_kolor["natezenie_manual"] = lampa_kolorowa.natezenie_manual;

//   JsonObject lampa_biale = doc.createNestedObject("lampa_biale");
//   lampa_biale["on_g_start"] = lampa_biala.on_g_start;
//   lampa_biale["on_n_start"] = lampa_biala.on_m_start;
//   lampa_biale["on_g_stop"] = lampa_biala.on_g_stop;
//   lampa_biale["on_m_stop"] = lampa_biala.on_m_stop;
//   lampa_biale["off_g_start"] = lampa_biala.off_g_start;
//   lampa_biale["off_m_start"] = lampa_biala.off_m_start;
//   lampa_biale["off_g_stop"] = lampa_biala.off_g_stop;
//   lampa_biale["off_m_stop"] = lampa_biala.off_m_stop;
//   lampa_biale["natezenie_max"] = lampa_biala.natezenie_max;
//   lampa_biale["tryb"] = lampa_biala.tryb;
//   lampa_biale["natezenie_manual"] = lampa_biala.natezenie_manual;

//   File file_lampa = SPIFFS.open("/lampy.txt", "w");
//   if (!file_lampa)
//   {
// #ifdef DEBUG
//     Serial.println("Błąd otwarcia pliku konfiguracyjnego pompy");
// #endif
//   }
//   else
//   {
//     //request->send(200, "text/plain", "OK");
//     serializeJson(doc, file_lampa);
//     //configFile.print(p->value());
//     file_lampa.close();
// #ifdef DEBUG
//     Serial.println("Saved system config file");
// #endif
//   }

//   return;
// }
