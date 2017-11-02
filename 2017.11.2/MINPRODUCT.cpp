#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 100100
#define pp pair<int, int>
#define IO cin.tie(NULL);cout.tie(NULL);

using namespace std;

int n;
long long a[N];

int main() {
    IO;
    freopen("MINPRODUCT.inp","r",stdin);
    freopen("MINPRODUCT.out","w",stdout);
    scanf("%d", &n);
    REP(i, n) {
        scanf("%lld", &a[i]);
    }
    sort(a, a + n);

    printf("%lld", min(a[n - 1] * a[n - 2],min(a[0] * a[1], a[0] * a[n - 1])));
}

