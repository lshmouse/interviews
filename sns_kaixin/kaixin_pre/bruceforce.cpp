#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>

using namespace std;

typedef unsigned int uint;

struct ip_seg
{
    uint from_ip,to_ip;
    string name;
};

vector<ip_seg> ip_segs;


/**
   ip 192.168.0.1-> unit
*/

uint ipstring_to_uint(string ips)
{
    uint ip=0;
    uint t=0;
    for (int i=0; i<ips.size();i++)
    {
        if (ips[i]=='.')
        {
            ip=(ip<<8)|t;
            t=0;
        }
        else if ( isdigit(ips[i]))
        {
            t=t*10+(int)(ips[i]-'0');
        }
    }
    ip=(ip<<8)|t;
    return ip;
}

void find(string ips)
{
    uint ip=ipstring_to_uint(ips);
    for(int i=0;i< ip_segs.size();i++){
        if(ip_segs[i].from_ip <= ip && ip_segs[i].to_ip >= ip){
            cout<< ips <<"\t"<< ip_segs[i].name <<"\n";
            break;
        }
    }
}

void add_ip_seg(string from_ips,string to_ips,string name)
{
    ip_seg seg;
    seg.from_ip=ipstring_to_uint(from_ips);
    seg.to_ip = ipstring_to_uint(to_ips);
    seg.name=name;
    ip_segs.push_back(seg);
}

int main(int argc,char **argv)
{
    if (argc != 3)
    {
        printf("Usage: ./ipfinder ipbase.txt ipcheck.txt\n");
    }
    else
    {
        ifstream ipbase(argv[1]);
        if (!ipbase)
        {
            cout<<"Cannot open file "<<argv[1]<<"\n";
        }
        else
        {
            string line;
            int pa,pb;
            while (getline(ipbase,line))
            {
                pa=line.find('\t');
                pb=line.rfind('\t');
                add_ip_seg(line.substr(0,pa),line.substr(pa+1,pb-pa-1),line.substr(pb+1));
            }
            ipbase.close();
        }
        ifstream ipcheck(argv[2]);
        if (!ipcheck)
        {
            cout<<"Cannot open file "<<argv[2]<<"\n";
        }
        else
        {
            string ips;
            while (getline(ipcheck,ips))
            {
                find(ips);
            }
            ipcheck.close();
        }
    }
    return 0;
}
