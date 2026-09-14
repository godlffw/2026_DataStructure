#include <bits/stdc++.h>

using namespace std;

int arr[1005][25];
char ans[25];

int main() {
    int k;
    cin >> k;
    int mx = -1;
    for(int i = 1; i < k; i++) {
        int n;
        while(1) {
            cin >> n;
            if (n == 0) break;
            arr[n][i] = 1;
            mx = max(mx,n);
        }
    } 
    char arrived = 'A';
    for(int i = 1; i < k+1; i++) {
        int t = i;
        int j = 1;
        while(j != mx+1) {
            if(arr[j][t] && !arr[j][t-1]) {//오른쪽 {
                while(arr[j][t]) t++;

            }
            
            else if (!arr[j][t] && arr[j][t-1]) {//왼쪽
                while(arr[j][t-1]) t--;
            }
            
            j++;
        }
        ans[t] = arrived;
        arrived++;
    }
    int an = 1;
    while(ans[an]) cout << ans[an++] << " ";
}
