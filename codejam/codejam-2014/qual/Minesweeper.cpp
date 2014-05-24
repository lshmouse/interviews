#include <stdio.h>

int R, C, M;

char A[64][64];
int B[64][64];

bool F[64][64];

int delta[] = {-1, 0, 1};
int calc(int x, int y) {
    int ret = 0;
    for(int i = 0; i < 3; i++)
        for (int j = 0; j < 3 ;j ++){
            int x1 = x + delta[i];
            int y1 = y + delta[j];
            if (x1 < 0 || x1 >= R) continue;
            if (y1 < 0 || y1 >= C) continue;
            if (x == x1 && y == y1) continue;
            if (A[x1][y1] == '*') ret++;
        }
    return ret;
}

int dfs(int x, int y) {
    if (F[x][y]) return 0;
    F[x][y] = true;
    int ret = 0;
    
    if (A[x][y] == '.') ret +=1;

    if (B[x][y] != 0) return ret;

    for(int i = 0; i < 3; i++)
        for (int j = 0; j < 3 ;j ++){
            int x1 = x + delta[i];
            int y1 = y + delta[j];
            if (x1 < 0 || x1 >= R) continue;
            if (y1 < 0 || y1 >= C) continue;
            if (x == x1 && y == y1) continue;
            ret += dfs(x1, y1);
        }
    return ret;
}

bool check() {
   if (M == 1) return true;
   for (int i = 0; i < R; i++) {
       for(int j = 0; j < C; j++) {
           F[i][j] = false;
           B[i][j] = calc(i, j);             
           // printf("%d ", B[i][j]);
       }
      //  printf("\n");
   }
   if (dfs(0, 0) == M) return true;
   return false;
}

bool solve() {
    M = R * C - M;
    for(int i = 0; i < R; i++) A[i][C] = '\0';
   
    for (int x = 1 ; x <= C && x <= M; x ++) {
        if (R * x < M) continue;

        for(int i = 0; i< R; i++)
            for (int j = 0; j < C ; j++) 
                A[i][j] = '*';

        for(int i = 0; i< R; i++)
            for (int j = 0; j < x ; j++){
                if ( i * x + j < M) {
                    A[i][j] = '.';
                }
            }
        if (check()) {
           A[0][0] = 'c';
           return true;
        }
    }
    return false;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t  = 1; t <= T; t ++) {
        scanf("%d%d%d", &R, &C, &M);
        //printf("Case #%d:\n", t);
        bool flag = solve();
    //    printf("%d %d %d\n", R, C, M);
        if ( M == 2) continue;
        if ( M == 3) continue;
        if (flag) {
            for(int i = 0; i < R; i++) {
               // printf("%s\n", A[i]);
            }
        } else {
            printf("Case #%d:\n", t);
            printf("%d %d %d\n", R, C, M);
            printf("Impossible\n");
        }
     //   printf("\n");
    }
}
