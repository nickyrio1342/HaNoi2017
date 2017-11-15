#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 100100
#define pp pair<int, int>

using namespace std;
double a, b, s, m, n;
const double pi = acos(-1);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    while (true) {
        cin>>a>>b>>s>>n>>m;
        if (a == 0 && b == 0 && s == 0 && n == 0 && m == 0) return 0;
        double alpha = atan(m * b / (a * n));
        double x = b / (2 * sin(alpha));
        alpha = alpha / pi * 180;
        double speed = (x * m * 2) / s;
        cout<<fixed<<setprecision(2)<<alpha<<' '<<fixed<<setprecision(2)<<speed<<endl;
    }
}
