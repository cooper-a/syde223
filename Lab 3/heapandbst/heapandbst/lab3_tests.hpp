#ifndef LAB3_TESTS_HPP
#define LAB3_TESTS_HPP

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

#include <algorithm>
#include <sstream>
#include <queue>

#include "lab3_priority_queue.hpp"
#include "lab3_binary_search_tree.hpp"

#define TI TaskItem
#define PQ PriorityQueue

class PriorityQueueTest {
public:
	// PURPOSE: Tests if the new queue is valid
	bool test1() {
		PriorityQueue q(5);
		ASSERT_TRUE( q.empty() );
		ASSERT_TRUE( !q.full() );
		ASSERT_TRUE( q.get_size() == 0 );
		return true;
	}
	// PURPOSE: Tests enqueue of one item and then dequeue of that item
	bool test2() {
		//Using a macro to save some typing
		PQ q(10);
		ASSERT_TRUE(q.enqueue(PQ::TI(12, "igor")));
		ASSERT_TRUE(!q.empty());
		ASSERT_TRUE(q.get_size() == 1);
		ASSERT_TRUE(q.dequeue());
		ASSERT_TRUE(q.empty());
		ASSERT_TRUE(q.get_size() == 0);
		return true;
	}

	// PURPOSE: Tests enqueue too many
	bool test3() {
		PQ q(3);
		ASSERT_TRUE(q.enqueue(PQ::TI(12, "igor")));
		ASSERT_TRUE(q.enqueue(PQ::TI(13, "igor")));
		ASSERT_TRUE(q.enqueue(PQ::TI(14, "igor")));
		ASSERT_FALSE(q.enqueue(PQ::TI(1, "igor")));
		return true;
	}

	// PURPOSE: Tests enqueue too many then dequeue too many
	bool test4() {
		PQ q(5);
		ASSERT_TRUE(q.enqueue(PQ::TI(12, "igor")));
		ASSERT_TRUE(q.enqueue(PQ::TI(13, "igor")));
		ASSERT_TRUE(q.enqueue(PQ::TI(14, "igor")));
		ASSERT_TRUE(q.enqueue(PQ::TI(2, "igor")));
		ASSERT_TRUE(q.enqueue(PQ::TI(29, "igor")));
		ASSERT_FALSE(q.enqueue(PQ::TI(1, "igor")));
		// q.print();
		ASSERT_TRUE(q.dequeue());
		ASSERT_TRUE(q.dequeue());
		ASSERT_TRUE(q.dequeue());
		ASSERT_TRUE(q.dequeue());
		ASSERT_TRUE(q.dequeue());
		ASSERT_FALSE(q.dequeue());
		return true;
	}

};

class BinarySearchTreeTest {
public:
	bool insert_nodes(BinarySearchTree &tree, int *in, int nin) {
		for(int i = 0; i < nin; i++) {
			ASSERT_TRUE(tree.insert(BinarySearchTree::TaskItem(in[i],"Test Task")));
		}
		return true;
	}

	// PURPOSE: Traverse the tree using breadth-first traversal
	// Output is as follows: "val1 val2 ... valN"
	std::string level_order(BinarySearchTree::TaskItem* root) {
		if (!root) {
      		return "";
    	}    

		std::stringstream ss;
		std::queue<BinarySearchTree::TaskItem*> node_queue;
		node_queue.push(root);
		while (!node_queue.empty()) {
			BinarySearchTree::TaskItem* cur_node = node_queue.front();
			node_queue.pop();
			ss << cur_node->priority << " ";
			if (cur_node->left) {
				node_queue.push(cur_node->left);
			}
			if (cur_node->right) {
				node_queue.push(cur_node->right);
			}
		}
    
		std::string level_order_str = ss.str();

		return level_order_str.substr(0, level_order_str.size() - 1);
	}

	// PURPOSE: Tests if the new tree is valid
	bool test1() {
		std::string expected_tree_level_order = "";
    
		BinarySearchTree bst;
		ASSERT_TRUE(bst.root == NULL);
		ASSERT_TRUE(bst.size == 0 && bst.get_size() == 0);
    
		// compare the tree's representation to the expected tree
		std::string tree_level_order = level_order(bst.root);
		ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)
		return true;
	}
// lab provided names are too long :(
#define BTI(n) BinarySearchTree::TaskItem(n, "igor") 
	// PURPOSE: Tests a tree with one node
	bool test2() {
		std::string expect = "42";
		BinarySearchTree b;

		ASSERT_TRUE(b.insert(BTI(42)));
		ASSERT_TRUE(*b.root == BTI(42));
		ASSERT_TRUE(b.size == 1 && b.get_size() == 1);
		ASSERT_TRUE(b.max() == b.min() && b.min() == BTI(42));
		ASSERT_TRUE(b.height() == 0);
		ASSERT_TRUE(b.exists(BTI(42)));
		ASSERT_FALSE(b.exists(BTI(41)));
		ASSERT_FALSE(b.remove(BTI(24)));
		ASSERT_TRUE(level_order(b.root) == expect);
		ASSERT_TRUE(b.remove(BTI(42)));

		return true;
	}

	// PURPOSE: Tests insert, remove, and size on linear list formation with three elements
	bool test3() {
		std::string expect = "101 102 103";
		BinarySearchTree b;
		
		for (int i = 101; i < 104; i++) {
			ASSERT_TRUE(b.insert(BTI(i)));
			ASSERT_TRUE(b.get_size() == b.size && b.size == i - 100);
		}
		ASSERT_TRUE(level_order(b.root) == expect);
		ASSERT_TRUE(b.size == 3 && b.get_size() == 3);
		ASSERT_TRUE(b.max() == BTI(103) && b.min() == BTI(101));
		ASSERT_TRUE(b.height() == 2);
		for (int i = 101; i < 104; i++) {
			ASSERT_TRUE(b.exists(BTI(i)));
		}
		ASSERT_FALSE(b.remove(BTI(104)));
		for (int i = 103; i > 100; i--) {
			ASSERT_TRUE(b.remove(BTI(i)));
		}

		return true;
	}

	// PURPOSE: Tests removal of a node with one child
	bool test4() {
		std::string expect_pre = "200 100 500 300";
		std::string expect_post = "200 100 300";
		BinarySearchTree b;

		ASSERT_TRUE(b.insert(BTI(200)));
		ASSERT_TRUE(b.insert(BTI(100)));
		ASSERT_TRUE(b.insert(BTI(500)));
		ASSERT_TRUE(b.insert(BTI(300)));
		ASSERT_TRUE(b.height() == 2);
		ASSERT_TRUE(level_order(b.root) == expect_pre);

		ASSERT_TRUE(b.remove(BTI(500)));
		ASSERT_TRUE(b.height() == 1);
		ASSERT_FALSE(b.exists(BTI(500)));
		ASSERT_TRUE(level_order(b.root) == expect_post);

		return true;
	}

	// PURPOSE: Tests insert of multiple elements and remove till nothing remains
	bool test5() {
		int toInsert[] = { 400, 200, 600, 100, 300, 500, 700 };
		std::string expect_pre = "400 200 600 100 300 500 700";
		std::string expect_post = "";
		BinarySearchTree b;

		for (int i = 0; i < 7; i++) {
			ASSERT_TRUE(b.insert(BTI(toInsert[i])));
			ASSERT_TRUE(b.size == b.get_size() && b.size == i + 1);
		}
		ASSERT_TRUE(b.height() == 2);
		ASSERT_TRUE(level_order(b.root) == expect_pre);
		for (int i = 6; i >= 0; i--) {
			ASSERT_TRUE(b.remove(BTI(toInsert[i])));
			ASSERT_FALSE(b.exists(BTI(toInsert[i])));
		}
		ASSERT_TRUE(level_order(b.root) == expect_post);
		ASSERT_TRUE(b.root == NULL);

		return true;
	}

	// PURPOSE: Tests removal of root node when both children of root have two children
	bool test6() {
		int toInsert[] = { 400, 200, 600, 100, 300, 500, 700 };
		std::string expect_pre = "400 200 600 100 300 500 700";
		std::string expect_post = "500 200 600 100 300 700";
		BinarySearchTree b;

		for (int i = 0; i < 7; i++) {
			ASSERT_TRUE(b.insert(BTI(toInsert[i])));
			ASSERT_TRUE(b.size == b.get_size() && b.size == i + 1);
		}
		ASSERT_TRUE(b.remove(BTI(400)));
		ASSERT_TRUE(level_order(b.root) == expect_post);

		return true;
	}

	// PURPOSE: Tests depth with many inserts and some removes
	bool test7() {
		std::string expected = "500 499 501 498 502 497 503 496 504";
		BinarySearchTree b;

		for (int i = 500; i < 505; i++) {
			ASSERT_TRUE(b.insert(BTI(i)));
			ASSERT_TRUE(b.height() == i - 500);
		}
		int final_height = b.height();
		for (int i = 499; i >= 496; i--) {
			ASSERT_TRUE(b.insert(BTI(i)));
			ASSERT_TRUE(b.height() == final_height);
		}
		for (int i = 499; i >= 496; i--) {
			ASSERT_TRUE(b.remove(BTI(i)));
			ASSERT_TRUE(b.height() == final_height);
		}
		for (int i = 500; i < 505; i++) {
			ASSERT_TRUE(b.remove(BTI(i)));
		}
		ASSERT_TRUE(b.size == 0);

		return true;
	}

	// PURPOSE: Tests lots of inserts and removes
	bool test8() {
		std::string expected = "400 200 600 100 300 500 700 50 150 250 350 450 550 650 750";
		int toInput[] = { 400, 200, 600, 100, 300, 500, 700, 
						  50, 150, 250, 350, 450, 550, 650, 750 };
		BinarySearchTree b;

		for (int i = 0; i < 15; i++) {
			ASSERT_TRUE(b.insert(BTI(toInput[i])));
			ASSERT_TRUE(b.exists(BTI(toInput[i])));
		}
		ASSERT_TRUE(level_order(b.root) == expected);
		for (int i = 0; i < 15; i++) {
			ASSERT_TRUE(b.remove(BTI(toInput[i])));
			ASSERT_FALSE(b.exists(BTI(toInput[i])));
		}
		ASSERT_TRUE(b.size == 0);
		return true;
	}
};
#endif
