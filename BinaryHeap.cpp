#include "MinHeap.cpp"
#include <iostream>
using namespace std;

int main()
{
	MinHeap<int>* m_heap = new MinHeap<int>(14);
	m_heap->Insert(1);
	m_heap->Insert(2);
	m_heap->Insert(3);
	m_heap->Insert(4);
	m_heap->Insert(7);
	m_heap->Insert(5);
	m_heap->Insert(11);
	cout << "Following insertions we have: " << endl << endl;
	cout << *m_heap << endl << endl;
	m_heap->Delete();
	cout << "Following deletion we have: " << endl << endl;
	cout << *m_heap << endl << endl;
	return 0;

}
