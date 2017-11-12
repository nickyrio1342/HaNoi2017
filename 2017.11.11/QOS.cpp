#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 1001
#define pp pair<int, int>
#define IO cin.tie(NULL);cout.tie(NULL);
#define MOD (long long) (1e9 + 7)
#define bit(S, i) ((S >> i) & 1)
#define sz(a) (int) a.size()
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
		write(-x); return;
	}
	if (x < 10) {
		putchar(char(x + 48));
	}
	else {
		write(x / 10);
		putchar(char(48 + x % 10));
	}
}
template<typename T> inline void writeln(T x) {
	write(x);
	putchar('\n');
}
using namespace std;
 
int n, K, x;
vector<pp> a;
map<int, int, greater<int> > tab;
long long f[2][N];
int c[N + 1][N * 50 + 1];
 
void init() {
	FOR(i, 0, N) FOR(j, 0, N * 50) c[i][j] = 0;
	FOR(i, 0, N * 50) c[0][i] = 1;
	FOR(i, 1, N) {
		c[i][i] = 1;
		FOR(j, i + 1, 50 * N) c[i][j] = (c[i - 1][j - 1] + c[i][j - 1]) % MOD;
	}
}
 
void solve() {
	read(n); read(K);
	tab.clear();
	a.clear();
	REP(i, n) {
		read(x);
		tab[x]++;
	}
	for (auto x : tab) a.push_back(x);
	memset(f, 0, sizeof f);
	f[0][0] = 1;
	int used = 0;
	int d = 0;
	REP(i, sz(a) - 1) {// Type i
		d = 1 - d;
		int posEmpty = n - used;
		REP(j, K + 1) f[d][j] = 0;
		REP(j, min(K, used) + 1) {// j person died
			REP(k, min(K - j, a[i].second) + 1) { // choose k person died type i 
				f[d][j + k] = (f[d][j + k] + f[1 - d][j] * c[k][posEmpty - a[i].second + k - 1] % MOD) % MOD;
			}
 
		}
		used += a[i].second;
	}
	writeln(f[d][K]);
}
int main() {
	IO;
	int test;
	read(test);
	init();
	FOR(itest, 1, test) {
		printf("Case %d: ", itest);
		solve();
	}
} 
