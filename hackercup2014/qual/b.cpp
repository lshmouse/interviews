#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

#define maxn 128

struct Player{
    string name;
    int percentage;
    int height;
};
  
bool cmp(const Player& a, const Player& b){  
    if (a.percentage == b.percentage) return a.height > b.height;
    return a.percentage > b.percentage;
}  

int m, p;
Player A[32];
bool flag[16];
int pt[16];

vector<string> results;

int getOut(int n) {
    int p = -1;
    for (int i = 0 ; i < n ; i++) if (flag[i]) {
        if (p == -1) {
            p = i;
        } else if (pt[i] >= pt[p]){
            p = i;
        }
    }
    return p;
}

int getIn(int n) {
    int p = -1;
    for (int i = 0 ; i < n ; i++) if (!flag[i]) {
        if (p == -1) {
            p = i;
        } else if (pt[i] < pt[p]){
            p = i;
        }
    }
    return p;
}

void simulate(int n, int s) {
    for (int i = 0 ; i < n; i++) flag[i] = false; 
    for (int i = 0 ; i < n; i++) pt[i] = 0; 
    for (int i = 0; i < p; i ++) flag[i] = true;

    for (int i = 1; i <= m; i++) {
        for (int j = 0 ; j < n ; j++) if (flag[j]) pt[j]++;

        int out = getOut(n);
        int in = getIn(n);

        if (in == -1) continue;

        flag[out] = false;
        flag[in] = true;
    }
    
    for (int i = 0 ; i < n ; i++) if (flag[i]) {
        results.push_back(A[s + 2*i].name);
    }
}   

int main() {
    int T, n;
    cin >> T;
    for (int t = 0; t < T; t++) {
        results.clear();
        cin >> n >> m >> p;
        for (int i = 0; i < n; i++) {
           cin >> A[i].name >> A[i].percentage >> A[i].height;
        }
        sort(A, A + n, cmp);
        
        simulate((n + 1)/2, 0);
        simulate(n /2, 1);

        sort(results.begin(), results.end());

        cout << "Case #" << t +1 << ":";
        for (int i = 0; i < results.size(); i++) {
            cout << " " << results[i];
        }
        cout << endl;
    }
}
