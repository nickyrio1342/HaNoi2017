/*
Chúng ta sẽ sort danh sách kề của mỗi đỉnh tăng dần theo trọng số của cạnh.
...
Không biết nên nói gì tiếp theo...
*/
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 100100
#define pp pair<long long, int>
#define IO cin.tie(NULL);cout.tie(NULL);
#define bit(S, i) ((S >> i) & 1)

using namespace std;

struct edge {
    int u, v, c, realCost;
};
vector<edge> e;
vector<vector<int> > g;
int n, m;
bool cmp(const int &a, const int &b) {
    return e[a].c < e[b].c;
}
priority_queue<pp> heap;
vector<vector<pp> > newE;
vector<long long> d;

void Dijkstra() {
    REP(i, m * 4) d[i] = 1e18;
    int tmp = g[0][0];
    d[tmp ^ 1] = 0;
    heap.push(pp(0, tmp ^ 1));
    while (!heap.empty()) {
        int id = heap.top().second;
        long long dist = -heap.top().first;
        heap.pop();
        if (dist != d[id]) continue;
        int id2 = id;
        if (id >= 2 * m) id2 -= 2 * m;
        if (e[id2].v == n + 1) {
            printf("%lld", dist);
            return;
        }
        for (pp tt : newE[id]) {
            int v = tt.first;
            int v2 = v;
            if (v2 >= 2 * m) v2 -= 2 * m;
            edge tmp = e[v2];
            int c = tt.second;
            if (d[v] > d[id] + c) {
                d[v] = d[id] + c;
                heap.push(pp(-d[v], v));
            }
        }
    }
}

int main() {
    IO;
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d %d", &n, &m);
    int u, v, c;
    g.resize(n + 2);
    d.resize(m * 4 + 10);
    newE.resize(m * 4 + 10);
    REP(i, m) {
        scanf("%d %d %d", &u, &v, &c);
        edge ee = {u, v, c, c};
        g[u].push_back(e.size());
        e.push_back(ee);
        ee = {v, u, c, c};
        g[v].push_back(e.size());
        e.push_back(ee);
    }
    edge ee = {0, 1, 0, 0};
    g[0].push_back(e.size());
    e.push_back(ee);
    ee = {1, 0, 0, 0};
    g[1].push_back(e.size());
    e.push_back(ee);
    ee = {n, n + 1, 0, 0};
    g[n].push_back(e.size());
    e.push_back(ee);
    ee = {n + 1, n, 0, 0};
    g[1 + n].push_back(e.size());
    e.push_back(ee);
    m += 2;
    FOR(i, 0, n + 1) sort(g[i].begin(), g[i].end(), cmp);
    // id : Increase cost
    // id + m * 2 : Decrease cost
    FOR(i, 0, n + 1) {
        REP(j, -1 + (int)g[i].size()) {
            // Remember that add (int) before a.size()
            // Because when a.size() == 0, a.size() - 1 is not exist.
            int id = g[i][j];
            int v_id = g[i][j + 1];
            //Increase cost
            newE[id].push_back(pp(v_id, e[v_id].c - e[id].c));
            //Decrease cost
            newE[v_id + 2 * m].push_back(pp(id + 2 * m, 0));
        }
        REP(j, g[i].size()) {
            int id = g[i][j];
            newE[id].push_back(pp(id ^ 1, e[id].c));
            newE[id].push_back(pp(2 * m + (id ^ 1), e[id].c));
            newE[id + 2 * m].push_back(pp(id ^ 1, e[id].c));
            newE[id + 2 * m].push_back(pp(2 * m + (id ^ 1), e[id].c));
        }
    }
    Dijkstra();
}
