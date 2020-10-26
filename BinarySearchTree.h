/** Link-based implementation of the ADT binary search tree.
@file BinarySearchTree.h */
#ifndef BINARY_SEARCH_TREE_
#define BINARY_SEARCH_TREE_
#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
#include "NotFoundException.h"
#include "PrecondViolatedExcept.h"
#include <memory>

template<class ItemType>
class BinarySearchTree : public BinaryNodeTree<ItemType>
{
private:
	std::shared_ptr<BinaryNode<ItemType>> rootPtr;
	int nodeCnt;

protected:
	//------------------------------------------------------------
	// Protected Utility Methods Section:
	// Recursive helper methods for the public methods.
	//------------------------------------------------------------

	// Places a given new node at its proper position in this binary
	// search tree.
	auto placeNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
		std::shared_ptr<BinaryNode<ItemType>> newNode)->std::shared_ptr<BinaryNode<ItemType>>;
	auto removeValue(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
		const ItemType target,
		bool& isSuccessful)->std::shared_ptr<BinaryNode<ItemType>>;
	auto removeNode(std::shared_ptr<BinaryNode<ItemType>> nodePtr)->std::shared_ptr<BinaryNode<ItemType>>;
	// Removes the leftmost node in the left subtree of the node
	// pointed to by nodePtr.
	// Sets inorderSuccessor to the value in this node.
	// Returns a pointer to the revised subtree.
	auto removeLeftmostNode(std::shared_ptr<BinaryNode<ItemType>>subTreePtr,
		ItemType& inorderSuccessor)->std::shared_ptr<BinaryNode<ItemType>>;

	// Returns a pointer to the node containing the given value,
	// or nullptr if not found.
	auto findNode(std::shared_ptr<BinaryNode<ItemType>> treePtr,
		const ItemType& target) const->std::shared_ptr<BinaryNode<ItemType>>;

public:
	//------------------------------------------------------------
	// Constructor and Destructor Section.
	//------------------------------------------------------------
	BinarySearchTree();
	BinarySearchTree(const ItemType& rootItem);
	BinarySearchTree(const BinarySearchTree<ItemType>& tree);
	virtual ~BinarySearchTree();

	//------------------------------------------------------------
	// Public Traversals Section.
	//------------------------------------------------------------
	void preorderTraverse(void visit(ItemType&)) const;
	void inorderTraverse(void visit(ItemType&)) const;
	void postorderTraverse(void visit(ItemType&)) const;

	//------------------------------------------------------------
	// Public Methods Section.
	//------------------------------------------------------------
	bool isEmpty() const;
	int getHeight() const;
	int getNumberOfNodes() const;
	ItemType getRootData() const throw(PrecondViolatedExcept);
	void setRootData(const ItemType& newData);
	void clear();
	ItemType getEntry(const ItemType& anEntry) const throw(NotFoundException);
	bool contains(const ItemType& anEntry) const;
	bool add(const ItemType& newEntry);
	// Removes the given target value from the tree while maintaining a
	// binary search tree.
	bool remove(const ItemType& target);


}; // end BinarySearchTree
#endif