#include <stdio.h>
#include <math.h>
#include <algorithm>

int gcd(int a, int b) {
  if (b == 0) return a;
  if (a == 0) return b;
  return gcd(b, a%b);
}

int main() {
  int t, x1, y1, x2, y2;
  scanf("%d", &t);
  while (t-- > 0) {
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    
    int x = abs(x1 - x2);
    int y = abs(y1 - y2);
    printf("%d\n", gcd(x, y) - 1);
  }
}
