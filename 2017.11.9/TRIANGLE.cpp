#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 200100
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

int n, q;
long long u[N * 3], v[N * 3], c[N * 2];
vector<long long> d;
set<long long> ptx[N * 3], pty[N * 3];

int main() {
    IO;
    freopen("TRIANGLE.inp","r",stdin);
    freopen("TRIANGLE.out","w",stdout);
    read(n);read(q);
    REP(i, n) {
        read(u[i + q]); read(v[i + q]);
        d.push_back(u[i + q]);
        d.push_back(v[i + q]);
    }
    REP(i, q) {
        read(c[i]);read(u[i]);read(v[i]);
        d.push_back(u[i]);
        d.push_back(v[i]);
    }
    sort(d.begin(), d.end());
    REP(i, n) {
        u[i + q] = lower_bound(d.begin(), d.end(), u[i + q]) - d.begin();
        v[i + q] = lower_bound(d.begin(), d.end(), v[i + q]) - d.begin();
        ptx[u[i + q]].insert(v[i + q]);
        pty[v[i + q]].insert(u[i + q]);
    }
    REP(i, q) {
        u[i] = lower_bound(d.begin(), d.end(), u[i]) - d.begin();
        v[i] = lower_bound(d.begin(), d.end(), v[i]) - d.begin();
        if (c[i] == 1) {
            ptx[u[i]].insert(v[i]);
            pty[v[i]].insert(u[i]);
        }
        else {
            if (c[i] == 2) {
                ptx[u[i]].erase(v[i]);
                pty[v[i]].erase(u[i]);
            }
            else {
                if (pty[v[i]].empty() || ptx[u[i]].empty()) {
                    writeln(0);
                    continue;
                }
                int minX = d[*pty[v[i]].begin()];
                int maxX = d[*pty[v[i]].rbegin()];
                int minY = d[*ptx[u[i]].begin()];
                int maxY = d[*ptx[u[i]].rbegin()];
                long long ans = 1ll * max(abs(maxX - d[u[i]]), abs(minX - d[u[i]])) * max(abs(minY - d[v[i]]), abs(maxY - d[v[i]]));
                write(ans / 2);
                if (ans % 2) {
                    putchar('.'); putchar('5');
                }
                putchar('\n');
            }
        }
    }
}
