#include <DelayFunctions.h>

//save memory with correct count of timers.
DelayFunctions delayObj(4); //how many timers.

void exampleFunctionForHalfSecond()
{
  Serial.println("HalfSecond");
}

void exampleFunctionForOneSecond()
{
  Serial.println("Second");
}

void exampleFunctionForFiveSecond()
{
  Serial.println("FiveSecond");
}

void exampleFunctionForTenSecond()
{
  Serial.println("TenSecond");
}

void setup() 
{
  Serial.begin(9600);
  delayObj.NewDelayFunction(500, exampleFunctionForHalfSecond);
  delayObj.NewDelayFunction(1000, exampleFunctionForOneSecond);
  delayObj.NewDelayFunction(5000, exampleFunctionForFiveSecond);
  delayObj.NewDelayFunction(10000, exampleFunctionForTenSecond);
  Serial.println("Start");
}

void loop() 
{
  delayObj.loop();
}