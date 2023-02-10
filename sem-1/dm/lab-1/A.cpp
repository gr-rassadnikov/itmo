#include <iostream>
//#include <bits/stdc++.h>
#include  <vector>

using namespace std;

int reflex(vector<vector<int>> a) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
        if (a[i][i] == 0) {
            return 0;
        }
    }
    return 1;
}

int antireflex(vector<vector<int>> a) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
        if (a[i][i] == 1) {
            return 0;
        }
    }
    return 1;
}

int simm(vector<vector<int>> a) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
                if (a[i][j] != a[j][i]) {
                    return 0;
                }


        }
    }
    return 1;
}

int antisimm(vector<vector<int>> a) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == a[j][i] && a[i][j] == 1 && i != j) {
                return 0;
            }
        }
    }
    return 1;
}

int tranz(vector<vector<int>> a) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (a[i][j] == 1 && a[j][k] == 1) {
                    if (a[i][k] == 0) {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}


int main() {

    int n;
    cin >> n;

    vector<vector<int>> a(n);

    vector<vector<int>> b(n);
    vector <vector <int>> c(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i].push_back(0);
            c[i].push_back(0);
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            b[i].push_back(0);
            cin >> b[i][j];
        }
    }
    cout << reflex(a) <<" "<<  antireflex(a) <<" "<<  simm(a) <<" "<<  antisimm(a) <<" "<< tranz(a) << endl;
    cout << reflex(b) <<" "<<  antireflex(b) <<" "<<  simm(b) <<" "<<  antisimm(b) <<" "<< tranz(b) << endl;

    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            for (int k=0;k<n;k++) {
                if (a[i][j] == 1 && b[j][k] == 1){
                    c[i][k]=1;
                }
            }
        }

    }
    for (int i=0;i<n;i++){
        for (int j:c[i]){
            cout << j << " ";
        }
        cout << endl;
    }
    return 0;
}
