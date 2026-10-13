#include <bits/stdc++.h>
using namespace std;

struct Func {
    string name;
    vector<string> cmd;
    long long total_exc = 0;
};


vector<Func> funcs;

int iscalling[22], pos[22], n;


int find_idx(string name) {
    for (int i = 0; i < n; i++)
        if (funcs[i].name == name)
            return i;

    return -1;
}

void execute(int idx) {
    stack<int> call;
    call.push(idx);

    while (!call.empty()) {
        idx = call.top();
        iscalling[idx] = 1;

        if (pos[idx] == funcs[idx].cmd.size()) {
            iscalling[idx] = 2;
            call.pop();
            continue;
        }

        int next = find_idx(funcs[idx].cmd[pos[idx]]);
        //일반 명령이면 -1, 함수면 index
        
        if (next < 0)
            funcs[idx].total_exc++;
        else {
            if (iscalling[next] == 1) {
                cout << "DEADLOCK";
                exit(0);
            }

            if (!iscalling[next]) {
                call.push(next);
                continue;
            }

            funcs[idx].total_exc += funcs[next].total_exc;
        }

        pos[idx]++;
    }
}

string answer(int idx, long long k) {
    if (k < 0)
        k += funcs[idx].total_exc + 1;

    while (k > 0 && k <= funcs[idx].total_exc) {
        for (string temp : funcs[idx].cmd) {
            int next = find_idx(temp);

            long long cnt = 1;
            if (next >= 0)
                cnt = funcs[next].total_exc;

            if (k > cnt) k -= cnt;
            else if (next >= 0) {
                idx = next;
                break;
            }
            else
                return funcs[idx].name + "-" + temp;
        }
    }

    return "NONE";
}

int main() {
    long long k[2];
    cin >> n >> k[0] >> k[1];
    funcs.resize(n);

    string temp;
    for (Func &f : funcs) {
        cin >> f.name;

        while (cin >> temp && temp != "$")
            f.cmd.push_back(temp);
    }

    int main_idx = find_idx("M");

    execute(main_idx);

    for (auto x : k)
        cout << answer(main_idx, x) << '\n';
}
