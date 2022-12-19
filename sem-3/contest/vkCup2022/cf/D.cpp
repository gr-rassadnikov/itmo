//
// Created by Grigorii Rassadnikov on 17.12.2022.
//

#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

map<char, int> mast = {{'C', 0},
                       {'D', 1},
                       {'S', 2},
                       {'H', 3}};

map<char, int> number = {{'6', 0},
                         {'7', 1},
                         {'8', 2},
                         {'9', 3},
                         {'T', 4},
                         {'J', 5},
                         {'Q', 6},
                         {'K', 7},
                         {'A', 8}};

set<pair<int, int>> alice;
set<pair<int, int>> bob;

pair<int, int> toMove(string s) {
    return {mast[s[1]], number[s[0]]};
}
map<pair<vector<pair<int, int>>, pair<int, pair<int,int>>>,bool> cash;

auto bfs(vector<pair<int, int>> board, int move, int cntA, int cntB) -> bool {
//    cout << move << " " << cntA << " " << cntB << "\n";
    if (cash.contains({board,{move,{cntA,cntB}}})) {
        return cash[{board,{move,{cntA,cntB}}}];
    }
    if (cntA <= 0 && move == 0) {
        return false;
    }
    if(cntB <= 0 && move == 1){
        return false;
    }

    if (cntA <= 0 && move == 1) {
        return true;
    }
    if(cntB <= 0 && move == 0){
        return true;
    }
    bool canWin = false;
    bool md = false;
    for (int i = 0; i < 4; ++i) {
        int l = board[i].first;
        int r = board[i].second;
        if (move == 1) {
            if (l == -1 && r == -1) {
                if (alice.contains({i, 3})) {
                    vector<pair<int, int>> new_board = board;
                    new_board[i].first = 3;
                    new_board[i].second = 3;
                    canWin = canWin || !bfs(new_board, 0, cntA-1, cntB);
                    if (canWin){return true;}
                    md = true;
                }
            } else {
                if (alice.contains({i, l - 1})) {
                    vector<pair<int, int>> new_board = board;
                    new_board[i].first -= 1;
                    canWin = canWin || !bfs(new_board, 0, cntA-1, cntB);
                    if (canWin){return true;}
                    md = true;
                }
                if (alice.contains({i, r + 1})) {
                    vector<pair<int, int>> new_board = board;
                    new_board[i].second += 1;
                    canWin = canWin || !bfs(new_board, 0, cntA-1, cntB);
                    if (canWin){return true;}
                    md = true;
                }
            }
        } else {
            if (l == -1 && r == -1) {
                if (bob.contains({i, 3})) {
                    vector<pair<int, int>> new_board = board;
                    new_board[i].first = 3;
                    new_board[i].second = 3;
                    canWin = canWin || !bfs(new_board, 1, cntA, cntB-1);
                    if (canWin){return true;}
                    md = true;
                }
            } else {
                if (bob.contains({i, l - 1})) {
                    vector<pair<int, int>> new_board = board;
                    new_board[i].first -= 1;
                    canWin = canWin || !bfs(new_board, 1, cntA, cntB-1);
                    if (canWin){return true;}
                    md = true;
                }
                if (bob.contains({i, r + 1})) {
                    vector<pair<int, int>> new_board = board;
                    new_board[i].second += 1;
                    canWin = canWin || !bfs(new_board, 1, cntA, cntB-1);
                    if (canWin){return true;}
                    md = true;
                }
            }
        }
    }
    if (!md) {
        canWin = canWin || !bfs(board, (move + 1) % 2, cntA, cntB);
    }
    cash[{board,{move,{cntA,cntB}}}] = canWin;
    return canWin;
}

int main() {

    for (int i = 0; i < 18; ++i) {
        string s;
        cin >> s;
        pair<int, int> move = toMove(s);
        alice.insert(move);
    }

    for (int i = 0; i < 18; ++i) {
        string s;
        cin >> s;
        pair<int, int> move = toMove(s);
        bob.insert(move);
    }

    vector<pair<int, int>> board(4, {-1, -1});
    if (bfs(board, 1, 18, 18)) {
        cout << "Alice";
    } else {
        cout << "Bob";
    }


    return 0;
}
