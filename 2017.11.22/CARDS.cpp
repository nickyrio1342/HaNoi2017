#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 100100
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

void SetLink(Node *x, Node *y, bool right) {
    //y is child of x
    y -> parent = x;
    if (right) x -> right = y;
    else x -> left = y;
}
// Build tree (1..n)
Node * root, * NIL;
void BuildTree(int n) {
    NIL = new Node;
    *NIL = {NIL, NIL, NIL, 0, 0};
    root = new Node {NIL, NIL, NIL, 1, 1};
    FOR(i, 2, n) {
        Node * x = new Node{root, NIL, NIL, i, i};
        root -> parent = x;
        root = x;
    }
}

void Visit(Node * p) {
    if (p == NIL) return;
    Visit(p -> left);
    cout<<p ->key<<' ';
    Visit(p -> right);
}

inline void Update(Node *x) {
    x -> size = x -> left -> size + x -> right -> size + 1;
}
Node * Locate(Node * root, int k) {
    //Find i'th node in tree(root)
    if (root -> left -> size + 1 == k) return root;
    if (root -> left -> size >= k) return Locate(root -> left, k);
    else return Locate(root -> right, k - root -> left -> size - 1);
}

void UpTree(Node * x) {
    Node * y = x -> parent;
    Node * z = y -> parent;
    if (x == y -> left) {
        SetLink(y, x -> right, false);
        SetLink(x, y, true);
    }
    else {
        SetLink(y, x -> left, true);
        SetLink(x, y, false);
    }
    SetLink(z, x, z -> right == y);
    if (y != NIL) Update(y);
    if (x != NIL) Update(x);
}
/*
void Splay(Node * p) {
    while (p -> parent != NIL)
        UpTree(p);
}
*/
void Splay(Node * x) {
    do {
        if (x -> parent == NIL) return;
        Node * y = x -> parent;
        Node * z = y -> parent;
        if (z == NIL) UpTree(x);
        else {
            if ((z -> left == y) == (y -> left == x)) {
                UpTree(y);
                UpTree(x);
            }
            else {
                UpTree(x);
                UpTree(x);
            }
        }
    } while (true);
}
void Split(Node * T, int u, Node * &a, Node * &b) {
    if (u == 0) {
        a = NIL;
        b = T;
        return;
    }
    Node * x = Locate(T, u);
    Splay(x);
    a = x;
    b = x -> right;
    a -> right = NIL;
    b -> parent = NIL;
    if (a != NIL) Update(a);
}

Node * Join(Node *a, Node *b) {
    if (a == NIL) return b;
    while (a -> right != NIL) a = a -> right;
    Splay(a);
    SetLink(a, b, true);
    Update(a);
    return a;
}
int n, x;
int main() {
    IO;
    freopen("CARDS.inp","r",stdin);
    freopen("CARDS.out","w",stdout);
    read(n);read(x);
    BuildTree(n);
    while (x--) {
        int i, len, j;
        read(i); read(len); read(j);
        Node *L, *M, *R;
        Split(root, i - 1, L, M);
        Split(M, len, M, R);
        root = Join(L, R);
        Split(root, j - 1, L, R);
        root = Join(L, M);
        root = Join(M, R);
    }
    Visit(root);
}
