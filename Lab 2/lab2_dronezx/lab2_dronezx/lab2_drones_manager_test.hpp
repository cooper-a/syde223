#ifndef DRONES_MANAGER_TEST
#define DRONES_MANAGER_TEST

#include "lab2_drones_manager.hpp"
#include <random>

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

#define DM DronesManager
#define DMS DronesManagerSorted

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

	// I use the macro DM for DronesManager because the name is long.

	// PURPOSE: select() and search() work properly
	bool test3() {
		DM m;
		for (int i = 0; i < 10; i++) 
			m.insert_back(DM::DroneRecord(100 * i));
		for (int i = 0; i < 10; i++) {
			ASSERT_TRUE(m.search(100 * i) == i)
			ASSERT_TRUE(m.select(i) == DM::DroneRecord(100 * i))
		}
		DMS ms;
		for (int i = 0; i < 10; i++)
			ms.insert_back(DM::DroneRecord(100 * i));
		for (int i = 0; i < 10; i++) {
			ASSERT_TRUE(m.search(100 * i) == i)
			ASSERT_TRUE(m.select(i) == DM::DroneRecord(100 * i))
		}
	    return true;
	}
	
	// PURPOSE: remove_front() and remove_back() on one-element list
	bool test4() {
		DM m;
		m.insert_back(DM::DroneRecord(100));
		ASSERT_TRUE(m.remove_front())
		ASSERT_FALSE(m.remove_front())
		m.insert_back(DM::DroneRecord(100));
		ASSERT_TRUE(m.remove_back());
		ASSERT_FALSE(m.remove_back());
	    return true;
	}
	
	// PURPOSE: replace() and reverse_list() work properly
	bool test5() {
		DM m1, m2;
		ASSERT_FALSE(m1.replace(0, DM::DroneRecord(999)))
		for (int i = 0; i < 10; i++) {
			DM::DroneRecord r = DM::DroneRecord(i * 100);
			m1.insert_back(r);
			m2.insert_front(r);
		}
		ASSERT_TRUE(m1.reverse_list())
		for (int i = 0; i < 10; i++)
			ASSERT_TRUE(m1.select(i) == m2.select(i))
		for (int i = 0; i < 10; i++)
			ASSERT_TRUE(m1.replace(i, DM::DroneRecord(999)))
		ASSERT_FALSE(m1.replace(10, DM::DroneRecord(999)))
	    return true;
	}
	
	// PURPOSE: insert_front() keeps moving elements forward
	bool test6() {
		DM m;
		for (int i = 0; i < 10; i++) {
			m.insert_front(DM::DroneRecord(100 * i));
			ASSERT_TRUE(m.select(i) == DM::DroneRecord(0))
			ASSERT_TRUE(m.select(0) == DM::DroneRecord(100 * i))
		}
	    return true;
	}
	
	// PURPOSE: inserting at different positions in the list
	bool test7() {
		DM m;
		for (int i = 0; i < 10; i++)
			m.insert_back(DM::DroneRecord(200 * i + 100));
		for (int i = 0; i < 10; i++) {
			ASSERT_TRUE(m.insert(DM::DroneRecord(200 * i), i * 2))
		}
		for (int i = 0; i < m.get_size(); i++) {
			ASSERT_TRUE(m.select(i) == DM::DroneRecord(100 * i));
		}
	    return true;
	}
	
	// PURPOSE: try to remove too many elements, then add a few elements
	bool test8() {
		DM m;
		for (int i = 0; i < 20; i++)
			m.insert_back(DM::DroneRecord(100 * i));
		for (int i = 0; i < 10; i++) {
			ASSERT_TRUE(m.remove(10));
		}
		ASSERT_FALSE(m.remove(10));
		for (int i = 0; i < 20; i++) {
			if (i < 10) {
				ASSERT_TRUE(m.remove(0))
			} else {
				ASSERT_FALSE(m.remove(0))
			}
		}
		for (int i = 0; i < 10; i++) {
			m.insert_back(DM::DroneRecord(100 * i));
		}
		for (int i = 0; i < 10; i++) {
			ASSERT_TRUE(m.select(i) == DM::DroneRecord(100 * i));
		}
	    return true;
	}
	
	// PURPOSE: lots of inserts and deletes, some of them invalid
	bool test9() {
		minstd_rand gen;
		gen.seed(42);
		DM m;
		for (int i = 0; i < 10; i++) {
			m.insert_back(DM::DroneRecord(100 * i));
		}
		for (auto i = 0; i < 30; i++) {
			int idx = gen() % 20;
			if (idx >= m.get_size()) {
				ASSERT_FALSE(m.insert(DM::DroneRecord(100 * i), idx))
			} else {
				ASSERT_TRUE(m.insert(DM::DroneRecord(100 * i), idx))
			}
		}
		for (auto i = 0; i < 30; i++) {
			int idx = gen() % 20;
			if (idx >= m.get_size()) {
				ASSERT_FALSE(m.remove(idx))
			} else {
				ASSERT_TRUE(m.remove(idx))
			}
		}
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
		ASSERT_TRUE(sort_test_two.is_sorted_asc());

		sort_test.sort_desc();
		ASSERT_TRUE(sort_test.is_sorted_desc());
		sort_test_two.sort_desc();
		ASSERT_TRUE(sort_test_two.is_sorted_desc());

		DronesManager::DroneRecord drones[]{
			DronesManager::DroneRecord(100),
			DronesManager::DroneRecord(200),
			DronesManager::DroneRecord(300),
			DronesManager::DroneRecord(400)
		};

		DronesManager m;
		DronesManager m2;
		for (int i = 0; i < 4; ++i) {
			ASSERT_TRUE(m.insert(drones[i], i))
				ASSERT_TRUE(m2.insert_back(drones[i]))
		}

		for (int i = 0; i < 4; ++i) {
			ASSERT_TRUE(m.select(i) == m2.select(i))
		}

		m.reverse_list();
		m.reverse_list();

		for (int i = 0; i < 4; ++i) {
			ASSERT_TRUE(m.select(i) == m2.select(i))
		}

		m.reverse_list();

		for (int i = 0; i < 3; ++i) {
			ASSERT_TRUE(m.remove(1))
		}

		ASSERT_TRUE(m.first == m.last)
		ASSERT_TRUE(m.size == 1)
		ASSERT_TRUE(m.select(0) == drones[3])

		ASSERT_TRUE(m.remove(0))
		ASSERT_FALSE(m.remove(0))
		ASSERT_TRUE(m.first == NULL && m.first == m.last)

		return true;
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
		DronesManagerSorted m1;
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
