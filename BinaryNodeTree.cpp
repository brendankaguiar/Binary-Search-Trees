#include "BinaryNodeTree.h"


/*Constructors*/
template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree() : rootPtr(nullptr)
{} // end constructor

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem) : rootPtr(rootItem)
{} // end constructor

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem, 
	const std::shared_ptr<BinaryNodeTree<ItemType>> leftTreePtr,
	const std::shared_ptr<BinaryNodeTree<ItemType>> rightTreePtr) 
	: rootPtr(rootItem)
{
	 copyTree(leftTreePtr->rootPtr);
	 copyTree(rightTreePtr->rootPtr);
} // end constructor

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const BinaryNodeTree<ItemType>& treePtr)
{
	rootPtr = copyTree(treePtr.rootPtr); // Take note of this impl. in lecture
} // end copy constructor

template<class ItemType>
BinaryNodeTree<ItemType>::~BinaryNodeTree()
{
	destroyTree(rootPtr);
} // end constructor


/* Protected Methods*/
template<class ItemType>
auto BinaryNodeTree<ItemType>::copyTree(const std::shared_ptr<BinaryNode<ItemType>> oldTreeRootPtr) const -> std::shared_ptr<BinaryNode<ItemType>>
{
	std::shared_ptr<BinaryNode<ItemType>> newTreePtr;
	// Copy tree nodes during a preorder traversal
	if (oldTreeRootPtr != nullptr)
	{
		// Copy node
		newTreePtr = std::make_shared<BinaryNode<ItemType>>(oldTreeRootPtr->getItem(), nullptr, nullptr);
		newTreePtr->setLeftChildPtr(copyTree(oldTreeRootPtr->getLeftChildPtr()));
		newTreePtr->setRightChildPtr(copyTree(oldTreeRootPtr->getRightChildPtr()));
	} // end if
	// Else tree is empty (newTreePtr is nullptr)
	return newTreePtr;
} // end copyTree

template<class ItemType>
void BinaryNodeTree<ItemType>::destroyTree(std::shared_ptr<BinaryNode<ItemType>> subTreePtr)
{
	if (subTreePtr != nullptr)
	{
		destroyTree(subTreePtr->getLeftChildPtr());
		destroyTree(subTreePtr->getRightChildPtr());
		subTreePtr.reset(); // Decrement reference count to node
	} // end if
} // end destroyTree

template<class ItemType>
int BinaryNodeTree<ItemType>::
getHeightHelper(std::shared_ptr<BinaryNode<ItemType>> subTreePtr) const
{
	if (subTreePtr == nullptr)
		return 0;
	else
		return 1 + std::max(getHeightHelper(subTreePtr->getLeftChildPtr()), getHeightHelper(subTreePtr->getRightChildPtr()));
} // end getHeightHelper

template<class ItemType>
auto BinaryNodeTree<ItemType>::balancedAdd(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
	std::shared_ptr<BinaryNode<ItemType>> newNodePtr) -> std::shared_ptr<BinaryNode<ItemType>>
{
	if (subTreePtr == nullptr)
		return newNodePtr;
	else
	{
		auto leftPtr = subTreePtr->getLeftChildPtr();
		auto rightPtr = subTreePtr->getRightChildPtr();
		if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr))
		{
			rightPtr = balancedAdd(rightPtr, newNodePtr);
			subTreePtr->setRightChildPtr(rightPtr);
		}
		else
		{
			leftPtr = balancedAdd(leftPtr, newNodePtr);
			subTreePtr->setLeftChildPtr(leftPtr);
		} // end if
		return subTreePtr;
	}  // end if
} // end balancedAdd


/* Public Methods*/

template<class ItemType>
bool BinaryNodeTree<ItemType>::add(const ItemType& newData)
{
	auto newNodePtr = std::make_shared<BinaryNode<ItemType>>(newData);
	rootPtr = balancedAdd(rootPtr, newNodePtr);
	return true;
} // end add

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeight() const
{
	return getHeightHelper(rootPtr);
} // end getHeight


/* Traversal Methods*/
template<class ItemType>
void BinaryNodeTree<ItemType>::
inorder(void visit(ItemType&),
	std::shared_ptr<BinaryNode<ItemType>> treePtr) const
{
	if (treePtr != nullptr)
	{
		inorder(visit, treePtr->getLeftChildPtr());
		ItemType theItem = treePtr->getItem();
		visit(theItem);
		inorder(visit, treePtr->getRightChildPtr());
	} // end if
} // end inorder

template<class ItemType>
void BinaryNodeTree<ItemType>::
preorder(void visit(ItemType&),
	std::shared_ptr<BinaryNode<ItemType>> treePtr) const
{
	if (treePtr != nullptr)
	{
		ItemType theItem = treePtr->getItem();
		visit(theItem);
		inorder(visit, treePtr->getLeftChildPtr());
		inorder(visit, treePtr->getRightChildPtr());
	} // end if
} // end preorder

template<class ItemType>
void BinaryNodeTree<ItemType>::
postorder(void visit(ItemType&),
	std::shared_ptr<BinaryNode<ItemType>> treePtr) const
{
	if (treePtr != nullptr)
	{
		ItemType theItem = treePtr->getItem();
		visit(theItem);
		inorder(visit, treePtr->getRightChildPtr());
		inorder(visit, treePtr->getLeftChildPtr());
	} // end if
} // end postorder

template<class ItemType>
void BinaryNodeTree<ItemType>::inorderTraverse(void visit(ItemType&)) const
{
	inorder(visit, rootPtr);
} // end inorderTraverse

template<class ItemType>
void BinaryNodeTree<ItemType>::preorderTraverse(void visit(ItemType&)) const
{
	preorder(visit, rootPtr);
} // end preorderTraverse

template<class ItemType>
void BinaryNodeTree<ItemType>::postorderTraverse(void visit(ItemType&)) const
{
	postorder(visit, rootPtr);
} // end postorderTraverse