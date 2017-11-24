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

int n, k;
long long a[N], s[N];
vector<int> e;
int main() {
    IO;
    //freopen("CHECKPOINT.inp","r",stdin);
    //freopen("CHECKPOINT.out","w",stdout);
    read(n);read(k);
    long long sum = 0, ans = 0;
    int neg = 0, start = 0;
    /*REP(last, n) {
        read(a[last]);
        sum += a[last];
        if (a[last] < 0) neg++;
        while (neg > k || sum < 0) {
            sum -= a[start];
            if (a[start] < 0) neg--;
            ++start;
        }
        ans = max(ans, sum);
    }*/
    e.push_back(0);
    FOR(i, 1, n) {
        read(a[i]);
        if (a[i] < 0) e.push_back(i);
    }
    FOR(i, 1, n) s[i] = s[i - 1] + a[i];
    int now = 0;
    FOR(i, 1, n) {
        if (a[i] < 0) {
            now++;
            continue;
        }
        FOR(j, max(0, now - k), now) {
            int t = e[j];
            ans = max(ans, s[i] - s[t]);
        }
    }
    writeln(ans);
}
