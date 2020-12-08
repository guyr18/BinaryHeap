// MaxHeap.cpp
// @author: Robert Guy
//
// This header file represents a binary max-heap data structure.
// It provides two simple functions:
//
//	1. Insertion
//	2. Deletion
//
// Furthermore, the heap is stored in a type, T, array. All nodes
// in a binary min-heap follow a specific ordering property. Such that,
// for every node X (excluding the root) the parent has a larger key
// value than X. Taking this into account, all method(s) attempt to
// preserve an upper bounds of O(logN).
//
// The cached nodes are stored in a specific pattern to achieve this
// time complexity. The pattern states that:
//	1. Parent nodes are stored at index, i' where i' = floor(i / 2).
//	2. Left children are stored at index, i' where i' = 2i + 1.
//	3. Right children are stored at index, i' where i' = 2i + 2.

#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
class MinHeap
{

	// The array cache that this heap is stored in.
	T* _cache;

	// The current size of this heap.
	size_t _size;

	// The current capacity of this heap.
	size_t _capacity;

	// PercolateUp(x) performs a parent-to-parent search. When it finds a proper 
	// location, for insertion it inserts the node in that location. A proper 
	// location can be defined as a node that meets the ordering property for 
	// this heap, in relation its children.
	void PercolateUp(size_t index)
	{

		// Grab the parent node.
		const size_t& parent = GetParentNode(index);

		// Check if _cache[index] is not the only not and if
		// a swap is needed. 
		if (parent > 0 && _cache[parent] < _cache[index])
		{

			swap(_cache[parent], _cache[index]);
			PercolateUp(parent);

		}
	}

	// PercolateDown(index) takes a type size_t, index, and performs a parent-to-parent search.
	// It searches for a root node replacement so that a swap can be made.
	void PercolateDown(size_t index)
	{

		// Is this a leaf node? If it is we are at a dead end. And effectively,
		// we're done.
		if (GetLeftChildNode(index) < _size && GetRightChildNode(index) < _size)
		{

			// Grab the parent node. Parent nodes are stored at index i,
			// where i = (i - 1) / 2. However, we are percolating down, 
			// which means we start at the beginning of the heap. Adding two
			// to the index will alter the equation, giving us: 
			//
			//	((i + 2) - 1) / 2
			//	= (i + 1) / 2
			//
			// This will percolate us down.
			size_t parent = GetParentNode(index + 2);

			// Grab the left child of the parent node.
			size_t left_child = GetLeftChildNode(parent);

			// Grab the right child of the parent node.
			size_t right_child = GetRightChildNode(parent);

			// Does this parent have two children?
			if (_cache[left_child] > -1 && _cache[right_child] > -1)
			{

				// Lets figure out which child is the smallest and swap with the parent.
				const unsigned int max_value = max(_cache[left_child], _cache[right_child]);
				const size_t max_index = max_value == _cache[left_child] ? left_child : right_child;
				swap(_cache[parent], _cache[max_index]);
				PercolateDown(max_index);

			}
			// There is only one child.
			else
			{

				// Figure out the index of the remaining child and swap with the parent.
				const size_t child_select = _cache[left_child] != -1 ? left_child : right_child;
				swap(_cache[parent], _cache[child_select]);
				PercolateDown(child_select);

			}
		}
	}

	// CacheResize(new_capacity) takes a type, size_t: capacity. It deletes, reallocates, and
	// copies the original data to a new, contiguous block of memory.
	void CacheResize(size_t new_capacity)
	{

		T* temp = _cache; // Store a pointer to the original cache.
		delete _cache; // Delete the original cache to avoid a memory leak.
		_cache = new T[new_capacity]; // Allocate a new cache of length new_capacity and type T in memory.

		// Iterate across the old capacity. Essentially, copy all the
		// elements to the newly allocated memory block.
		for (size_t i = 1; i < _capacity; i++)
		{

			_cache[i] = temp[i];

		}

		_capacity = new_capacity; // Update the capacity to our new one.

	}

	// Print(out) prints the cache contents to the specific ostream, out.
	void Print(ostream& out) const
	{

		for (size_t i = 0; i < _size; i++)
		{

			out << i << ". " << _cache[i] << endl;

		}
	}

public:

	// An explicit, one-parameter constructor that accepts 
	// a type, _size_t: capacity. It allocates the heap
	// cache, type T, array.
	explicit MinHeap(size_t capacity)
	{

		_cache = new T[capacity + 1];
		_size = 0;
		_capacity = capacity;

	}

	// Insert(x) inserts a type T object, x, to the heap cache. 
	void Insert(const T& x)
	{

		// Increment size to account for the node that we are adding.
		_size++;

		// The heap is now full. So, lets resize it.
		if (_size == _capacity)
		{

			// Resize it to double the current capacity.
			// This could be changed, possibly if you have
			// the rationale and a reasonable factor to do so with.
			CacheResize(_capacity * 2);

		}

		// Add x to to the end of the heap.
		_cache[_size - 1] = x;

		// We need to percolate up, from node to node, so that we
		// can find a node that fits the ordering property of this 
		// heap. So, lets do that.
		PercolateUp(_size - 1);

	}

	// Delete() deletes the root node that is stored in the heap cache. It then
	// finds a new root node by percolating down the heap. The new root node must meet
	// the ordering requirement for this heap.
	void Delete()
	{

		// Pointer to the root node.
		T& root_node = _cache[0];

		// Pointer to the last node in the heap cache.
		T& last_node = _cache[_size - 1];

		// Swap the contents of these two nodes.
		swap(root_node, last_node);

		// Decrement the size of the heap.
		_size--;

		// Percolate down the heap cache, so that we can find a root node replacement
		// that matches the ordering property.
		PercolateDown(0);

	}

	// GetParentNode(index) returns the parent node of a given index.
	size_t GetParentNode(const size_t& index)
	{

		return (index - 1) / 2;

	}

	// GetLeftChildNode(index) returns the left child of a given index.
	size_t GetLeftChildNode(const size_t& index)
	{

		return (2 * index) + 1;

	}

	// GetRightChildNode(index) returns the right child of a given index.
	size_t GetRightChildNode(const size_t& index)
	{

		return (2 * index) + 2;

	}

	// A defined output overload for '<<'.
	friend ostream& operator<<(ostream& out, const MaxHeap& max_heap)
	{

		max_heap.Print(out);
		return out;

	}
};