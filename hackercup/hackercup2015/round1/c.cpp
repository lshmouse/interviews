#include <stdio.h>

#define maxn 4096
#define MOD 1000000007

int A[maxn][maxn], B[maxn][maxn];

void init() {
    A[1][0] = A[1][1] = 1;
    for (int i = 2; i < maxn; i++) {
        for(int j = 0; j <= i; j++) A[i][j] = 0;
        for(int j = 0; j < i; j++) {
           // left win
           if (j > (i - 1 - j) && (j + 1) > (i - j -1)) A[i][j+1] = (A[i][j+1] + A[i-1][j]) % MOD;
           // right win
           if (j > (i - 1 - j) && j  > (i - j)) A[i][j] = (A[i][j] + A[i-1][j]) % MOD;
        }
    }
    B[1][0] = B[1][1] = 1;
    for (int i = 2; i < maxn; i++) {
        for(int j = 0; j <= i; j++) B[i][j] = 0;
        for(int j = 0; j < i; j++) {
           // left win
           if (j <= (i - 1 - j) && (j + 1) <= (i - j -1)) B[i][j+1] = (B[i][j+1] + B[i-1][j]) % MOD;
           // right win
           if (j <= (i - 1 - j) && j  <= (i - j)) B[i][j] = (B[i][j] + B[i-1][j]) % MOD;
        }
    }
}


int main() {
   init();
   int T, a, b;
   scanf("%d", &T);
   for (int t = 1; t <= T; t++) {
       scanf("%d-%d", &a, &b);
       printf("Case #%d: %d %d\n", t, A[a+b][a], B[b + b][b]);
   }
}
