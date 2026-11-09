#include <bits/stdc++.h>
using namespace std;

int sol[12][10002], x[12];


stack<int> stk, store;

int main() {
    int n, tar;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> x[i];
        stk.push(i);
    }
    cin >> tar;



    while (stk.size() > 1) {
        store.push(x[stk.top()]);
        stk.pop();
    }

    int i = stk.top();
    for (int j = x[i]; j <= tar; j += x[i])
        sol[i][j] = 1;

    while (!store.empty()) {
        int c = store.top();
        store.pop();

        i = stk.top() + 1;
        stk.push(i);

        for (int j = c; j <= tar; j++)
            sol[i][j] = (sol[i - 1][j - c] + sol[i][j - c]) % 19991;

    }

    cout << sol[n-1][tar];  
}
