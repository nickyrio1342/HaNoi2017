#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 3333
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

int n, m, a[N][N], h[N], b[N][N];
stack<int> st;

bool ok(int i, int j) {
    FOR(ii, i, i + 2) if (a[ii][j] - a[ii][j + 1] != a[ii][j + 1] - a[ii][j + 2]) return false;
    FOR(jj, j, j + 2) if (a[i][jj] - a[i + 1][jj] != a[i + 1][jj] - a[i + 2][jj]) return false;
    return true;
}
void solve()
{
    read(m);read(n);
    FOR(i, 1, m) FOR(j, 1, n) read(a[i][j]);
    FOR(i, 1, m - 2) {
        FOR(j, 1, n - 2) {
            if (ok(i, j)) b[i][j] = 1;
            else b[i][j] = 0;
        }
    }
    int ans = 0;
    FOR(i, 1, m - 2) {
        b[i][0] = -1;
        FOR(j, 1, n - 2) if (b[i][j] != 0) b[i][j] += b[i - 1][j];
        b[i][n - 1] = 0;
        FOR(j, 0, n - 1) h[j] = b[i][j];
        while (!st.empty()) st.pop();
        st.push(0);
        FOR(j, 1, n - 1) {
            while (h[st.top()] >= h[j]) {
                int height = h[st.top()];
                st.pop();
                if (height == 0) continue;
                ans = max(ans, (height + 2) * (j - st.top() + 1));
            }
            st.push(j);
        }
    }
    //1 Line
    FOR(i, 1, m) {
        FOR(j, 1, n) {
            if (j < 3) b[i][j] = j;
            else {
                if (a[i][j] - a[i][j - 1] == a[i][j - 1] - a[i][j - 2]) b[i][j] = b[i][j - 1] + 1;
                else b[i][j] = 2;
            }
            ans = max(ans, b[i][j]);
        }
        if (i != 1) {
            FOR(j, 1, n) ans = max(ans, 2 * min(b[i][j], b[i - 1][j]));
        }
    }
    FOR(j, 1, n) {
        FOR(i, 1, m) {
            if (i < 3) b[i][j] = i;
            else {
                if (a[i][j] - a[i - 1][j] == a[i - 1][j] - a[i - 2][j]) b[i][j] = b[i - 1][j] + 1;
                else b[i][j] = 2;
            }
            ans = max(ans, b[i][j]);
        }
        if (j != 1) {
            FOR(i, 1, m) {
                ans = max(ans, 2 * min(b[i][j], b[i][j - 1]));
            }
        }
    }
    writeln(ans);
}
int main() {
    IO;
    freopen("ARY1.in","r",stdin);
    int test;
    cin>>test;
    while (test--) {
        solve();
    }
}
