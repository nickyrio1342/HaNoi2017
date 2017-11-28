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

char s[N];
vector<int>H, M;
int main() {
    IO;
 //   freopen("input.txt","r",stdin);
  //  freopen("output.txt","w",stdout);
    int n;
    read(n);
    scanf("%s", &s);
    int cntH = 0, cntM = 0;
    if (n == 1) {
        putchar('H');putchar('M');
        return 0;
    }
    REP(i, n - 1) {
        if (s[i] == 'H') {
            cntH++; H.push_back(i);
        }
        else {
            cntM++; M.push_back(i);
        }
    }
    if (cntH > cntM) {
        putchar('H');
    }
    if (cntH < cntM) {
        putchar('M');
    }
    if (cntH == cntM) {
        if (s[n - 2] == 'H') putchar('M');
        else putchar('H');
    }
}
