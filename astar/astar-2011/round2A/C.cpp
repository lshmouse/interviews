#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
#include <map>
#include <list>

using namespace std;

int n;

int index[10];
char chars[11];
char A[10][5];
int use;
vector<int> uses;
int ans=0;

void dfs(int k){
	if(k==n){
		vector<int> state;
		for(int i=0;i<n;i++){
			if(index[i]>-1){
			//	printf("%d", i);
			}else{
				//printf(" ");
			}
		}
		//printf("\n");
		uses.push_back(use);
		return;
	}
	index[k] = -1;
	chars[k+1]= -1;
	dfs(k+1);
	for(int i=0;i<n;i++){
		if((use&(1<<i))==0){
			for(int j=0;j<4;j++){
				if(chars[k]==-1){
					index[k]=i;
					chars[k+1]=A[i][(j+2)/4];
					use+=(1<<i);
					dfs(k+1);
					use-=(1<<i);
				}else{
					if(A[i][j]==chars[k]){
						chars[k+1]=A[i][(j+2)/4];
					    index[k]=i;
						use+=(1<<i);
						dfs(k+1);
						use-=(1<<i);
					}
				}
			}
		}
	}
}
int main(){
    //freopen("E:\\astar\\data.in","r",stdin);
    //freopen("E:\\astar\\data.out","w",stdout);
	while(scanf("%d",&n)!=-1){
		if(n==0)break;
		for(int i=0;i<n;i++){
			scanf("%s",&A[i]);
		}
		ans=n;
		chars[0]=-1;use=0;
		dfs(0);
		printf("%d\n", ans);
	}
    return 0;
}
