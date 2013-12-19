#include <stdio.h>
#include <set>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define maxn 10240

int n, m;
char out[maxn];
bool flag[128];
int A[6];
int c1, c2;

int get() {
    int v = rand() % n;
    if (flag[v] == false) return get();
    return v + 1;
}

bool win() {
    for (int i = 0; i < 6; i+=2) {
        if (A[i] + A[i+1] > c1 + c2) return false;
        if ((A[i] + A[i+1]) == (c1 + c2) && max(A[i], A[i+1]) > max(c1, c2)) return false;
    }
    return true;
}

bool solve() {
    int count = 0;
    int total = 100 * n;
    for (int k = 0; k < total; k++ ) {
        for (int i = 0; i < 6; i++) {
            A[i] = get();
            flag[A[i] -1] = false;
        }
        if (win()) {
            count++;
        }
        for (int i = 0; i < 6; i++) flag[A[i]-1]= true;
    }
    if (count * 4 >= total) return true;
    return false;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1 ; t<= T; t++){
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) flag[j] = true;
            srand(time(NULL));
            scanf("%d%d", &c1, &c2);
            flag[c1-1]= false, flag[c2-1]= false;
            out[i] = solve()? 'B':'F';
        }
        out[m] = '\0';
        printf("Case #%d: %s\n", t, out);
    }
}
