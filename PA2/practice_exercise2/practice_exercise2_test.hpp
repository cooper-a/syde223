/*
 * 
 * Please note: we wrote the code before there were some clarifications on slack,
 * where Audrey said not to use to_string so you don't have to include extra libraries to test.
 * However this function is included in the <string> library that is included in the specs.
 * We submitted before the friday deadline, only resubmitting to add the specs that were
 * clarified *after* the deadline. Please be lenient on part marks because of the vague specs.
 * 
 */

#include "practice_exercise2.hpp"
#include <cmath> // used for pow function to help build btrees
#include <iostream> // used for printing
#include <vector> // used as utility to help build btrees
#include <sstream> // used to test cout buffer from print functions

using namespace std;

// used as INT_MIN
#define IM (-2147483648)

// please don't grade this, this is just to build trees
// the lab specs didn't say anything about using a class and I was lazy ok
BinaryTreeNode* build_BTree(int* nodes, int levels) {
    vector<vector<BinaryTreeNode*>> tree;
    // allocate new nodes for each desired node
    for (int i = 0; i < levels; i++) {
        tree.push_back(vector<BinaryTreeNode*>());
        int nodeCount = int(pow(2, i));
        for (int j = 0; j < nodeCount; j++) {
            int ind = nodeCount - 1 + j;
            if (nodes[ind] == IM) {
                tree[i].push_back(NULL);
            } else {
                tree[i].push_back(new BinaryTreeNode(nodes[ind]));
            }
        }
    }
    // link tree together
    for (int i = 0; i < levels - 1; i++) {
        int nodeCount = int(pow(2, i));
        for (int j = 0; j < nodeCount; j++) {
            if (tree[i][j] != NULL) {
                tree[i][j]->left = tree[i + 1][2 * j];
                tree[i][j]->right = tree[i + 1][2 * j + 1];
            }
        }
    }
    return tree[0][0];
}

void delete_BTree(BinaryTreeNode* root) {
    if (root != NULL) {
        delete_BTree(root->right);
        delete_BTree(root->left);
    }
}

bool print_sum_test() {
    cout << "***********************************" << endl;
    cout << "testing find_and_print_sum_of_nodes" << endl;
    cout << "***********************************" << endl;
    // IM represents a NULL node
    int trees[3][15] = {
        {
            5, 
            3, 1, 
            -1, 8, IM, 11, 
            18, IM, 6, IM, IM, IM, IM, IM 
        },
        {
            2,
            2, 2,
            2, 2, 2, 2,
            1, 2, 2, 2, 2, 2, 2, 2
        },
        {
            4,
            3, 1,
            2, IM, 2, IM,
            1, IM, IM, IM, IM, 3, IM, IM
        }
    };
    int desired_sums[] = {
        17,
        3,
        10
    };
    string expected[] = {
        " 5 1 11\n"
        " 3 8 6\n"
        " -1 18\n",

        " 2 1\n",

        " 4 3 2 1\n"
        " 4 1 2 3\n"
    };
    bool ret = true;
    for (int i = 0; i < 3; i++) {
        cout << ">>>>>>>>TEST " << to_string(i + 1) << "<<<<<<<<" << endl;
        // get the tree
        auto root = build_BTree(trees[i], 4);
        string buf = "";
        stringstream ss;
        // write the output of the function to a stringstream for testing
        auto old_buf = cout.rdbuf(ss.rdbuf());
        find_and_print_sum_of_nodes(root, desired_sums[i], 0, buf);
        cout.rdbuf(old_buf);
        cout << "expected: \n" << expected[i];
        cout << "retrieved: \n" << ss.str();
        // compare the expected vs the actual output
        bool correct = ss.str() == expected[i];
        cout << "........correct? " << (correct ? "YES" : "NO") << endl;
        ret = ret && correct;
        delete_BTree(root);
    }
    return ret;
}

bool max_sum_test() {
    cout << "*****************************" << endl;
    cout << "testing find_max_sum_of_nodes" << endl;
    cout << "*****************************" << endl;
    // IM represents a NULL node
    int trees[3][15] {
        {
            5,
            6, -15,
            15, 10, -12, 9,
            IM, IM, IM, -5, IM, IM, IM, IM
        },
        {
            6,
            10, 4,
            IM, -5, IM, -6,
            IM, IM, IM, 4, IM, IM, IM, 7
        },
        {
            1,
            2, 3,
            4, -9, -9, 5,
            6, -9, -9, -9, -9, -9, -9, 7
        }
    };
    int expected[] = {
        31,
        21,
        28
    };
    bool ret;
    for (int i = 0; i < 3; i++) {
        cout << ">>>>>>>>TEST " << to_string(i + 1) << "<<<<<<<<" << endl;
        auto root = build_BTree(trees[i], 4);
        int ans = find_max_sum_of_nodes(root);
        cout << "expected:  " << expected[i] << endl;
        cout << "retrieved: " << ans << endl;
        bool correct = expected[i] == ans;
        ret = ret && correct;
        cout << "........correct? " << (correct ? "YES" : "NO") << endl;
        delete_BTree(root);
    }
    return ret;
}
