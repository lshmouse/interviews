#include <stdio.h>
#include <algorithm>

using namespace std;

int n;
double A[1024], B[1024];
int war(double* a, double* b) {
    int ret = 0;
    int s = 0;
    for(int i = 0; i < n ; i++) {
        while (s < n && b[s] < a[i]) s++;
        if (s >= n) break;
        ret ++; 
        s++;
    }
    return n - ret;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t  = 1; t <= T; t ++) {
        scanf("%d", &n);
        for (int i = 0; i < n ; i++) scanf("%lf", &A[i]);
        for (int i = 0; i < n ; i++) scanf("%lf", &B[i]);
        sort(A, A + n);
        sort(B, B + n);
        int y = n - war(B, A);
        int z = war(A, B);
        printf("Case #%d: %d %d\n", t, y, z);
    }
}
