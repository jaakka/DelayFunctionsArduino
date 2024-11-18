#include "Arduino.h"
#include "DelayFunctions.h"

// Konstruktori, joka alustaa ajastimien määrän ja varaa muistia
DelayFunctions::DelayFunctions(int argTimersCount)
{
    _maxTimersCount = argTimersCount;  // Asetetaan enimmäismäärä
    timeFunctions = new DelayFunction[_maxTimersCount];  // Dynaaminen muistivaraus ajastimille
    _timersCount = 0;  // Alustetaan ajastimien määrä nollaksi
}

// Destruktori, joka vapauttaa dynaamisesti varatun muistin
DelayFunctions::~DelayFunctions()
{
    delete[] timeFunctions;  // Vapautetaan muistivaraus
}

// Päivittää ajastimen aikarajan 
void DelayFunctions::updateTime(void (*cb)(), unsigned long interval)
{
    for (int i = 0; i < _timersCount; i++)
    {
        if (timeFunctions[i].callback == cb)  // Jos callback-muuttuja vastaa
        {
            timeFunctions[i].interval = interval;  // Päivitetään ajastimen interval
        }
    }
}

// Hankkii ajastimen aikarajan
unsigned long DelayFunctions::getTime(void (*cb)())
{
    for (int i = 0; i < _timersCount; i++)
    {
        if (timeFunctions[i].callback == cb)  // Jos callback-muuttuja vastaa
        {
            return timeFunctions[i].interval;  // Palautetaan ajastimen interval
        }
    }
    return -1;
}

// Lisää uuden ajastimen ajastinluetteloon
void DelayFunctions::NewDelayFunction(unsigned long interval, void (*cb)())
{
    if (_timersCount < _maxTimersCount)
    {
        timeFunctions[_timersCount] = DelayFunction(cb, interval);
        timeFunctions[_timersCount].lastRun = millis();  // Alustetaan viimeinen suoritushetki
        _timersCount++;
    }
    else
    {
        Serial.println("Max timers reached! Cannot add more timers.");
    }
}

// Kutsutaan pääloopissa ja tarkistaa ajastimet
void DelayFunctions::loop()
{
    unsigned long currentMillis = millis();  // Haetaan nykyinen aika
    for (int i = 0; i < _timersCount; i++)
    {
        // Tarkistetaan, onko ajastin ehtinyt aikarajan
        if (currentMillis - timeFunctions[i].lastRun >= timeFunctions[i].interval)
        {
            if (timeFunctions[i].callback != nullptr)
            {
                timeFunctions[i].callback();  // Kutsutaan ajastimen callback
                timeFunctions[i].lastRun = currentMillis;  // Päivitetään viimeinen suoritushetki
            }
        }
    }
}

// DelayFunction-konstruktori, joka alustaa ajastimen
DelayFunction::DelayFunction()
{
    interval = 0;
    callback = nullptr;
}

// Parametrillinen konstruktori, joka asettaa callbackin ja intervalin
DelayFunction::DelayFunction(void (*_callback)(), unsigned long _interval)
{
    callback = _callback;
    interval = _interval;
}
