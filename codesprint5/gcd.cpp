#include <stdio.h>

#define llong long long
#define MOD 1000000007

int n, A[512];
llong B[512], C[102400];

int gcd(int a,int b)
{
    while (b!=0) { int k=b; b=a%b; a=k; }
    return a;
}

llong getSum(int gcd) {
    llong ret = 0;
    for (int i = 0; i < n; i++) B[i] = A[i]/ gcd;    
    llong t = 1;
    for (int i = 0; i < n ;i ++) {
        t = t * B[i] % MOD;
    }
    return t;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 0; t < T; t ++) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%d", &A[i]);
        int g = A[0];
        for (int i = 1; i < n; i++) if (A[i] < g) g = A[i];
        for (int i = 1; i <= g; i ++) C[i] = getSum(i); 
        for (int i = g; i >= 2; i--) {
           C[1] = (C[1] - C[i] + MOD) % MOD;
           for (int j = 2; j * j <= i; j++) if (i % j == 0){
                C[j] = (C[j] - C[i] + MOD) % MOD; 
                if ((i/j) != j) C[i / j] = (C[i / j] - C[i] + MOD ) % MOD; 
           }
        }
        llong sum = 0;
        for (int i = 1; i <= g; i ++) sum = (sum +  i * C[i] ) % MOD; 
        printf("%lld\n", sum);
    }
}
