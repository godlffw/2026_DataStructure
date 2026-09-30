#include <bits/stdc++.h>
using namespace std;

int getsum(vector<pair<int, int>>& vec) {
    int sum = 0;
    for (auto v : vec) sum += v.second;
    return sum;
}

int main() {
    int n,k,id,cote,from,to;
    cin >> n >> k;
    
    vector<pair<string, vector<pair<int, int>>>> rec;

    while(n--) {
        //시작하기전 정렬
        sort(rec.begin(), rec.end(), [](auto a, auto b) {if (a.second.size() != b.second.size()) { return a.second.size() > b.second.size();} return getsum(a.second) > getsum(b.second);});
        for (int i = 0; i < rec.size(); i++) {
            sort(rec[i].second.begin(), rec[i].second.end(), [](auto a, auto b) {if (a.second != b.second) {return a.second > b.second;} return a.first > b.first;});

        }
        string keyword;
        cin >> keyword;
        if (keyword == "POP") {
            //POP 
            int total_size = 0;
            for (int i = 0; i < rec.size(); i++) {
                for (int j = 0; j < rec[i].second.size(); j++) {
                    total_size++;
                }
            }
            cin >> from >> to;
            vector<int> ans_list;
            for (int i = 0; i < total_size; i++) {
                for (int j = 0; j < rec.size(); j++) {
                    if (i < rec[j].second.size() && rec[j].second.size() >= k) {
                        ans_list.push_back(rec[j].second[i].first);
                    }
                }
            }

            if (from <= ans_list.size() && from > 0) { //from이 범위안에 있다면
                if (to > ans_list.size()) to = ans_list.size(); //to가 범위초과라면 있는 원소까지만
                for (int i =from-1; i <= to-1; i++) {
                    cout << ans_list[i] << " ";
                    //벡터에서 삭제
                    for (int m = 0; m < rec.size(); m++) {
                        for (int n = 0; n < rec[m].second.size(); n++) {
                            if (rec[m].second[n].first == ans_list[i]) {
                                rec[m].second.erase(rec[m].second.begin() + n); 
                                break;
                            } 
                        }
                    }
                }
                cout << endl;
            }
        }
        else { //등록
            cin >> id >> cote; //id, cote 입력
            auto i = 0; //i = 소속
            for (; i < rec.size(); i++) {
                if  (rec[i].first == keyword) { //이미 존재하는 대학교
                    rec[i].second.push_back({id, cote});
                    break;
                }
            }
            if (i ==  rec.size()) rec.push_back({keyword, {{id, cote}}}); //새로운 대학 등록
            
            
            
        }
    }
}
