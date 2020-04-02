#include "practice_exercise2.hpp"
#include <iostream>
#include <string>
#include <climits>
using namespace std;

void find_and_print_sum_of_nodes(BinaryTreeNode* T, int desired_sum, int cur_sum,
    string buffer) {
    // exit if T is NULL
    if (T == NULL) {
        return;
    }

    // update the ongoing sum with current value for T
    int new_sum = cur_sum + T->value;

    // update the current path string
    string new_buffer = buffer + " " + to_string(T->value);

    // if the desired sum is found, print the corresponding path
    if (new_sum == desired_sum) {
        cout << new_buffer << endl;
    }

    // continue down the left subtree
    find_and_print_sum_of_nodes(T->left, desired_sum, new_sum, new_buffer);

    // continue down right subtree
    find_and_print_sum_of_nodes(T->right, desired_sum, new_sum, new_buffer);

    // restart from the left subtree if buffer = ""
    if (buffer == "") {
        find_and_print_sum_of_nodes(T->left, desired_sum, 0, "");
    }

    if (buffer == "") {
        find_and_print_sum_of_nodes(T->right, desired_sum, 0, "");
    }
}

int find_max_sum_of_nodes(BinaryTreeNode* T, int& temp_max_sum) {
    // exit if T is NULL
    if (T == NULL) {
        return 0;
    }

    // derive the maximum sum for the left subtree
    int left_sum = find_max_sum_of_nodes(T->left, temp_max_sum);

    // derive the maximum sum for the right subtree
    int right_sum = find_max_sum_of_nodes(T->right, temp_max_sum);

    // compare T->value, left_sum + T->value, and right_sum + T->value
    int sumMax1 = left_sum + T->value > right_sum + T->value ? 
        left_sum + T->value : right_sum + T->value;
    // int sumMax1 = (left_sum > right_sum ? left_sum : right_sum) + T->value;
    int max1 = sumMax1 > T->value ? sumMax1 : T->value;

    // compare max1, left_sum + right_sum + T->value, store as max2
    int tempSum = left_sum + right_sum + T->value;
    int max2 = tempSum > max1 ? tempSum : max1;

    // update temp_max_sum with the new max
    int trueMax = max1 > max2 ? max1 : max2;
    if (trueMax > temp_max_sum) {
        temp_max_sum = trueMax;
    }

    // return max1
    return max1;
}

int find_max_sum_of_nodes(BinaryTreeNode* T) {
    int temp_max_sum = INT_MIN;
    
    find_max_sum_of_nodes(T, temp_max_sum);

    return temp_max_sum;
}