/*
    https://github.com/jaakka/DelayFunctionsArduino
    Library created by Jaakko Talvitie 18.11.2024
*/

#ifndef DELAYFUNCTIONS_H
#define DELAYFUNCTIONS_H

#include "Arduino.h"

class DelayFunction
{
  public:
    DelayFunction();  
    DelayFunction(void (*_callback)(), unsigned long _interval);  
    unsigned long lastRun; 
    unsigned long interval;  
    void (*callback)();      
};

class DelayFunctions
{
  public:
    DelayFunctions(int timersCount); 
    ~DelayFunctions();               
    void NewDelayFunction(unsigned long interval, void (*cb)());  
    void loop();                      
    void updateTime(void (*cb)(), unsigned long interval); 
    unsigned long getTime(void (*cb)());  

  private:
    int _maxTimersCount;    
    int _timersCount;      
    DelayFunction* timeFunctions;  
};

#endif
