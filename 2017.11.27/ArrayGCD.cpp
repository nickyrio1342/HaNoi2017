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
I copied it (^.^)
*/
#include <bits/stdc++.h>
#define FOR(_i, a, b) for (int _i = a; _i<= b; _i++)
#define FORD(_i, a, b) for (int _i = a; _i>=b; _i--)
#define REP(_i, a) for (int _i = 0; _i<a; _i++)
#define N 1001000
#define pp pair<int, int>
#define bit(S, i) (((S) >> i) & 1)
#define IO ios::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
#define taskname ""
using namespace std;

int n, A, B, a[N];

vector<int> e;
long long dp[N][3];
long long solve(int u) {
  int x = u;
  e.clear();
  FOR(i, 2, sqrt(u)) if (x % i == 0) {
    e.push_back(i);
    while (x % i == 0) x /= i;
  }
  if (x > 1) e.push_back(x);
  long long ans = 1e18;

  //0 : Not used Segment
  //1 : Used but now is not
  //2 : Using now
  for (int x : e) {
    FOR(i, 1, n) REP(j, 3) dp[i][j] = 1e18;
    dp[0][0] = dp[0][1] = dp[0][2] = 0;
    FOR(i, 1, n) {
      if (a[i] % x == 0) {
        dp[i][0] = dp[i - 1][0];
        dp[i][1] = min(dp[i - 1][0], min(dp[i - 1][1], dp[i - 1][2]));
        dp[i][2] = min(dp[i - 1][0], dp[i - 1][2]) + A;
      }
      else {
        if (a[i] % x == 1 || a[i] % x == x - 1) {
          dp[i][0] = dp[i - 1][0] + B;
          dp[i][1] = min(min(dp[i - 1][0] + B, dp[i - 1][1] + B), dp[i - 1][2] + min(A, B));
          dp[i][2] = min(dp[i - 1][0], dp[i - 1][2]) + A;
        }
        else {
          dp[i][0] = 1e18;
          dp[i][1] = 1e18;
          dp[i][2] = min(dp[i - 1][0], dp[i - 1][2]) + A;
        }
        REP(j, 3) dp[i][j] = min(dp[i][j] , (long long)1e18);
      }
      //cerr<<1;
    }
    ans = min(ans, min(dp[n][0], min(dp[n][1], dp[n][2])));
  }
  return ans;
}
int main() {
    //freopen(taskname".inp","r",stdin);
    //freopen(taskname".out","w",stdout);
    IO;
    cin>>n>>A>>B;
    FOR(i, 1, n) cin>>a[i];
 //   BuildRMQ();
    long long ans = 1e18;
    ans = min(ans, solve(a[1]));
    ans = min(ans, solve(a[1] - 1));
    ans = min(ans, solve(a[1] + 1));
    ans = min(ans, solve(a[n]));
    ans = min(ans, solve(a[n] + 1));
    ans = min(ans, solve(a[n] - 1));
    cout<<ans;
}
