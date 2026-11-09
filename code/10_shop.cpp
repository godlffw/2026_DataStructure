#include <bits/stdc++.h>

using namespace std;

struct Member{
    int id;
    int product;
};

vector <Member> counter;
queue<Member> line;

int main() {
    int n,k,id,numofcal;
    cin >> n >> k;
    counter.resize(k);


    while(n--) {
        cin >> id >> numofcal;
        line.push({id, numofcal});
    }

    for (auto& v : counter) {
        if (line.empty()) break;
        v = line.front();
        line.pop();
    }

    while(!line.empty() || any_of(counter.begin(), counter.end(), [](auto a) {return a.product > 0;})) {
        for (auto &v : counter) {
            if(v.product > 0) v.product--;
        }
        vector<int> temp;
        for (auto &v : counter) {
            if(!v.product && v.id) {
                temp.push_back(v.id);
                if (!line.empty()) {
                    v = line.front();
                    line.pop();
                }
                else v = {0,0}; 
            }
        }
        for (int i = temp.size()-1; i > -1; i--) {
            cout << temp[i] << "\n";
        }
    }

}
