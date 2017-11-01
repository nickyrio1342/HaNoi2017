/* Nhận xét:
    1, Việc sắp từng hàng và từng cột độc lập với nhau.
    2, Tính chất trung vị
*/
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 100100
#define pp pair<int, int>
#define IO ios::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);

using namespace std;

vector<long long> x, y;
int n;

bool prime(int n) {
    FOR(i, 2, sqrt(n)) if (n % i == 0) return false;
    return true;
}

void solve1() {// If n prime
    REP(i, n) {
        cin>>x[i]>>y[i];
    }
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    long long row = x[n / 2];
    long long col = y[n / 2];
    //Into a row
    long long ans = 0;
    REP(i, n) ans += abs(row - x[i]);
    FORD(i, n / 2, 0) ans += abs(y[i] - (col + i  - n / 2));
    FOR(i, n / 2 + 1, n - 1) ans += abs(y[i] - (col + i - n / 2));
    long long res = ans;
    //Into a column
    ans = 0;
    REP(i, n) ans += abs(col - y[i]);
    FORD(i, n / 2, 0) ans += abs(x[i] - (row + i - n / 2));
    FOR(i, n / 2 + 1, n - 1) ans += abs(x[i] - (row + i - n / 2));
    res = min(res, ans);
    cout<<res;
}

long long cal(vector<long long> x, int k) {
    vector<int> e;e.clear();
    REP(i, x.size()) e.push_back(x[i] - i / k);
    sort(e.begin(), e.end());
    long long ans = 0;
    long long med = e[e.size() / 2];
    for (long long x : e) ans += abs(med - x);
    return ans;
}

void solve2() {
    REP(i, n) {
        cin>>x[i]>>y[i];
    }
    long long res = 1e18;
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    FOR(i, 1, sqrt(n)) if (n % i == 0) {
        res = min(res, cal(x, i) + cal(y, n / i));
        res = min(res, cal(x, n / i) + cal(y, i));
    }
    cout<<res;
}
int main() {
    IO;
    freopen("QUEUE.inp","r",stdin);
    freopen("QUEUE.out","w",stdout);
    cin>>n;
    x.resize(n);
    y.resize(n);
    solve2();
    return 0;
}
