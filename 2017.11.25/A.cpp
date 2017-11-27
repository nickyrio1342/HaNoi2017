#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 1001000
#define pp pair<int, int>
#define IO ios::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
#define bit(S, i) (((S) >> i) & 1)
using namespace std;

int n;
int main() {
    IO;
    cin>>n;//read(n);
    int mxx = 2e9, mxy = 2e9, mnx = -2e9, mny = -2e9;
    REP(i, n) {
        int x1 = 2e9, x2 = -2e9, y1 = 2e9, y2 = -2e9, xx, yy;
        REP(j, 4) {
            cin>>xx>>yy;//read(xx);read(yy);
            int x = xx - yy, y = xx + yy;
            x1 = min(x1, x);
            x2 = max(x2, x);
            y1 = min(y1, y);
            y2 = max(y2, y);
        }
        mxx = min(mxx, x2);
        mxy = min(mxy, y2);
        mnx = max(mnx, x1);
        mny = max(mny, y1);
    }
    mxx--;mxy--;mnx++;mny++;
    //cerr<<mxx<<' '<<mnx<<' '<<mxy<<' '<<mny<<endl;
    int row = (mxx - mnx + 1);
    int col = (mxy - mny + 1);
    //cerr<<row<<' '<<col<<endl;
    if (row <= 0 || col <= 0) {
        cout<<0 ;return 0;
    }
    long long ans = 0;
    int roweven, rowodd = roweven = row / 2;
    int coleven, colodd = coleven = col / 2;
    if (((mnx % 2 + 2) % 2) == ((mxx % 2) + 2) % 2) {
        if (((mnx % 2) + 2) % 2) rowodd++;
        else roweven++;
    }
    if (((mny % 2 + 2) % 2) == ((mxy % 2) + 2) % 2) {
        if ((mny % 2 + 2) % 2) colodd++;
        else coleven++;
    }
    cerr<<coleven<<' '<<colodd<<endl;

    cerr<<roweven<<' '<<rowodd<<endl;
    ans = 1ll * coleven * roweven + 1ll * colodd * rowodd;
    cout<<ans;
}
