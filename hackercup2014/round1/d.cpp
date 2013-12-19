#include <stdio.h>
#define maxn 70
int A[maxn];
bool flag[64];

int main() {
    int t = 1;
    for (int i =2; i < maxn; i++) {
        A[i] = t; 
        for (int j = 2 ; j < i; j++) if (A[j] > 0 && i % j == 0) {
            A[i] = 0;
            break;
        }
        if (A[i] != 0){
            t++;
            printf("%d ", i);
        }
    }
    printf("\n%d\n", t);

    int count = 0;
    for (int i = 0; i < 64; i++) flag[i] = false;
    int sum = 0; 
    for (int i = 50; i < 132; i++) {
        bool ok = true;
        for (int j = 2; j<i && j < maxn; j++) if (A[j] > 0 && i % j == 0) {
           if (flag[A[j] -1]) {
               ok = false;
               break;
           }
        }
        
        if (ok) {
            count++;
            printf("%d ", i);
            sum += i;
            if (count == 20) printf("\n%d sum: %d\n", i, sum); 
            for (int j = 2; j<i && j < maxn; j++) if (A[j] > 0&& i % j == 0) {
                flag[A[j] -1] = true;
            }
        }
    }
}
