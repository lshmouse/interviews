#include <stdio.h>
#include <algorithm>

void swap(int&a, int&b) {
    int t = a;
    a = b;
    b =t;
}

bool next_permutation(int *array, int size) {
    if (size == 1) return false;
    // find the swap postion
    int p = -1;
    for(int i = size - 2; i >= 0; i--){
        if (array[i] < array[i + 1]) {
            p = i;
            break;
        }
    }
    if (p == -1) return false;
    //
    for(int i = size - 1; i > p; i--){
        if (array[i] > array[p]) {
            swap(array[i], array[p]);
            break;
        }
    }
    // reverse[p+1, size -1];
    for(int i = 0 ; i < (size - p -1) / 2; i++){
        swap(array[p+1+i], array[size -1 -i]);
    }
    return true;
}

void print(const int* array, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int array[] = {1,2,2,4,5};
    do {
        print(array, 5);
    } while(next_permutation(array, 5));
    return 0;
}
