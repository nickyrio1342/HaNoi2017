//Subtask 1, 2 : BFS lưu trạng thái
//Subtask 3:
/* Nhận xét rằng mỗi lần sắp xếp thì trạng thái mới chia ra làm một số cụm, mỗi cụm thì cùng giá trị tại cột k.
Mỗi lần sắp xếp thì việc chọn k chỉ điều kiển được các cụm, còn các thành phần trong cụm do những thằng k' trước quy định
-> Những thằng K giống nhau bị thừa (Vd : 5 1 3 1 5 thì đơn giản hóa còn 3 1 5) -> Chỉ sort mỗi cột 1 lần.
-> DPT : 9! * 9 * chi phí sắp xếp, kiểm tra
*/
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 100100
#define IO ios::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);

#define pp pair<int, int>

using namespace std;

int m, n, s;

vector<int> vec() {
    vector<int> res;res.clear();
    FOR(i, 1, m) res.push_back(i);
    return res;
}

vector<vector<int> > tab, a;
int k;
bool cmp(const pp &aa, const pp &bb) {
    return  (a[aa.first - 1][k] < a[bb.first - 1][k])
    || (a[aa.first - 1][k] == a[bb.first - 1][k] && aa.second < bb.second);
}

vector<int> sort(vector<int> e) {

    REP(i, m - 1) FORD(j, m - 1, i + 1) {
        if (a[e[j] - 1][k] < a[e[j - 1] - 1][k]) swap(e[j - 1], e[j]);
    }/*
    sort(e.begin(), e.end(), cmp);
    REP(i, m) e[i].second = i; */
    return e;
}

vector<int> now2;
bool check(vector<int> now) {
    REP(i, m) REP(j, n) if (tab[i][j] != a[now[i] - 1][j]) return false;
    return true;
}

struct data {
    string st;
    vector<int> status;
};

queue<data> q;

void bfs() {
    data t;
    t.st = "";
    t.status = vec();
    q.push(t);
    while (!q.empty()) {
        data u = q.front();
        q.pop();
        if (check(u.status)) {
            cout<<u.st.size()<<endl;
            for (char c : u.st) cout<<c<<' '; return;
        }
        bool mark[10];
        memset(mark, false ,sizeof mark);
        for (char c : u.st) mark[c - '0'] = true;
        REP(i, n) if (!mark[i + 1]){
            k = i;
            vector<int> nxt = sort(u.status);
            string NEW = u.st + char(49 + i);
            q.push(data({NEW, nxt}));
        }
    }
}

int main() {
    freopen("SCTAB.inp","r",stdin);
    freopen("SCTAB.out","w",stdout);
    IO;
    cin>>m>>n>>s;
    tab.resize(m);
    REP(i, m) {
        tab[i].resize(n + 1);
        REP(j, n) cin>>tab[i][j];
        tab[i][n] = i;
    }
    a = tab;
    int x;
    REP(i, m) now2.push_back(i + 1);
    while (s--) {
        cin>>x;
        k = x - 1;
        now2 = sort(now2);
    }
    REP(i, m) {
        REP(j, n) tab[i][j] = a[now2[i] - 1][j];
    }
    bfs();return 0;
}
