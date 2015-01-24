#include <stdio.h>

#define maxn 10000
#define maxm 10240000

bool flag[maxn];
int prime[maxn], N;
int res[maxm];

void init() {
    N = 0;
    for (int i = 0; i < maxn; i ++) flag[i] = true;
    flag[0] = flag[1] = false;
    for (int i = 0; i < maxn; i++) {
        if (flag[i] == false) continue;
        prime[N++] = i;
        for (int j = i ; i * j < maxn; j++) flag[i*j] = false;
    }
    res[0] = res[1] = 0;
    for (int i = 2; i < maxm; i++) {
        int tmp = i;
        res[i] = 0;
        for (int j = 0; j < N && prime[j] <= tmp; j++) {
            if (tmp % prime[j] == 0) {
                res[i] ++;
                while (tmp % prime[j] == 0) tmp = tmp / prime[j];
            }
        }
        if (tmp != 1) res[i]++;
    }
}
int a, b, c;

int main() {
    init();
    int T;
    scanf("%d", &T);
    for (int t = 0; t < T ;t ++){
        scanf("%d%d%d", &a, &b, &c);
        int count = 0;
        for (int i = a; i <=b ;i ++) if (res[i] == c) count++;
        printf("Case #%d: %d\n", t + 1, count);
    }
}
