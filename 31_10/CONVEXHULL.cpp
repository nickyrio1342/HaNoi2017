#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 1001000
#define pp pair<long long, long long>
#define IO ios::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
#define x first
#define y second
#define sz(a) (int) a.size()

using namespace std;

int n;
pp s[N];

long long ccw(pp a, pp b, pp c) {
    return (c.y - b.y) * (b.x - a.x) - (c.x - b.x) * (b.y - a.y);
}
vector<int> e;

void ConvexHull() {
    REP(i, n) {
        while (sz(e) >= 2 && ccw(s[e[sz(e) - 2]], s[e[sz(e) - 1]], s[i]) <= 0) e.pop_back();
        e.push_back(i);
    }
    int t = sz(e) + 1;
    FORD(i, n - 2, 0) {
        while (sz(e) >= t && ccw(s[e[sz(e) - 2]], s[e[sz(e) - 1]], s[i]) <= 0) e.pop_back();
        e.push_back(i);
    }

}

long long CC (pp a, pp b) {
    return a.x * b.y - a.y * b.x;
}
void Area() {
    long long ans = 0;
    REP(i, sz(e) - 1) {
        ans += CC(s[e[i]], s[e[i + 1]]);
    }
    ans = abs(ans);
    if (ans % 2) {
        cout<<ans/2<<".5";
    } else cout<<ans/2<<".0";
    cout<<endl;
}
int main() {
    freopen("CONVEXHULL.inp","r",stdin);
    freopen("CONVEXHULL.out","w",stdout);
    IO;
    cin>>n;
    REP(i, n) cin>>s[i].y>>s[i].x;
    sort(s, s + n);
    ConvexHull();
    cout<<e.size() - 1<<endl;
    reverse(e.begin(), e.end());
    Area();
    REP(i, e.size() - 1) cout<<s[e[i]].y<<' '<<s[e[i]].x<<endl;
}
