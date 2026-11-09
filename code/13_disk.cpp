#include <bits/stdc++.h>

using namespace std;

vector<string>cmd_list = {"write", "show", "delete", "compact"};

struct File {
    int id;
    int size;
    int loc;
};

int input_to_case(string cmd) {
    auto it = find(cmd_list.begin(), cmd_list.end(), cmd);
    return distance(cmd_list.begin(), it);
}

list<File> memory;
map<string, int> filename;

int main() {
    int volume;
    string cmd;
    cin >> volume;
    memory.push_back({0, volume, 0});
    int myid = 1; //고유번호
    while(cin >> cmd && cmd != "end") {
        string name;
        switch(input_to_case(cmd)) {
            case 0: {
                //write
                int newfile_size;
                cin >> name >>newfile_size;
                int total = newfile_size;
                if (filename.find(name) != filename.end()) {
                    cout << "error\n";
                    continue;
                }
                //diskfull : 용량 초과
                if (newfile_size > volume) {
                    cout << "diskfull\n";
                    continue;
                }
                filename[name] = myid;
                auto it = memory.begin();
                for (; it != memory.end(); it++) {
                    if (!it -> id && it->size >= newfile_size) {
                        break;
                    } 
                }
                if (it == memory.end()) it = memory.begin();
                while(newfile_size>0) {
                    if (!it->id) {//빈 자리 
                        if (it->size >= newfile_size){ //저장공간이 파일보다 크다 -> 한번에 다 저장
                            int old_size = it->size;
                            int old_loc = it->loc;
                            it = memory.erase(it);
                            it = memory.insert(it, {myid, newfile_size, old_loc});
                            //만약 저장공간이 파일보다 크다
                            if (old_size > newfile_size) {
                                memory.insert(next(it), {0,old_size-newfile_size,old_loc+newfile_size});
                            } 
                            newfile_size = 0;
                            break;
                        }

                        else {//저장공간이 파일보다 작으면 일단 저장하고 넘어가기
                            it->id = myid;
                            newfile_size -= it->size;
                        }
                        
                    }
                    it++; 
                }
                volume-= total;
                myid++;
                break;
            }
            case 1 :{
                //show
                cin >> name;
                auto it = memory.begin();
                vector<int> loc_box;
                if (filename.find(name) == filename.end()) {
                    cout << "error\n";
                    continue;
                }
                int tar = filename[name];
                for(; it != memory.end();it++) {
                    if (it->id == tar) {
                        loc_box.push_back(it->loc);
                    }
                } 
                for (int i : loc_box) cout << i << " ";
                cout << "\n";
                break;
            }
            case 2: {
                //delete
                cin >> name;
                if (filename.find(name) == filename.end()) {
                    cout << "error\n";
                    continue;
                }
                int tar = filename[name];
                auto it = memory.begin();
                for (; it != memory.end(); it++) {
                    if (it->id == tar) {
                        volume += it->size;
                        it->id = 0;
                    }
                }

                it = memory.begin();
                while(it != memory.end()) {
                    auto nxt_it = next(it);

                    if (nxt_it == memory.end()) {
                        break;
                    }

                    if (!it->id && nxt_it->id ==0 ) {
                        it->size += nxt_it->size;
                        memory.erase(nxt_it);
                    }
                    else it++;
                }            
                filename.erase(name);
                break;
            }
            case 3: {
                //compact
                auto it = memory.begin();
                int loc = 0;
                while (it != memory.end()) {
                    if (!it->id) {
                        it = memory.erase(it);
                    }
                    else {
                        it->loc = loc;
                        loc += it->size;
                        it++;
                    }
                }

                //이제 서로 겹치는 파일들 이어붙이기
                it = memory.begin();
                while (it != memory.end()) {
                    auto nxt_it = next(it);
                    if(nxt_it == memory.end()) break;

                    if (it->id == nxt_it->id) {
                        it->size += nxt_it->size;
                        memory.erase(nxt_it);
                    }
                    else {
                        it++;
                    }
                }
                if (volume > 0 ) memory.push_back({0, volume, loc});
                break;
            }
            default:
                break;
        }
    }
}
