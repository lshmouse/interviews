#include <stdio.h>
#include <set>
#include <algorithm>

using namespace std;

#define maxn 1024000
#define llong long long

int n, m;
llong A[maxn], B[maxn];
set<llong> sa, da, sb, db;

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1 ; t<= T; t++){
        scanf("%d%d", &n, &m);
        llong x1, a1, b1, c1, r1;
        scanf("%lld%lld%lld%lld%lld", &x1, &a1, &b1, &c1, &r1);
        llong x2, a2, b2, c2, r2;
        scanf("%lld%lld%lld%lld%lld", &x2, &a2, &b2, &c2, &r2);
        A[0] = x1, B[0] = x2;
        for (int i = 1 ;i < max(n, m) ;i ++) {
            if (i < n) A[i] = (a1 * A[(i-1) % n] + b1 * B[(i-1) % m] + c1) % r1;
            if (i < m) B[i] = (a2 * A[(i-1) % n] + b2 * B[(i-1) % m] + c2) % r2;
        }
        /**
        for (int i = 0; i < n; i++)printf("%lld ", A[i]);
        printf("\n");
        for (int i = 0; i < m; i++)printf("%lld ", B[i]);
        printf("\n");
        */

        llong ret = 0;
        sa.clear(), sb.clear();
        da.clear(), db.clear();
        int i = 0, j = 0;

        while (i < n || j < m) {
            if (j == m || sa.size() < sb.size()) {
                llong tmp = A[i];
                if (sa.find(tmp) == sa.end()) {
                    if (sb.find(tmp) == sb.end()) {
                        db.insert(tmp);
                    } 
                    
                    if (da.find(tmp) != da.end())
                        da.erase(da.find(tmp));
                    
                    sa.insert(tmp);
                }
                i++;
            } else {
                llong tmp = B[j];
                if (sb.find(tmp) == sb.end()) {
                    if (sa.find(tmp) == sa.end()) {
                        da.insert(tmp);
                    }
                    
                    if (db.find(tmp) != db.end())
                        db.erase(db.find(tmp));
                    
                    sb.insert(tmp);
                }
                j++;
            }
            
            if ((da.size() == 0) && (db.size() == 0)) {
               int left = 0;
               while (i < n && (sa.find(A[i]) != sa.end())) { i++; left++;}

               int right = 0;
               while (j < m && (sb.find(B[j]) != sb.end())) { j++; right++;}
               
               ret += 1LL * (left + 1) * (right + 1);
            }
        }
        printf("Case #%d: %lld\n", t, ret);
    }
}
