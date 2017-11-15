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


int a[N], b[N], n, fr[N];
vector<int> e[N];

void dfs(int u, int p) {
    for (int v : e[u]) if (v != p) {
        if (fr[v] == 0) {
            fr[v] = 3 - fr[u];
            dfs(v, u);
        } else {
            if (fr[v] != 3 - fr[u]) {
                writeln(0);
                exit(0);
            }
        }
    }
}

int main() {
    IO;
    read(n);
    int cnt = n - 1;
    REP(i, n) read(a[i]);
    REP(i, n) read(b[i]);
    REP(i, n) REP(j, i) {
        if (a[i] == a[j] || b[i] == b[j]) {
            e[i].push_back(j);
            e[j].push_back(i);
        }
        if (a[i] == b[j] || b[i] == a[j]) {
            e[i].push_back(++cnt);
            e[cnt].push_back(i);
            e[j].push_back(cnt);
            e[cnt].push_back(j);
        }
    }
    memset(fr, 0, sizeof fr);
    long long ans = 1;
    REP(i, cnt + 1) if (fr[i] == 0) {
        fr[i] = 1;
        dfs(i, -1);
        ans *= 2ll;
    }
    writeln(ans);
}
