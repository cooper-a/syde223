#ifndef PE2
#define PE2

#include <string>
using namespace std;

typedef struct BinaryTreeNode {
    int value;
    BinaryTreeNode* left;
    BinaryTreeNode* right;
    BinaryTreeNode(int val) : value(val), left(NULL), right(NULL) {}
} BinaryTreeNode;

// Step 1
void find_and_print_sum_of_nodes(BinaryTreeNode* T, int desired_sum, int cur_sum,
    string buffer);

// Step 2
int find_max_sum_of_nodes(BinaryTreeNode* T);
#endif // PE2
