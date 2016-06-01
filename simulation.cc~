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
  
  // Create Client and SErver Nodes
  NodeContainer clientNodes;
  clientNodes.Create (10);
  NodeContainer serverNodes;
  serverNodes.Create(5);
  
  
  WifiHelper wifi = WifiHelper::Default();
  
  //Helpers for Channel and Physical Layer
  YansWifiChannelHelper channel = YansWifiChannelHelper::Default () ;
  YansWifiPhyHelper phy = YansWifiPhyHelper::Default();
  
  //Associate channel to physical layer
  phy.SetChannel( channel.Create() );
  
  //Helper for wifiMac
  WifiMacHelper wifiMac;
  
  //Set Mac as Adhoc  
  WifiMac.settype("ns3::AdhocWifiMac");
  
  //Install Adhoc wifi on client devices
  NetDeviceContainer cDevices;
  cDevices = wifi.Install(phy, mac, cDevices);
  
  //Install Adhoc wifi on server devices
  NetDeviceContainer sDevices;
  sDevices - wifi.Install(phy, mac, sDevices);
  
  //Set up and installation  of mobility model
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
  
  OlsrHelper olsr;
  Ipv4StaticRoutingHelper staticRouting ;
  
  Ipv4ListRoutingHelper list ;
  
  list.add(staticRouting, 0);
  list.add(olsr, 10);
  
  Ipv4AddressHelper address;
  NS_LOG_INFF("Assign IP Address");
  
  address.SetBase("10.1.0.0", "255.255.255.0");
  Ipv4InterfaceContainer clientInterface ;
  clientInterface = address.assign(cDevices);
   
  address.SetBase("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer serverInterface;
  serverInterface = address.assign(sDevices);
  
  return 0; 
}
