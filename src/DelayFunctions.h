#ifndef DELAYFUNCTIONS_H
#define DELAYFUNCTIONS_H

#include "Arduino.h"

// DelayFunction-luokka, joka edustaa yksittäistä ajastinta
class DelayFunction
{
  public:
    DelayFunction();  // Konstruktori, joka alustaa ajastimen
    DelayFunction(void (*_callback)(), unsigned long _interval);  // Parametrillinen konstruktori
    unsigned long lastRun; 
    unsigned long interval;  // Ajastimen aikaraja
    void (*callback)();      // Callback-funktion osoitin
};

class DelayFunctions
{
  public:
    DelayFunctions(int timersCount);  // Konstruktori, joka alustaa ajastimien määrän
    ~DelayFunctions();                // Destruktori, joka vapauttaa dynaamisen muistin
    void NewDelayFunction(unsigned long interval, void (*cb)());  // Lisää uuden ajastimen
    void loop();                      // Pääloopin metodi, joka käsittelee ajastimet
    void updateTime(void (*cb)(), unsigned long interval);  // Päivittää ajastimen ajan
    unsigned long getTime(void (*cb)());  // Hankkii ajastimen ajan

  private:
    int _maxTimersCount;      // Ajastimien enimmäismäärä
    int _timersCount;         // Käytössä olevien ajastimien määrä
    DelayFunction* timeFunctions;  // Dynaamisesti varattu taulukko ajastimille
};

#endif
