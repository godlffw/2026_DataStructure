#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;


class LocalRandom {
private:
    uint32_t state;
public:
    explicit LocalRandom(int key) {
        state = static_cast<uint32_t>(key);
    }

    uint32_t next() {
        state = state * 1664525u + 1013904223u;
        return state;
    }
};

vector<int> get_seat(int p, int q, int key) {
    if (q < p) { cerr << "\nBound p,q error"; exit(1); }

    vector<int> Guest;
    for (int i = p; i <= q; i++) Guest.push_back(i);

    LocalRandom rng(key);

    // Fisher-Yates random shuffle
    for (int i = (int)Guest.size() - 1; i > 0; i--) {
        int j = rng.next() % (i + 1);
        swap(Guest[i], Guest[j]);
    }

    return Guest;
}


const int BLOCK = 1024;

int main() {
    int p, q, key;
    cin >> p >> q >> key;

    auto Guest = get_seat(p, q, key);
    int n = Guest.size(), base = 1;
    while (base * BLOCK < n) base *= 2;

    vector<int> cnt(base * 2);
    list<vector<int>> lst;
    vector<decltype(lst)::iterator> seat;

    for (int i = 0; i < n; i += BLOCK) {
        int end = min(n, i + BLOCK);

        lst.emplace_back(Guest.begin() + i, Guest.begin() + end);
        seat.push_back(prev(lst.end()));
        cnt[base + i / BLOCK] = end - i;
    }

    for (int i = base - 1; i; i--)
        cnt[i] = cnt[i * 2] + cnt[i * 2 + 1];

    int pos = 0, out = Guest[0];

    while (n > 1) {
        pos = (pos + out) % n;
        int k = pos, node = 1;

        while (node < base) {
            cnt[node]--;
            node *= 2;

            if (k >= cnt[node]) {
                k -= cnt[node];
                node++;
            }
        }
        cnt[node]--;


        auto it = seat[node - base];

        out = (*it)[k];
        it->erase(it->begin() + k);

        if (it->empty()) lst.erase(it);
        n--;
    }

    cout << lst.front().front() << '\n';
}
