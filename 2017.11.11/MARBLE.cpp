#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 1001000
#define pp pair<int, int>
#define IO ios::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
#define bit(S, i) ((S >> i) & 1)

using namespace std;

const long long MOD = 1e9 + 7;

int a[62][62];
struct matrix {
	long long t[62][62];
	void reset(int k) {
		REP(i, 62) REP(j, 62) t[i][j] = 0;
		if (!k) return;
		REP(i, 62) REP(j, 62) t[i][j] = a[i][j];
	}
}c, POW[64];

struct column {
	long long t[62];
	void reset(int k) {
		REP(i, 62) t[i] = 0;
		if (k) REP(i, 62) t[i] = 1;
	}
}d;
column operator* (const matrix &a, const column &b) {
	d.reset(0);
	REP(i, 62) REP(j, 62) {
		d.t[i] = (d.t[i] + a.t[i][j] * b.t[j] % MOD) % MOD;
	}
	return d;
}	
matrix operator* (const matrix &a, const matrix &b) {
	c.reset(0);
	REP(i, 62) REP(j, 62) REP(k, 62) {
		c.t[i][j] = (c.t[i][j] + a.t[i][k] * b.t[k][j] % MOD) % MOD;
	}
	return c;
}

long long m, n, k;

int idx(char c) {
	if ('a' <= c && c <= 'z') return c - 'a';
	if ('A' <= c && c <= 'Z') return c - 'A' + 26;
	return c - '0' + 52;
}

map<long long, bitset<62>> tab;

void initPOW() {
	POW[0].reset(1);
	FOR(i, 1, 63) POW[i] = POW[i - 1] * POW[i - 1];
}

void Up(column &res, long long level) {
	REP(i, 62) if (bit(level, i)) {
		res = POW[i] * res;
	}
}

int main() {
	IO;
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	cin >> n >> m >> k;
	char x, y;
	REP(i, 62) REP(j, 62) a[i][j] = 1;
	while (m--) {
		cin >> x >> y;
		a[idx(x)][idx(y)] = a[idx(y)][idx(x)] = 0;
	}
	initPOW();
	REP(i, k) {
		int type;
		long long pos;
		bitset<62> status;
		cin >> type >> pos >> x;
		if (type) {
			status.reset();
			status.set(idx(x));
		}
		else {
			status.set();
			status.reset(idx(x));
		}
		if (tab.find(pos) == tab.end()) tab[pos] = status;
		else tab[pos] &= status;
	}
	long long now = 1;
	column res; res.reset(1);
	for (auto query : tab) {
		if (query.first == 1) {
			REP(i, 62) if ((int)query.second.test(i)) {} else res.t[i] = 0;
			continue;
		}
		if (now < query.first - 1) Up(res, query.first - 1 - now);
		now = query.first;
		column temp; temp.reset(0);
		REP(i, 62) if (query.second[i]) {
			REP(j, 62) if (a[j][i]) {
				temp.t[i] = (temp.t[i] + res.t[j]) % MOD;
			}
		}
		res = temp;
	}
	if (now < n) Up(res, n - now);
	long long ans = 0;
	long long tmp = 1;
	//REP(i, 1000) tmp = tmp * 62 % MOD;
	REP(i, 62) {
		ans = (ans + res.t[i]) % MOD;
		//cout << res.t[i] << ' ';
	}
	cout << ans;
}
