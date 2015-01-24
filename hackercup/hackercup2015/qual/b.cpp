#include <stdio.h>

int sum(int* a, int len, int status) {
    int sum = 0;
    for (int i = 0; i < len; i++) {
        if (((1<<i) & status) > 0) {
            sum += a[i];
        }
    }
    return sum;
}

int n, A[3], B[3][32];

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 0 ; t < T; t++) {
        for (int i = 0; i < 3 ; i++) scanf("%d", &A[i]);
        scanf("%d", &n);
        for(int i = 0;  i < n ; i++) {
            scanf("%d %d %d", &B[0][i], &B[1][i], &B[2][i]);
        }
        bool done = false;
        for (int i = 0; i < (1<<n); i++) {
           bool flag = true;
           for (int j = 0 ;j < 3; j++) {
             if (A[j] != sum(B[j], n, i)) {
                flag = false;
             }
           }
           if (flag) { 
             done = true; 
             break; 
           }
        }
        printf("Case #%d: %s\n", t + 1, done ? "yes":"no");
    }
}
