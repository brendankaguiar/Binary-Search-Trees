# the compiler: g++ for C++ program
CXX = g++ --std=c++11

#compiler flags:
# -g adds debugging inf to executable file
# -Wall turns on most, not all, compiler warnings
CXXFLAGS = -Wall -g

# the build target executable:

Exercise4: main.o BinaryNode.o BinaryNodeTree.o BinarySearchTree.o PrecondViolatedExcept.o NotFoundException.o #first line lists dependency of trunk.
	$(CXX) $(CXXFLAGS) -o Exercise4 main.o BinaryNode.o BinaryNodeTree.o BinarySearchTree.o PrecondViolatedExcept.o NotFoundException.o

#next line is building the object files with its dependencies.
main.o: BinaryNode.cpp BinaryNode.h BinaryTreeInterface.h BinaryNodeTree.cpp BinaryNodeTree.h BinarySearchTree.cpp BinarySearchTree.h PrecondViolatedExcept.h PrecondViolatedExcept.cpp NotFoundException.h NotFoundException.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

BinaryNode.o: BinaryNode.h

#indented line, known as generator line, not needed after first one bc of CXX.

BinaryNodeTree.o: BinaryNode.h BinaryNodeTree.h BinaryTreeInterface.h PrecondViolatedExcept.h NotFoundException.h

BinarySearchTree.o: BinaryNode.h BinarySearchTree.h BinaryTreeInterface.h PrecondViolatedExcept.h NotFoundException.h

PrecondViolatedExcept.o: PrecondViolatedExcept.h

NotFoundException.o: NotFoundException.h

clean:
	rm Exercise4 main.o BinaryNode.o BinaryNodeTree.o BinarySearchTree.o PrecondViolatedExcept.o NotFoundException.o