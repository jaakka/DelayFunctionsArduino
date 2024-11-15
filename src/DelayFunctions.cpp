#include "Arduino.h"
#include "W211Control.h"
#include "W211Enums.h"

W211Control::W211Control(MCP_CAN canB) 
{
    _canB = canB;
    _bAvailable = true;
}

W211Control::W211Control(MCP_CAN canB, MCP_CAN canC) 
{
    _canB = canB;
    _canC = canC;
    _bAvailable = true;
    _cAvailable = true;
}

void W211Control::simulateKey(KeyStatus keyStatus) 
{
    if(!_simulateKey)
    {
        _keyStatus =  keyStatus;
        _simulateKey = true;
        Outputln(true,"Key simulator started.");
    }
        else
    {
        Outputln(true,"Key simulator already started.");
    }
}

void W211Control::simulateSpeed(int speed)
{
    if(!_simulateLeftFrontSpeed && !_simulateRightFrontSpeed && !_simulateLeftRearSpeed && !_simulateRightRearSpeed)
    {
        W211Control::simulateFrontLeftSpeed(speed);
        W211Control::simulateFrontRightSpeed(speed); 
        W211Control::simulateRearLeftSpeed(speed); 
        W211Control::simulateRearRightSpeed(speed);

        Outputln(true,"Simulator started for all wheels.");
    } 
        else
    {
        Outputln(true,"Simulator is already started for all wheels.");
    }
}

void W211Control::turnSpeedSimulatorOff()
{
    if(_simulateLeftFrontSpeed || _simulateRightFrontSpeed || _simulateLeftRearSpeed || _simulateRightRearSpeed)
    {
        W211Control::turnFrontLeftSpeedSimulatorOff();
        W211Control::turnFrontRightSpeedSimulatorOff();
        W211Control::turnRearLeftSpeedSimulatorOff();
        W211Control::turnRearRightSpeedSimulatorOff();

        Outputln(true,"Simulator is now turned off for all wheels.");
    }
        else
    {
        Outputln(true,"Simulator is already stopped for all wheels.");
    }
}

void W211Control::simulateFrontLeftSpeed(int speed)
{
    if(!_simulateLeftFrontSpeed)
    {
        _simulateLeftFrontSpeed = true; 
        Outputln(true,"Simulator is started for front left wheel. ("+String(speed)+"km/h)");
    }
        else
    {
        Outputln(true,"Simulator is already started for front left wheel.");
    }
}

void W211Control::turnFrontLeftSpeedSimulatorOff();
{
    _simulateLeftFrontSpeed = false;
}

void W211Control::simulateFrontRightSpeed(int speed); 
{
    if(!_simulateRightFrontSpeed)
    {
        _simulateRightFrontSpeed = true; 
        Outputln(true,"Simulator is started for front right wheel. ("+String(speed)+"km/h)");
    }
        else
    {
        Outputln(true,"Simulator is already started for front right wheel.");
    }
}

void W211Control::turnFrontRightSpeedSimulatorOff();
{
    _simulateLeftFrontSpeed = false;
}

void W211Control::simulateRearLeftSpeed(int speed); 
{
    if(!_simulateLeftRearSpeed)
    {
        _simulateLeftRearSpeed = true; 
        Outputln(true,"Simulator is started for rear left wheel. ("+String(speed)+"km/h)");
    }
        else
    {
        Outputln(true,"Simulator is already started for rear left wheel.");
    }
}

void W211Control::turnRearLeftSpeedSimulatorOff();
{
    _simulateLeftFrontSpeed = false;
}

void W211Control::simulateRearRightSpeed(int speed); 
{
    if(!_simulateRightRearSpeed)
    {
        _simulateRightRearSpeed = true; 
        Outputln(true,"Simulator is started for rear right wheel. ("+String(speed)+"km/h)");
    }
        else
    {
        Outputln(true,"Simulator is already started for rear right wheel.");
    }
}

void W211Control::turnRearRightSpeedSimulatorOff();
{
    _simulateLeftFrontSpeed = false;
}

void W211Control::turnKeySimulatorOff()
{
    if(_simulateKey)
    {
        _keyStatus = KeyStatus::NotInserted;
        _simulateKey = false;
        Outputln(true,"Key simulator is turned off.");
    }
        else
    {
        Outputln(true,"Key simulator already turned off.");
    }
}

void W211Control::enableDebugMsgs()
{
    _output = true;
    Outputln(true,"Debug messages is now enabled.");
}

void W211Control::disableDebugMsgs()
{
    Outputln(true,"Debug messages is now disabled.");
    _output = false;
}

void W211Control::Outputln(bool prexEnabled, String msg) 
{
    if(_output)
    {
        if(prexEnabled)
        {
            Serial.println(String(_prex)+msg);
        }
        else
        {
            Serial.println(msg);
        }
    }
}

void W211Control::Output(String msg) 
{
    if(_output)
    {
        Serial.print(msg);
    }
}

void W211Control::loop() 
{
    W211Control::PowerLoop();
}

void W211Control::PowerLoop() 
{
    if(_lastPowerMsgTime + 1000 < millis() && _simulateKey)
    {
        _lastPowerMsgTime = millis();
        int keyMsg = 0x0; //  case KeyStatus.NotInserted:

        switch (_keyStatus)
        {
            case KeyStatus::Inserted:
                keyMsg = 0x1;
            break;

            case KeyStatus::HalfPower:
                keyMsg = 0x3;
            break;

            case KeyStatus::FullPower:
                keyMsg = 0x15;
            break;
        }

        unsigned char CanMsg[] = {keyMsg,0x0,0x0,0x0,0x0,0x0,0x0,0x0};
        for (int i = 0; i < 20; i++) 
        {
            _canB.sendMsgBuf(0x00, 0, 8, CanMsg);
        }
    }
}

