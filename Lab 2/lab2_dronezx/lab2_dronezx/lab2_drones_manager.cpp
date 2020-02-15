#include "lab2_drones_manager.hpp"

// TODO: Implement all of the listed functions below

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
	if (size == 0) return DroneRecord(0);
	if (index > size - 1) index = size - 1;
	DroneRecord* current = first;
	for (unsigned int i = 0; i < index; i++) {
		current = current->next;
	}
	DroneRecord selected = DroneRecord(*current);
	return selected;
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

}

bool DronesManager::insert(DroneRecord value, unsigned int index) {
	if (index > size) return false;
	if (index == 0) insert_front(value);
	else if (index == size) insert_back(value);
	else {
		DroneRecord* copied_value = new DroneRecord(value);
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
	if (index > size - 1) return false;
	if (index == 0) remove_front();
	else if (index == size - 1) remove_back();
	else {
		DroneRecord* current = first;
		for (unsigned int i = 0; i < index; i++) {
			current = current->next;
		}
		current->prev->next = current->next;
		current->next->prev = current->prev;
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
	if (index > size - 1) return false;
	DroneRecord* copied_value = new DroneRecord();
	*copied_value = value;
	DroneRecord* current = first;
	for (unsigned int i = 0; i < index; i++) {
		current = current->next;
	}
	if (current == first) first = copied_value;
	if (current == last) last = copied_value;
	if (copied_value != first) current->prev->next = copied_value;
	if (copied_value != last) current->next->prev = copied_value;
	return false;
}

bool DronesManager::reverse_list() {
	if (first == NULL) return true;
	DroneRecord* current = first;
	while (current) {
		DroneRecord* temp_next = current->next;
		current->next = current->prev;
		current->prev = temp_next;
		current = current->next;
	}
	DroneRecord* temp = first;
	first = last;
	last = temp;
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
	bool is_sorted_asc = true;
	while (current) {
		is_sorted_asc = prev_val >= current->droneID;
		prev_val = current->droneID;
		current = current->next;
	}
	return is_sorted_asc;
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
	DroneRecord* current = first;
	DroneRecord* prev_drone;
	DroneRecord* next_drone;
	if (current->droneID > current->next->droneID) {
		prev_drone = current->prev;
		next_drone = current->next;
		if (prev_drone != NULL) {
			prev_drone->next = next_drone;
		}
		current->next = next_drone->next;
		current->prev = next_drone;
		next_drone->next = current;
		next_drone->prev = prev_drone;
	}
}
    
void DronesManagerSorted::sort_desc() {
	sort_asc();
	reverse_list();
}
