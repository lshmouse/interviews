#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <map>


// define the maximum size of the result cache

#define IP_SIZE 200000
#define CACHE_SIZE 10000
#define CACHE_NOT_FOUND -1


#define uint unsigned int
#define ull unsigned long long


//#typedef 

ull ip_data[IP_SIZE];


struct ip_seg{
       uint from,to;     
       char* name;
};



/**
   ull= ip*2^32 + location
**/
ull ip_add_location(ull ip, ull location){
    ull result=ip;
    result<<=32;
    result|=location;
    return result;
}

//map<ull,ull> cache_ip_map;

/**
   binary search the key value array
*/
int bsearch(ull ip_ull,int from,int to){
    int pos=0;
    int mid;
    while(from<=to){
		mid=(from + to) >>1;
		if(ip_data[mid]<=ip_ull){
			pos = mid;
			from= mid + 1;
		}else{
			to= mid - 1;
		}
	}
	return pos;
}



int search(uint ip){
	ull ip_ull= ip_add_location(ip,0ull);
	return bsearch(ip_ull,0,IP_SIZE-1);   
}


/**
   cache
**/

int get_cache(ull ip){
//    if(map.find(ip)!=-1){
//    	return
//    }
    return CACHE_NOT_FOUND;
}

void add_cache(ull ip,ull location){
     // map size
}
/**
   ip 192.168.0.1-> unit
*/
uint ipstring_to_uint(char* str){
     uint ip=0;
     return ip;
}

/**
 binary search + cache
**/
int main(int argc,char ** argv){
    if(argc != 3){
         printf("Usage: ./ipfinder ipbase.txt ipcheck.txt\n");
    }else{
          FILE* fp;
          if((fp = fopen(argv[1],"r"))==NULL){
             printf("Cannot open file %s\n",argv[1]);
          }else{
			 getLine();
             fclose(fp);
          }
       
          if((fp = fopen(argv[2],"r"))==NULL){
             printf("Cannot open file %s\n",argv[2]);
          }else{
             ull ip=1ull;
             int location;
             if ((location=get_cache(ip))!= CACHE_NOT_FOUND){
                printf("get it in cache!\n");
             }else{
                location = search(ip);
                add_cache(ip, location);
             }
             fclose(fp);
          }
    }
    system("pause");
    return 0;
}
