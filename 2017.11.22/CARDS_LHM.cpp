#include <iostream>
#include <cstdio>
using namespace std;
#define taskname "CARDS"
const int maxN = 1e5;
struct TNode
{
    int Value, Size;
    TNode *P, *L, *R;
};
TNode NodeMemory[maxN], *Alloc = &NodeMemory[0];
TNode Sentinel, *nil, *root;
int n, x;

inline void SetL(TNode* Parent, TNode* Child)
{
    Parent->L = Child;
    Child->P = Parent;
}

inline void SetR(TNode* Parent, TNode* Child)
{
    Parent->R = Child;
    Child->P = Parent;
}

inline void SetC(TNode* Parent, TNode* Child, bool InRight)
{
    if (InRight) SetR(Parent, Child);
    else SetL(Parent, Child);
}

inline void Update(TNode* x)
{
    x->Size = x->L->Size + x->R->Size + 1;
}

inline void UpTree(TNode* x)
{
    TNode* y = x->P;
    TNode* z = y->P;
    if (x == y->L)
    {
        SetL(y, x->R);
        SetR(x, y);
    }
    else
    {
        SetR(y, x->L);
        SetL(x, y);
    }
    SetC(z, x, z->R == y);
    Update(y);
    Update(x);
}

inline void Splay(TNode* x)
{
    do
    {
        TNode* y = x->P;
        if (y == nil) break;
        TNode*  z = y->P;
        if (z != nil)
            if ((y == z->L) == (x == y->L)) UpTree(y);
            else UpTree(x);
        UpTree(x);
    }
    while (true);
}

inline TNode* Locate(TNode* x, int i)
{
    do
    {
        int s = x->L->Size + 1;
        if (s == i) return x;
        if (i < s) x = x->L;
        else
        {
            i -= s;
            x = x->R;
        }
    }
    while (true);
}

void Enter()
{
    cin >> n >> x;
    nil = &Sentinel;
    *nil = {0, 0, nil, nil, nil};
    root = nil;
    for (int i = 1; i <= n; i++)
    {
        TNode* x = Alloc++;
        *x = {i, i, nil, root, nil};
        root->P = x;
        root = x;
    }
}

inline void Split(TNode* x, int i, TNode* &a, TNode* &b)
{
    if (i == 0)
    {
        a = nil; b = x;
        return;
    }
    x = Locate(x, i); Splay(x);
    a = x; b = x->R;
    a->R = nil; Update(a);
    b->P = nil;
}

inline TNode* Join(TNode* a, TNode* b)
{
    if (a == nil) return b;
    while (a->R != nil) a = a->R;
    Splay(a);
    SetR(a, b);
    Update(a);
    return a;
}

void Print(TNode* x)
{
    if (x == nil) return;
    Print(x->L);
    cout << x->Value << ' ';
    Print(x->R);
}

void Solve()
{
    for (; x > 0; x--)
    {
        int i, m, j;
        cin >> i >> m >> j;
        TNode *a, *b, *c;
        Split(root, i - 1, a, b);
        Split(b, m, b, c);
        root = Join(a, c);
        Split(root, j - 1, a, c);
        root = Join(Join(a, b), c);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen(taskname".inp", "r", stdin);
    freopen(taskname".out", "w", stdout);
    Enter();
    Solve();
    Print(root);
}
