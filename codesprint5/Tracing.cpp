#include <stdio.h>

#define llong long long
#define MOD 1000000007LL

llong multiply(llong n) {
    llong tmp = 1;
    for (int i = 2; i <= n ; i ++) tmp = tmp * i % MOD;
    return tmp;
}

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

int main() {
    int t, m, n;
    scanf("%d", &t);
    for (int i = 0 ; i < t ;i ++) {
        scanf("%d%d", &n, &m);
        llong a = multiply(n + m - 2);
        llong b = multiply(m - 1) * multiply(n-1) % MOD;
        llong c = gcd(a, b);
        a = a /c , b = b /c;
        llong x, y;
        extended_gcd(b, MOD, x, y);
        x = (a * x % MOD + MOD ) % MOD;
        printf("%lld\n", x);
    }
}
