#include "practice_exercise2.hpp"
#include "practice_exercise2_test.hpp"
#include <iostream>

int main(void) {
    cout << "PRACTICE_EXERCISE2: RUNNING TESTS...\n" << endl;
    bool printPass = print_sum_test();
    bool maxPass = max_sum_test();
    cout << "**********************" << endl;
    cout << "TEST RESULTS:" << endl;
    cout << "find_and_print_sum_of_nodes: " << (printPass ? "PASSED" : "FAILED") << endl;
    cout << "find_max_sum_of_nodes:       " << (maxPass ? "PASSED" : "FAILED") << endl;
    getchar();
    return 0;
}
