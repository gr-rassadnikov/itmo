//
// Created by Grigorii Rassadnikov on 25.01.2023.
//

#include <iostream>
#include <vector>

using namespace std;

void dfs(int i, int j, vector<vector<int>> &a){
    if (a[i][j]=='.') {
        return;
    }
    a[i][j] = '.';
    if (a[i-1][j]=='O') {
        dfs(i - 1, j,a);
    }
    if (a[i+1][j]=='O') {
        dfs(i + 1, j,a);
    }
    if (a[i][j-1]=='O') {
        dfs(i, j - 1,a);
    }
    if (a[i][j+1]=='O') {
        dfs(i, j + 1,a);
    }
}

int main() {
    int n,m;
    cin >> m >> n;
    vector<vector<int>> a(m+2,vector<int>(0));
    for (int i = 1; i < m+1; ++i) {
        string b;
        cin >> b;
        a[i].push_back('.');
        for(char c: b){
            a[i].push_back(c);
        }
        a[i].push_back('.');
    }
    for (int i = 0; i < n+2; ++i) {
        a[0].push_back('.');
        a[m+1].push_back('.');
    }

    int cmp=0;
    for (int i = 1; i < m+1; ++i) {
        for (int j = 1; j < n+1; ++j) {
            if(a[i][j]=='O'){
                dfs(i,j,a);
                cmp++;
            }
        }
    }
    cout <<cmp;
    return 0;
}

