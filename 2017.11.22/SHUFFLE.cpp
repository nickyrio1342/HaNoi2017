#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 1001000
#define pp pair<int, int>
#define IO cin.tie(NULL);cout.tie(NULL);
#define bit(S, i) (((S) >> i) & 1)
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
        write(-x);return;
    }
    if (x < 10) {
        putchar(char(x + 48));
    }
    else {
        write(x/10);
        putchar(char(48 + x%10));
    }
}
template<typename T> inline void writeln(T x) {
    write(x);
    putchar('\n');
}
using namespace std;

struct Node {
    Node *left, *right, *parent;
    int key, size;
};

inline void SetLink(Node *a, Node *b, bool right) {
    b -> parent = a;
    if (right) a -> right = b;
    else a -> left = b;
}

inline void Update(Node *a) {
    a -> size = 1 + a -> left -> size + a -> right -> size;
}
Node *root, *nil, *pos[N];
void Build(int n) {
    nil = new Node{};
    *nil = {nil, nil, nil, 0, 0};
    root = nil;
    FOR(i, 1, n) {
        Node *x = new Node{root, nil, nil, i, i};
        SetLink(x, root, false);
        pos[i] = x;
        root = x;
    }
}

inline void UpTree(Node *x) {
    Node *y = x -> parent;
    Node *z = y -> parent;
    if (y -> left == x) {
        SetLink(y, x -> right, false);
        SetLink(x, y, true);
    }
    else {
        SetLink(y, x -> left, true);
        SetLink(x, y, false);
    }
    SetLink(z, x, z -> right == y);
    if (y != nil) Update(y);
    if (x != nil) Update(x);
}

inline void Splay(Node *x) {
    do {
        Node *y = x -> parent;
        if (y == nil) return;
        Node *z = y -> parent;
        if (z != nil) {
            if ((z -> left == y) == (y -> left == x)) UpTree(y);
            else UpTree(x);
        }
        UpTree(x);
    } while (true);
}
inline Node * Locate(Node *x, int k) {
    if (x -> left -> size + 1 == k) return x;
    if (x -> left -> size >= k) return Locate(x -> left, k);
    return Locate(x -> right, k - x -> left -> size - 1);
}

inline void Split(Node *T, int u, Node * &a, Node * &b) {
    if (u == 0) {
        a = nil;
        b = T;return;
    }
    Node *x = Locate(T, u);
    Splay(x);
    a = x;
    b = x -> right;
    a -> right = nil;
    b -> parent = nil;
    if (a != nil) Update(a);
}

inline Node * Join(Node *a, Node *b) {
    if (a == nil) return b;
    while (a -> right != nil) a = a -> right;
    Splay(a);
    SetLink(a, b, true);
    if (a != nil) Update(a);
    return a;
}

inline int At(int k) {
    Node *x = pos[k];
    Splay(root = x);
    return x -> left -> size + 1;
}

int dp[N];
struct FenwickTree {
    vector<int> BIT;
    int n;
    void reset(int n) {
        this -> n = n;
        BIT.clear(); BIT.resize(n + 1);
    }

    void Up(int u, int p) {
        for (; u <= n; u += u&-u) {
            if (dp[BIT[u]] < dp[p]) BIT[u] = p;
        }
    }

    int GetPos(int u) {
        int ans = 0;
        for(; u > 0; u -= u&-u) {
            if (dp[BIT[u]] > dp[ans]) ans = BIT[u];
        }
        return ans;
    }
}BIT;
vector<int> a;
int trace[N];

void Visit(Node *p) {
    if (p == nil) return;
    Visit(p -> left);
    a.push_back(p -> key);
    Visit(p -> right);
}
set<int> used;

int main() {
    IO;
    freopen("SHUFFLE.inp","r",stdin);
    freopen("SHUFFLE.out","w",stdout);
    int n, m;
    read(n); read(m);
    Build(n);
    while (m--) {
        int i, j;
        read(i);read(j);
        Node *L, *R, *M;
        Split(root, i - 1, L, M);
        Split(M, 1, M, R);
        root = Join(L, R);
        Split(root, j - 1, L, R);
        root = Join(Join(L, M), R);
    }
    a.push_back(0);
    Visit(root);
    BIT.reset(n);
    int ans = 0;
    FOR(i, 1, n) {
        int p = BIT.GetPos(a[i]);
        dp[i] = dp[p] + 1;
        trace[i] = p;
        if (dp[ans] < dp[i]) ans = i;
        BIT.Up(a[i], i);
    }
    writeln(n - dp[ans]);
    int t = ans;
    while (t != 0) {
        used.insert(a[t]);
        t = trace[t];
    }
    int now = n;
    ans = n - dp[ans];
    while (ans) {
        Node *x = Locate(root, now);
        if (used.find(x -> key) == used.end()) {

            ans--;
            Node *L, *R, *M;
            Split(root, now - 1, L, M);
            Split(M, 1, M, R);
            root = Join(L, R);
            //
            int p;
            auto PREV = used.lower_bound(x -> key);
            if (PREV == used.begin()) p = 1;
            else {
                PREV--;
                p = At(*PREV) + 1;
            }
            write(now);putchar(' ');writeln(p);
            Split(root, p - 1, L, R);
            root = Join(Join(L, M), R);
            used.insert(x -> key);
        } else now--;
    }
}
