/***************************************************************************
**Controls an Arduino to send current to a Thinking Cap (v1.0)**
**Contains methods to initiate tDCS (with ramp-up and ramp-down) and CES**
**Warning:  Do not exceed 2 mA of current!**
**This library is designed to work with the corresponding header file.  If that file
was not included, you can find it at [insert project URL here]**
**Written 2012 by ianmathwiz7, of Grindhouse Wetware (ianmathwiz7@gmail.com)**
***************************************************************************/

#include "thinkingcap.h"

int chargetime = 5000; //How long (in ms)to allow capacitor C1 to charge (for tMS)
int pulsetime = 20;    //How long (in µs) to allow capacitor C1 to discharge (for tMS)

ThinkingCap::ThinkingCap()
{
	this->redpin = 13;
	this->greenpin = 12;
	this->bluepin = 11;
	this->currentpin = 10;
	this->magneticpin1 = 9;
	this->magneticpin2 = 8;
}

ThinkingCap::ThinkingCap(int rpin, int gpin, int bpin, int cpin, int mpin1, int mpin2)
{
	this->redpin = rpin;
	this->greenpin = gpin;
	this->bluepin = bpin;
	this->currentpin = cpin;
	this->magneticpin1 = mpin1;
	this->magneticpin2 = mpin2;
}

boolean ThinkingCap::begin()
{
	pinMode(redpin, OUTPUT);
	pinMode(greenpin, OUTPUT);
	pinMode(bluepin, OUTPUT);
	pinMode(currentpin, OUTPUT);
	pinMode(magneticpin1, OUTPUT);
	pinMode(magneticpin2, OUTPUT);
	
	return Serial.begin(9600);
}

void ThinkingCap::tDCS(int rampTime, int stimTime)
{
	//Turn status LED yellow
	digitalWrite(greenpin, HIGH);
	digitalWrite(bluepin, HIGH);
	int startTime = millis();
	for(;;)
	{
		//Figure out partial voltage
		int val = (int)(millis() - startTime)/1000.0;
		int pwmVal = map(val,0,rampTime,0,255);
		if(val >= rampTime) break;  //If voltage fully ramped, go on
		else analogWrite(currentpin, pwmVal);  //Otherwise, update the pin voltage
	}
	//Keep voltage at max and zero the timer
	digitalWrite(currentpin, HIGH);
	int timer = millis();
	//Turn status LED red
	digitalWrite(bluepin, LOW);
	digitalWrite(greenpin, LOW);
	digitalWrite(redpin, HIGH);
	Serial.println("The current is fully ramped; 20 minutes left");
	//While 20 minutes haven't passed
	while((millis() - timer) < (int)stimTime * 60000.0)
	{
	    //Serial.println("I'm in yr loop"); (used to help debug code, and kept for its pure hilariousness)
	    //Every 30 seconds, print how much time is left
		if(!((millis() - timer) % 30000))
		{
		Serial.print(1200.0 - (millis() - timer)/1000.0);
		Serial.println(" seconds left!");
	}
	}
	//After 20 minutes, ramp down current
	int endTime = millis();
	Serial.println("Ramping down current.");
	for(;;)
	{
		//Figure out partial voltage
		int val = (int)(rampTime - (millis() - endTime))/1000.0;
		int pwmVal = map(val,0,rampTime,0,255);
		if(val <= 0) break;  //If voltage fully ramped, go on
		else analogWrite(currentpin, pwmVal);  //Otherwise, update the pin voltage
	}
	//print "time's up" and turn off current
	Serial.println("Time's up!");
	digitalWrite(currentpin, LOW);
	digitalWrite(redpin, LOW);
	digitalWrite(greenpin, HIGH);
}

/*
 ***FOR INTERNAL USE ONLY; NOT RECOMMENDED FOR CONSUMER USE***
void ThinkingCap::tMS()
{
	digitalWrite(magneticpin1, HIGH); //Activate the tMS circuit
	delay(chargetime);                //Wait for capacitor C1 to charge
	digitalWrite(magneticpin2, HIGH); //Tell the transistor to close the second circuit
	digitalWrite(bluepin, HIGH);      //Turn status LED blue
	delayMicroseconds(pulsetime);
	digitalWrite(magneticpin2, LOW);  //Go away, closed circuit (unnecessary if a thyristor is used instead of a P-type transistor
	digitalWrite(bluepin, LOW);       //Turn status LED off
}*/

void ThinkingCap::CES(int frequency)
{
	double interval = 1000000 / ((double)frequency * 2);
	digitalWrite(currentpin, HIGH);   //Pulse the electric current
	digitalWrite(redpin, HIGH);       //Turn status LED magenta
	digitalWrite(bluepin, HIGH);
	delayMicroseconds(interval);
	digitalWrite(currentpin, LOW);    //Turn off electric current
	digitalWrite(redpin, LOW);        //Turn status LED off
	digitalWrite(bluepin, LOW);
	delayMicroseconds(interval);
}