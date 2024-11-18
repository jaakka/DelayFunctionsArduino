#include <DelayFunctions.h>

//save memory with correct count of timers.
DelayFunctions delayObj(1); //how many timers.

void setup() 
{
  Serial.begin(9600);
  delayObj.NewDelayFunction(1000, myTimeFunction);
}

void loop() 
{
  delayObj.loop(); // Stay alive
}

void myTimeFunction()
{
  Serial.println("Second!");
}