#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

typedef vector<string> VS;

int dp[50][50];
bool flag[50];
string pron[50];

VS sound_table[256*256];
vector<string> friends;
string answer;

int ansId=-1;

int find(string buf,char key){
    for(int i=0;i< buf.size();i++){
    	if(buf[i]==key){
			return i;		
		}
	}
	return -1;
}

int getGBKID(char a,char b){
	int t=(int(a)+128)*256+(int(b)+128);
	return t;
}

vector<string> getSmall(string sound){
	vector<string> smallSounds;
	if(sound.size()>1){
		smallSounds.push_back(sound.substr(0,1));
	}
	if(sound.size()>2){
		if(sound[1]=='h'){
			smallSounds.push_back(sound.substr(0,2));
		}
	}
	return smallSounds;
}

void addGBKSound(int gbkid,string sound){
	sound_table[gbkid].push_back(sound);
}

void init(){
	for(int k=0;k<256*256;k++){
		if(sound_table[k].size()>0){
			sort(sound_table[k].begin(),sound_table[k].end());
			int len=sound_table[k].size();
			
			for(int i = 0; i < len; i++){
				vector<string> sounds=getSmall(sound_table[k][i]);

				for(int j = 0;j < sounds.size();j ++){
					sound_table[k].push_back(sounds[j]);
				}
			}
		}
	}
}

vector<string> format(string name){
	vector<string> segs;
	for(int i=0;i<name.size();i++){
		if(name[i]<0){ //中文
			if(int(name[i])+128 > 41){
				segs.push_back(name.substr(i,2));
			}
			i++;
		}else if(isalpha(name[i])){
			string str;
			while(isalnum(name[i])&&i<name.size()){
				str+=tolower(name[i]);
				i++;
			}
			segs.push_back(str);
			i--;
		}
	}
	return segs;
}

vector<vector<string> > prev(string name,vector<string> segs){
	vector<vector<string> > sounds;
	for(int i=0;i<segs.size();i++){
		if(segs[i][0]<0){ // 汉字
			int id =getGBKID(segs[i][0],segs[i][1]);
			sounds.push_back(sound_table[id]);
			sounds[sounds.size()-1].push_back(segs[i]);
		}else{ // 英文字符
			vector<string> smalls;
			for(int j = 0;j < segs[i].size(); j++){
				smalls.push_back(segs[i].substr(0,j+1));
			}
			sounds.push_back(smalls);
		}
	}
	return sounds;
}
void show(vector<vector<string> > sounds){
	for(int i=0;i<sounds.size();i++){
		cout<< "smalls: ";
		for(int j=0;j<sounds[i].size();j++){
			cout<< sounds[i][j]<<" ";
		}
		cout<<"\n";
	}
}

string getBest(int k,string small,vector<string> segs){
	for(int i=0;i<50;i++)flag[i]=false;	
	int s=k;
	int t=small.size();
	while(t>0){
		string str = small.substr(dp[s][t],t-dp[s][t]);
	
		if(str[0]> 0){
			flag[s-1]=true;
			pron[s-1]=str;
		}
		t=dp[s][t];
		s--;
	}
	string result;
	
	for(int i=0;i<segs.size();i++){
		if(segs[i][0] < 0){	
			int id=getGBKID(segs[i][0],segs[i][1]);
			if(flag[i]==true){
				for(int j=0;j<sound_table[id].size();j++){	
					if(sound_table[id][j].compare(0,pron[i].size(),pron[i]) == 0){
						result += sound_table[id][j];
						break;
					}
				}
			}else{
				result+=sound_table[id][0];
			}
		}else{
			result+=segs[i];
		}
	}
	return result;
}

void match(string small,int fid){
	string name =friends[fid];
	
	vector<string> segs = format(name);
	vector<vector<string> > sounds =prev(name,segs);
	//show(sounds);
	
	for(int i=0;i< sounds.size()+1;i++)
		for(int j=0;j< 50 ;j++){
			dp[i][j]=-1;
		}	
	for(int i=0;i<sounds.size()+1 ;i++)dp[i][0]=0;
	
	for(int i=0;i< sounds.size();i++){
		for(int j=0;j< small.size();j++){
		
			if(dp[i][j] >= 0){
			
				for(int k=0;k<sounds[i].size();k++){
				
					int t=j+sounds[i][k].size();
					
					if(t <= small.size()){
						if(small.compare(j,sounds[i][k].size(),sounds[i][k])==0){
							dp[i+1][t]=j;
							if(t==small.size()){
								string result = getBest(i+1,small,segs);
									if(ansId < 0){
										answer=result;
										ansId=fid;
									}else if(answer.compare(result) > 0){
										answer=result;
										ansId=fid;
									}
							}
						}
					}
				}
			}
		}
	}
}

string smallformat(string name){
	string format;
	for(int i=0;i<name.size();i++){
		if(name[i]<0){ //中文
			format+=name[i];
			i++;
			format+=name[i];
		}else if(isalpha(name[i])){ // 英文
			format+=tolower(name[i]);
		}
	}
	return format;
}

void work(string small){
	ansId=-1;
	string fsmall =smallformat(small);
	
	for(int i=0;i<friends.size();i++){
		match(fsmall,i);
	}
	
	if(ansId< 0){
		cout<<small<<"\t"<<"-1"<<endl;		
	}else{
		cout<<small<<"\t"<<friends[ansId]<<endl;		
	}
}

int main(int argc,char ** argv){
	char buf[1024];
    if(argc != 4){
         printf("Usage: ./friend_finder vocab.txt friends.txt query.txt\n");
    }else{ 
		freopen(argv[1],"r",stdin);
		string str,sound;
		while(getline(buf)){
			 int p=find(buf,'\t');
			 int len=strlen(buf);
			 if(p==-1){
			 	for(int i=0;i<len;i+=2){
				   	int id=getGBKID(str[i],str[i+1]);
				   	addGBKSound(id,sound);
				}
			 }else{
				 sound=str.substr(0,p);
				 for(int i=p+1;i<len;i+=2){
				   	int id=getGBKID(str[i],str[i+1]);
				   	addGBKSound(id,sound);
				 }
			 }
		}
		init();
		freopen(argv[1],"r",stdin);
		while(getline(friends_file, str)){
			friends.push_back(str);
		}
		freopen(argv[1],"r",stdin);
		while(getline(query_file, str)){
			work(str);
		}
    }
    return 0;
}
