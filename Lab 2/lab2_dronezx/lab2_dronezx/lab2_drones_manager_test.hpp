#ifndef DRONES_MANAGER_TEST
#define DRONES_MANAGER_TEST

#include "lab2_drones_manager.hpp"

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

class DronesManagerTest {
public:
	// PURPOSE: New empty list is valid
	bool test1() {
		DronesManager manager;
		ASSERT_TRUE(manager.get_size() == 0)
		ASSERT_TRUE(manager.empty() == true)
		ASSERT_TRUE(manager.first == NULL)
		ASSERT_TRUE(manager.last == NULL)
	    return true;
	}
	
	// PURPOSE: insert_front() and insert_back() on zero-element list
	bool test2() {
		DronesManager manager1, manager2;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager2.insert_back(DronesManager::DroneRecord(100));
	    
		ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 1)
		ASSERT_TRUE(manager1.first != NULL && manager1.first == manager1.last)
		ASSERT_TRUE(manager2.first != NULL && manager2.first == manager2.last)
		ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL)
		ASSERT_TRUE(manager2.first->prev == NULL && manager2.last->next == NULL)
		ASSERT_TRUE(manager1.select(0) == manager2.select(0) && manager1.select(0) == DronesManager::DroneRecord(100))		
	    return true;
	}
	
	// TODO: Implement all of the test cases below
	
	// PURPOSE: select() and search() work properly
	bool test3() {
		DronesManager::DroneRecord drones[]{
			DronesManager::DroneRecord(100),
			DronesManager::DroneRecord(200),
			DronesManager::DroneRecord(300),
			DronesManager::DroneRecord(400)
		};

		DronesManager m;
		DronesManager m2;
		for (int i = 0; i < 3; ++i) {
			m.insert_back(drones[i]);
		}

		ASSERT_TRUE(DronesManager::DroneRecord(200) == m.select(1))
			ASSERT_TRUE(DronesManager::DroneRecord(300) == m.select(2))
			ASSERT_TRUE(DronesManager::DroneRecord(0) == m2.select(5))

			ASSERT_TRUE(m.search(drones[1]) == 1)
			ASSERT_TRUE(m.search(drones[3]) == m.size)

			return true;
	}
	
	// PURPOSE: remove_front() and remove_back() on one-element list
	bool test4() {
		DronesManager::DroneRecord d(100);
		DronesManager m1;
		DronesManager m2;
		m1.insert_back(d);
		m2.insert_back(d);

		ASSERT_TRUE(m1.remove_front())
			ASSERT_TRUE(m1.first == NULL)
			ASSERT_TRUE(m1.last == NULL)
			ASSERT_TRUE(m1.size == 0)

			ASSERT_TRUE(m2.remove_back())
			ASSERT_TRUE(m2.first == NULL)
			ASSERT_TRUE(m2.last == NULL)
			ASSERT_TRUE(m2.size == 0)

			return true;
	}
	
	// PURPOSE: replace() and reverse_list() work properly
	bool test5() {
		DronesManager::DroneRecord drones[]{
		DronesManager::DroneRecord(100),
		DronesManager::DroneRecord(200),
		DronesManager::DroneRecord(300),
		DronesManager::DroneRecord(400)
		};

		DronesManager m;
		DronesManager m2;

		for (int i = 0; i < 4; ++i) {
			m.insert_back(drones[i]);
		}
		for (int i = 3; i >= 0; --i) {
			m2.insert_back(drones[i]);
		}

		ASSERT_FALSE(m.replace(4, drones[0]))
			ASSERT_TRUE(m.replace(3, drones[0]))
			ASSERT_TRUE(m2.replace(0, drones[0]))
			ASSERT_TRUE(m.reverse_list())
			for (int i = 0; i < 4; ++i) {
				ASSERT_TRUE(m.select(i) == m2.select(i))
			}

		return true;
	}
	
	// PURPOSE: insert_front() keeps moving elements forward
	bool test6() {
		DronesManager::DroneRecord drones[]{
			DronesManager::DroneRecord(100),
			DronesManager::DroneRecord(200),
			DronesManager::DroneRecord(300),
			DronesManager::DroneRecord(400)
		};

		DronesManager m;
		DronesManager m2; // holds the expected result

		for (int i = 0; i < 4; ++i) {
			m2.insert_back(drones[i]);
		}

		m.insert_front(drones[3]);
		ASSERT_TRUE(m.insert_front(drones[2]));
		ASSERT_TRUE(*m.first == drones[2])
			ASSERT_TRUE(m.select(0) == drones[2])
			ASSERT_TRUE(m.first->next == m.last)
			m.insert_front(drones[1]);
		m.insert_front(drones[0]);
		for (int i = 0; i < 4; ++i) {
			ASSERT_TRUE(m.select(i) == m2.select(i))
		}

		return true;
	}
	
	// PURPOSE: inserting at different positions in the list
	bool test7() {
		DronesManager::DroneRecord drones[]{
			DronesManager::DroneRecord(100),
			DronesManager::DroneRecord(200),
			DronesManager::DroneRecord(300),
			DronesManager::DroneRecord(400)
		};

		DronesManager m;
		DronesManager m2; // expected result
		for (int i = 0; i < 4; ++i) {
			m2.insert_back(drones[i]);
		}

		ASSERT_TRUE(m.insert(drones[1], 0))
			ASSERT_FALSE(m.insert(drones[3], 3))
			ASSERT_TRUE(m.insert(drones[0], 0))
			ASSERT_TRUE(m.insert(drones[3], 2))
			ASSERT_TRUE(m.insert(drones[2], 2))

			for (int i = 0; i < 4; ++i) {
				ASSERT_TRUE(m.select(i) == m2.select(i))
			}

		return true;
	}
	
	// PURPOSE: try to remove too many elements, then add a few elements
	bool test8() {
		DronesManager::DroneRecord drones[]{
			DronesManager::DroneRecord(100),
			DronesManager::DroneRecord(200),
			DronesManager::DroneRecord(300),
			DronesManager::DroneRecord(400)
		};

		DronesManager m;
		DronesManager m2; // expected result after a couple of middle removals
		for (int i = 0; i < 4; ++i) {
			m.insert_back(drones[i]);
		}
		m2.insert_front(drones[0]);
		m2.insert_back(drones[3]);
		ASSERT_TRUE(m.remove(2))
			ASSERT_TRUE(m.remove(1))
			ASSERT_TRUE(m.select(0) == m2.select(0))
			ASSERT_TRUE(m.select(1) == m2.select(1))

			ASSERT_FALSE(m.remove(2))
			ASSERT_TRUE(m.remove(0))
			ASSERT_TRUE(m.remove(0))
			ASSERT_FALSE(m.remove(0))

			ASSERT_TRUE(m.insert(drones[0], 0))
			ASSERT_TRUE(m.insert(drones[2], 0))
			ASSERT_TRUE(m.insert(drones[1], 1))
			ASSERT_TRUE(m.select(1) == drones[1])

			return true;
	}
	
	// PURPOSE: lots of inserts and deletes, some of them invalid
	bool test9() {
		DronesManager::DroneRecord drones[]{
			DronesManager::DroneRecord(100),
			DronesManager::DroneRecord(200),
			DronesManager::DroneRecord(300),
			DronesManager::DroneRecord(400)
		};

		DronesManager m;
		for (int i = 0; i < 4; ++i) {
			m.insert_front(drones[i]);
			m.insert_back(drones[i]);
		}
		// at this point, the list looks like:
		// [400, 300, 200, 100, 100, 200, 300, 400]

		for (int i = 0; i < 4; ++i) {
			ASSERT_TRUE(m.remove(2))
		}
		ASSERT_FALSE(m.remove(4))
			for (int i = 0; i < 4; ++i) {
				ASSERT_TRUE(m.insert(drones[0], 2))
			}
		ASSERT_FALSE(m.insert(drones[3], 9))
			ASSERT_TRUE(m.size == 8)
			for (int i = 0; i < 8; ++i) {
				ASSERT_TRUE(m.remove_front())
			}
		ASSERT_FALSE(m.remove(0))

			return true;
	}    
	    	
	// PURPOSE: inserts into an unsorted list, then sort the list
	bool test10() {
		DronesManager::DroneRecord drones_test_sort[]{
			DronesManager::DroneRecord(172),
			DronesManager::DroneRecord(2),
			DronesManager::DroneRecord(4),
			DronesManager::DroneRecord(4),
			DronesManager::DroneRecord(3),
			DronesManager::DroneRecord(5),
		};

		DronesManagerSorted sort_test;
		sort_test.insert_front(drones_test_sort[0]);
		sort_test.insert_front(drones_test_sort[1]);
		sort_test.insert_front(drones_test_sort[2]);
		sort_test.insert_front(drones_test_sort[3]);
		sort_test.insert_front(drones_test_sort[4]);
		sort_test.insert_front(drones_test_sort[5]);
		
		DronesManagerSorted sort_test_two;

		sort_test.sort_asc();
		ASSERT_TRUE(sort_test.is_sorted_asc());
		sort_test_two.sort_asc();
		ASSERT_TRUE(sort_test.is_sorted_asc());

		sort_test.sort_desc();
		ASSERT_TRUE(sort_test.is_sorted_desc());
		sort_test_two.sort_desc();
		ASSERT_TRUE(sort_test_two.is_sorted_desc());
	}  
	
	// PURPOSE: insert and remove into sorted manager in ascending order
	bool test11() {
		DronesManager::DroneRecord drones[]{
			DronesManager::DroneRecord(100),
			DronesManager::DroneRecord(200),
			DronesManager::DroneRecord(300),
			DronesManager::DroneRecord(400),
			DronesManager::DroneRecord(500)
		};
		DronesManagerSorted m;
		m.insert_front(drones[0]);
		m.insert_sorted_asc(drones[1]);
		m.insert_sorted_asc(drones[4]);
		m.insert_sorted_asc(drones[3]);
		m.insert_sorted_asc(drones[2]);
		ASSERT_TRUE(m.select(0) == drones[0]);
		ASSERT_TRUE(m.select(1) == drones[1]);
		ASSERT_TRUE(m.select(2) == drones[2]);
		ASSERT_TRUE(m.select(3) == drones[3]);
		ASSERT_TRUE(m.select(4) == drones[4]);
		ASSERT_TRUE(m.is_sorted_asc());
		ASSERT_TRUE(!m.is_sorted_desc());
		return true;
	}
	
	// PURPOSE: insert and remove into sorted manager in descending order
	bool test12() {
		DronesManager::DroneRecord drones[]{
			 DronesManager::DroneRecord(100),
			 DronesManager::DroneRecord(200),
			 DronesManager::DroneRecord(300),
			 DronesManager::DroneRecord(400),
			 DronesManager::DroneRecord(500)
		};
		DronesManagerSorted m;
		m.insert_sorted_desc(drones[0]);
		m.insert_sorted_desc(drones[1]);
		m.insert_sorted_desc(drones[4]);
		m.insert_sorted_desc(drones[3]);
		m.insert_sorted_desc(drones[2]);
		ASSERT_TRUE(m.select(0) == drones[4]);
		ASSERT_TRUE(m.select(1) == drones[3]);
		ASSERT_TRUE(m.select(2) == drones[2]);
		ASSERT_TRUE(m.select(3) == drones[1]);
		ASSERT_TRUE(m.select(4) == drones[0]);
		ASSERT_TRUE(m.is_sorted_desc());
		ASSERT_TRUE(!m.is_sorted_asc());
		return true;
	}  
};

#endif
