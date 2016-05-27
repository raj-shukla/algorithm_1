#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/config-store-module.h"
#include "ns3/wifi-module.h"
#include "ns3/internet-module.h"
#include "ns3/olsr-helper.h"
#include "ns3/ipv4-static-routing-helper.h"
#include "ns3/ipv4-list-routing-helper.h"
 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");

int main (int argc, char *argv[])
{
  Time::SetResolution (Time::NS);
  
  NodeContainer clientNodes;
  clientNodes.Create (10);
  NodeContainer serverNodes;
  serverNodes.Create(5);
  
  YansWifiChannelHelper channel = YansWifiChannelHelper::Default () ;
  YansWifiPhyHelper phy = YansWifiPhyHelper::Default();
  WifiMacHelper wifiMac;
  WifiHelper wifi = WifiHelper::Default();
  
  WifiMac.settype("ns3::AdhocWifiMac");
  
  NetDeviceContainer cDevices;
  cDevices = wifi.Install(phy, mac, cDevices);
  
  NetDeviceContainer sDevices;
  sDevices - wifi.Install(phy, mac, sDevices);
  
  MobilityHelper mobility;
  mobility. SetPositionAllocator("ns3::GridPositionAllocator,
  "MinX", DoubleValue (0.0),
  "MinY", DoubleValue (0.0),
  "DeltaX", DoubleValue (5.0),
  "DeltaY", DoubleValue (10.0),
  "GridWidth", UintegerValue (3),
  "LayoutType", StringValue ("RowFirst")) ;
  
  mobility.SetMobility("ns3::RandomWalk2dMobilityModel",
  "Bounds", RectangleValue(Rectangle(-50, 50, -50, 50))) ;
  
  mobility.Install(clientNodes);
  mobility.Install(serverNodes);
  
  
  return 0; 
}
