#include<bits/stdc++.h>

using namespace std;

struct a3 {
    // 正则实现 字符串分割方法
    vector<string> stringSplit(const string& str, char delim) {
        string s;
        s.append(1, delim);
        regex reg(s);
        vector<string> elems(sregex_token_iterator(str.begin(), str.end(), reg, -1),
                                       sregex_token_iterator());
        return elems;
    }

    // 字符串排序
    static bool customCompare(int a, int b) {
        return a > b;
    }

    //
    int main() {
        string s; scanf("%s", &s);
        vector<string> tmp = stringSplit(s, ' ');
//        sort(tmp, customCompare);
        return 0;
    }

};

int main() {
//    int a[] = {3,2,1};
    vector<int> a = {4,3,2};
    vector<string> b = {"c", "b", "a"};
//    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for(auto x: b) cout << x << " ";
}