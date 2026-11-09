#include <bits/stdc++.h>
using namespace std;

int board[27][27];
int dis[27][27][4];


int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

struct State{
    int x,y,dir;
};

int main() {
    memset(board, -1, sizeof(board));
    memset(dis, 0x3f, sizeof(dis));
    int N,t;
    cin >> N >> t;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
        }
    }


    queue <State> que;
    
    for (int i = 0; i < 4; i++) {
        dis[N-1][0][i] = 0;
        que.push({N-1, 0, i});
    }
    
    while (!que.empty()) {
        State cur = que.front();
        que.pop();
        for (int dir = 0; dir <4; dir++) {
            int nx = cur.x + dx[dir];
            int ny = cur.y + dy[dir];
            if(nx <0 || nx >= N || ny <0 || ny >= N) continue;
            if (board[nx][ny] == 1 ) continue;

            int time = dis[cur.x][cur.y][cur.dir] + 1;
            if (cur.dir != dir) time+= t;

            if (time < dis[nx][ny][dir]) {
                dis[nx][ny][dir] = time;
                que.push({nx, ny,dir});
            }
        }
        
    }
    int ans = 0x3f3f3f3f;
    for (int i = 0; i < 4; i++) {
        ans = min(ans, dis[0][N-1][i]);
    }   

    if (ans == 0x3f3f3f3f) cout << -1;
    else cout << ans;

}
