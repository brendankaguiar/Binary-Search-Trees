#ifndef BINARY_TREE_INTERFACE_
#define BINARY_TREE_INTERFACE_
#include <algorithm>
#include <iostream>
#include <ctime>

template<class ItemType>
class BinaryTreeInterface
{
public:
	virtual ItemType getRootData() const = 0;
	virtual bool add(const ItemType& newData) = 0;
	virtual bool remove(const ItemType& target) = 0;
	virtual ItemType getEntry(const ItemType& target) const = 0;
	virtual int getHeight() const = 0;
	// Traverses this binary tree in preorder (inorder, postorder) and
	// calls the function visit once for each node
	// @param visit A client-defined function that performs an operation on either each visited node or its data
	virtual void inorderTraverse(void visit(ItemType&)) const = 0;
	virtual void preorderTraverse(void visit(ItemType&)) const = 0;
	virtual void postorderTraverse(void visit(ItemType&)) const = 0;
	// Destroys this tree and frees its assigned memory
	virtual ~BinaryTreeInterface() { }
}; // end BinaryTreeInterface
#endif