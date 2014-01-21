#include <stdio.h>
#include <vector>

using namespace std;

#define llong long long

vector<llong> alls;

int main() {
    alls.push_back(9);    
    int start = 0;
    for (int i = 2; i <16; i++) {
        int cur = alls.size();
        for (int j = start; j < cur; j++) {
            llong t = alls[j];
            alls.push_back(t * 10);
            alls.push_back(t * 10 + 9);
        }
        start = cur;
    }
    
    int t, v;
    scanf("%d", &t);
    for (int i = 1; i <= t; i ++) {
        scanf("%d", &v);
        for (int j = 0; j < alls.size(); j++) {
            if (alls[j] % v ==0) { printf("%lld\n",alls[j]); break; }
        }
    }
}
