#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include"heap.hpp"
#include"heap.hpp"
#include"huffmanTree.h"
using namespace std;

void Funtest1()
{
	int arr[] = { 1, 3, 5, 7, 9 };
	HuffmanTree<int>hp(arr, sizeof(arr) / sizeof(arr[0]));
	hp.LevelOrder();
}

//void Funtest()
//{
//	int arr[] = {53,17,79,9,45,65,87,23};
//	Heap <int,Greater>hp(arr, sizeof(arr) / sizeof(arr[0]));
//	hp.Insert(6);
//	hp.Remove();
//}

int main()
{
	Funtest1();
	system("pause");
	return 0;
}
