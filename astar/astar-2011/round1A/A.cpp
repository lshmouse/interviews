#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
#include <map>
#include <list>

using namespace std;

int main() {
    // freopen("E:\\astar\\data.in", "r", stdin);
    // freopen("E:\\astar\\data.out", "w", stdout);
    int n, m;
    while (-1 != scanf("%d%d", &n, &m)) {
        int counter = 0;
        long long result = 0;
        for (int i = 0; i < m; i++) {
            int t;
            scanf("%d", &t);
            if (t >= 2) {
                counter++;
                result += n - 2 * counter + 1;
            }
        }
        printf("%lld\n", result);
    }
    return 0;
}
