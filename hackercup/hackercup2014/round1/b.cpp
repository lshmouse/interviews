#include <stdio.h>
#include <string.h>

#include <algorithm>
using namespace std;

#define llong long long

int n, c, k;

int solve() {
    int ret = n + k;
    for (int a = 1; a <= min(n, k); a ++) {
        int b = n - a;
        for (llong i = 1; i * a <= k; i++) {
            int j = b == 0 ? 0 : (k - i * a) / b;
            if (i >= j) {
               // printf("%d %lld %d %d\n", a, i, b, j); 
               if (n * j >= c) ret = min(c, ret);
               if (a * i + b * j >= c) ret = min(ret, c + b);
            }
        }
    }
    return ret;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        scanf("%d%d%d", &n, &k ,&c);
        printf("Case #%d: %d\n", t + 1, solve());
    }
}
