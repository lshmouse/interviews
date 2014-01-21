#include <stdio.h>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

int n, G[512][512], pre[512];

double g[512][512], dist[512];
int p, q;
vector<int> a, b;

bool bellman() {
    int flag=0;
    for(int i= 0 ;i < n;i++) {
        dist[i] = 0.0;
        pre[i] = -1;
    }
    for(int i= 0 ; i < n; i++)
    { 
        for(int j=0;j< a.size() ;j++) 
        { 
            int  u = a[j], v= b[j];
            if(dist[v]>dist[u]+ g[u][v]) 
            { 
                dist[v]=dist[u] + g[u][v]; 
                pre[v] = u;
                flag=1; 
            } 
        } 
        if(flag==0)break; 
    }
    p = 0, q = 0; 
    bool f = false;
    for(int i=0;i< a.size(); i++)  {
       int  u = a[i], v= b[i];
       if(dist[v]> dist[u]+ g[u][v]) { 
          f = true;
          /**
          p += G[u][v]; q++;
          int end = v;

          while(u != end && u != -1) {
            v = u;
            u = pre[u];
            p += G[u][v]; q++;
          }
          */
          break;
       }
    }
    
    return f; 
}

int main() {
    a.clear(), b.clear();
    scanf("%d", &n);
    double left = 0, right = 0;
    for (int i = 0; i < n ; i++)
        for (int j = 0; j< n ;j ++) {
            scanf("%d", &G[i][j]); 
            if (G[i][j] > 0) {
                a.push_back(i);
                b.push_back(j);
                right = max(right, 1.0 * G[i][j]);
            }
        }
    int P, Q;
    while (fabs(left - right) > 1e-3) {
        double mid = (left + right) / 2;
        for (int i = 0; i < n ; i++)
            for (int j = 0; j< n ;j ++) {
                if (G[i][j] > 0) g[i][j] = mid - G[i][j];
                else g[i][j] = 0.0;
            }
        if (bellman()) {
            P = p , Q = q;
            left = mid;    
        } else {
            right = mid;
        }
    }
    printf("%d/%d\n", P, Q);
}
