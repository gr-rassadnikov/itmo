#include <iostream>
#include <vector>

using namespace std;

struct node {
    node *zero = nullptr;
    node *one = nullptr;
    int level = -1;

    node(int level) {
        this->level = level;
    }
};

struct tree {
    node *root;

    tree() {
        root = new node(0);
    }

    void insert(vector<bool> &bit, node *u, int index) {
        if (index == -1) {
//            cout << u->level << "\n";
            return;
        }
        if (bit[index]) {
            if (u->one == nullptr) {
                u->one = new node(u->level + 1);
            }
            insert(bit, u->one, index - 1);
        } else {
            if (u->zero == nullptr) {
                u->zero = new node(u->level + 1);
            }
            insert(bit, u->zero, index - 1);
        }
    }

    void get(vector<bool> &bit, node *u, int index, vector<bool> &ans) {
        if (index == -1) {
            return;
        }
        if (bit[index]) {
            if (u->one) {
                ans[index] = true;
                get(bit, u->one, index - 1, ans);
            } else {
                ans[index] = false;
                get(bit, u->zero, index - 1, ans);
            }
        } else {
            if (u->zero) {
                ans[index] = false;
                get(bit, u->zero, index - 1, ans);
            } else {
                ans[index] = true;
                get(bit, u->one, index - 1, ans);
            }
        }
    }
};


int main() {
    int q;
    cin >> q;
    tree t;
    int k;
    cin >> k;
    q--;
    vector<bool> b(32);
    for (int i = 0; i < 32; i++) {
        b[i] = (k % 2 == 1);
        k=k/2;
    }
    t.insert(b, t.root, 31);
    cout << "0\n";

    int mm = 0;
    while (q--) {
        cin >> k;
        vector<bool> bit(32, false);
        vector<bool> bitN(32, false);
        for (int i = 0; i < 32; i++) {
            bit[i] = (k % 2 == 1);
            bitN[i] = !bit[i];
            k=k/2;
        }
        vector<bool> ans(32, false);
//        cout << "bitN ";
//        for(int i=0;i<32;i++){
//            cout << bitN[i];
//        }
//        cout << "\n";
        t.get(bitN, t.root, 31, ans);
//        cout << "ans ";
//        for(int i=0;i<32;i++){
//            cout << ans[i];
//        }
//        cout << "\n";
        int res = 0;
        int st = 1;
        for (int i = 0; i < 32; i++) {
            ans[i] = (ans[i] != bit[i]);
            if (ans[i]) {
                res += st;
            }
            st *= 2;
        }
//        cout << "ans after ";
//        for(int i=0;i<32;i++){
//            cout << ans[i];
//        }
//        cout << "\n";
        mm=max(mm,res);
        cout << mm << "\n";
        t.insert(bit, t.root, 31);

    }
    return 0;
}