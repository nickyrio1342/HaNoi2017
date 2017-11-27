/*
              .,-:;//;:=,
          . :H@@@MM@M#H/.,+%;,
       ,/X+ +M@@M@MM%=,-%HMMM@X/,
     -+@MM; $M@@MH+-,;XMMMM@MMMM@+-
    ;@M@@M- XM@X;. -+XXXXXHHH@M@M#@/.
  ,%MM@@MH ,@%=             .---=-=:=,.
  =@#@@@MX.,                -%HX$$%%%:;
 =-./@M@M$                   .;@MMMM@MM:
 X@/ -$MM/                    . +MM@@@M$
,@M@H: :@:                    . =X#@@@@-
,@@@MMX, .                    /H- ;@M@M=
.H@@@@M@+,                    %MM+..%#$.
 /MMMM@MMH/.                  XM@MH; =;
  /%+%$XHH@$=              , .H@@@@MX,
   .=--------.           -%H.,@@@@@MX,
   .%MM@@@HHHXX$$$%+- .:$MMX =M@@MM%.
     =XMMM@MM@MM#H;,-+HMM@M+ /MMMX=
       =%@M@M#@$-.=$@MM@@@M; %M%=
         ,:+$+-,/H#MMMMMMM@= =,
               =++%%%%+/:-.
It looks like Google Chrome, right?
*/
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<= b; ++i)
#define FORD(i, a, b) for (int i = a; i>=b; --i)
#define REP(i, a) for (int i = 0; i<a; ++i)
#define N 55
#define pp pair<int, int>
#define bit(S, i) (((S) >> i) & 1)
#define IO ios::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
#define taskname "subrev"
using namespace std;

int n, a[N], used[N][N][N][N], dp[N][N][N][N];

int cal(int l, int r, int mn, int mx) {
    if (l > r) return 0;
    if (l == r) {
        if (mn <= a[l] && a[l] <= mx) return 1;
        return 0;
    }
    if (used[l][r][mn][mx]) return dp[l][r][mn][mx];
    used[l][r][mn][mx] = true;
    int best = 0;
    best = max(best, cal(l + 1, r, mn, mx));
    best = max(best, cal(l, r - 1, mn, mx));
    if (mn <= a[l] && a[l] <= mx) {
        best = max(best, cal(l + 1, r, a[l], mx) + 1);
    }
    if (a[r] <= mx && a[r] >= mn) {
        best = max(best, cal(l, r - 1, mn, a[r]) + 1);
    }
    if (a[l] <= a[r] && mn <= a[l] && a[r] <= mx)
        best = max(best, cal(l + 1, r - 1, a[l], a[r]) + 2);
    //Swap a[l], a[r]
    if (mn <= a[r] && a[r] <= mx)
        best = max(best, cal(l + 1, r - 1, a[r], mx) + 1);
    if (a[l] <= mx && a[l] >= mn)
        best = max(best, cal(l + 1, r - 1, mn, a[l]) + 1);
    if (a[l] > a[r] && a[l] <= mx && a[r] >= mn)
        best = max(best, cal(l + 1, r - 1, a[r], a[l]) + 2);
    dp[l][r][mn][mx] = best;
    return best;
}
//9
//1 2 3 9 5 6 8 7 4
//      4     7 8 9
int main() {
    freopen(taskname".in","r",stdin);
    freopen(taskname".out","w",stdout);
    IO;
    cin >> n;
    FOR(i, 1, n) cin >> a[i];
    cout<<cal(1, n, 1, 50);
}
