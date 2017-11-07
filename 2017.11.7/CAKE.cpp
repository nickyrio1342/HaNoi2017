//Vì K nhỏ, chỉ cần quan tâm vị trí tương đối của các điểm với nhau -> nén điểm lại -> max Tọa độ = 100.
//BFS tìm số lượng thành phần liên thông bị chắn bởi các cạnh.

#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 100100
#define pp pair<int, int>
#define IO cin.tie(NULL);cout.tie(NULL);
#define bit(S, i) ((S >> i) & 1)
template<typename T> inline void read(T &x) {
    char c;
    bool neg = false;
    while (!isdigit(c = getchar()) && c != '-');
    x = 0;
    if (c == '-') {
        neg = true;
        c = getchar();
    }
    do {
        x = x * 10 + c - '0';
    } while (isdigit(c = getchar()));
    if (neg) x = -x;
}
template<typename T> inline void write(T x) {
    if (x < 10) {
        putchar(char(x + 48));
    }
    else {
        write(x/10);
        putchar(char(48 + x%10));
    }
}
template<typename T> inline void writeln(T x) {
    write(x);
    putchar('\n');
}
using namespace std;

struct data {
    int x1, y1, x2, y2;

    void change() {
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
    }

};
int k, m, n, mxx, mxy;
vector<data> e;
vector<int> xx, yy;
bool fr[222][222];
queue<pp> q;

const int d[4] = {0, 1, 0, -1};
const int c[4] = {1, 0, -1, 0};

bool inside(int i, int j) {
    if (i >=0 && i < mxx && j >= 0 && j < mxy) return true;
    return false;
}

bool in(pp u, data t) {
    if (u.first >= t.x1 && u.first < t.x2 && u.second >= t.y1 && u.second < t.y2) return true;
    return false;
}

void bfs(int ii, int jj) {
    while (!q.empty()) q.pop();
    q.push(pp(ii, jj));
    fr[ii][jj] = false;
    while (!q.empty()) {
        pp u = q.front(); q.pop();
        REP(i, 4) {
            pp v = pp(u.first + d[i], u.second + c[i]);
            if (inside(v.first, v.second) && fr[v.first][v.second]) {
                bool ok = true;
                for(data x : e) {
                    if ((in(u, x) && !in(v, x)) || (!in(u, x) && in(v, x))) {
                        ok = false; break;
                    }
                }
                if (ok) {
                    fr[v.first][v.second] = false;
                    q.push(v);
                }
            }
        }
    }
}
void solve() {
    read(n);read(m);
    if (m == 0) exit(0);
    read(k);
    e.clear();
    e.push_back(data({0, 0, m, n}));
    xx.clear();xx.push_back(0);xx.push_back(m);
    yy.clear();yy.push_back(0);yy.push_back(n);
    while(k--) {
        data now;
        read(now.x1);read(now.y1);read(now.x2);read(now.y2);
        now.change();
        xx.push_back(now.x1);
        xx.push_back(now.x2);
        yy.push_back(now.y1);
        yy.push_back(now.y2);
        e.push_back(now);
    }
    sort(xx.begin(), xx.end());
    sort(yy.begin(), yy.end());
    for (data &x : e) {
        x.x1 = lower_bound(xx.begin(), xx.end(), x.x1) - xx.begin();
        x.x2 = lower_bound(xx.begin(), xx.end(), x.x2) - xx.begin();
        x.y1 = lower_bound(yy.begin(), yy.end(), x.y1) - yy.begin();
        x.y2 = lower_bound(yy.begin(), yy.end(), x.y2) - yy.begin();
    }
    mxx = lower_bound(xx.begin(), xx.end(), m) - xx.begin();
    mxy = lower_bound(yy.begin(), yy.end(), n) - yy.begin();
    memset(fr, true, sizeof fr);
    int ans = 0;
    REP(i, mxx) REP(j, mxy) if (fr[i][j]) {
        ans++;
        bfs(i, j);
    }
    writeln(ans);
}
int main() {
   IO;
   freopen("CAKE.inp","r",stdin);
   freopen("CAKE.out","w",stdout);
   while (true) solve();
}
