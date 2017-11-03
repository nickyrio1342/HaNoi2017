//Problem 4 practice IOI 2016
//Submit at https://oj.uz/problem/view/IOI16_dna
#include "dna.h"

#include <cstdlib>

using namespace std;

string add(string st, char c, int len) {
    for (int i = 0; i<len; i++) st.push_back(c);
    return st;
}

string analyse(int n, int t) {
    string now;
    now.clear();
    int l = 1;
    int r = n;
    int cur = 0;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (make_test(add(now, '1', m))) {
            cur = m;
            l = m + 1;
        } else r = m - 1;
    }
    if (cur == 0) return add(now, '0', n);
    now = add(now, '1', cur);
    int cnt = 0;
    while (cnt <= cur) {
        if (make_test(now + '0')) {
            cnt = 0;now.push_back('0');
        }
        else {
            cnt++; now.push_back('1');
        }
    }
    int suffix = cur;
    l = cur + 1;
    r = now.size();
    while (l <= r) {
        int m = (l + r) >> 1;
        if (make_test(now.substr(0, m))) {
            suffix = m;
            l = m + 1;
        } else r = m - 1;
    }
    now = now.substr(0, suffix);
    while (now.size() < n) {
        if (make_test('1' + now)) now = '1' + now;
        else now = '0' + now;
    }
    return now;
}
