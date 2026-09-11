#include <bits/stdc++.h>

using namespace std;

int arr[10002]; 

int main() {
    int n;
    cin >> n;
    vector<pair<string,int>> list(n);
    while(n--) {
        cin >> list[n].first >> list[n].second;
        arr[list[n].second]++;
    }    
    sort(list.begin(), list.end(), [](auto a, auto b) {return a.second > b.second;});
    
    for (auto kv : list) {
        if (arr[kv.second] == 1) {
            cout << kv.first;
            return 0;
        }
    }
    cout << "NONE";
}
