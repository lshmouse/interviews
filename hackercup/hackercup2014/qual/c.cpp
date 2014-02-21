#include <stdio.h>

int k;
double Ps, Pr;
double Pu, Pw, Pd, Pl;

// total -> win -> P
double P[200][100][1001];

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T ; t++) {
        double Pi;
        scanf("%d%lf%lf%lf%lf%lf%lf%lf", &k, &Ps, &Pr, &Pi, &Pu, &Pw, &Pd, &Pl);

        for (int i = 0; i < 2 * k; i++)
            for (int j = 0; j <=i ; j++) 
                for (int p = 0 ; p < 1001; p++)
                    P[i][j][p] = 0.0;

        P[0][0][int(1000 * Pi)] = 1.0;

        double ret = 0;
        
        for (int i = 0; i < 2 * k; i++) {
            for (int j = 0; j <=i && j <= k; j++) if (i - j < k){
                for (int p = 0 ; p < 1001; p++) if (P[i][j][p] > 0.0 ) {
                   
                    if (j == k) {
                      ret +=P[i][j][p];
                      continue;
                   }
                   
                   double win = Ps * p/1000 + Pr * (1000 - p)/1000;
                   
                   int pp = p + (int)(1000 * Pu);
                   if (pp > 1000) pp = 1000;

                   P[i+1][j+1][pp] += P[i][j][p] * win * Pw;
                   
                   P[i+1][j+1][p] += P[i][j][p] * win * (1 - Pw);
                   
                   pp = p - (int)(1000 * Pd);
                   if (pp < 0 ) pp = 0;

                   P[i+1][j][pp] += P[i][j][p] * (1-win) * Pl;

                   P[i+1][j][p] += P[i][j][p] * (1-win) * (1 - Pl);
                }
            }
        }
        printf("Case #%d: %.6lf\n", t, ret);
    }
}
