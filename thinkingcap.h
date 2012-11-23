#ifndef __THINKINGCAP_H__
#define __THINKINGCAP_H__

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class ThinkingCap {
  protected:
  int redpin;
  int greenpin;
  int bluepin;
  int currentpin;
  int magneticpin;
  int transistorpin;
  public:
  ThinkingCap();                             //Default Constructor
  ThinkingCap(int, int, int, int, int, int); //Not-so-default constructor
  void begin();                              //Initializes the Thinking Cap
  void tDCS(int, int);                       //Carries out transcranial Direct Current Stimulation
  void tMS();                                //Carries out transcranial Magnetic Stimulation
  void CES(int);                             //Carries out Cranial Electrotherapy Stimulation
};

#endif