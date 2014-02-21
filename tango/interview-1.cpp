// rotate the array firstly, then totate the each word in the string

#include <stdint.h>
#include <stdio.h>

#include <algorithm>

using namespace std;

void Rotate(char* in, size_t first, size_t last) {
    for(size_t i = 0; first + i < last - i; ++i) {
        swap(in[first + i], in[last -i]);
    }
}

char* ReverseWords(char* in, size_t size) {
    CHECK_NULL(in); // in no null

    Rotate(in, 0, size - 1);
    size_t first = 0;
    for (size_t i = 0; i < size; i++){
        if (in[i] == ' ') { // a empty
            if(first < i) {
                Rotate(in, first, i - 1);
            }
            first = i + 1;
        }
    }
    if (first < size) {
        Rotate(in, first, size - 1);
    }
    return in;
}

// test case:
// (1) simple case: HELLO WORLD
// (2) single word: HELLO
// (3) multi empty between words: HELLO  WORLD
// (4) there is empty in the end of the string: HELLO  
// (5) in is null, check if the program will core
//
