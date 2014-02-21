#include <stdio.h>

#define llong long long
llong n, m;
llong a, b, k;

int main() {
  scanf("%lld%lld", &n, &m);
  llong sum = 0;
  for (int i = 0; i < m; i++) {
    scanf("%lld%lld%lld", &a, &b, &k);
    sum += (b -a + 1) * k;
  }
  printf("%lld\n", sum / n);
}
