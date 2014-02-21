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

#define INF 0x7fffffff

using namespace std;

int a, b, n, x, y;
int g[128][128];

int getMin(int x1, int y1, int x2, int y2) {
    int result = INF;
    for (int i = x1; i + 28 <= x2; i++) {
        for (int j = y1; j + 15 <= y2; j++) {
            int t = g[i + 28 - 1][j + 15 - 1] - g[i][j + 15 - 1]
                    - g[i + 28 - 1][j] + g[i][j];
            result = min(result, t);
        }
    }
    for (int i = x1; i + 15 <= x2; i++) {
        for (int j = y1; j + 28 <= y2; j++) {
            int t = g[i + 15 - 1][j + 28 - 1] - g[i][j + 28 - 1]
                    - g[i + 15 - 1][j] + g[i][j];
            result = min(result, t);
        }
    }
    return result;
}

void init(){
    for (int i = 1; i <= a; i++)
        g[i][0] += g[i - 1][0];
        
    for (int j = 1; j <= b; j++)
        g[0][j] += g[0][j - 1];
        
    for (int i = 1; i <= a; i++)
        for (int j = 1; j <= b; j++)
            g[i][j] += g[i - 1][j] + g[i][j - 1] - g[i - 1][j - 1];
}

int main() {
    // freopen("E:\\astar\\data.in", "r", stdin);
    // freopen("E:\\astar\\data.out", "w", stdout);
    while (-1 != scanf("%d%d", &a, &b)) {
        if (a == 0 && b == 0)
            break;
        scanf("%d", &n);
        for (int i = 0; i <= a; i++)
            for (int j = 0; j <= b; j++) {
                g[i][j] = 0;
            }
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &x, &y);
            g[x][y]++;
        }
        init();
        int result = INF;
        for(int i=0;i<=a;i++){
            int left =getMin(0,0,i,b);
            int right=getMin(i,0,a,b);
            if(left<INF&&right<INF){
                result=min(result, left+right);
            }
        }
        for(int i=0;i<=b;i++){
            int left =getMin(0, 0, a, i);
            int right=getMin(0, i, a, b);
            if(left<INF&&right<INF){
                result=min(result, left+right);
            }
        }
        printf("%d\n", result);
    }
    return 0;
}
