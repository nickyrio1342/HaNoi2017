#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 1111
#define pp pair<int, int>
#define IO ios::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
#define bit(S, i) ((S >> i) & 1)
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

string s[N];
int n, k;
bool END[N];

int main() {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    IO;
    cin>>n>>k;
    REP(i, n)
        cin>>s[n - i - 1];
    int ii = 0;
    if (k == 1) {
        cout<<"0 0 "<<n<<' '<<n;
        return 0;
    }
    END[n] = true;
    FORD(i, n - 1, 0) {
        bool ok = true;
        REP(j, n) if (s[i][j] == 'x') ok = false;
        END[i] = END[i + 1] & ok;
    }

    REP(i, n) {
        int cnt = 0, jj = 0;
        REP(j, n) if (s[i][j] == 'x') cnt++;
        if (cnt == 0) continue;
        if (cnt == 1) {
            if (END[i + 1]) {
                cout<<0<<' '<<ii<<' '<<n<<' '<<n;
                return 0;
            }
            else {
                cout<<0<<' '<<ii<<' '<<n<<' '<<i + 1<<'\n';
                ii = i + 1;
                k--;
            }
        }
        else {
            int jj = 0;
            REP(j, n) if (s[i][j] == 'x') {
                k--;cnt--;
                if (END[i + 1]) {
                    if (k == 1) {
                        cout<<jj<<' '<<ii<<' '<<j + 1<<' '<<n<<'\n';
                        cout<<j + 1<<' '<<ii<<' '<<n<<' '<<n<<'\n';
                        return 0;
                    }
                    if (cnt) cout<<jj<<' '<<ii<<' '<<j + 1<<' '<<n<<'\n';
                    else cout<<jj<<' '<<ii<<' '<<n<<' '<<n<<'\n';
                    jj = j + 1;
                }
                else {
                    if (k == 1) {
                        cout<<jj<<' '<<ii<<' '<<n<<' '<<i + 1<<'\n';
                        cout<<0<<' '<<i + 1<<' '<<n<<' '<<n<<'\n';
                        return 0;
                    }
                    if (cnt) cout<<jj<<' '<<ii<<' '<<j + 1<<' '<<i + 1<<'\n';
                    else cout<<jj<<' '<<ii<<' '<<n<<' '<<i + 1<<'\n';
                    jj = j + 1;
                }
            }
            ii = i + 1;
        }
    }
}
