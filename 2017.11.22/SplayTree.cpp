#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 100100
#define pp pair<int, int>
#define IO cin.tie(NULL);cout.tie(NULL);
#define bit(S, i) (((S) >> i) & 1)
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

void Splay(Node * p) {
    while (p -> parent != NIL) UpTree(p);
}

void Split(Node * T, int u, Node * a, Node * b) {
    if (u == 0) {
        a = NIL;
        b = T;
        return;
    }
    Node * x = Locate(T, u);
    Splay(x);
    a = x;
    a -> right = NIL;
    b = x -> right;
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

int main() {
    //freopen("output.txt","w",stdout);
    int n;
    cin>>n;
    BuildTree(n);
    //Visit(root);
    FOR(i, 1, n) {
        Node * x = Locate(root, i);
        cout<<x -> key<<' ';
    }
    UpTree(Locate(root, n / 2));
    FOR(i, 1, n) {
        Node * x = Locate(root, i);
        cout<<x -> key<<' ';
    }
}
