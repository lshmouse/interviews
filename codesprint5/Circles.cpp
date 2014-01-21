#include <stdio.h>

#define maxn 1024000
#define MOD 1000000007
#define llong long long

llong A[maxn], B[maxn], C[maxn];

int n, k;

llong gcd(llong a,llong b)
{
    while (b!=0) { llong k=b; b=a%b; a=k; }
    return a;
}

llong extended_gcd(llong a,llong b,llong &x,llong &y)
{
    llong ans,t;
    if (b==0) { x=1; y=0; return a; }
    else { ans=extended_gcd(b,a%b,x,y); t=x; x=y; y=t-(a/b)*y;}
    return ans;
}

llong solve(llong a, llong b) {
    llong c = gcd(a, b);
    a = a /c , b = b /c;
    llong x, y;
    extended_gcd(b, MOD, x, y);
    x = (a * x % MOD + MOD ) % MOD;
    return x;
}

llong calc(llong n, llong m) {
    llong a = A[n];
    llong b = A[m] * A[n - m]% MOD;
    return solve(a, b);
}

int main() {
   A[0] = 1;
   for (int i = 1; i < maxn ; i ++) A[i] = A[i-1] * i % MOD;
   B[0] = 1, B[1] = 0, B[2] =1;
   for (int i = 3; i < maxn; i++) B[i] = (i -1 ) * (B[i-1] + B[i-2]) % MOD;

   int T;
   scanf("%d", &T);
   for (int t = 0; t < T; t ++) {
      scanf("%d%d", &n, &k);
      if (k == 1) {printf("0\n"); continue; }
     
      llong tmp = 1;
      for (int i = 1; i * k <= n; i++) {
          tmp = tmp * calc(i*k, k) * A[k-1] % MOD;
          C[i] = B[n - i * k] * calc(n, i * k) * tmp % MOD;
          C[i] = solve(C[i], A[i]);
      } 
   
      llong sum = 0;
      for (int i = 1; i <= n / k; i ++) {
        if (i % 2 ==1) sum = (sum + C[i] + MOD) % MOD;
        else sum = (sum - C[i] + MOD) % MOD;
      }
      printf("%lld\n", sum);
   }
}

