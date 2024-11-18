/*
    DelayFunctions, is designed for managing multiple software timers in Arduino projects.
    
    In this example, the timer function is demonstrated by printing a message 
    to the Serial Monitor every second.

    https://github.com/jaakka/DelayFunctionsArduino
    Library created by Jaakko Talvitie 18.11.2024
*/

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