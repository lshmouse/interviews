#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;

#define maxn 512

int n, m;
char A[maxn][maxn];
int dp[maxn][maxn];
int F[maxn][maxn], B[maxn][maxn];

int solve() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++){
            if (i ==0 && j ==0) F[0][0] = 1;
            else F[i][j] = 0;

            if (A[i][j] == '.'){
                if (i > 0) F[i][j] = max(F[i][j], 1 + F[i - 1][j]);
                if (j > 0) F[i][j] = max(F[i][j], 1 + F[i][j - 1]);
            }
            // printf("Forward %d %d %d\n", i, j, F[i][j]);
        }
    for (int i = n - 1; i >= 0; i--)
        for (int j = m - 1; j >= 0; j--) {
            B[i][j] = 0;         
            if (A[i][j] == '.') {
                B[i][j] = 1;
                if (i + 1 < n) B[i][j] = max(B[i][j], 1 + B[i + 1][j]);
                if (j + 1 < m) B[i][j] = max(B[i][j], 1 + B[i][j+1]);
            }
            // printf("Backward %d %d %d\n", i, j, B[i][j]);
        } 

    int ret = 1;

    // leftward
    for (int i = 0; i < n ; i++)
        for(int j = 0; j < m; j++) {
            if (A[i][j] == '#') dp[i][j] = 0;
            else {
                dp[i][j] = 1;
                if (j > 0) dp[i][j] = max(dp[i][j], dp[i][j-1] + 1);
                if (i + 1 < n) dp[i][j] = max(dp[i][j], B[i+1][j] + 1);

                if (i > 0 && F[i-1][j] > 0) {
                    ret = max(ret, dp[i][j] + F[i-1][j]);
                }
            }
        }

    // upward
    for (int i = 0; i < n ; i++)
        for(int j = 0; j < m; j++) {
            if (A[i][j] == '#') dp[i][j] = 0;
            else {
                dp[i][j] = 1;
                if (i > 0) dp[i][j] = max(dp[i][j], dp[i-1][j] + 1);
                if (j + 1 < m) dp[i][j] = max(dp[i][j], B[i][j + 1] + 1);

                if (j > 0 && F[i][j-1] > 0) {
                    ret = max(ret, dp[i][j] + F[i][j - 1]);
                }
            }
        }
    return ret;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) scanf("%s", A[i]);
        printf("Case #%d: %d\n", t + 1, solve());
    }
}
