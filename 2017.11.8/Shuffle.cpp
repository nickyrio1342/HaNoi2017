#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 1001000
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

vector<int> c[N];
int pos[N], a[N], b[N], n, cnt, dd[N], vs[N], d[N];
bool fr[N];
void dfs(int u, int t, int bb, int &ok) {
    fr[u] = false;
    if (a[u] == bb) ok = vs[u] + 1;
    c[cnt].push_back(u);
    dd[u] = cnt;
    pos[u] = c[cnt].size() - 1;
    if (a[u] == t) return;
    vs[a[u]] = vs[u] + 1;
    dfs(a[u], t, bb, ok);
}

#define sz(a) (int)a.size()
int tab[N];
bool NT[N];

long long lcm(long long a, long long b) {
    return a / __gcd(a, b) * b;
}
int main() {
   IO;
   read(n);
   FOR(i, 1, n) read(a[i]);
   FOR(i, 1, n) read(b[i]);
   FOR(i, 1, n) fr[i] = true;
   long long tmp = 0;
    FOR(i, 1, n) tab[i] = -1;
   FOR(i, 1, n) if (fr[i]) {
       int ok = -1;
       cnt++;
       vs[i] = 0;
       dfs(i, i, b[i], ok);
       if (ok == -1) {
            printf("NIE");return 0;
       }
   
       int t1 = sz(c[cnt]);
       int t2 = ok;
       if (tab[t1] == -1 || tab[t1] == t2) tab[t1] = t2;
       else {
            printf("NIE");return 0;
       }
       FOR(j, 0, (sz(c[cnt])) - 1) {
            int u = c[cnt][j];
            if (c[cnt][(j + ok) % sz(c[cnt])] != b[u]) {
                printf("NIE");
                return 0;
            }
       }
   }
   // 
   memset(NT, true ,sizeof NT);
    FOR(i, 2, n) if (NT[i]){
        int tt = -1;
        int ttt = -1;
        if (tab[1] != -1) tt = 1;
        if (tab[i] != -1 && tab[1] != -1) {
            if (tab[i] % i != tab[1] % 1) {
                 printf("NIE");
                return 0;
            }
        }
        for (int j = i + i; j <= n; j += i) if (tab[i] != -1 && tab[j] != -1){
            NT[j] = false;
            if (tab[j] % i != tab[i] % i) {
                 printf("NIE");
                return 0;
            }
        } else NT[j] = false;
    }
   //
   printf("TAK");
}
