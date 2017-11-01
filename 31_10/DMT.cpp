#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 1000001
#define pp pair<int, int>
#define IO cin.tie(NULL);cout.tie(NULL);

using namespace std;

bool NT[N];
vector<int> prime, tab;
void Eratos() {
    FOR(i, 2, N - 1) {
        if (!NT[i]) {
            prime.push_back(i);
            if (1ll * i * i >= N) continue;
            for (int j = i * i; j < N; j += i) NT[j] = true;
        }
    }

}
long long a, b;
int main() {
    freopen("DMT.inp","r",stdin);
    freopen("DMT.out","w",stdout);
    IO;
    Eratos();
    REP(i, prime.size() - 1) if (i != 1) if (3ll * prime[i] >= N) break;
    else tab.push_back(3 * prime[i]);
    sort(tab.begin(), tab.end());
    int test;
    scanf("%d", &test);
    while (test--) {
        scanf("%lld %lld", &a, &b);
        if (b < 36) {
            printf("0\n");continue;
        }
        if (a == 1) a++;
        long long ans = 0;
        if (a <= 6561 && 6561 <= b) ans++;
        int bb = (int) sqrt(b);
        int aa = ceil(sqrt(a));
        if (aa <= bb) ans += upper_bound(tab.begin(), tab.end(), bb) - lower_bound(tab.begin(), tab.end(), aa);
        printf("%lld\n", ans);
    }
}
