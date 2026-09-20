    #include <bits/stdc++.h>

    using namespace std;

    int main() {
        int n, arr[6], sc;
        cin >> n;
        for (auto &i : arr) cin >> i;
        
        vector<pair<string, array<int, 6>>> student(n);
        
        for (auto &in : student) {
            cin >> in.first;
            vector<int> score;
            while(cin >> sc && sc != -1) score.push_back(sc);
            auto begin = score.begin(),  end = score.end();
            
            in.second = {
                end-begin, accumulate(begin, end, 0), *min_element(begin, end),
                *max_element(begin, end), count(begin, end, 100), 
                count_if(begin, end, [](auto a){return a <= 50;})
            };
            
        }
        
        while(n--) {
            int best = 0;
            for (int i = 1; i < student.size(); i++) {
                int j = 0;
                for (; j < 6; j++) {
                    int now = arr[j] -1;
                    auto comp1 = student[i].second[now], comp2 = student[best].second[now];
                    if (comp1 == comp2) continue;


                    if(now==5^comp1>comp2) best = i; //if (now == 5 ? comp1 < comp2 : comp1 > comp2)
                    break;

                }
                if (j == 6 && student[i].first < student[best].first) best = i; 
            }
            cout << student[best].first<< endl;
            student.erase(student.begin() + best);
        }

        
    }
