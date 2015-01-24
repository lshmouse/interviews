#include <stdio.h>
#include <string.h>

#define maxn 1024000

struct Node {
    bool end;
    int count;
    int child[26];
};

int N;
Node tree[maxn];

int init_node() {
    tree[N].count = 0;
    for (int i = 0; i < 26 ;i ++) tree[N].child[i] = -1;
    return N++;
}


void insert_tree(Node* node, char* str) {
    for (int i  = 0 ; str[i] != 0; i ++) {
        int ch = int(str[i] - 'a');
        if (node->child[ch] == -1) {
            node->child[ch] = init_node();
        }
        node->count++;
        node = &tree[node->child[ch]];
    } 
    node->count++;
}


int find_tree(Node * node, char* str) {
    for (int i  = 0 ; str[i] != 0; i ++) {
        int ch = int(str[i] - 'a');
        if (node->count == 1) return i;
        node = &tree[node->child[ch]];
    } 
    return strlen(str);
}

int n;
char buf[maxn];

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t ++){
        scanf("%d", &n);
        int res = 1;
        N = 0;
        init_node();
        for (int i = 0; i < n ; i++){
            scanf("%s", buf);
            insert_tree(&tree[0], buf);
            res += find_tree(&tree[0], buf);
        }
        printf("Case #%d: %d\n", t, res);
    }
}
