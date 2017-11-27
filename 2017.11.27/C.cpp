/*
              .,-:;//;:=,
          . :H@@@MM@M#H/.,+%;,
       ,/X+ +M@@M@MM%=,-%HMMM@X/,
     -+@MM; $M@@MH+-,;XMMMM@MMMM@+-
    ;@M@@M- XM@X;. -+XXXXXHHH@M@M#@/.
  ,%MM@@MH ,@%=             .---=-=:=,.
  =@#@@@MX.,       ___      -%HX$$%%%:;
 =-./@M@M$        |   )      .;@MMMM@MM:
 X@/ -$MM/        |    )      . +MM@@@M$
,@M@H: :@:        |  )         . =X#@@@@-
,@@@MMX, .        |\           /H- ;@M@M=
.H@@@@M@+,        | \         %MM+..%#$.
 /MMMM@MMH/.      |  \       X M@MH; =;
  /%+%$XHH@$=              , .H@@@@MX,
   .=--------.           -%H.,@@@@@MX,
   .%MM@@@HHHXX$$$%+- .:$MMX =M@@MM%.
     =XMMM@MM@MM#H;,-+HMM@M+ /MMMX=
       =%@M@M#@$-.=$@MM@@@M; %M%=
         ,:+$+-,/H#MMMMMMM@= =,
               =++%%%%+/:-.
*/
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<= b; ++i)
#define FORD(i, a, b) for (int i = a; i>=b; --i)
#define REP(i, a) for (int i = 0; i<a; ++i)
#define N 100100
#define pp pair<int, int>
#define bit(S, i) (((S) >> i) & 1)
#define IO ios::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
#define taskname ""
using namespace std;

struct edge {
  int u, v, cap, flow;
};
struct Dinic {
	vector<int> ptr, d;
	vector<vector<int> > g;
	vector<edge> e;
	queue<int> q;
	int n, s, t;

	void reset(int n) {
		this -> n = n;
		ptr.clear(); d.clear(); g.clear(); e.clear();
		ptr.resize(n); d.resize(n); g.resize(n);
	}

	void clear(int k) {
		while (e.size() > k) {
			edge ee = e.back();
			g[ee.u].pop_back();
			e.pop_back();
		}
		REP(i, e.size()) e[i].flow = 0;
	}
	void addEdge(int u, int v, int cap) {
		edge ee = {u, v, cap, 0};
		g[u].push_back(e.size());
		e.push_back(ee);
		ee = {v, u, 0, 0};
		g[v].push_back(e.size());
		e.push_back(ee);
	}

	int getMaxFlow(int s, int t) {
		this -> s = s;
		this -> t = t;
		int flow = 0;
		while (bfs()) {
			while (int x = dfs(s, 1e9)) {
				flow += x;
			}
		}
		return flow;
	}
private:
	bool bfs() {
		REP(i, n) { ptr[i] = 0; d[i] = -1; }
		d[s] = 0;
		q.push(s);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			//cerr<<g[u].size()<<endl;
			for (int id : g[u])
                if (e[id].flow < e[id].cap) {
				int v = e[id].v;
				if (d[v] == -1) {
					d[v] = d[u] + 1;
					q.push(v);
				}
			}
		}
		return d[t] != -1;
	}

	int dfs(int u, int flow) {
		if (u == t) return flow;
		for(;ptr[u] < g[u].size(); ++ptr[u]) {
			int id = g[u][ptr[u]];
			int v = e[id].v;
			if (e[id].flow < e[id].cap && d[v] == d[u] + 1) {
				if (int x = dfs(v, min(flow, e[id].cap - e[id].flow))) {
					e[id].flow += x;
					e[id^1].flow -= x;
					return x;
				}
			}
		}
		return 0;
	}
}D;
const int inf = 1e9;
int d[N];
int n, m;
vector<pp> e[N];
priority_queue<pp> heap;

void Dijkstra() {
	FOR(i, 1, n) d[i] = inf;
	d[1] = 0;
	heap.push(pp(0, 1));
	while (!heap.empty()) {
		int u = heap.top().second;
		int dist = -heap.top().first;
		heap.pop();
		if (d[u] != dist) continue;
		for (pp tt : e[u]) {
			int v = tt.first;
			int c = tt.second;
			if (d[v] > d[u] + c) {
				d[v] = d[u] + c;
				heap.push(pp(-d[v], v));
			}
		}
	}
}

void CreateFlow() {
	D.reset(n + 1);
	FOR(u, 1, n) {
		for (pp tt : e[u]) {
			int v = tt.first;
			int c = tt.second;
			if (d[v] == d[u] + c) {
				D.addEdge(v, u, 1);
			}
		}
	}
}
int a[N], c[N];
void Solve() {
	FOR(i, 1, n) a[i] = i;
	sort(a + 1, a + n + 1, [] (const int &a, const int &b) {return d[a] < d[b];});
	int bef = 1;

	int ans = 0;
	FOR(i, 1, n) {
		if (i == n || d[a[i]] < d[a[i + 1]]) {
			int tmp = D.e.size();
			FOR(j, bef, i) if (c[a[j]]) D.addEdge(0, a[j], c[a[j]]);
			ans += D.getMaxFlow(0, 1);
			D.clear(tmp);
			bef = i + 1;
		}
	}
	cout<<ans<<endl;
	//FOR(i, 1, n) cout<<d[i]<<endl;
}
int people;
void Enter() {
	cin>>n>>m>>people;
	int u, v, w;
	REP(i, m) {
		cin>>u>>v>>w;
		e[u].push_back(pp(v, w));
		e[v].push_back(pp(u, w));
	}
	REP(i, people) {
		cin>>w;
		c[w]++;
	}
}
int main() {
    //freopen(taskname".inp","r",stdin);
    //freopen(taskname".out","w",stdout);
    freopen("E:\\input.txt","r",stdin);
    freopen("E:\\out.txt","w",stdout);
    IO;
	Enter();
	Dijkstra();
	CreateFlow();
	Solve();
}
