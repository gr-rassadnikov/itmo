#include <iostream>
#include <vector>

// Definition for singly-linked list.
using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution1 {
public:
    ListNode *mergeTwoLists(ListNode *u, ListNode *v) {
        ListNode *from = step(u, v);
        if (!from) {
            return from;
        }
        ListNode *now = step(u, v);
        from->next = now;
        while (now) {
            now->next = step(u, v);
            now = now->next;
        }
        return from;
    }

    ListNode *step(ListNode *&u, ListNode *&v) {
        ListNode *get;
        if (u && v) {
            if (u->val < v->val) {
                get = u;
                u = u->next;
            } else {
                get = v;
                v = v->next;
            }
        } else if (u && !v) {
            get = u;
            u = u->next;
        } else if (!u && v) {
            get = v;
            v = v->next;
        } else {
            get = u;
        }
        return get;
    }
};


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution2 {
public:
    bool isBalanced(TreeNode *root) {
        bool is = true;
        h(root, is);
        return is;
    }

    int h(TreeNode *node, bool &is) {
        if (!node) {
            return 0;
        }
        int l = h(node->left, is);
        int r = h(node->right, is);
        if (abs(r - l) > 1) {
            is = false;
        }
        return max(l, r) + 1;

    }
};


class Solution3 {
public:
    bool isSymmetric(TreeNode *root) {
        vector<TreeNode *> a = {root};
        vector<TreeNode *> b;
        while (!a.empty()) {
            for (auto v: a) {
                if (!v) continue;
                b.push_back(v->left);
                b.push_back(v->right);
            }
            for (int i = 0; i < b.size() / 2; i++) {
                if (!b[i] || !b[b.size() - i - 1]) {
                    if (b[i] || b[b.size() - i - 1]) {
                        return false;
                    }
                } else if (b[i]->val != b[b.size() - i - 1]->val) {
                    return false;
                }
            }
            a = b;
            b.clear();

        }

        return true;
    }

    vector<int> getNodes(TreeNode *node) {
        vector<int> arr = {};
        f(node, arr);
        return arr;
    }

    void f(TreeNode *v, vector<int> &arr) {
        if (v) {
            arr.push_back(v->val);
            f(v->left, arr);
            f(v->right, arr);
        } else {
            arr.push_back(-101);
        }
    }
};

//class Solution4 {
//    func isValidNode(node : TreeNode?, mn : Int, mx : Int) -> Bool {
//        guard let node = node else {return false}
//        var isValid = true
//        if let left = node.left {
//                if left.val >= node.val {
//                    return false
//                }
//                if left.val >= mx || left.val <= mn {
//                            return false
//                    }
//                isValid = isValid && isValidNode(node: left, mn: mn, mx: min(mx, node.val))
//            }
//        if let right = node.right {
//                if right.val <= node.val {
//                    return false
//                }
//                if right.val <= mn || right.val >= mx {
//                            return false
//                    }
//                isValid = isValid && isValidNode(node: right, mn: max(mn, node.val), mx: mx)
//            }
//        return isValid
//    }
//    func isValidBST(_ root: TreeNode?) -> Bool {
//        return isValidNode(node: root, mn: Int.min, mx: Int.max)
//    }
//}

//class Solution {
//    func isSubsequence(_ s: String, _ t: String) -> Bool {
//        var index = s.startIndex
//        if index == s.endIndex {
//            return true
//        }
//        for char in t {
//                if char == s[index] {
//                    index = s.index(after: index)
//                }
//                if index == s.endIndex {
//                    return true
//                }
//        }
//        return false
//    }
//}

//class Solution {
//    func twoSum(_ nums: [Int], _ target: Int) -> [Int] {
//        for i in 0..<nums.count {
//            for j in i+1..<nums.count {
//                if (nums[i] + nums[j] == target) {
//                    return [i , j]
//                }
//            }
//        }
//        return [-1, -1]
//    }
//}

//class Solution {
//    func groupAnagrams(_ strs: [String]) -> [[String]] {
//        var hash = Dictionary<[Character], [String]>()
//        for str in strs {
//                var chars = str.map{$0}
//
//                chars.sort()
//
//                hash[chars] = hash[chars, default: []] + [str]
//
//                // if let g = hash[chars] {
//                //     hash[chars].append(str)
//                // } else{
//                //     hash[chars] = [str]
//                // }
//        }
//        return hash.map{$1}
//    }
//}

class Solution5 {
public:
    void rotate(vector<vector<int>> &a) {
        int n = a.size();
        int k = n - 1;
        for (int i = 0; i < n / 2; i++) {
            for (int j = 0; j < n / 2; j++) {
                int c1 = a[j][k - i];
                a[j][k - i] = a[i][j];
                int c2 = a[k - i][k - j];
                a[k - i][k - j] = c1;
                int c3 = a[k - j][k - k + i];
                a[k - j][k - k + i] = c2;
                a[i][k - k + j] = c3;
            }
        }

        if (n % 2 == 1) {
            int i = n / 2;
            for (int j = 0; j < n / 2; j++) {
                int c1 = a[j][k - i];
                a[j][k - i] = a[i][j];
                int c2 = a[k - i][k - j];
                a[k - i][k - j] = c1;
                int c3 = a[k - j][k - k + i];
                a[k - j][k - k + i] = c2;
                a[i][k - k + j] = c3;
            }
        }
    }
};

class Solution6 {
public:
    int search(vector<int> &nums, int target) {
        int l = -1;
        int r = nums.size();
        while (r - l > 1) {
            int m = (r + l) / 2;
            if (nums[m] < target) {
                l = m;
            } else {
                r = m;
            }
        }
        if (r == nums.size()) {
            return -1;
        }
        if (nums[r] == target) {
            return r;
        }
        return -1;
    }
};

#include <map>

class Solution {
public:
    int subarraysDivByK(vector<int> &nums, int k) {
        map<int, int> d;
        d[0] = 1;
        int sum = 0;
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            sum += nums[i];
            int ost = (k + sum % k) % k;
            cout << ost;
            if (d.find(ost) != d.end()) {
                ans += d[ost]++;
            } else {
                d[ost] = 1;
            }

        }
        return ans;
    }
};

class Solution7 {
public:
    int maxDistToClosest(vector<int> &seats) {
        int n = seats.size();
        vector<int> toL(n, 1e9);
        vector<int> toR(n, 1e9);
        if (seats[0] == 1) toL[0] = 0;
        for (int i = 1; i < n; i++) {
            if (seats[i] == 1) {
                toL[i] = 0;
            } else {
                toL[i] = toL[i - 1] + 1;
            }
        }
        if (seats[n - 1] == 1) toR[n - 1] = 0;
        for (int i = n - 2; i >= 0; i--) {
            if (seats[i] == 1) {
                toR[i] = 0;
            } else {
                toR[i] = toR[i + 1] + 1;
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (seats[i] == 0) {
                int loc = min(toL[i], toR[i]);
                ans = max(ans, loc);
            }
        }
        return ans;
    }
};


using namespace std;

#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <string>

int main() {
    vector<int> a = {3, 6, 2, 1, 9, 3};
    sort(a.begin(), a.end(),
         [](const int &a, const int &b) -> bool {
             return a > b;
         });

    std::reverse(a.begin(), a.end());
    cout << (-8) % (3);

//    поиске upper_bound для значения 5 это будет итератор (указатель, если концепция итератора для вас нова) на значение 6 - первое большее значение.
//оответственно, lower_bound будет указывать на первое не меньшее значение - на первое 5.
//Например, код
    int s[20] = {1, 2, 3, 4, 5, 6, 7, 7, 7, 8, 9, 9, 11, 11, 12, 16, 20, 20, 20, 20};

    for (int *p = lower_bound(s, s + 20, 10);
         p != upper_bound(s, s + 20, 20); ++p)
        cout << *p << " ";
    cout << endl;


//    11 11 12 16 20 20 20 20
    return 0;
}
