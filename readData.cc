#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;



std::vector <int> jobId;
std::vector <double> jobArrivalT;
std::vector <int> client;
std::vector <int> dataBytes;


void ReadData()
{
FILE *fp ;
char character ;
double word ;
double data ;
int i ;
  
fp = fopen("data.txt", "r" ) ;
  
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
    
for(i = 0; i <=5; ++i)
{
  //printf("hjklghjkl"); 
  cout << i ;
  cout << jobArrivalT.size() << endl;
  cout << jobArrivalT[i]  ;
}
}
