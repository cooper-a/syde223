#include "lab2_drones_manager.hpp"
#include <iostream>
// TODO: Implement all of the listed functions below
using namespace std;

#define INT_MAX 2147483647

DronesManager::DronesManager() {
	first = NULL;
	last = NULL;
	size = 0;
}

DronesManager::~DronesManager() {
	if (!size == 0) {
		DroneRecord* current = first->next;
		DroneRecord* next;
		while (current != NULL) {
			next = current->next;
			delete(current);
			current = next;
		}
	}
	
}

bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
	bool equals = true;
	equals = lhs.droneID == rhs.droneID && lhs.range == rhs.range && lhs.batteryType == rhs.batteryType && lhs.description == rhs.description;
	equals = equals && lhs.droneType == rhs.droneType && lhs.manufacturer == rhs.manufacturer && lhs.yearBought == rhs.yearBought;
	return equals;
}

unsigned int DronesManager::get_size() const {
	return size;
}

bool DronesManager::empty() const {
	return size == 0;
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
	if (first == NULL) return DroneRecord(0);
	if (index > size - 1) index = size - 1;
	DroneRecord* current = first;
	unsigned int counter = 0;
	while (current) {
		if (counter == index) {
			return *current;
		}
		counter++;
		current = current->next;
	}
	
}

unsigned int DronesManager::search(DroneRecord value) const {
	if (first == NULL) return 0;
	DroneRecord* current = first;
	int index = 0;
	while (current != NULL) {
		if (*current == value) return index;
		current = current->next;
		index++;
	}
	return size;
}

void DronesManager::print() const {
	DroneRecord* current = first;
	if (current == NULL) cout << "NULL" << endl;
	while (current) {
		cout << "[" << current->droneID << "]->";
		current = current->next;
	}
	cout << "NULL" << endl;
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {
	if (index > size) return false;
	if (index == 0) insert_front(value);
	else if (index == size) insert_back(value);
	else {
		DroneRecord* copied_value = new DroneRecord();
		*copied_value = value;
		DroneRecord* current = first;
		for (unsigned int i = 0; i < index; i++) {
			current = current->next;
		}
		DroneRecord* temp_prev = current->prev;
		temp_prev->next = copied_value;
		copied_value->prev = temp_prev;
		current->prev = copied_value;
		copied_value->next = current;
		size++;
	}
	return true;
}

bool DronesManager::insert_front(DroneRecord value) {
	DroneRecord* copied_value = new DroneRecord();
	*copied_value = value;
	if (first == NULL) {
		first = copied_value;
		last = copied_value;
	}
	else {
		first->prev = copied_value;
		copied_value->next = first;
		first = copied_value;
	}
	size++;
	return true;
}

bool DronesManager::insert_back(DroneRecord value) {
	DroneRecord* copied_value = new DroneRecord();
	*copied_value = value;
	if (last == NULL) {
		first = copied_value;
		last = copied_value;
	}
	else {
		last->next = copied_value;
		copied_value->prev = last;
		last = copied_value;
	}
	size++;
	return true;
}

bool DronesManager::remove(unsigned int index) {
	if (first == NULL) return false;
	if (index > size - 1) return false;
	if (index == 0) remove_front();
	else if (index == size - 1) remove_back();
	else {
		DroneRecord* current = first;
		for (unsigned int i = 0; i < index; i++) {
			current = current->next;
		}
		DroneRecord* next_drone = current->next;
		DroneRecord* prev_drone = current->prev;
		current->prev->next = next_drone;
		current->next->prev = prev_drone;
		delete current;
		size--;
	}
	return true;
}

bool DronesManager::remove_front() {
	if (first == NULL) return false;
	if (first->next == NULL) {
		delete first;
		first = NULL;
		last = NULL;
	}
	else {
		DroneRecord* temp_first = first;
		first = first->next;
		first->prev = NULL;
		delete temp_first;
	}
	size--;
	return true;
}

bool DronesManager::remove_back() {
	if (first == NULL) return false;
	if (first->next == NULL) {
		delete first;
		first = NULL;
		last = NULL;
	}
	else {
		DroneRecord* temp_last = last;
		last->prev->next = NULL;
		last = last->prev;
		delete temp_last;
	}
	size--;
	return true;
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
	if (first == NULL) return false;
	if (index > size - 1) return false;
	DroneRecord* copied_value = new DroneRecord();
	*copied_value = value;
	DroneRecord* current = first;
	for (unsigned int i = 0; i < index; i++) {
		current = current->next;
	}
	copied_value->next = current->next;
	copied_value->prev = current->prev;
	if (*current == *first) first = copied_value;
	else current->prev->next = copied_value;
	if (*current == *last) last = copied_value;
	else current->next->prev = copied_value;
	return true;
}

bool DronesManager::reverse_list() {
	if (first == NULL) return true;
	DroneRecord* current = first;
	DroneRecord* temp = NULL;
	while (current) {
		temp = current->prev;
		current->prev = current->next;
		current->next = temp;
		current = current->prev;
	}
	DroneRecord* temp_first = first;
	first = last;
	last = temp_first;
	return true;
}

bool DronesManagerSorted::is_sorted_asc() const {
	DroneRecord* current = first;
	unsigned int prev_val = 0;
	bool is_sorted_asc = true;
	while (current) {
		is_sorted_asc = prev_val <= current->droneID;
		prev_val = current->droneID;
		current = current->next;
	}
	return is_sorted_asc;
}

bool DronesManagerSorted::is_sorted_desc() const {
	DroneRecord* current = first;
	unsigned int prev_val = INT_MAX;
	bool is_sorted_desc = true;
	while (current) {
		is_sorted_desc = prev_val >= current->droneID;
		prev_val = current->droneID;
		current = current->next;
	}
	return is_sorted_desc;
}

bool DronesManagerSorted::insert_sorted_asc(DroneRecord val) {
	if (is_sorted_asc()) {
		DroneRecord* current = first;
		unsigned int counter = 0;
		while (current && current->droneID < val.droneID) {
			counter++;
			current = current->next;
		}
		insert(val, counter);
		return true;
	}
	return false;
}

bool DronesManagerSorted::insert_sorted_desc(DroneRecord val) {
	if (is_sorted_desc()) {
		DroneRecord* current = first;
		unsigned int counter = 0;
		while (current && current->droneID > val.droneID) {
			counter++;
			current = current->next;
		}
		insert(val, counter);
		return true;
	}
	return false;
}

void DronesManagerSorted::sort_asc() {
	if (first == NULL || first->next == NULL) return;
	DroneRecord* current;
	bool used_swap = false;
	do {
		used_swap = false;
		current = first;
		while (current->next != NULL) {
			if (current->droneID > current->next->droneID) {
				swap(current->droneID, current->next->droneID);
				swap(current->batteryType, current->next->batteryType);
				swap(current->description, current->next->description);
				swap(current->droneType, current->next->droneType);
				swap(current->manufacturer, current->next->manufacturer);
				swap(current->range, current->next->range);
				swap(current->yearBought, current->next->yearBought);
				used_swap = true;
			}
			current = current->next;
		}
	} while (used_swap);
}
    
void DronesManagerSorted::sort_desc() {
	sort_asc();
	reverse_list();
}
