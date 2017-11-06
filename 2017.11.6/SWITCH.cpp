#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 100100
#define pp pair<int, int>
#define IO cin.tie(NULL);cout.tie(NULL);
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

char s[N];
bool a[10][10];
int m, u, v;;
int main() {
    IO;
    freopen("SWITCH.inp","r",stdin);
    freopen("SWITCH.out","w",stdout);
    read(m);
    memset(a, false, sizeof a);
    REP(i, m) {
        read(u);read(v);
        a[u][v] = a[v][u] = true;
    }
    scanf("%s", &s);
    int ans = 0;
    int n = strlen(s);
    FOR(i, 1, n - 1) {
        int pos = i;
        FORD(j, i - 1, 0) if (!a[s[i] - '0'][s[j] - '0']) break;
        else if (s[i] > s[j]) pos = j;
        char now = s[i];
        FORD(j, i - 1, pos) s[j + 1] = s[j];
        s[pos] = now;
        ans += i - pos;
    }
    writeln(ans);
    printf("%s", s);
}
