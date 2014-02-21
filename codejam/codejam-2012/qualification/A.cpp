#include <stdio.h>
#include <string.h>

#include <string>

using namespace std;

static const string a = "y e q z ejp mysljylc kd kxveddknmc re jsicpdrysi rbcpc ypc rtcsra dkh wyfrepkym veddknkmkrkcd de kr kd eoya kw aej tysr re ujdr lkgc jv";
static const string b = "a o z q our language is impossible to understand there are twenty six factorial possibilities so it is okay if you want to just give up";

char map[26];

int getId(char ch) {
    return ch - 'a';
}

void init() {
    for (int i = 0 ; i < a.size(); i++) {
        if (a[i] == ' ') continue;
        map[getId(a[i])] = b[i];
    }
}

int main(){
    init();
    int T;
    char input[128];
    scanf("%d\n", &T);
    for (int cases = 0; cases < T; cases++) {
        gets(input);
        int len = strlen(input);
        for (int i = 0; i < len ;i++) {
            if (input[i] == ' ') continue;
            input[i] = map[getId(input[i])];
        }
        printf("Case #%d: %s\n", cases + 1, input);
    }
}
