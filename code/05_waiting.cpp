#include <bits/stdc++.h>

using namespace std;

void split_vector(vector<vector<int>>& arr, int k, int index) {
    if (arr[index].size() == 2 * k) {
        vector<int> new1(k), new2(k);
        for (int i = 0; i < k; i++) {
            new1[i] = arr[index][i];
            new2[i] = arr[index][i+k];
        }
        arr[index] = new1;
        arr.insert(arr.begin() + index+1, new2);

    }
}

int main() {
    int n,k,waiting_num;
    char op;
    cin >> n >> k;
    vector<vector<int>> waiting;

    for (int i = 0; i < n; i++) {
        cin >> op >> waiting_num;
        if (op =='+') { //입장
            if (waiting.empty()) { //초기상태
                vector<int> chair = {waiting_num};
                waiting.push_back(chair);
            }
            else { // 뭔가가 들어가있긴 함
                //1. 맨앞에 넣는다 
                //(10,20) 80 -> (10,20,80) //크긴 한데 사이즈가 1임
                //(10,20) 5 -> (5,10,20) //작고 사이즈가 1임 
                //(10,20) (25, 30) (40, 45)  5 //작음
                //작거나 사이즈가 1이 조건
                int t = 0;
                if (waiting[0][0] > waiting_num || waiting.size() == 1) {
                    waiting[0].push_back(waiting_num);
                }
               
                
                //2. 중간에 넣는다
                // (10,20) (30,40) 25  -> (10,20,25) (30,40)
                //  (20,40) (50,70)  45 - > (20,40,45) (50,70)
                //waiting num이 앞의 배열의 첫번째 원소보다 크고 뒤의 배열의 첫원소보다 작다
                else {
                    for (; t < waiting.size()-1; t++) {
                        if(waiting[t][0] < waiting_num && waiting[t+1][0] > waiting_num) {
                            waiting[t].push_back(waiting_num);
                            break;
                        }
                    }
                    //3. 맨 끝에 넣는다.
                    //(10,20) (40,60) (100,1000) 150 -> ... (100, 150, 1000)
                    //... (100,200,300) 250 -> (100, 200,250, 300) -> (100, 200) (250, 300)
                    //일단 넣고 함수로 쪼개기
                    if (t == waiting.size()-1) { 
                        waiting[t].push_back(waiting_num);
                    }
                }
                // for (int q = 0; q < waiting.size(); q++) {
                //         sort(waiting[q].begin(), waiting[q].end());
                // } //쪼개기전 정렬
                sort(waiting[t].begin(), waiting[t].end()); 
                split_vector(waiting, k, t); //t는 쪼갤 인덱스
            }
                
        }      
                
            
        
        else { //퇴장
            //발견했다? 그거 지운다
            //근데 지웠는데 해당 벡터가 비었다? 그거도 지운다
            for (int i = 0; i < waiting.size(); i++) {
                for (int j = 0; j < waiting[i].size(); j++) {
                    if (waiting[i][j] == waiting_num) { //찾았다
                        waiting[i].erase(waiting[i].begin() + j);
                        if (waiting[i].empty()) waiting.erase(waiting.begin() + i);
                        break;
                    }
                }
            }
        }

    }
    for (auto ar : waiting) {
            cout << ar[0] << "\n";
    }
}
