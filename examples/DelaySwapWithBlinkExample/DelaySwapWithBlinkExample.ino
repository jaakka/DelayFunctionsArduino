#include <DelayFunctions.h>

//FOR ARDUINO #define ledPin = LED_BUILTIN;  
#define ledPin 2 //2 for ESP dev board


//save memory with correct count of timers.

//how many timers
DelayFunctions myTimerSystem(1);

void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  myTimerSystem.NewDelayFunction(1000,exampleTimeFunction); // set start loop time to 1s
}

void loop()
{
  myTimerSystem.loop(); // Stay alive
}

void exampleTimeFunction()
{
  if(myTimerSystem.getTime(exampleTimeFunction) == 1000) // Get timer current delay
  {
    myTimerSystem.updateTime(exampleTimeFunction, 100); // Swap delay to 100ms
  }
  else
  {
    myTimerSystem.updateTime(exampleTimeFunction, 1000); // Swap delay to 1s
  }

  digitalWrite(2,HIGH);
  delay(10);
  digitalWrite(2,LOW);
}