#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct edge {
    int to;
    int ch;

    edge(int to, int ch) {
        this->to = to;
        this->ch = ch;
    }

};

struct nody {
    int zero = 1e9;
    int one = 1e9;

    int get() {
        return max(zero, one);
    }
    int getCh(){
        if (one>zero){
            return  0;
        }
        return 1;
    }

    nody(int zero = 1e9, int one = 1e9){
        this->zero = zero;
        this->one = one;
    }
};

void dfs(int u, vector<vector<edge>> &Gn, vector<nody> &data) {
    for (auto e: Gn[u]) {
        if (e.ch == 0) {
            data[e.to].one = min(data[e.to].one, data[u].get() + 1);
        } else {
            data[e.to].zero = min(data[e.to].zero, data[u].get() + 1);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<edge>> Gn(n);
    vector<nody> data(n);


    for (int i = 0; i < m; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        u--;
        v--;
        Gn[v].push_back(edge(u, t));
    }

    data[n - 1] = nody(0, 0);
    for (int i = n - 1; i >= 0; i--) {
        dfs(i, Gn, data);
    }

    if (data[0].get() == 1e9) {
        cout << "-1\n";
    } else {
        cout << data[0].get() << "\n";
    }
    for(auto i: data){
        cout << i.getCh();
    }
    return 0;
}