#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
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

using namespace std; 
using namespace ns3;


NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");

class Jobs
{
  public:
  void AssignData(int jId, double jAtime, int cNode, int packetS, int packetR);
  int GetServerNode(void );
  int GetClientNode() ;
  unsigned GetPacketSent() ;
  double GetJobArrivalTime ();
  
  private:
  u_int32_t jobId; 
  u_int32_t packetSent;
  u_int32_t packetReceive;
  u_int32_t clientNode;
  double jobArrivalTime; 
  
};

void Jobs::AssignData(int jId, double jAtime, int cNode, int packetS, int packetR)
{
  jobId = jId ;
  clientNode = cNode ;
  jobArrivalTime = jAtime ;
  packetSent = packetS ;
  packetReceive = packetR ;
}

int Jobs::GetServerNode(void)
{
  int server ;
  server = rand()%5 ;
  return server ;
}

int Jobs::GetClientNode()
{
  return this->clientNode ;
}

unsigned Jobs::GetPacketSent()
{
  return this->packetSent;
}

double Jobs::GetJobArrivalTime()
{
  return this->jobArrivalTime ;
}
int main (int argc, char *argv[])
{
  Time::SetResolution (Time::NS);
  
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
  
  double simulationTime = 10 ;
  
  std::vector <Jobs> job (5, Jobs()) ;

  job[0].AssignData(0, 1.000000001, 3, 2048u, 1048u) ;
  job[1].AssignData(1, 0.000000011, 5, 4096u, 3072u) ;
  job[2].AssignData(2, 0.000000200, 4, 1024u, 1024u) ;
  job[3].AssignData(3, 0.000000230, 2, 4192u, 2048u) ;
  job[4].AssignData(4, 0.000000300, 8, 3072u, 2048u) ;

  // Create Client and SErver Nodes
  NodeContainer clientNodes, serverNodes ;
  clientNodes.Create (10);
  serverNodes.Create(5);
  
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
  
  
  for (int i = 0; i < int(job.size());  i++)
  {
    ApplicationContainer clientApp, serverApp ;
    UdpServerHelper udpServer (9) ;
    serverApp = udpServer.Install(serverNodes.Get(job[i].GetServerNode() )) ; 
    serverApp.Start(Seconds (0)) ;
    serverApp.Stop(Time(simulationTime + 1)) ;
    
    UdpClientHelper udpClient (clientInterface.GetAddress( job[i].GetClientNode() ) , 9) ;
    udpClient.SetAttribute("MaxPackets", UintegerValue (job[i].GetPacketSent() ) ) ;
    udpClient.SetAttribute("Interval", TimeValue (Seconds (1.0))) ;
    udpClient.SetAttribute("PacketSize", UintegerValue(1472)) ;
    clientApp.Start( Time (job[i].GetJobArrivalTime() )) ;
    clientApp.Stop(Time (simulationTime + 1)) ;
  }
  
  Simulator::Stop(Seconds(simulationTime + 1)) ;
  Simulator::Run() ;
  Simulator::Destroy () ;
  

  return 0; 
}

