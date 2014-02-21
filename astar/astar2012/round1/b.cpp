#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int num = 0, sum = 0;
        scanf("%d", &num);
        int tmp;
        for (int j = 0; j < num; ++j) {
            scanf("%d", &tmp);
            sum += tmp;
        }
        sum = sum - num + 1;
        printf("%d\n", sum);
    }
    return 0;
}
