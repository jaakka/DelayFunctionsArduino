/*
    https://github.com/jaakka/DelayFunctionsArduino
    Library created by Jaakko Talvitie 18.11.2024
*/

#include "Arduino.h"
#include "DelayFunctions.h"

DelayFunctions::DelayFunctions(int argTimersCount)
{
    _maxTimersCount = argTimersCount;  
    timeFunctions = new DelayFunction[_maxTimersCount]; 
    _timersCount = 0;  
}

DelayFunctions::~DelayFunctions()
{
    delete[] timeFunctions;  
}

void DelayFunctions::updateTime(void (*cb)(), unsigned long interval)
{
    for (int i = 0; i < _timersCount; i++)
    {
        if (timeFunctions[i].callback == cb) 
        {
            timeFunctions[i].interval = interval;  
        }
    }
}

unsigned long DelayFunctions::getTime(void (*cb)())
{
    for (int i = 0; i < _timersCount; i++)
    {
        if (timeFunctions[i].callback == cb)  
        {
            return timeFunctions[i].interval;  
        }
    }
    return -1;
}

void DelayFunctions::NewDelayFunction(unsigned long interval, void (*cb)())
{
    if (_timersCount < _maxTimersCount)
    {
        timeFunctions[_timersCount] = DelayFunction(cb, interval);
        timeFunctions[_timersCount].lastRun = millis();  
        _timersCount++;
    }
}

void DelayFunctions::loop()
{
    unsigned long currentMillis = millis();  
    for (int i = 0; i < _timersCount; i++)
    {
        if (currentMillis - timeFunctions[i].lastRun >= timeFunctions[i].interval)
        {
            if (timeFunctions[i].callback != nullptr)
            {
                timeFunctions[i].callback(); 
                timeFunctions[i].lastRun = currentMillis;  
            }
        }
    }
}

DelayFunction::DelayFunction()
{
    interval = 0;
    callback = nullptr;
}

DelayFunction::DelayFunction(void (*_callback)(), unsigned long _interval)
{
    callback = _callback;
    interval = _interval;
}
