#ifndef BINARY_NODE_TREE_
#define BINARY_NODE_TREE_
#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "PrecondViolatedExcept.h"
#include "NotFoundException.h"

template<class ItemType>
class BinaryNodeTree : public BinaryTreeInterface<ItemType>
{
private:
	std::shared_ptr<BinaryNode<ItemType>> rootPtr;
protected:
	// Copies the tree rooted at treePtr and returns a pointer to the root of the copy
	auto copyTree(const std::shared_ptr<BinaryNode<ItemType>> oldTreeRootPtr)
		const->std::shared_ptr<BinaryNode<ItemType>>;
	// Recursively deletes all nodes from the tree
	void destroyTree(std::shared_ptr<BinaryNode<ItemType>> subTreePtr);
	// PROTECTED UTILITY METHODS SECTION: RECURSIVE HELPER METHODS FOR THE PUBLIC METHODS
	int getHeightHelper(std::shared_ptr<BinaryNode<ItemType>> subTreePtr) const;
	// Recursively adds a new node to the tree in a left/right fashion to keep tree balanced
	auto balancedAdd(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
		std::shared_ptr<BinaryNode<ItemType>> newNodePtr)->std::shared_ptr<BinaryNode<ItemType>>;
	//removeValue() not implemented in BinaryNode Tree. Override in inheritad BinarySearchTree.h unnecessary.
	void inorder(void visit(ItemType&), std::shared_ptr<BinaryNode<ItemType>> treePtr) const;
	void preorder(void visit(ItemType&), std::shared_ptr<BinaryNode<ItemType>> treePtr) const;
	void postorder(void visit(ItemType&), std::shared_ptr<BinaryNode<ItemType>> treePtr) const;

public:
	// CONSTRUCTOR AND DESTRUCTOR SECTION

	BinaryNodeTree();
	BinaryNodeTree(const ItemType& rootItem);
	BinaryNodeTree(const ItemType& rootItem,
		const std::shared_ptr<BinaryNodeTree<ItemType>> leftTreePtr,
		const std::shared_ptr<BinaryNodeTree<ItemType>> rightTreePtr);
	BinaryNodeTree(const BinaryNodeTree<ItemType>& treePtr);
	virtual ~BinaryNodeTree();

	// PUBLIC BINARY_TREE_INTERFACE METHODS SECTION
	/*
	bool isEmpty() const;
	int getNumberOfNodes() const;
	ItemType getRootData() const throw(PrecondViolatedExcept);
	ItemType getEntry(const ItemType& anEntry) const throw(NotFoundException);
	bool contains(const ItemType& anEntry) const;
	//bool remove(const ItemType& data); // Removes specified item from the tree
	//void clear();
	*/
	bool add(const ItemType& newData); // Adds an item to the tree
	int getHeight() const; // returns height of binary tree
	// PUBLIC TRAVERSAL SECTION
	// OVERLOADED OPERATOR SECTION
	/*BinaryNodeTree& operator = (const BinaryNodeTree& rightHandSide);
	*/
	void inorderTraverse(void visit(ItemType&)) const; // <- Use in binarySearch Tree
	void preorderTraverse(void visit(ItemType&)) const;
	void postorderTraverse(void visit(ItemType&)) const;
}; // end BinaryNodeTree
#endif