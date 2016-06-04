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

void ReadData(); 

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");
std::vector <int> jobId;
std::vector <double> jobArrivalT;
std::vector <int> client;
std::vector <int> dataBytes;

class Jobs
{
  public:
  
  private:
  u_int32_t jobId; 
  u_int32_t dataSize;
  u_int32_t clientNode;
  double jobArrivalTime; 
  
};

int main (int argc, char *argv[])
{
  Time::SetResolution (Time::NS);
  
  // Create Client and SErver Nodes
  NodeContainer clientNodes, serverNodes ;
  clientNodes.Create (10);
  serverNodes.Create(5);
  
  std::vector <Jobs> jobs ;
  
  
  WifiHelper wifi = WifiHelper::Default ();
  
  //Helpers for Channel and Physical Layer
  YansWifiChannelHelper channel = YansWifiChannelHelper::Default () ;
  YansWifiPhyHelper phy = YansWifiPhyHelper::Default();
  
  //Associate channel to physical layer
  phy.SetChannel( channel.Create() );
  
  //Helper for wifiMac
  WifiMacHelper wifiMac;
  
  //Set Mac as Adhoc  
  wifiMac.SetType("ns3::AdhocWifiMac");
  
  //Install Adhoc wifi on client devices
  NetDeviceContainer cDevices = wifi.Install(phy, wifiMac, clientNodes);
  
  //Install Adhoc wifi on server devices
  NetDeviceContainer sDevices =  wifi.Install(phy, wifiMac, serverNodes) ;
  
  //Set up and installation  of mobility model
  MobilityHelper mobility;
  mobility. SetPositionAllocator("ns3::GridPositionAllocator", \
                                 "MinX", DoubleValue (0.0), \
                                 "MinY", DoubleValue (0.0), \
                                 "DeltaX", DoubleValue (5.0), \
                                 "DeltaY", DoubleValue (10.0), \
                                 "GridWidth", UintegerValue (3), \
                                 "LayoutType", StringValue ("RowFirst")) ;
  
  mobility.SetMobilityModel("ns3::RandomWalk2dMobilityModel", "Bounds", RectangleValue(Rectangle(-50, 50, -50, 50))) ;
  
  mobility.Install(clientNodes);
  mobility.Install(serverNodes);
  
  //Enable routing protocol OLSR
  OlsrHelper olsr;
  Ipv4StaticRoutingHelper staticRouting ;
  
  Ipv4ListRoutingHelper list ;
  
  list.Add(staticRouting, 0);
  list.Add(olsr, 10);
  
  InternetStackHelper stack ; 
  stack.SetRoutingHelper(list) ;
  stack.Install(clientNodes) ;
  stack.Install(serverNodes) ; 
  
  Ipv4AddressHelper address;
  NS_LOG_INFO("Assign IP Address");
  
  address.SetBase("10.1.0.0", "255.255.255.0");
  Ipv4InterfaceContainer clientInterface ;
  clientInterface = address.Assign(cDevices);
   
  address.SetBase("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer serverInterface;
  serverInterface = address.Assign(sDevices);
  
  return 0; 
}



void ReadData()
{
  FILE *fp ;
  char dataFile[20] ;
  char character ;
  double word ;
  double data ;
  int i ;
  
  fp = fopen(dataFile, "r" ) ;
  
    while(1)
    {
        character = fgetc( fp );
        if(character == EOF)
        {
            break ;
        }
        for(i = 0 ;i <=3; i ++)
        {
            if (i == 0)
            {
                data = fscanf ( fp, " %lf ", &word) ;   
                jobId.push_back(int(data)) ;
            }
            if (i == 1)
            {
                data = fscanf ( fp, " %lf ", &word) ;   
                jobArrivalT.push_back(data) ;
            }
            if (i == 2)
            {
                data = fscanf ( fp, " %lf ", &word) ;   
                client.push_back(int(data)) ;
            }
            if (i == 3)
            {
                data = fscanf ( fp, " %lf ", &word) ;   
                dataBytes.push_back(int(data));
            }
        }
    }
}
