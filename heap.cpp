#pragma once
#include<vector>
#include<assert.h>
#include<queue>
#include<stdlib.h>
#include<iostream>



template<class T>
class Greater
{
public:
	bool operator()(const T&left, const T&right)
	{
		return left >= right;
	}
};
template<class T>
class Less
{
public:
	bool operator()(const T&left, const T&right)
	{
		return left < right;
	}
};

template<class T, template <class>class  Compare=Less>
class Heap
{
public:
	Heap()
	{}

	Heap(const T arr[], size_t size)
	{
		//_heap.resize(size);
		//保存数据
		for (size_t idx = 0; idx < size; ++idx)
		{
			_heap.push_back(arr[idx]);
			
		}
		//找最后一个非叶子节点
		size_t root = (_heap.size() - 2)/2;
		for (int idx = root; idx >= 0; --idx)
		{
			//调整idx为根的树,使其每个节点满足堆的性质
			_AdjustDown(idx,size);
		}
	}

	void Insert(const T& data)
	{
		_heap.push_back(data);
		size_t size = _heap.size();
		if (size > 1)
		{
			size_t size = _heap.size();
			size_t root = (size - 2) / 2;
			_AdjustUp(size);
		}
	}

	void Remove()
	{
		assert(!Empty());//assert为假触发
		size_t size = _heap.size();
		if (size > 1)
		{
			std::swap(_heap[0], _heap[size - 1]);
			_heap.pop_back();
			_AdjustDown(0, size - 1);
		}
		else
		{
			_heap.pop_back();
		}
	}

	bool Empty()const
	{
		return _heap.empty();
	}

	size_t size()
	{
		return  _heap.size();
	}
	T &Top()
	{
		return _heap[0];
	}


	~Heap()
	{}
public:

	void _AdjustDown(size_t root, size_t size)
	{
		size_t parent = root;

		//默认左孩子最小
		size_t child = root * 2 + 1;
		
		while (child<size)
		{
			

			if (child + 1 < size && Compare<T>()(_heap[child+1], _heap[child]))
			{
				child = child + 1;
			}

		//	if (_heap[parent] > _heap[child])
			if (Compare<T>()(_heap[parent], _heap[child]))
			{
				std::swap(_heap[parent], _heap[child]);
				parent = child;
				child = child * 2 + 1;
			}
			else{ break; }
		}
	}

	void _AdjustUp(size_t size)
	{
		size_t parent = (size - 2) / 2;
		size_t child = size - 1;
		while (child != 0)
		{
		//	if (_heap[child]<_heap[parent])
			if (Compare<T>()(_heap[child], _heap[parent]))
			{
				std::swap(_heap[child], _heap[parent]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
				break;
		}
	}
private:
	std::vector<T>_heap;
};




//
//template<class T>
//class Less
//{
//	bool operator()(const T&left, const T&right)
//	{
//		return left <= right;
//	}
//};
//template<class T>
//class Greater
//{
//	bool operator()(const T&left, const T&right)
//	{
//		return left > right;
//	}
//};
//
//template<class T, template<class Greater>>
//class Heap
//{
//public:
//	Heap()
//	{}
//
//	Heap(const T arr[], size_t size)w
//	{
//		//_heap.resize(size);
//		//保存数据
//		for (size_t idx = 0; idx < size; ++idx)
//		{
//			_heap.push_back(arr[idx]);
//
//		}
//		//找最后一个非叶子节点
//		size_t root = (_heap.size() - 2) / 2;
//		for (int idx = root; idx >= 0; --idx)
//		{
//			//调整idx为根的树,使其每个节点满足堆的性质
//			_AdjustDown(idx, size);
//		}
//	}
//
//	void Insert(const T& data)
//	{
//		_heap.push_back(data);
//		size_t size = _heap.size();
//		if (size > 1)
//		{
//			size_t size = _heap.size();
//			size_t root = (size - 2) / 2;
//			_AdjustUp(size);
//		}
//	}
//
//	void Remove()
//	{
//		assert(!Empty());//assert为假触发
//		size_t size = _heap.size();
//		if (size > 1)
//		{
//			std::swap(_heap[0], _heap[size - 1]);
//			_heap.pop_back();
//			_AdjustDown(0, size - 1);
//		}
//		else
//		{
//			_heap.pop_back();
//		}
//	}
//
//	bool Empty()const
//	{
//		return _heap.empty();
//	}
//
//	size_t size()
//	{
//		return size_t _heap.size();
//	}
//
//
//	~Heap()
//	{}
//public:
//	void _AdjustDown(size_t root, size_t size)
//	{
//		size_t parent = root;
//
//		//默认左孩子最小
//		size_t child = root * 2 + 1;
//
//		while (child<size)
//		{
		//	if (Compare<T>()(_heap[child]>_heap[child+1])
//			if (child + 1 < size && _heap[child] > _heap[child + 1])
//			{
//				child = child + 1;
//			}
//			//	if (_heap[parent] > _heap[child])
//			if (Compare()(_heap[parent], _heap[child]))
//			{
//				std::swap(_heap[parent], _heap[child]);
//				parent = child;
//				child = child * 2 + 1;
//			}
//			else{ break; }
//		}
//	}
//
//
//	void _AdjustUp(size_t size)
//	{
//		size_t parent = (size - 2) / 2;
//		size_t child = size - 1;
//		while (child != 0)
//		{
//			//if (_heap[child]<_heap[parent])
//			if (Compare()(_heap[child], _heap[parent]))
//			{
//				std::swap(_heap[child], _heap[parent]);
//				child = parent;
//				parent = (child - 1) / 2;
//			}
//			else
//				break;
//		}
//
//	}
//
//
//private:
//
//	std::vector<T>_heap;
//
//};
