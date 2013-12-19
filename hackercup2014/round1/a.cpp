#include <stdio.h>
#include <string.h>

#include <algorithm>
using namespace std;

#define llong long long

char A[64], B[64];
int n ;

void solve(llong m) {
    llong t = 1;
    while (m > 0) {
        if (m/t <= n) break;
        t = t * n;
        m -= t;
    }
    m = m - 1;
    for (int i = 0; t > 0; i ++) {
        B[i] = A[(int)(m / t)];
        B[i + 1 ] = '\0';
        m = m % t;
        t = t / n;
    }
}

int main() {
    int T;
    llong m;
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        scanf("%s %lld", A, &m);
        n = strlen(A);
        if (n == 1) {
            printf("Case #%d: ", t+1);
            for (int i = 0; i < m ; i++) printf("%c", A[0]);
            printf("\n");
        } else {
            solve(m);
            printf("Case #%d: %s\n", t+1, B);
        }
    }
}
