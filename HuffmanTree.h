#pragma once
#include"heap.hpp"
#include<queue>

template<class T>
struct HuffmanCompare
{
	bool operator()(const T pLeft, const T pRight)
	{
		return (pLeft->_weight) < (pRight->_weight);
	}



};

template<class T>
struct HuffmanTreeNode
{

	HuffmanTreeNode(const T weight)
	: _pLeft(NULL)
	, _pRight(NULL)
	, _weight(weight)
	{}


	HuffmanTreeNode<T>*_pLeft;
	HuffmanTreeNode<T>*_pRight;
	T _weight;
};

template<class T, class Compare = HuffmanCompare<T>>
class HuffmanTree
{
public:

	HuffmanTree()
	{}
	HuffmanTree(const T arr[], size_t size)
	{
		_pRoot=_CreatHuffmanTree(arr, size);
	}

	~HuffmanTree()
	{
		_DsetoryTree(_pRoot);
	}

	void LevelOrder()
	{
		if (NULL == _pRoot)
			return;
		HuffmanTreeNode<T>*pCur = _pRoot;
		queue<HuffmanTreeNode<T>*>q;
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

	HuffmanTreeNode<T>*_CreatHuffmanTree(const T arr[], size_t size)
	{
		
		Heap<HuffmanTreeNode<T>*,Compare>hp;
		for (size_t idx = 0; idx < size; ++idx)
		{
			hp.Insert(new HuffmanTreeNode<T>(arr[idx]));
		}

		while (hp.size()>1)
		{
			//从堆中取两个权值较小的数
			HuffmanTreeNode<T>*pLeft = hp.Top();
			hp.Remove();

			HuffmanTreeNode<T>*pRight = hp.Top();
			hp.Remove();

			HuffmanTreeNode<T>*parent = new HuffmanTreeNode<T>(pLeft->_weight + pRight->_weight);
			parent->_pLeft = pLeft;
			parent->_pRight = pRight;

			hp.Insert(parent);
		}
		return hp.Top();
	}

	void _DsetoryTree(HuffmanTreeNode<T>*&pRoot)
	{
		if (pRoot)
		{
			_DsetoryTree(pRoot->_pLeft);
			_DsetoryTree(pRoot->_pRight);
		}
	}

private:
	HuffmanTreeNode<T>*_pRoot;
};
