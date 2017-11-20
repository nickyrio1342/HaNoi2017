#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 201000
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

struct data {
    int x, y, pos;

    bool operator < (const data &a) {
        if (pos < 0) return (x < a.x) || ((x == a.x) && y < a.y);
        return (x < a.x) || ((x == a.x) && pos < a.pos);
    }
}s[N], t[N * 2], t2[N * 2];

struct edge {
    int u, v, c;
    bool operator < (const edge &a) {
        return c < a.c;
    }
};

vector<int> X, Y;
struct SegmentTree {
    vector<int> IT, lazy;
    int n;
    void reset(int n) {
        this -> n = n;
        IT.clear();IT.resize(n * 4);
        lazy.clear();lazy.resize(n * 4);
    }

    void Down(int k) {
        if (lazy[k] == 0) return;
        lazy[k * 2] += lazy[k];
        lazy[k * 2 + 1] += lazy[k];
        IT[k * 2] += lazy[k];
        IT[k * 2 + 1] += lazy[k];
        lazy[k] = 0;
    }
    void Update(int u, int v, int val) {
        Up(1, 1, n, u, v, val);
    }

    long long GetMax(int u, int v) {
        return Get(1, 1, n, u, v);
    }
private:
    void Up(int k, int l, int r, int u, int v, int val) {
        if (l > v || r < u) return;
        if (u <= l && r <= v) {
            IT[k] += val;
            lazy[k] += val;
            return;
        }
        int m = (l + r) >> 1;
        Down(k);
        Up(k * 2, l, m, u, v, val);
        Up(k * 2 + 1, m + 1, r, u, v, val);
        IT[k] = max(IT[k * 2], IT[k * 2 + 1]);
    }

    long long Get(int k, int l, int r, int u, int v) {
        if (l > v || r < u) return 0;
        if (u <= l && r <= v) return IT[k];
        Down(k);
        int m = (l + r) >> 1;
        return max(Get(k * 2, l, m, u, v), Get(k * 2 + 1, m + 1, r, u, v));
    }
}sIT;

int n, m, c;

int IdxX(int x) {
    return lower_bound(X.begin(), X.end(), x) - X.begin() + 1;
}

int IdxY(int x) {
    return lower_bound(Y.begin(), Y.end(), x) - Y.begin() + 1;
}

vector<edge> newE;
void CreateGraph() {
    sort(s, s + n);
    sort(t, t + 2 * m);
    sIT.reset(n + 2 * m + 1);
    int i_t = 0;
    REP(i, n) {
        if (i == 0 || s[i].x != s[i - 1].x) {
            while (i_t < 2 * m && (t[i_t].x < s[i].x || (t[i_t].x == s[i].x && t[i_t].pos < m))) {
                if (t[i_t].pos < m) {
                    sIT.Update(IdxY(t[i_t].y), IdxY(t2[t[i_t].pos + m].y), 1);
                }
                else {
                     sIT.Update(IdxY(t2[t[i_t].pos - m].y), IdxY(t[i_t].y), -1);
                }
                i_t++;
            }
        }
        else {
            if (sIT.GetMax(IdxY(s[i - 1].y), IdxY(s[i].y)) == 0) {
                newE.push_back(edge({-s[i].pos, -s[i - 1].pos, s[i].y - s[i - 1].y}));
            }
        }
    }
}
int f[N];

long long ff[N];
vector<int> e;

void Union(int a, int b) {
    int t = f[a] + f[b];
    if (f[a] <= f[b]) {
        f[a] = t;
        f[b] = a;
        return;
    }
    f[a] = b;
    f[b] = t;
}

int root(int u) {
    if (f[u] < 0) return u;
    f[u] = root(f[u]);
    return f[u];
}

int main() {
    IO;
    freopen("E:\\input.txt","r",stdin);
    freopen("E:\\out.txt","w",stdout);
    read(n);read(m);read(c);
    REP(i, n) {
        read(s[i].x); read(s[i].y);
        X.push_back(s[i].x);
        Y.push_back(s[i].y);
        s[i].pos = -i - 1;
    }
    REP(i, m) {
        read(t[i].x);read(t[i].y);read(t[m + i].x);read(t[m + i].y);
        X.push_back(t[i].x);
        X.push_back(t[i + m].x);
        Y.push_back(t[i].y);
        Y.push_back(t[i + m].y);
        t2[i] = t[i]; t2[i + m] = t[i + m];
        t[i].pos = i;
        t[m + i].pos = m + i;
    }
    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());
    CreateGraph();
    // Rotate
    REP(i, n) swap(s[i].x, s[i].y);
    REP(i, 2 * m) {
        swap(t[i].x, t[i].y);
        swap(t2[i].x, t2[i].y);
    }
    swap(X, Y);
    CreateGraph();
    FOR(i, 1, n) f[i] = -1;
    int cnt = n;
    sort(newE.begin(), newE.end());
    for (edge x : newE) {
        int a = root(x.u);
        int b = root(x.v);
        if (a != b) {
            e.push_back(x.c);
            cnt--;
            Union(a, b);
        }
    }
    //Query
    ff[e.size()] = 0;
    FORD(i, (int) e.size() - 1, 0) {
        ff[i] = ff[i + 1] + e[i];
    }
    int bx, hx;

    while (c--) {
        read(bx); read(hx);
        if (hx < cnt) {
            writeln(-1);
            continue;
        }
        if (e.empty()) {
            writeln(1ll * bx * n);
            continue;
        }
        if (bx >= e.back()) {
            writeln(ff[0] + 1ll * bx * cnt);
            continue;
        }
        int t1 = upper_bound(e.begin(), e.end(), bx) - e.begin();
        int t2 = (int) e.size() - (hx - cnt);
        int tt = max(t1, t2);
        writeln(ff[0] - ff[tt] + 1ll * ((int)e.size() + cnt - tt) * bx);
    }

}
