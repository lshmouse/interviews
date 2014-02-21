#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <utility>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>
using namespace std;

int N;
int A, B;
int P[10000];

int gcd(int A, int B)
{
         while (A != 0)
         {
                   int C = B % A;
                   B = A;
                   A = C;
         }
         return B;
}

int main()
{
         while (scanf("%d", &N) > 0 && N > 0)
         {
                   scanf("%d%d", &A, &B);
                   for (int I = 0; I < N; I++) scanf("%d", &P[I]);
                   A = gcd(B - A, N);
                   bool Ans = true;
                   for (int I = A; I < N; I++) if (P[I] % A != P[I - A] % A) Ans = false;
                   for (int I = 0; I < A; I++) if (P[I + 1] % A != (P[I] + 1) % A) Ans = false;
                   if (Ans) cout << "Yes" << endl;
                   else cout << "No" << endl;
         }
        return 0;
}
