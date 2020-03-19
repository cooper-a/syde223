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
		q.print();
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
		string expected = "";
    
		BinarySearchTree tree;
		ASSERT_TRUE(tree.root == NULL);
		ASSERT_TRUE(tree.size == 0 && tree.get_size() == 0);
		ASSERT_TRUE(tree.height() == 0);
		string real = level_order(tree.root);
		ASSERT_TRUE(expected == real);
		return true;
	}

	// PURPOSE: Tests a tree with one node
	bool test2() {
		std::string expected_tree_level_order = "5";
		BinarySearchTree bst;
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(5, "Test Task")));
		cout << "my level order" << level_order(bst.root);
		ASSERT_TRUE(!bst.remove(BinarySearchTree::TaskItem(4, "Test Task")));
		ASSERT_TRUE(bst.exists(BinarySearchTree::TaskItem(5, "Test Task")));
		ASSERT_TRUE(bst.max() == bst.min() && bst.max() == BinarySearchTree::TaskItem(5, "Test Task"));
		ASSERT_TRUE(bst.get_size() == 1);

		std::string tree_level_order = level_order(bst.root);
		ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)
			return true;
	}

	// PURPOSE: Tests insert, remove, and size on linear list formation with three elements
	bool test3() {
		std::string expected_tree_level_order = "10 8";

		BinarySearchTree bst;
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(10, "Test Task")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(8, "Test Task")));
		ASSERT_TRUE(bst.get_size() == 2);
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(65, "Test Task")));
		ASSERT_TRUE(bst.get_size() == 3);

		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(65, "Test Task")));
		ASSERT_TRUE(bst.get_size() == 2);

		std::string tree_level_order = level_order(bst.root);
		ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)
			return true;
	}

	// PURPOSE: Tests removal of a node with one child
	bool test4() {
		std::string expected_tree = "3 2 6";

		BinarySearchTree bst;
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(3, "Test Task")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(7, "Test Task")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(6, "Test Task")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(2, "Test Task")));

		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(7, "Test Task")));
		ASSERT_TRUE(!bst.exists(BinarySearchTree::TaskItem(7, "Test Task")));
		ASSERT_TRUE(level_order(bst.root).compare(expected_tree) == 0)
			return true;
	}

	// PURPOSE: Tests insert of multiple elements and remove till nothing remains
	bool test5() {
		std::string expected_tree = "";

		BinarySearchTree bst;
		int in[] = { 8, 3, 10, 15 };

		ASSERT_TRUE(insert_nodes(bst, in, 4));
		ASSERT_TRUE(!bst.remove(BinarySearchTree::TaskItem(9, "Test Task")));
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(8, "Test Task")));
		ASSERT_TRUE(bst.max() == BinarySearchTree::TaskItem(15, "Test Task"));
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(15, "Test Task")));
		ASSERT_TRUE(bst.max() == BinarySearchTree::TaskItem(10, "Test Task"));
		ASSERT_TRUE(bst.min() == BinarySearchTree::TaskItem(3, "Test Task"));
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(10, "Test Task")));
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(3, "Test Task")));
		ASSERT_TRUE(bst.root == NULL);
		ASSERT_TRUE(level_order(bst.root).compare(expected_tree) == 0)
			return true;
	}

	// PURPOSE: Tests removal of root node when both children of root have two children
	bool test6() {
		std::string expected_tree1 = "6 3 10 1 9 15";
		std::string expected_tree2 = "9 3 10 1 6 15";

		BinarySearchTree bst;
		int in[] = { 8, 3, 10, 1, 6, 9, 15 };

		ASSERT_TRUE(insert_nodes(bst, in, 7));
		ASSERT_TRUE(!bst.remove(BinarySearchTree::TaskItem(12, "Test Task")));
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(8, "Test Task")));
		ASSERT_TRUE(level_order(bst.root).compare(expected_tree1) == 0 ||
			level_order(bst.root).compare(expected_tree2) == 0)
			return true;
	}

	// PURPOSE: Tests depth with many inserts and some removes
	bool test7() {
		std::string expected_tree = "0 -5 10 -2 1 -4 -1";
		cout << endl;

		BinarySearchTree bst;
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(0, "Test Task")));
		cout << bst.height() << "should be 0";
		ASSERT_TRUE(bst.height() == 0)
			ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(10, "Test Task")));
		ASSERT_TRUE(bst.height() == 1)
			ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(-5, "Test Task")));
		ASSERT_TRUE(bst.height() == 1)
			ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(-2, "Test Task")));
		ASSERT_TRUE(bst.height() == 2);
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(-4, "Test Task")));
		ASSERT_TRUE(bst.height() == 3);
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(-1, "Test Task")));
		ASSERT_TRUE(bst.height() == 3);
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(1, "Test Task")));
		ASSERT_TRUE(bst.height() == 3);
		ASSERT_TRUE(level_order(bst.root).compare(expected_tree) == 0)
			return true;
	}

	// PURPOSE: Tests lots of inserts and removes
	bool test8() {
		std::string expected_tree = "8 2 9 1 7 4 3 5 6";

		BinarySearchTree bst;
		int in[] = { 8, 2, 7, 4, 5, 3, 1, 9, 6 };
		int nin = 9;
		ASSERT_TRUE(insert_nodes(bst, in, nin));
		ASSERT_TRUE(level_order(bst.root).compare(expected_tree) == 0)
			for (int i = 0; i < nin; ++i) {
				ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(in[i], "Test Task")));
			}
		ASSERT_TRUE(!bst.remove(BinarySearchTree::TaskItem(in[0], "Test Task")));
		return true;
	}
};
#endif
