#include <W211Control.h>
#include <mcp_can.h>
#include <SPI.h>

MCP_CAN canB(10);
MCP_CAN canC(6);

W211Control W211Controller(canB,canC);

void setup() 
{
  while (CAN_OK != canB.begin(CAN_83K3BPS)){Serial.println("CAN B init fail");  delay(500); }  
  while (CAN_OK != canC.begin(CAN_500KBPS)){Serial.println("CAN C init fail");  delay(500); }  
  Serial.begin(115200);
  W211Controller.enableDebugMsgs();
  W211Controller.simulateKey(KeyStatus::FullPower);
}

void loop() 
{
  W211Controller.loop();
}