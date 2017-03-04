#pragma once
#include<vector>
#include<assert.h>

 
template<class T>
class less
{
public:
	bool operator()(const T& left, const T& right)
	{
		return left <= right;
	}
};

template<class T>
class Greater
{
public:
	bool operator()(const T& left, const T& right)
	{
		return left > right;
	}
};

template<class T, class Compare = Greater<T>>
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
		if(size>1)
		{
			_AdjustUp(size);
		}

	}

	void Remove()
	{
		assert(!Empty());
		size_t size = _heap.size();
		if(size>1)
		{
			std::swap(_heap[0], _heap[size - 1]);
			_heap.pop_back();
			_AdjustDown(0, size-1);
		}
		else
			_heap.pop_back();
	}

	bool Empty()const
	{
		return _heap.empty();
	}
	size_t size()
	{
		return _heap.size();
	}

	T& Top()
	{
		return _heap[0];
	}


	~Heap()
	{}
private:


	void _AdjustUp(size_t size)
	{
		size_t parent =  (size-2)/2;
		size_t child = size - 1;
		while(child != 0)
		{
		   //if(_heap[child] < _heap[parent])
			if(Compare()(_heap[child], _heap[parent]))
		   {
				std::swap(_heap[child], _heap[parent]);
				child = parent;
				parent = (child-1)/2;
		   }
			else
			{
				break;
			}
		}
	}
	void _AdjustDown(size_t root,size_t size)
	{
		size_t parent = root;

		//默认左孩子最小
		size_t child = root * 2 + 1;
		
		while (child<size)
		{
			if (child + 1 < size && !Compare()(_heap[child], _heap[child+1]))
			{
				child = child + 1;
			}
			//if (_heap[parent] > _heap[child])
			if(Compare()(_heap[child], _heap[parent]))
			{
				std::swap(_heap[parent], _heap[child]);
				parent = child;
				child = child * 2 + 1;
			}
			else
				break;

		}
	}

private:

	std::vector<T>_heap;

};

void Funtest()
{
	int arr[] = {53,17,79,9,45,65,87,23};
	Heap<int> hp(arr,sizeof(arr)/sizeof(arr[0]));
	hp.Insert(6);
	hp.Remove();
	hp.size();
}




#pragma once
#include <queue>
#include "heap.hpp"
#include<iostream>
using namespace std;


template<class T>
struct HuffmanTreeNode
{
	HuffmanTreeNode(const T weight)
	: _pLeft(NULL)
	, _pRight(NULL)
	, _weight(weight)
	{}


	HuffmanTreeNode<T>* _pLeft;
	HuffmanTreeNode<T>* _pRight;
	T _weight;
};

template<class T>
struct HuffmanCompare
{
public:

	bool operator()(const HuffmanTreeNode<T>* pLeft, const HuffmanTreeNode<T>* pRight)
	{
		return (pLeft->_weight < pRight->_weight);
	}
};



template<class T, class Compare = HuffmanCompare<T>>
class HuffmanTree
{
public:

	HuffmanTree()
	{}
	HuffmanTree(const T arr[], size_t size)
	{
		_pRoot = _CreatHuffmanTree(arr, size);
	}

	~HuffmanTree()
	{
		_DsetoryTree(_pRoot);
	}

	void LevelOrder()
	{
		if (NULL == _pRoot)
			return;
		queue<HuffmanTreeNode<T>*> q;
		HuffmanTreeNode<T>* pCur = _pRoot;
		
		q.push(_pRoot);
		while (!q.empty())
		{
			pCur = q.front();
			cout << pCur->_weight << " ";
			if (pCur->_pLeft)
				q.push(pCur->_pLeft); 
			if (pCur->_pRight)
				q.push(pCur->_pRight);
			q.pop();

		}

	}

private:

	HuffmanTreeNode<T>* _CreatHuffmanTree(const T arr[], size_t size)
	{
		
		Heap<HuffmanTreeNode<T>*, Compare> hp;
		for (size_t idx = 0; idx < size; ++idx)
		{
			hp.Insert(new HuffmanTreeNode<T>(arr[idx]));
		}

		while (hp.size()>1)
		{
			//从堆中取两个权值较小的数
			HuffmanTreeNode<T>* pLeft = hp.Top();
			hp.Remove();

			HuffmanTreeNode<T>* pRight = hp.Top();
			hp.Remove();

			HuffmanTreeNode<T>* parent = new HuffmanTreeNode<T>(pLeft->_weight + pRight->_weight);
			parent->_pLeft = pLeft;
			parent->_pRight = pRight;

			hp.Insert(parent);
		}
		return hp.Top();
	}

	void _DsetoryTree(HuffmanTreeNode<T>*& pRoot)
	{
		if (pRoot)
		{
			_DsetoryTree(pRoot->_pLeft);
			_DsetoryTree(pRoot->_pRight);
			delete pRoot;
		}
	}

private:
	HuffmanTreeNode<T>* _pRoot;
};

void FunTest1()
{
	int arr[] = {7, 5, 3, 1, 9};
	HuffmanTree<int> ht(arr, sizeof(arr)/sizeof(arr[0]));
	ht.LevelOrder();
	
}