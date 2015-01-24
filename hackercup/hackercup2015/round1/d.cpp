#include <stdio.h>
#include <queue>
#include <algorithm>

using namespace std;

#define maxn 204800

struct State{
    int k, sum;
};

int n, A[maxn], B[maxn], in[maxn], S[maxn], E[maxn];
State dp[maxn][2];
int sum[maxn];

void init() {
    for (int i = 0 ;i < n; i++) in[i] = 0;
    for (int i = 1 ;i < n; i++) {
        in[A[i]]++;
    }
    S[0] = 0;
    for (int i = 1; i < n; i++) S[i] = S[i-1] + in[i-1];
    for (int i = 0; i < n; i++) E[i] = S[i];
    for (int i = 1; i < n; i++) B[E[A[i]]++] = i;
}

void work(int k) {
    if (S[k] == E[k]) {
      dp[k][0].k = 1;
      dp[k][0].sum = 1;
      dp[k][1].k = 2;
      dp[k][1].sum = 2;
      return;
    }
    int max = 1;
    for (int i = S[k]; i < E[k]; i++) {
       int t = B[i];
       for (int j = 0; j < 2; j ++) {
          if (dp[t][j].k > max) max = dp[t][j].k;
       }
    }
    for (int i = 1; i <= max + 1; i ++) {
        sum[i] = i;
        for (int j = S[k]; j < E[k]; j++) {
           int t = B[j];
           if (dp[t][0].k != i) {
             sum[i]+= dp[t][0].sum;
           } else {
             sum[i]+= dp[t][1].sum;
           }
        }
       // printf("%d %d\n", i, sum[i]);
    }

    int p1 = -1;
    for (int i = 1; i <= max + 1; i ++) {
        if (p1 == -1 || sum[i] < sum[p1]) {
            p1  = i;
        }
    }
    dp[k][0].k = p1;
    dp[k][0].sum = sum[p1];
    
    int p2 = -1;
    for (int i = 1; i <= max + 1; i ++) {
        if (i == p1) continue;
        if (p2 == -1 || sum[i] < sum[p2]) {
            p2  = i;
        }
    }
    dp[k][1].k = p2;
    dp[k][1].sum = sum[p2];
    // printf("state %d %d %d\n", k, dp[k][0].sum, dp[k][1].sum);

}

void solve() {
    queue<int> q;
    for (int i = 0 ; i < n; i++) if (in[i] == 0) q.push(i);
    while (!q.empty()) {
      int from = q.front();
      q.pop();
      work(from);
     
      if (from == 0) return;

      int t = A[from];
      in[t] --;
      if (in[t] ==0) q.push(t);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1 ; t <= T; t++){
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &A[i]);
            A[i] --;
        }
        init();
        solve();
        printf("Case #%d: %d\n", t, dp[0][0].sum);
    }
}
