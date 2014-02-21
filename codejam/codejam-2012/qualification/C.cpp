#include <stdio.h>

#include <string.h>

bool flag[2048000];

int getLens(int num) {
    int ret = 0;
    while(num > 0){
        num = num/10;
        ret ++;
    }
    return ret;
}

int main() {
    int T, A, B;
    scanf("%d", &T);
    for (int cases = 0; cases < T; cases++) {
        int ret = 0;
        scanf("%d%d", &A, &B);
        int number = getLens(A);

        int base = 1;
        for (int i = 0; i < number - 1; i++){
            base = base * 10;
        }

        for (int i = A; i <=B; i++) {
            flag[i] = false;
        }
        
        for (int i = A; i <= B; i++){
            if (flag[i])continue;
            flag[i] = true;
            int count = 1;
            int tmp = i;
            for(int j = 0; j < number;j++) {
                tmp = tmp/10 + (tmp%10) * base;
                if (tmp >=A && tmp <=B) {
                    if (flag[tmp]) break;
                    flag[tmp] = true;
                    count++;
                }
            }

            ret += count * (count-1) / 2;
        }
        printf("Case #%d: %d\n", cases + 1, ret);
    }
    return 0;
}
