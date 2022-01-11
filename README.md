## BinaryHeap

This repository represents a binary heap data structure that I implemented in C++. 
It is used as an attempt to solidify my knowledge regarding minimum and maximum binary heaps.

## Documentation

Inside file, **BinaryHeap.cpp**, I've presented examples that display **insertion and ***deletion*** operations within a minimum 
binary heap. A heap object can be instantiated by declaring a new MinHeap or MaxHeap object, dependent on which you require.

**MinHeap**  
```c++
#include "MinHeap.cpp";

int x = 14;
MinHeap<int>* m_heap = new MinHeap<int>(x);

```

**MaxHeap**  
```c++
#include "MaxHeap.cpp";

int x = 14;
MinHeap<int>* m_heap = new MinHeap<int>(x);

```

**Insertion**  
Assuming, we have some heap object, **m_heap**, allocated to the heap, we can perform insertion as follows:

```c++
int y = 1;
m_heap->Insert(y)
```

**Deletion**  
Likewise, given some heap object, **m_heap**, we can extract the minimum or maximum key (relative to the heap type; min or max) such as:

```c++
m_heap->Delete();
```
