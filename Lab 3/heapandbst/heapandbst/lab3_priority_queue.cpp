#include "lab3_priority_queue.hpp"
#include <iostream>

using namespace std;

// PURPOSE: Parametric constructor 
// initializes heap to an array of (n_capacity + 1) elements
PriorityQueue::PriorityQueue(unsigned int n_capacity) {
	heap = new TaskItem * [n_capacity + 1];
	size = 0;
	capacity = n_capacity;
}

// PURPOSE: Explicit destructor of the class PriorityQueue
PriorityQueue::~PriorityQueue() {
	for (unsigned int i = 1; i <= size; i++) {
		delete(heap[i]);
	}
	delete heap;
}

// PURPOSE: Returns the number of elements in the priority queue
unsigned int PriorityQueue::get_size() const {
	return size;
}

// PURPOSE: Returns true if the priority queue is empty; false, otherwise
bool PriorityQueue::empty() const {
	return size == 0;
}

// PURPOSE: Returns true if the priority queue is full; false, otherwise
bool PriorityQueue::full() const {
	return size == capacity;
}

// PURPOSE: Prints the contents of the priority queue; format not specified
void PriorityQueue::print() const {
	for (unsigned int i = 1; i < size + 1; i++) {
		cout << heap[i]->priority << ", ";
	}
}

// PURPOSE: Returns the max element of the priority queue without removing it
// if the priority queue is empty, it returns (-1, "N/A")
PriorityQueue::TaskItem PriorityQueue::max() const {
	if (size != 0) return *heap[1];
	return TaskItem(-1, "NULL");
}

// PURPOSE: Restores the max heap by heapifying up provided the index of a newly inserted element
void PriorityQueue::heapify_up(int index) {
	int parent_index;
	if (index != 1) {
		parent_index = index / 2;
		if (heap[parent_index]->priority < heap[index]->priority) {
			swap(heap[parent_index], heap[index]);
			heapify_up(parent_index);
		}
	}
}

// PURPOSE: Inserts the given value into the priority queue
// re-arranges the elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::enqueue( TaskItem val ) {
	if (full()) return false;
	TaskItem* new_val = new TaskItem(val.priority, val.description);
	heap[size + 1] = new_val;
	size++;
	int index = size;
	heapify_up(size);
	return true;
}

//PURPOSE: Heapifys down the node to restore the heap property
void PriorityQueue::heapify_down(int index) {
	unsigned int left, right;
	left = 2 * index + 1;
	right = 2 * index;
	int max = index;
	if (left < size && heap[left]->priority > heap[index]->priority) max = left;
	if (right < size && heap[right]->priority > heap[max]->priority) max = right;
	if (max != index) {
		swap(heap[index], heap[max]);
		heapify_down(max);
	}
}

// PURPOSE: Removes the top element with the maximum priority
// re-arranges the remaining elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::dequeue() {
	if (size == 0) return false;
	swap(heap[1], heap[size]);
	delete(heap[size]);
	heap[size] = NULL;
	size--;
	heapify_down(1);
	return true;
}
