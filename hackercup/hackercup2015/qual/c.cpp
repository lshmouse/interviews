#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;

int m, n;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

char maze[128][128];
char g[4][128][128];
bool v[4][128][128];

struct Node{
  int x, y, s;
};

bool check(Node a) {
    if (a.x >= m || a.x < 0) return false;
    if (a.y >= n || a.y < 0) return false;
    if (v[a.s % 4][a.x][a.y]) return false;
    return g[a.s % 4][a.x][a.y] == '.';
}

int dfs(Node s) {
   queue<Node> q;
   q.push(s);
   v[s.s % 4][s.x][s.y] = true;
   while (!q.empty()) {
      Node from = q.front();
      q.pop();
      for (int i = 0; i < 4; i++) {
         Node to;
         to.x =  from.x + dx[i];
         to.y = from.y + dy[i];
         to.s = from.s + 1;
         if (check(to)) {
            q.push(to);
            v[to.s % 4][to.x][to.y] = true;
            if (maze[to.x][to.y] == 'G') {
                return to.s;
            }
         }
      }
   }
   return -1;
}

int getDirection(char ch) {
    if (ch == '^') return 0;
    if (ch == '>') return 1;
    if (ch == 'v') return 2;
    if (ch == '<') return 3;
    printf("Wrong input\n");
    return -4;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 0 ; t < T; t++) {
       scanf("%d%d", &m, &n);
       for (int i = 0; i < m ; i++) scanf("%s", maze[i]);
       Node s;
       s.s = 0;
       for (int k = 0 ; k < 4 ;k ++) {
           for (int i = 0; i < m; i++) {
             for (int j = 0; j < n ; j++) {
               g[k][i][j] = '.';
               v[k][i][j] = false;
             }
             g[k][i][n]= '\0';
           }
           for (int i = 0; i < m; i++) {
             for (int j = 0; j < n ; j++) {
               if (maze[i][j] == '.') continue;
               if (maze[i][j] == 'S') {
                 s.x = i, s.y = j;
                 continue;
               }
               if (maze[i][j] == 'G') continue;
               if (maze[i][j] == '#') { 
                   g[k][i][j] = '#';
                   continue;
               }
               // laser
               g[k][i][j] = '#';
               int d = (getDirection(maze[i][j]) + k) % 4;
               int x = i, y = j;
               while (true) {
                   x += dx[d], y +=dy[d]; 
                   if (x < 0 || x >= m) break;
                   if (y < 0 || y >= n) break;
                   if (maze[x][y] == '#') break;
                   if (maze[x][y] == '^') break;
                   if (maze[x][y] == '>') break;
                   if (maze[x][y] == 'v') break;
                   if (maze[x][y] == '<') break;
                   g[k][x][y] = '#';
               }
             }
          }
      }
      int ret = -1;
      ret = dfs(s);
      if (ret > 0) {
        printf("Case #%d: %d\n", t + 1, ret);
      } else {
        printf("Case #%d: impossible\n", t + 1);
      }
    }
}
