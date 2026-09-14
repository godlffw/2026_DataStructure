#include <bits/stdc++.h>

using namespace std;

int arr[1002][22];
char ans[22];

int main() {
    int k;
    cin >> k;
    int mx = -1;
    for(int i = 0; i < k-1; i++) {
        int n;
        while(1) {
            cin >> n;
            if (n == -1) break;
            arr[n][i] = 1;
            mx = max(mx,n);
        }
    } 
    char arrived = 'a';
    for(int i = 0; i < k; i++) {
        int t = i;
        int j = 0;
        while(j != mx+1) {
            if(arr[j][t]) {
                t++;
            }
            else if (t > 0 && arr[j][t-1]) {
                t--;
            }
            j++;
        }
        ans[t] = arrived;
        arrived++;
    }
    int an = 0;
    while(ans[an]) cout << ans[an++] << " ";
}
