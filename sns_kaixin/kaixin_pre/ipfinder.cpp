#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

#define TABLE_SIZE 256
#define TABLE_SIZE_BYTES 24

typedef unsigned int uint;
typedef map<string,uint> mapSU;

struct ip_seg{
       uint from_ip;
       char *name;
};

bool ipCmp(const ip_seg &a,const ip_seg &b){
	return a.from_ip < b.from_ip;
}

int ip_seg_sz;
vector<vector<ip_seg> > ip_segs_table(TABLE_SIZE);
ip_seg* ip_segs;

/**
   binary search the key value array
*/
int bsearch(uint ip,int from,int to){
    int pos=0;
    int mid;
    while(from<=to){
		mid=(from + to) >>1;
		if(ip_segs[mid].from_ip <= ip){
			pos = mid;
			from= mid + 1;
		}else{
			to= mid - 1;
		}
	}
	return pos;
}
int search(uint ip){
	return bsearch(ip, 0, ip_seg_sz - 1);   
}
uint ipstring_to_uint(char *ips,int from, int to){
	uint ip=0;
	uint t=0;
	for (int i=from ; i< to;i++){
    	if(ips[i]=='.'){
		    ip=(ip<<8)|t;
		    t=0;        
		}else if( isdigit(ips[i])){
	    	t=t*10+(int)(ips[i]-'0');
		}
     }
     ip=(ip<<8)|t;
     return ip;
}

void add_ip_seg(uint from_ip,char* string){
	ip_seg seg;
	seg.from_ip= from_ip;
	seg.name=(char*)malloc(sizeof(char)*(strlen(string)+1));
	strcpy(seg.name,string);
	ip_segs_table[seg.from_ip>>TABLE_SIZE_BYTES].push_back(seg);
}

int find(char* buf,int from, char key){
    int len=strlen(buf);
    for(int i=from;i<len;i++){
    	if(buf[i]==key){
			return i;		
		}
	}
	return -1;
}

void prev(){
	ip_seg_sz=0;
	for(int i=0;i<TABLE_SIZE;i++){
		sort(ip_segs_table[i].begin(),ip_segs_table[i].end(),ipCmp);
		ip_seg_sz +=ip_segs_table[i].size();
	}
	ip_segs = (ip_seg *)malloc(sizeof(ip_seg)*ip_seg_sz);
	ip_seg_sz=0;
	for(int i=0;i<TABLE_SIZE;i++){
		for(int j=0;j<ip_segs_table[i].size();j++){
			ip_segs[ip_seg_sz++] = ip_segs_table[i][j];
			/**if(ip_seg_sz==0){
				ip_segs[ip_seg_sz++] = ip_segs_table[i][j];
			}else if(ip_segs_table[i][j].name_id != ip_segs[ip_seg_sz-1].name_id){
				ip_segs[ip_seg_sz++] = ip_segs_table[i][j];
			}*/
		}
	}
}
int main(int argc,char ** argv){
	char * buf =(char *) malloc(sizeof(char)*4096);
    if(argc != 3){
         printf("Usage: ./ipfinder ipbase.txt ipcheck.txt\n");
    }else{ 
		freopen(argv[1],"r",stdin);
		int pa,pb;
		while(gets(buf)){
			pa=find(buf, 0, '\t');
			pb=find(buf, pa+1, '\t');		
			add_ip_seg(ipstring_to_uint(buf,0,pa),buf+pb+1);
		}
		prev();				
		freopen(argv[2],"r",stdin);
		while(gets(buf)){
			uint ip=ipstring_to_uint(buf,0,strlen(buf));	     			
			int pos=search(ip);
			printf("%s\t%s\n",buf,ip_segs[pos].name);			
		}
		free(buf);
		free(ip_segs);
    }
    return 0;
}
