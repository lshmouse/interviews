#include <stdio.h>

int formatInt(int key, char* array) {
    int len = 0;
    while (key > 0) {
        array[len++] = key % 10;
        key /= 10;
    }
    return len;
}

int parseInt(char* array, int len) {
    if (array[len-1] == 0) printf("Wrong!\n");
    int val = 0;
    for (int i = 0; i < len; i++) {
        val = val * 10 + array[len - 1 - i];
    }
    return val;
}

void swap(char* array, int i, int j) {
    int tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

char buf[100];

int main() {
    int T, val;
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
       scanf("%d", &val);
       int min = val, max = val;
       int len = formatInt(val, buf);
       for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
           if (j + 1 == len && buf[i] == 0) continue;
           swap(buf, i, j);
           int tmp = parseInt(buf, len);
           if (tmp < min) min = tmp;
           if (tmp > max) max = tmp;
           swap(buf, j, i);
        }
       }
       printf("Case #%d: %d %d\n", t + 1, min, max);
    }
}
