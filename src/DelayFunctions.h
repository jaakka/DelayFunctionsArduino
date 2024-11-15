#ifndef W211ClusterControl_h
#define W211ClusterControl_h

#include "Arduino.h"
#include "mcp_can.h"
#include "SPI.h"
#include "W211Enums.h"

class W211Control
{
  public:
    W211Control(MCP_CAN canB);
    W211Control(MCP_CAN canB, MCP_CAN canC);
    void loop();

    void steeringWheelButtonPress(SteeringWheelBtn button);

    void enableDebugMsgs();
    void disableDebugMsgs();

    void simulateKey(KeyStatus keyStatus); 
    void turnKeySimulatorOff();

    void simulateSpeed(int speed); 
    void turnSpeedSimulatorOff();

    void simulateFrontLeftSpeed(int speed); 
    void turnFrontLeftSpeedSimulatorOff();

    void simulateFrontRightSpeed(int speed); 
    void turnFrontRightSpeedSimulatorOff();

    void simulateRearLeftSpeed(int speed); 
    void turnRearLeftSpeedSimulatorOff();

    void simulateRearRightSpeed(int speed); 
    void turnRearRightSpeedSimulatorOff();
 
  private:
    String _prex = "W211 control: ";
    MCP_CAN _canB, _canC;
    int delayForCanBMsgs = 1440, delayForCanCMsgs = 240;
    unsigned long _lastPowerMsgTime = 0;
    bool _output = false, _simulateKey = false, _bAvailable = false, _cAvailable = false, _simulateLeftFrontSpeed = false, _simulateRightFrontSpeed = false, _simulateLeftRearSpeed = false, _simulateRightRearSpeed = false;
    KeyStatus _keyStatus = KeyStatus::NotInserted;
    
    void Outputln(bool _prexEnabled,String _msg);
    void Output(String _msg);
    void PowerLoop();
};

#endif