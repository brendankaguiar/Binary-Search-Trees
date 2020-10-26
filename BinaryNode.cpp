#include "BinaryNode.h"

template <class ItemType>
BinaryNode<ItemType>::BinaryNode() 
	:leftChildPtr(nullptr), rightChildPtr(nullptr)
{} // end constructor

template <class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType& anItem) 
	: leftChildPtr(nullptr), rightChildPtr(nullptr), item(anItem)
{} // end constructor


template <class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType& anItem,
	std::shared_ptr<BinaryNode<ItemType>> leftPtr,
	std::shared_ptr<BinaryNode<ItemType>> rightPtr)
	: item(anItem), leftChildPtr(leftPtr), rightChildPtr(rightPtr)
{} // end constructor

template <class ItemType>
void BinaryNode<ItemType>::setItem(const ItemType& anItem)
{
	item = anItem;
} // end setItem

template <class ItemType>
ItemType BinaryNode<ItemType>::getItem() const
{
	return item;
} // end getItem

template <class ItemType>
bool BinaryNode<ItemType>::isLeaf() const
{
	return (leftChildPtr == nullptr && rightChildPtr == nullptr) ? true : false; // ternary statement
} // end getItem

template <class ItemType>
auto BinaryNode<ItemType>::getLeftChildPtr() const  -> std::shared_ptr<BinaryNode<ItemType>>
{
	return leftChildPtr;
} // end getLeftChildPtr

template <class ItemType>
auto BinaryNode<ItemType>::getRightChildPtr()  const  -> std::shared_ptr<BinaryNode<ItemType>>
{
	return rightChildPtr;
} // end getRightChildPtr

template <class ItemType>
void BinaryNode<ItemType>::setLeftChildPtr(std::shared_ptr<BinaryNode<ItemType>> leftPtr)
{
	leftChildPtr = leftPtr;
} // end setLeftChildPtr

template <class ItemType>
void BinaryNode<ItemType>::setRightChildPtr(std::shared_ptr<BinaryNode<ItemType>> rightPtr)
{
	rightChildPtr = rightPtr;
} // end setRightChildPtr