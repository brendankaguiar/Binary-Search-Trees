#include "BinaryNode.cpp"
#include "BinaryNodeTree.cpp"
#include "BinarySearchTree.cpp"

#define SIZE 100

/* Function Definitons */
void visit(int& target);
void loadArr(int[]);
void menu(int& choice);
void resetMenu(int& reset);

/* main function */
int main()
{
	/* Program Reset Features */
	signed int reset = 0;
	while (!reset)
	{
		/* Variable Declaration */
		BinarySearchTree<int> myTree;
		int treeArr[SIZE];
		int switch_on;

		/* Main Menu */
		menu(switch_on);

		/* Load Features */
		loadArr(treeArr);
		for (int i = 0; i < SIZE; i++)
		{
			myTree.add(treeArr[i]);
			std::cout << "From Tree[" << i << "]: " << myTree.getEntry(treeArr[i]) << "\t";
		} // end for
		std::cout << std::endl;
		
		/* Switch Menu */
		switch (switch_on)
		{
		case 1:
			std::cout << "Tree Height: " << myTree.getHeight() << std::endl;
			break;
		case 2:
			std::cout << "\nInorder Traversal:\n";
			myTree.inorderTraverse(visit); // tree sort, an efficient algorithm of O(nlogn) complexity
			break;
		case 3:
			std::cout << "\nPreorder Traversal:\n";
			myTree.preorderTraverse(visit); // print root, traverse left branch, then traverse right branch
			break;
		case 4:
			std::cout << "\nPostorder Traversal:\n";
			myTree.postorderTraverse(visit); // print root, traverse right branch, then traverse left branch
			break;
			std::cout << "Invalid entry.\n";
		default:
			break;
		} // end switch

		/* Reset Menu */
		resetMenu(reset);
	}
	return 0;
}

/* Function Implementations */
void visit(int& target)
{
	std::cout << target << "\t";
} // end visit

void loadArr(int target[])
{
	std::cout << "Loading Array" << std::endl;
	for (int i = 0; i < SIZE; i++)
		target[i] = rand() % 200 + 1;     // range 1 to 200
	std::cout << "Array loaded successfully." << std::endl;
} // end loadArr

void menu(int& choice)
{
	std::cout << "\nThis program provides information from a randomly generated Binary Search Tree.\n\n\n";
	std::cout << "Choose from the following options:\n";
	std::cout << "\t1) Get Height\n\t2) InOrder Traversal\n\t3) PreOrder Traversal\n\t4) PostOrder Traversal\n\n";
	std::cout << "Enter Choice: ";
	std::cin >> choice;
} // end menu

void resetMenu(int&reset)
{
	std::cout << "\nWould you like to end the program?\n";
	std::cout << "Choose 0 for No and 1 for Yes.\n";
	std::cout << "Enter Choice: ";
	std::cin >> reset;
	if ((reset > 1) || (reset < 0))
	{
		std::cout << "\nInvalid Input: Ending program.";
		reset = 1;
	} // end if
} // end resetMenu