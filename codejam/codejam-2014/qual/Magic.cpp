#include <stdio.h>

int A[4], B[4];
void input(int* A) {
   int r, t;
   scanf("%d", &r); 
   for (int i = 1; i<=4; i++) {
       for (int j = 0; j < 4; j++) {
         scanf("%d", &t);
         if (i == r) A[j] = t;
       }
   }
}

int solve(int& ret) {
   int count = 0;
   for (int i = 0; i < 4; i++)
       for (int j = 0; j < 4; j++) if (A[i] == B[j]) {
           count ++;
           ret = A[i];
       }
   return count;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t  = 1; t <= T; t ++) {
        input(A); input(B);
        int ret = 0;
        int count  = solve(ret);
        if (count > 1)printf("Case #%d: Bad magician!\n", t);
        else if (count == 1) printf("Case #%d: %d\n", t, ret);
        else printf("Case #%d: Volunteer cheated!\n", t);
    }
}
