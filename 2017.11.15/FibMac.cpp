#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 100100
#define pp pair<long long, long long>
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

int n, q, u, v;
char c;
long long f[N];

long long lazy[N * 4];
const long long MOD = 1e9 + 7;
//bef f(x - 1)
//now f(x)

struct data {
    long long bef, now;
    int cnt0;
};
data IT[N * 4];

void Add(data &now, long long val) {
    data tmp;
    tmp.bef = (now.bef * f[val - 1] % MOD + now.now * f[val] % MOD) % MOD;
    tmp.now = (now.bef * f[val] % MOD + now.now * f[val + 1] % MOD) % MOD;
    tmp.cnt0 = now.cnt0;
    now = tmp;
    if (now.cnt0 > 0) {
        now.bef = (now.bef + f[val - 1] * 1ll * now.cnt0 % MOD) % MOD;
        now.now = (now.now + f[val] * 1ll * now.cnt0 % MOD) % MOD;
        now.cnt0 = 0;
        return;
    }
}

void Down(int k, int l, int r) {
    if (lazy[k] == 0) return;
    int m = (l + r) >> 1;
    lazy[k * 2] += lazy[k];
    lazy[k * 2 + 1] += lazy[k];
    Add(IT[k * 2], lazy[k]);
    Add(IT[k * 2 + 1], lazy[k]);
    lazy[k] = 0;
}
void Up(int k, int l, int r, int u, int v) {
    if (l > v || r < u) return;
    if (u <= l && r <= v) {
        Add(IT[k], 1);
        lazy[k]++;
        return;
    }
    Down(k, l, r);
    int m = (l + r) >> 1;
    Up(k * 2, l, m, u, v);
    Up(k * 2 + 1, m + 1, r, u, v);
    IT[k].bef = (IT[k * 2].bef + IT[k * 2 + 1].bef) % MOD;
    IT[k].now = (IT[k * 2].now + IT[k * 2 + 1].now) % MOD;
    IT[k].cnt0 = IT[k * 2].cnt0 + IT[k * 2 + 1].cnt0;
}

long long Get(int k, int l, int r, int u, int v) {
    if (l > v || r < u) return 0;
    if (u <= l && r <= v) return IT[k].now;
    int m = (l + r) >> 1;
    Down(k, l, r);
    long long ans = (Get(k * 2, l, m, u, v) + Get(k * 2 + 1, m + 1, r, u, v)) % MOD;
    return ans;
}

void build(int k, int l, int r) {
    if (l == r) {
        IT[k].cnt0 = 1;
        return;
    }
    int m = (l + r) >> 1;
    build(k * 2, l, m);
    build(k * 2 + 1, m + 1, r);
    IT[k].cnt0 = r - l + 1;
}

int main() {
    IO;
    read(n); read(q);
    build(1, 1, n);
    f[0] = 0; f[1] = 1;
    FOR(i, 2, q) {
        f[i] = f[i - 1] + f[i - 2];
        if (f[i] >= MOD) f[i] -= MOD;
    }
    while (q--) {
        scanf("%c", &c);
        read(u);read(v);
        if (c == 'D') Up(1, 1, n, u, v);
        else writeln(Get(1, 1, n, u, v));
    }
}
