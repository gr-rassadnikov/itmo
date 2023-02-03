//
// Created by Grigorii Rassadnikov on 25.01.2023.
//

#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int maxN = 1e5;

// O(n log n), should better - it's easy, use array of used

struct Graph {

    int n, m;
    vector<vector<int>> g;
    vector<bool> used;
    vector<int> topSortOrder;
    vector<int> component;
    int color = 0;
    vector<vector<int>> transpose;

    vector<int> lintHardToG;


    void input() {
        cin >> n >> m;
        g.assign(n, {});
        used.assign(n, false);
        component.assign(n, -1);
        for (int i = 0; i < m; ++i) {
            int b, e;
            cin >> b >> e;
            b--;
            e--;
            g[b].push_back(e);
        }
        transpose.assign(n, {});
        for (int v = 0; v < n; v++) {
            for (int u: g[v]) {
                transpose[u].push_back(v);
            }
        }
        lintHardToG.assign(n, -1);

    }

    void dfs(int v) {
        used[v] = true;
        for (auto e: g[v]) {
            if (!used[e])
                dfs(e);
        }
        topSortOrder.push_back(v);
    }

    void topSort() {
        for (int i = 0; i < n; ++i) {
            if (!used[i]) {
                dfs(i);
            }
        }
        reverse(topSortOrder.begin(), topSortOrder.end());
    }

    void dfs2(int v) {
        component[v] = color;
        for (int u: transpose[v]) {
            if (component[u] == -1) {
                dfs2(u);
            }
        }
    }

    void hardComponents() {
        for (int v: topSortOrder) {
            if (component[v] == -1) {
                lintHardToG[color] = v;
                dfs2(v);
                color++;
            }
        }
    }

    Graph getHardGraph() {
        Graph hard;
        hard.n = color;
        hard.g.assign(hard.n, {});
        hard.lintHardToG.assign(n, -1);
        hard.used.assign(n, false);
        for (int i = 0; i < n; ++i) {
            for (int to: g[i]) {
                hard.g[component[i]].push_back(component[to]);
            }
        }
        hard.lintHardToG = lintHardToG;
        return hard;
    }

    void dfs3(int v, set<int> &leafs) {
        if (used[v]) {
            return;
        }
        used[v] = true;
        int isLeaf = true;
        for (auto e: g[v]) {
            if (!used[e]) {
                dfs3(e, leafs);
            }
            if (e != v) {
                isLeaf = false;

            }
        }
        if (isLeaf) {
            leafs.insert(v);
        }

    }

    set<int> getHardLeafs() {
        set<int> leafs;
        for (int i = 0; i < n; ++i) {
            if (!used[i]) {
                dfs3(i, leafs);
            }
        }
        return leafs;
    }

    void printStation() {
        set<int> leafs = getHardLeafs();
        cout << leafs.size() << "\n";
        for (int e: leafs) {
            cout << lintHardToG[e] + 1 << "\n";
        }

    }

    void printG() {
        for (int i = 0; i < n; ++i) {
            cout << i << ": ";
            for (int to: g[i]) {
                cout << to << " ";
            }
            cout << endl;

        }
    }


};

int main() {
    Graph g;
    g.input();
    g.topSort();
    g.hardComponents();
    Graph hard = g.getHardGraph();
//    hard.printG();
    hard.printStation();

    return 0;
}
