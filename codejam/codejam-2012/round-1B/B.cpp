#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>

using namespace std;

static const int maxn = 128;

int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

int h, m, n;
int ceiling[maxn][maxn], F[maxn][maxn];

bool flag[maxn][maxn];
int time[maxn][maxn];

class Status {
    int i, j, water;
};
double ret;


bool valid(int x, int y) {
    if (x < 0 || x >= m) return false;
    if (y < 0 || y >= n) return false;
    return true;
}

bool check(int i, int j, int x, int y, int water) {
    if (F[x][y] + 50 > ceiling[x][y]) return false;
    if (F[i][j] + 50 > ceiling[x][y]) return false;
    if (water + 50 > ceiling[x][y]) return false;
}

int Calc(int i, int j, int x, int y, int water) {
   if (water - F[i][j] >= 20) return 10;
   else return 100;
}

void go(int i, int j, int water) {
    for (int k = 0; k < 4; k++) {
        int x = i + dx[k];
        int y = j + dy[k];
        if (valid(x, y)) {
            if (check(i, j, x, y, water)) {
               if (flag[i][j]) {
                    time[i][j] = min(time[i][j], water + Calc(i, j, x, y, water)); 
               } else {
                   time[i][j] = water + Calc(i, j, x, y, water);
               }
            }
        }
    }
}

void dfs(int i, int j, int water) {
    if (flag[i][j]== true) return;
    flag[i][j] = true;
    time[i][j] = 0;
    for (int k = 0; k < 4; k++) {
        int x = i + dx[k];
        int y = j + dy[k];
        if (valid(x, y)) {
            if (check(i, j, x, y, water)) {
                dfs(x, y, water); 
            }
        }
    }
}

double solve() {
    for(int i = 0;i < m; i++){
        for(int j = 0; j < n; j++) {
            flag[i][j] = false;
        }
    }
    dfs(0, 0, h);
    if (flag[m-1][n-1]) {
        return 0.0;
    }
    for(int k = 0; k <= h + m + n; k++) {
        for (int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if (flag[i][j] && time[i][j] <= i) {
                      go(i, j, h - k);
                }
            }
        }
        if (flag[m-1][n-1]) {
           return time[m-1][n-1] / 10.0;
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for(int cases = 1; cases <= T; cases++) {
        scanf("%d%d%d",&h, &m, &n);
        for(int i = 0;i < m; i++){
            for(int j = 0; j < n; j++) {
                scanf("%d", &ceiling[i][j]);
            }
        }
        
        for(int i = 0;i < m; i++){
            for(int j = 0; j < n; j++) {
                scanf("%d", &F[i][j]);
            }
        }

        printf("Case #%d: %.7lf\n", cases, solve());
    }
    return 0;
}
