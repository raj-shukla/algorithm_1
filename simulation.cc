#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");

int main (int argc, char *argv[])
{
  Time::SetResolution (Time::NS);
  
  NodeContainer clientNodes;
  clientNodes.Create (10);
  
  NodeContainer serverNodes;
  serverNodes.Create(5);
  printf("\nsNodes Created Successfully\n") ;
  
  return 0; 
}
