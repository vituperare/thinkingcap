#include <thinkingcap.h>

const int switchPin = 7;              //Connect a switch to pin 7
const int buttonPin = 6;              //Connect a spring-loaded push-button to pin 6
const int potentPin = A0;             //Connect a potentiometer to A0

boolean StartTC;                      //Stores whether or not the TC initialized successfully

ThinkingCap *tcap = new ThinkingCap(); //Default constructor; you can also pass arguments to it to set the pins

void setup()
{
  StartTC = (*tcap).begin();           //Prepares the Thinking Cap for use; also turns on the serial interface
  pinMode(switchPin, INPUT);
  pinMode(buttonPin, INPUT);
}

void loop()
{
  if(StartTC)                          //If the Thinking Cap setup was successful
  {
    if(digitalRead(buttonPin) == HIGH) //When the button is pushed
    {
      int potentVal = analogRead(potentPin);  //Get the value from the potentiometer
      if(digitalRead(switchPin) == HIGH) //If the switch is "on"
      {
        int time = map(potentVal, 0, 1023, 1, 60); //Convert the input value into a time
        (*tcap).tDCS(time / 2, time);  //Perform tDCS for that time, with ramp time equal to 1/120 of that
      }
      else                             //If the switch is "off"
      {
        while(digitalRead(buttonPin) == LOW)  //Until the button is pushed again
        {
          double freq = (double)map(potentVal, 0, 1023, 1, 500) / 100.0;  //Convert the input value into a frequency
          (*tcap).CES(freq);          //Perform CES with the given frequency
        }
      }
    }
  }
}
