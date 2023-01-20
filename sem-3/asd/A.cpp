#include <iostream>
#include <vector>
#include <set>

using namespace std;


struct Graph {
    vector<int> nodes;
    vector<vector<bool>> table;
    int cntNodes;

    vector<int> colors;

    void dfs_table_color(int u, int color) {
        if (colors[u] >= 0) {
            return;
        }
        colors[u] = color;
        for (int i = 0; i < cntNodes; ++i) {
            if (table[u][i] || table[i][u]) {
                dfs_table_color(i, color);
            }
        }
    }


    int cnt_components() {
        colors.assign(cntNodes, -1);
        for (int i = 0; i < cntNodes; ++i) {
            dfs_table_color(i, i);
        }

        set<int> col;
        for (auto c: colors) {
            col.insert(c);
        }
        return col.size();
    };

    void input_graph_from_list_to_table() {
        int m, n;
        cin >> m >> n;
        vector<string> data(m);

        for (int i = 0; i < m; ++i) {
            cin >> data[i];
        }
        int number = 0;
        table.assign(m * n, vector<bool>(m * n, false));
        cntNodes = m * n;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (data[i][j] == 'O') {
                    if (i > 0 && data[i - 1][j] == 'O') {
                        table[number - n][number] = true;
                    }
                    if (i < m - 1 && data[i + 1][j] == 'O') {
                        table[number + n][number] = true;
                    }
                    if (j > 0 && data[i][j - 1] == 'O') {
                        table[number - 1][number] = true;
                    }
                    if (j < n - 1 && data[i][j + 1] == 'O') {
                        table[number + 1][number] = true;
                    }
                }
                number++;
            }
        }
        for (const auto &i: table) {
            for (auto j: i) {
                cout << j;
            }
            cout << "\n";
        }
    }

};

int main() {
    Graph g;
    g.input_graph_from_list_to_table();
    cout << g.cnt_components();

    return 0;
}