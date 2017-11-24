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

inline void Update(Node *p) {
    p -> size = 1 + p -> right -> size + p -> left -> size;
}
Node *root, *nil;

inline void SetLink(Node *x, Node *y, bool right) {
    y -> parent = x;
    if (right) x -> right = y;
    else x -> left = y;
}

inline Node * Locate(Node *T, int k) {
    if (T -> left -> size + 1 == k) return T;
    if (T -> left -> size >= k) return Locate(T -> left, k);
    return Locate(T -> right, k - T -> left -> size - 1);
}
char s[N * 2];
inline void Build(int n) {
    nil = new Node{};
    *nil = Node{nil, nil, nil, 0, 0};
    root = nil;
    REP(i, n) {
        Node *x = new Node{root, nil, nil, s[i], i + 1};
        SetLink(x, root, false);
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
        if (y == nil)
            return;
        Node *z = y -> parent;
        if (z != nil) {
            if ((z -> left == y) == (y -> left == x)) UpTree(y);
            else UpTree(x);
        }
        UpTree(x);
    } while (true);
}

inline void Split(Node *T, int u, Node * &a, Node * &b) {
    if (u == 0) {
        a = nil; b = T; return;
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
vector<char> res;
void Visit(Node *p) {
    if (p == nil) return;
    Visit(p -> left);
    res.push_back(char(p -> key));
    Visit(p -> right);
}

int main() {
    IO;
    freopen("SO.inp","r",stdin);
    freopen("SO.out","w",stdout);
    scanf("%s", &s);
    int n = strlen(s);
    REP(i, n) s[n + n - i - 1] = s[i];
    n *= 2;
    Build(n);
    int m;
    read(m);
    while (m--) {
        int i, j, invert_i, invert_j;
        read(i);read(j);
        int len = j - i + 1;
        invert_i = n - i + 1;
        invert_j = n - j + 1;
        Node *L, *M, *R, *IL, *IR;
        Split(root, invert_j - 1, L, R);
        Split(R, len, IL, IR);
        Split(L, i - 1, L, M);
        Split(M, len, M, R);
        root = Join(L, IL);
        root = Join(root, R);
        root = Join(root, M);
        root = Join(root, IR);

    }
    Visit(root);
    REP(i, n / 2) putchar(res[i]);
}
