#include <bits/stdc++.h>

using namespace std;


int main() {
    int n,k, weight,max_index,min_index;
    cin >> n;
    vector<stack<int>> yard(n);

    for (auto &vc : yard) {
        cin >> k;
        while (k--) {
            cin >> weight;
            vc.push(weight);
        }
    }
    while(1) {
        int max_len = 0;
        int max_value = -1;
        int min_len = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (max_len < yard[i].size()) {
                max_index = i;
                max_value = yard[i].top();
                max_len = yard[i].size();
            }
            if (!yard[i].empty()&&max_len == yard[i].size() && max_value < yard[i].top()) {
                max_index = i;
                max_value = yard[i].top();
                max_len = yard[i].size();
            }
            if (min_len > yard[i].size()) {
                min_index = i;
                min_len = yard[i].size();
            }
            
        }
        if ((max_len - min_len) <= 1) break;
        int temp = yard[max_index].top();
        yard[max_index].pop();
        yard[min_index].push(temp);
        
    }
    vector<vector<int>> ans(n);
    for (int i = 0; i < n; i++) {
        if (yard[i].empty()) {
            ans[i].push_back(0);
        }
        while(!yard[i].empty()) {
            ans[i].push_back(yard[i].top());
            yard[i].pop();
        }
        reverse(ans[i].begin(), ans[i].end());
    }

    for (auto out : ans) {
        for (auto in : out) {
            cout << in << " ";
        }
        cout << "\n";
    }

    


}
