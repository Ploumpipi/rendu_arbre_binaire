using namespace std;
#include "CTree.h";

int main() {
	CTree tree;
	tree.addNode(5);
	tree.addNode(15);
	tree.addNode(2);
	tree.addNode(22);
	tree.addNode(16);
	tree.addNode(11);
	tree.addNode(3);
	tree.addNode(8);

	tree.afficher(tree.getArbre());


	return 0;
}