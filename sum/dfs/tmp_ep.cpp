#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

//struct exp{
    int n;
    int order[20]; // 按顺序依次记录被选择的整数
//    vector<int> order[20];
    bool chosen[20]; // 标记被选择的整数
//    vector<bool> chosen[20];
    void calc(int k) {
        if (k == n + 1) { // 问题边界
            for (int i = 1; i <= n; i++)
                printf("%d ", order[i]);
            puts("");
            return;
        }
        for (int i = 1; i <= n; i++) {
            if (chosen[i]) continue;
            order[k] = i;
            chosen[i] = 1;
            calc(k + 1);
            chosen[i] = 0;
            order[k] = 0; // 这一行可以省略
        }
    }

    int main() {
        cin >> n;
        calc(1);  // 主函数中的调用入口
    }
//};

//int main() {
//    exp e;
//    e.main();
//
////    exp1 e1;
////    e1.main();
//}