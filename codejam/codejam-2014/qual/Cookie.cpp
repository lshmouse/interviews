#include <stdio.h>
double C, F, X;
double solve() {
    double time = 0;
    double speed = 2; 
    double ret = X / speed;
    while (true) {
       time += C / speed;
       speed += F;
       if (time + X / speed < ret) {
          ret = time + X / speed;
       } else {
          break;
       }
    }
    return ret;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t  = 1; t <= T; t ++) {
        scanf("%lf%lf%lf", &C, &F, &X);
        printf("Case #%d: %.7lf\n", t, solve());
    }
}
