#include "BinarySearchTree.h"


/*Constructors*/

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree() : rootPtr(nullptr), nodeCnt(0)
{} // end default constructor

template<class ItemType>
BinarySearchTree<ItemType>::
BinarySearchTree(const ItemType& rootItem)
	: rootPtr(std::make_shared<BinarySearchTree<ItemType>>(rootItem, nullptr, nullptr)), nodeCnt(0)
{
} // end constructor

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType>& tree)
	:rootPtr(copyTree(tree.rootPtr)), nodeCnt(tree.nodeCnt)
{} // end copy constructor

template<class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree()
{
	clear();
} // end destructor


/*Protected Methods*/

// Recursively places a given new node at its proper position in a binary search tree
template<class ItemType>
auto BinarySearchTree<ItemType>::placeNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
	std::shared_ptr<BinaryNode<ItemType>> newNode) -> std::shared_ptr<BinaryNode<ItemType>>
{
	if (subTreePtr == nullptr)
		return newNode;
	else if (subTreePtr->getItem() > newNode->getItem())
	{
		auto tempPtr = placeNode(subTreePtr->getLeftChildPtr(), newNode);
		subTreePtr->setLeftChildPtr(tempPtr);
	}
	else // handles condition when newNode == subTreePtr
	{
		auto tempPtr = placeNode(subTreePtr->getRightChildPtr(), newNode);
		subTreePtr->setRightChildPtr(tempPtr);
	}
	return subTreePtr;
} // end placeNode

template<class ItemType>
auto BinarySearchTree<ItemType>::removeValue(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
	const ItemType target,
	bool& isSuccessful)->std::shared_ptr<BinaryNode<ItemType>>
{
	if (subTreePtr == nullptr)
	{
		isSuccessful = false;
	}
	else if (subTreePtr->getItem() == target)
	{
		// Item is in the root of some subtree
		subTreePtr = removeNode(subTreePtr);
		isSuccessful = true;
	}
	else if (subTreePtr->getItem() > target)
		// Search the left subtree
	{
		auto tempPtr = removeValue(subTreePtr->getLeftChildPtr(), target, isSuccessful);
		subTreePtr->setLeftChildPtr(tempPtr);
	}
	else
		// Search the right subtree 
	{
		auto tempPtr = removeValue(subTreePtr->getRightChildPtr(), target, isSuccessful);
		subTreePtr->setRightChildPtr(tempPtr);
	}
	return subTreePtr;
} // end removeValue

template<class ItemType>
auto BinarySearchTree<ItemType>::removeNode(std::shared_ptr<BinaryNode<ItemType>> nodePtr)
->std::shared_ptr<BinaryNode<ItemType>>
{
	if (nodePtr->isLeaf())
	{
		return nodePtr;
	}
	else if ((nodePtr->getLeftChildPtr() != nullptr && nodePtr->getRightChildPtr() == nullptr)
		|| (nodePtr->getLeftChildPtr() == nullptr && nodePtr->getRightChildPtr() != nullptr))
	{
		std::shared_ptr<BinaryNode<ItemType>> nodeToConnectPtr;
		if (nodePtr->getRightChildPtr() == nullptr)
			nodeToConnectPtr = nodePtr->getLeftChildPtr();
		else
			nodeToConnectPtr = nodePtr->getRightChildPtr();
		return nodeToConnectPtr;
	}
	else
	{
		ItemType inOrderSuccessor;
		auto tempPtr = removeLeftmostNode(nodePtr->getRightChildPtr(), inOrderSuccessor);
		nodePtr->setRightChildPtr(tempPtr);
		nodePtr->setItem(nodePtr->getItem());
		return nodePtr;
	}
} // end removeNode

// Removes the leftmost node in the left subtree of the node pointed to by nodePtr
// Sets inorder Successor to the value in this node
// Returns a ptr to the revised subtree
template<class ItemType>
auto BinarySearchTree<ItemType>::removeLeftmostNode(std::shared_ptr<BinaryNode<ItemType>>subTreePtr,
	ItemType& inorderSuccessor) ->std::shared_ptr<BinaryNode<ItemType>>
{
	if (subTreePtr->getLeftChildPtr() == nullptr)
	{
		// This is the node you want; it has no left child, but may have right subtree
		inorderSuccessor = subTreePtr->getItem();
		return removeNode(subTreePtr);
	}
	else
	{
		auto tempPtr = removeLeftmostNode(subTreePtr->getLeftChildPtr(), inorderSuccessor);
		subTreePtr->setLeftChildPtr(tempPtr);
		return subTreePtr;
	}
} // end removeLeftmostNode

template<class ItemType>
auto BinarySearchTree<ItemType>::findNode(std::shared_ptr<BinaryNode<ItemType>> treePtr,
	const ItemType& target) const->std::shared_ptr<BinaryNode<ItemType>>
{
	if (treePtr == nullptr)
		return nullptr;
	else if (treePtr->getItem() == target)
		return treePtr; // Found
	else if (treePtr->getItem() > target) // Search left subtree
		return findNode(treePtr->getLeftChildPtr(), target);
	else // Search right subtree
		return findNode(treePtr->getRightChildPtr(), target);
} // end findNode


/* Public Traverse Methods*/

template<class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(ItemType&)) const
{
	this->inorder(visit, rootPtr);
} // end inorderTraverse

template<class ItemType>
void BinarySearchTree<ItemType>::preorderTraverse(void visit(ItemType&)) const
{
	this->preorder(visit, rootPtr);
} // end preorderTraverse

template<class ItemType>
void BinarySearchTree<ItemType>::postorderTraverse(void visit(ItemType&)) const
{
	this->postorder(visit, rootPtr);
} // end postorderTraverse


/* Public Methods */
template<class ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const
{
	return (rootPtr == nullptr);
} // end isEmpty

template<class ItemType>
ItemType BinarySearchTree<ItemType>::getRootData() const throw(PrecondViolatedExcept)
{
	return (rootPtr != nullptr) ? rootPtr->getItem() : throw "nullPtr";
} // end getRootData

template<class ItemType>
ItemType BinarySearchTree<ItemType>::
getEntry(const ItemType& anEntry) const throw(NotFoundException)
{
	auto tempPtr = findNode(rootPtr, anEntry);
	if (tempPtr != nullptr)
	{
		return tempPtr->getItem();
	}
	else
		throw anEntry;
} // end getEntry

template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newData)
{
	auto newNodePtr = std::make_shared<BinaryNode<ItemType>>(newData);
	rootPtr = placeNode(rootPtr, newNodePtr);
	nodeCnt++;
	return true;
} // end add

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType& target)
{
	bool isSuccessful = false;
	rootPtr = removeValue(rootPtr, target, isSuccessful);
	if (isSuccessful)
		nodeCnt--;
	return isSuccessful;
} // end remove

template<class ItemType>
int BinarySearchTree<ItemType>::getHeight() const
{
	return BinaryNodeTree<ItemType>::getHeightHelper(rootPtr);
} // end getHeight

template<class ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodes() const
{
	return nodeCnt;
} // end getNumberOfNodes

template<class ItemType>
void BinarySearchTree<ItemType>::setRootData(const ItemType& newData)
{
	rootPtr->setItem(newData);
} // end setRootData

template<class ItemType>
void BinarySearchTree<ItemType>::clear()
{
	this->destroyTree(rootPtr);
	nodeCnt = 0;
} // end clear

template<class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType& anEntry) const
{
	bool isSuccessful = false;
	auto targetPtr = findNode(rootPtr, anEntry);
	if (getRootData(targetPtr) == anEntry)
		isSuccessful = true;
	return isSuccessful;
}
