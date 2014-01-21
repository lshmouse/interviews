#include <stdio.h>
#include <algorithm>
#include <set>
using namespace std;

#define llong long long
#define maxn 10000000000LL

int main() {
    set<llong> fibs;
    llong a = 0, b = 1;
    llong c =  a + b;
    fibs.insert(a);
    fibs.insert(b);

    while (c < maxn){
        fibs.insert(c);
        a = b;
        b = c;
        c =  a + b;
    }

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a);
        if (fibs.find(a) != fibs.end()) {
           printf("IsFibo\n"); 
        } else {
           printf("IsNotFibo\n"); 
        }
    }
}
