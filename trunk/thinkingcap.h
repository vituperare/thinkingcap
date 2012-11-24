/***************************************************************************
**Controls an Arduino to send current to a Thinking Cap (v1.0)**
**Contains methods to initiate tDCS (with ramp-up and ramp-down) and CES**
**Warning:  Do not exceed 2 mA of current!**
**This library is designed to work with the corresponding definition file.  If that file
was not included, you can find it at [insert project URL here]**
**Written 2012 by ianmathwiz7, of Grindhouse Wetware (ianmathwiz7@gmail.com)**
***************************************************************************/

 __THINKINGCAP_H__
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
  //void tMS();                                //Carries out transcranial Magnetic Stimulation
  void CES(int);                             //Carries out Cranial Electrotherapy Stimulation
};

#endif