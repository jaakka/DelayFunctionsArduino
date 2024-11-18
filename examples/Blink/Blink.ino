/*
    DelayFunctions, is designed for managing multiple software timers in Arduino projects.
    
    In this example, the timer function is demonstrated by blinking an LED.

    https://github.com/jaakka/DelayFunctionsArduino
    Library created by Jaakko Talvitie 18.11.2024
*/

#include <DelayFunctions.h>

//FOR ARDUINO #define ledPin = LED_BUILTIN;  
#define ledPin 2 //2 for ESP dev board


//save memory with correct count of timers.

DelayFunctions delayObj(1); //how many timers


void setup() 
{
  pinMode(ledPin, OUTPUT);
  delayObj.NewDelayFunction(1000, myTimeFunction);
}

void loop() 
{
  delayObj.loop(); // Stay alive
}

void myTimeFunction()
{
  if(digitalRead(ledPin) == HIGH)
  {
    digitalWrite(ledPin,LOW);
  }
    else
  {
    digitalWrite(ledPin,HIGH);
  }
}