#include <stdio.h>
#include <algorithm>
using namespace std;

#define maxn 128

int n;
char g[maxn][maxn];

bool check() {
    int lx = n, rx = -1;
    int ly = n, ry = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n ;j ++) if (g[i][j] == '#') {
            lx = min(i, lx), rx = max(i, rx);
            ly = min(j, ly), ry = max(j, ry);
        }
    }
    // impossible rx < lx
    if ((rx - lx) != (ry - ly)) return false;

    for (int i = lx; i <= rx; i++)
        for (int j = ly; j <= ry; j++) if (g[i][j] != '#' ) {
            return false;
        }
    return true;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%s", g[i]);
        }
        bool flag = check();
        if (flag) printf("Case #%d: YES\n", t + 1);
        else printf("Case #%d: NO\n", t + 1);
    }
}
