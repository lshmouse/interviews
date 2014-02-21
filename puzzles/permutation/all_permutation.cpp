#include <stdio.h>
#include <algorithm>

void swap(int&a, int&b) {
    int t = a;
    a = b;
    b =t;
}

void print(const int* array, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

void dfs(int *array, int size, int k) {
    if (k == size) {
        print(array, size);
        return;
    }
    for(int i = k; i < size; i++) {
        if (i == k || (array[i] != array[k])) {
            swap(array[i], array[k]);
            dfs(array, size, k + 1);
            swap(array[i], array[k]);
        }
    }
}

int main() {
    int array[] = {1,2,2,4,5};
    dfs(array, 5, 0);
    return 0;
}
