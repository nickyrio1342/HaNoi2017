#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 1001000
#define pp pair<int, int>
#define IO cin.tie(NULL);cout.tie(NULL);
#define bit(S, i) (((S) >> i) & 1)
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
#define data Data
#define esp 1e-6
int l, n;
struct data {
    long long t, v;
    int val, pos;
}s[N];
int BIT[N];
vector<data> e;
bool cmp(const data &a, const data &b) {
     return (long double)l / a.v + a.t < (long double) l / b.v + b.t;
}
bool cmpT(const data &a, const data &b) {
    return a.t > b.t;
}

void Up(int u, int val) {
    for(; u <= n; u += u&-u) BIT[u] = max(BIT[u], val);
}

int Get(int u) {
    int ans = 0;
    for(; u > 0; u -= u&-u) ans = max(ans, BIT[u]);
    return ans;
}
int main() {
    IO;
    freopen("WALKING.inp","r",stdin);
    freopen("WALKING.out","w",stdout);
    read(l);read(n);
    REP(i, n) {
        read(s[i].t);read(s[i].v);
        s[i].pos = i;
        e.push_back(s[i]);
    }
    sort(e.begin(), e.end(), cmp);
    s[e[0].pos].val = 1;
    int k = 1;
    FOR(i, 1, n - 1) {
        if ((long double)l / e[i].v + e[i].t - ((long double) l / e[i - 1].v + e[i - 1].t) > esp ) k++;
        s[e[i].pos].val = k;
    }
    int ans = 0;
    sort(s, s + n, cmpT);
    REP(i, n) {
        int now = Get(s[i].val - 1) + 1;
        ans = max(ans, now);
        Up(s[i].val, now);
    }
    writeln(ans);
}
