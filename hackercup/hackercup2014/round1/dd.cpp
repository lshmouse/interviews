#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;

#define maxn 150
#define llong long long

bool p[maxn];
llong B[132];

int n, m;
int A[20];
int ret = -1;

void dfs(int k, int s, int sum, llong flag) {
    if (k == n) {
        if (ret == -1) ret = sum;
        else ret = min(ret, sum);
        return;
    } 
    if (ret != -1 && sum > ret) return;
    if (A[k] == 0 || A[k] == 1) {
        dfs(k + 1, s, sum + A[k], flag);
    } else {
        for (int j = max(A[k], s); j < maxn; j++) {
            if (ret  > 0 && sum + j * (n - k) > ret) break;
            if ((flag & B[j]) == 0) {
                dfs(k + 1, j + 1, sum + j, flag|B[j]);
            }
        }
    }
}

void init() {
    for (int i = 0; i < maxn; i++){p[i] = true, B[i] = 0;} 
    p[0] = p[1] = false;
    int id  = 0;
    for (int i = 2; i < maxn; i++) if (p[i]) {
        B[i] = B[i] | (1LL<<id);
        for (int j = i + 1; j < maxn; j++) if (j % i == 0) {
            p[j] = false;
            B[j] = B[j] | (1LL<<id);
        }
        id ++;
    }
}

int main() {
    int T;
    scanf("%d", &T);
    init();
    for (int t = 0; t < T; t++) {
        scanf("%d%d", &n, &m);
        ret = -1;
        int sum = 0;
        for (int i = 0; i < n; i++){
            scanf("%d", &A[i]);
            sum += A[i];
            A[i] = (A[i] + m - 1) / m;
        }
        sort(A, A + n);
        bool zero = false;
        for (int i = 0; i < n; i++) {
            if (A[i] == 0){
                A[i] = 1;
                zero = true;
            }
        }
        dfs(0, 0, 0, 0);
        if ((ret == n) && zero) ret = ret - 1;
        printf("Case #%d: %d\n", t + 1, ret * m - sum);
    }
}
