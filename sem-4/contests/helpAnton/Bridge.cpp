#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;


void dfs(int v, int p, int t, vector<vector<int>> &graph,
         vector<int> &used, vector<int> &enter, vector<int> &ret,
         set<int> &bridges, map<pair<int, int>, int> &numberOfEdges) {
    used[v] = 1;
    enter[v] = ret[v] = t++;

    for (int i = 0; i < graph[v].size(); i++) {
        int to = graph[v][i];
        if (to == p) continue;
        if (used[to])
            ret[v] = min(ret[v], enter[to]);
        else {
            dfs(to, v, t, graph, used, enter, ret, bridges, numberOfEdges);
            ret[v] = min(ret[v], ret[to]);
            if (ret[to] > enter[v]) bridges.insert(numberOfEdges[{v, to}]);

        }
    }
}

int main() {

    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1);
    vector<int> used(n + 1), enter(n + 1), ret(n + 1);
    set<int> bridges;
    map<pair<int, int>, int> numberOfEdges;

    graph.resize(n + 1);
    used.resize(n + 1);
    enter.resize(n + 1);
    ret.resize(n + 1);

    for (int i = 1; i <= m; i++) {
        int beg, end;
        cin >> beg >> end;

        graph[beg].push_back(end);
        graph[end].push_back(beg);
        numberOfEdges[make_pair(beg, end)] = i;
        numberOfEdges[make_pair(end, beg)] = i;
    }

    int t = 1;

    for (int i = 0; i <= n; ++i) {
        if (!used[i]) {
            dfs(i, -1, t, graph, used, enter, ret, bridges, numberOfEdges);
        }
    }

    cout << bridges.size() << endl;
    for (auto iter = bridges.begin(); iter != bridges.end(); iter++) {
        cout << *iter << " ";
    }

    return 0;
}