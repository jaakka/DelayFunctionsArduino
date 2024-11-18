/*
    DelayFunctions, is designed for managing multiple software timers in Arduino projects.
    
    In this example, multiple timed functions are demonstrated, 
    and a message is printed to the Serial Monitor whenever one of them executes.

    https://github.com/jaakka/DelayFunctionsArduino
    Library created by Jaakko Talvitie 18.11.2024
*/

#include <DelayFunctions.h>

//save memory with correct count of timers.
DelayFunctions delayObj(4); //how many timers.

void setup() 
{
  Serial.begin(9600);
  delayObj.NewDelayFunction(500, exampleFunctionForHalfSecond);
  delayObj.NewDelayFunction(1000, exampleFunctionForOneSecond);
  delayObj.NewDelayFunction(5000, exampleFunctionForFiveSecond);
  delayObj.NewDelayFunction(10000, exampleFunctionForTenSecond);
}

void loop() 
{
  delayObj.loop(); // Stay alive
}




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