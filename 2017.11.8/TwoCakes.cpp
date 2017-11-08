/* Nếu không tồn tại a[i] = b[i] -> Kết quả là n. 
Gọi dp[i] là thời gian ngắn nhất để xử lí xong hết các thằng từ a[j..n] và b[k..n] với a[j] = b[k] = i.
Xét với thằng u, gọi dis[u] = a[j] - b[k] với a[j] = b[k] = u.
Có 2 trường hợp : 
  + Nếu mình cho thằng ở dãy A làm trước mình sẽ lấy tiếp các thằng từ a[j + 1..n] và b[k..n] nếu không tồn tại dis[v] = k + 1
   hoặc là chạy đến thằng v gần nhất (thõa dis[v] = k + 1 )và thừa hưởng kq từ dp[v]
  + Tương tự với trường hợp cho thằng ở dãy B đi trước
 DPT O(nlogn)
 */
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 1001000
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

int n, a[N], b[N], posb[N], dis[N * 2], dp[N];
vector<int> e[N * 2];

int main() {
    IO;
    read(n);
    FOR(i, 1, n) read(a[i]);
    FOR(i, 1, n) read(b[i]);
    int ok = -1;
    FOR(i, 1, n) {
        if (a[i] == b[i]) {
            ok = i;
            break;
        }
    }
    if (ok == -1) {
        writeln(n);
        return 0;
    }
    FOR(i, 1, n) posb[b[i]] = i;
    FOR(i, 1, n) {
        dis[a[i]] = i - posb[a[i]];
        e[dis[a[i]] + n].push_back(i);
    }
    FOR(i, 1, n * 2) sort(e[i].begin(), e[i].end());
    FORD(i, n, 1) {
        int u = a[i];
        //Case choose A first
        int newDist = dis[u] + 1 + n;
        int k = dis[u];
        auto jj = (lower_bound(e[newDist].begin(), e[newDist].end(), i));
        if (jj == e[newDist].end()) {
            if (k == 0) dp[u] = 2 + n - i;
            else {
                if (k > 0) dp[u] = 2 + n - i + k;
                else dp[u] = n - i + 1;
            }
        }
        else dp[u] = (*jj) - i + dp[a[(*jj)]];
        //Case choose B first
        newDist = k - 1 + n;
        jj = lower_bound(e[newDist].begin(), e[newDist].end(), i);
        if (jj == e[newDist].end()) {
            if (k == 0) {
                dp[u] = min(dp[u], 2 + n - i);
            }
            else {
                if (k > 0) dp[u] = min(dp[u], n - i + k + 1);
                else dp[u] = min(dp[u], n - i + 2);
            }
        }
        else dp[u] = min(dp[u], (*jj) - i + 1 + dp[a[(*jj)]]);
    }
    writeln(ok - 1 + dp[a[ok]]);
}
