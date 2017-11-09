/*
Có nhận xét là : GCD(i, i + 1) = 1. -> Mình tạo cây dfs sao cho không có cung chéo ( thực chất là dfs ưu tiên vào những đỉnh chưa duyệt )
rồi đánh số liên tiếp vào các cạnh. Đỉnh nằm giữa 2 cạnh được đánh số liên tiếp thì đã chắc chắn có gcd = 1. 
Các cạnh nối đến nó không làm thay đổi GCD này. Còn nếu có cạnh nối lên gốc thì tại gốc có 1 cạnh gcd = 1 rồi nên GCD tổng cũng sẽ là 1 
*/
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
    while (!isdigit(c = getchar()));
    x = 0;
    do {
        x = x * 10 + c - '0';
    } while (isdigit(c = getchar()));
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
int n, m, cnt;
vector<int> g[N];
bool fr[N];

struct data {
    int u, v, c;
};
vector<data> e;
void dfs(int u, int p) {
    fr[u] = false;
    for (int id : g[u]) if (fr[e[id].v]) {
        e[id].c = ++cnt;
        dfs(e[id].v, u);
    }
    for (int id : g[u]) if (e[id].c == 0 && e[id ^ 1].c == 0) {
        e[id].c = ++cnt;
    }
}
int main() {
    IO;
    freopen("ONEGCD.inp","r",stdin);
    freopen("ONEGCD.out","w",stdout);
    read(n);read(m);
    int u, v;
    FOR(i, 1, n) fr[i] = true;
    REP(i, m) {
        read(u);read(v);
        data ee = {u, v, 0};
        g[u].push_back(e.size());
        e.push_back(ee);
        ee = {v, u, 0};
        g[v].push_back(e.size());
        e.push_back(ee);
    }
    cnt = 0;
    dfs(1, -1);
    for (data x : e) if (x.c != 0) {
        write(x.u);
        putchar(' ');
        write(x.v);
        putchar(' ');
        writeln(x.c);
    }
}
