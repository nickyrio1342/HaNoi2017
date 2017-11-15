#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 10010
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
    if (x < 0) {
        putchar('-');
        write(-x);return;
    }
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

char s[51][51], st[N];
int m, n, d[2555][N];


int idx(int i, int j) {
    return i * n + j;
}

bool inside(int i, int j) {
    return i>=0 && i<m && j>=0 && j<n;
}

const int dd[4] = {0, 1, 0, -1};
const int cc[4] = {1, 0, -1, 0};
vector<int> e[N];
const int inf = 1e9;
queue<pp> q;
int cnt[N];

int main() {
    IO;
    freopen("KEYBOARDING.inp","r",stdin);
    freopen("KEYBOARDING.out","w",stdout);
    read(m);read(n);
    REP(i, m) scanf("%s", &s[i]);
    scanf("%s", &st);
    memset(cnt, 0, sizeof cnt);
    REP(i, m) REP(j, n) {
        cnt[s[i][j]]++;
        REP(k, 4) {
            int ii = i, jj = j;
            while (inside(ii, jj) && s[ii][jj] == s[i][j]) {
                ii += dd[k];
                jj += cc[k];
            }
            if (inside(ii, jj)) {
                e[idx(i, j)].push_back(idx(ii, jj));
            }
        }
    }
    int len = strlen(st);
    st[len++] = '*';
    REP(i, len + 2) REP(j, m * n) d[j][i] = inf;
    d[0][0] = 0;
    q.push(pp(0, 0));
    while (!q.empty()) {
        int u = q.front().first;
        int t = q.front().second;
        q.pop();
        if (s[u / n][u % n] == st[t] && d[u][t + 1] > d[u][t] + 1) {
            d[u][t + 1] = d[u][t] + 1;
            q.push(pp(u, t + 1));
        }
        for (int v : e[u]) {
            if (d[v][t] > d[u][t] + 1) {
                d[v][t] = d[u][t] + 1;
                q.push(pp(v, t));
            }
        }
    }
    int ans = -1;
    REP(i, m) REP(j, n) if (s[i][j] == '*') {
        if (ans == -1 || ans > d[idx(i, j)][len]) ans = d[idx(i, j)][len];
    }
    writeln(ans);
}
