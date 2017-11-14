/*
  + Sử dụng QHĐ theo từng chữ số, lưu số dư
  + Chuyển đổi sang hệ cơ số 2 để tăng tốc độ chuyển trạng thái
*/
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

const long long MOD = 1e9;
int a[5], n, m;
bool used[33][64][5][10];
long long dp[33][64][5][10];

bool ok(int u, int status, int add, int S, int newAdd) {
    int tmp = newAdd;
    REP(i, 5) if (!bit(status, i) && bit(S, i) > bit(a[i], u)) return false;
    else tmp += bit(S, i);
    return add == tmp / 2 ;
}

long long cal(int u, int status, int add, int mod9) {// bit i == 0 -> All digits before u of i'th element is the same a[i]
    if (u == -1) {
        if (mod9 || add) return 0;
        return 1;
    }
    if (used[u][status][add][mod9]) return dp[u][status][add][mod9];
    used[u][status][add][mod9] = true;
    long long res = 0;
    REP(S, 32) REP(newAdd, 5) if (ok(u, status, add, S, newAdd)) {
        int now = newAdd;
        int newStatus = status;
        REP(i, 5) if (bit(S, i)) {
            now++;
        }
        else {
            if (!bit(status, i) && bit(S, i) < bit(a[i], u)) {
                newStatus += 1 << i; // Set bit 1 for i'th bit
            }
        }
        if (!bit(status, 5)) {
            if ((now % 2) < bit(m, u)) newStatus += 1 << 5;
            else {
                if ((now % 2) > bit(m, u)) continue;
            }
        }
        res += cal(u - 1, newStatus, newAdd, ((mod9 * 2) + (now % 2)) % 9);
        if (res >= MOD) res -= MOD;
    }
    dp[u][status][add][mod9] = res;
    return res;
}

int main() {
    IO;
    freopen("VUIVE9.inp","r",stdin);
    freopen("VUIVE9.out","w",stdout);
    memset(a, 0, sizeof a);
    read(n); read(m);
    REP(i, n) read(a[i]);
    memset(used, false, sizeof used);
    writeln(cal(31, 0, 0, 0));
}
