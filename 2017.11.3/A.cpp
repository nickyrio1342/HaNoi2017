/*
Đề phía trên chỉ là lừa tình. Đề thực sự ở cuối bài :v.
Xét các vị trí x tăng dần. Xét tại thằng thứ i thì :
Có 2 trường hợp xảy ra:
1, Vị trí có > 2 con gần nhất có thể đến được từ x[i] thì ném hết chúng vào đấy.
2, Nếu không thể đến được vị trí đó thì :
 + Chúng ta có thể phân bố các con mèo trái nhất có thể sao cho mỗi con 1 vị trí và không đè lên những con phía trước
 + Chúng ta không thể phân bố như thế thì phải chấp nhận có 1 đống có > 2 con mèo và tối ưu nhất là đặt phải nhất có thể
 (để những thằng phía sau có thể đến được vị trí này)
 */
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b; ++i)
#define FORD(i, a, b) for (int i = a; i>=b; --i)
#define REP(i, a) for (int i = 0; i<a; ++i)
#define N 1111

#define pp pair<int, int>

using namespace std;

int n, k;
pp s[N];

int main() {
   // freopen("input.txt","r",stdin);
   // freopen("out.txt","w",stdout);
    cin.tie(NULL);cout.tie(NULL);
    scanf("%d", &n);
    FOR(i, 1, n) scanf("%d %d", &s[i].first, &s[i].second);
    scanf("%d", &k);
    sort(s + 1, s + n + 1);
    int l = -1e9;
    int pos2 = -1e9;
    int ans = 0;
    FOR(i, 1, n) {
        if (s[i].first - k <= pos2) continue;
        if (2 * k + 1 < s[i].second) {
            l = max(l, s[i].first + k);
            pos2 = s[i].first + k;
            ans++;
            continue;
        }
        int t = s[i].first + k - max(l, s[i].first - k - 1);
        if (t >= s[i].second) {
            l = max(l, s[i].first - k - 1) + s[i].second;
        }
        else {
            l = max(l, s[i].first + k);
            pos2 = s[i].first + k;
            ans++;
        }
    }
    printf("%d", ans);
}
