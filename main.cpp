#include <iostream>

using namespace std;

#define RED 1
#define BLACK 0

struct Node
{
	int data;
	int color;
	Node* parent, * left, * right;

	Node(int data) {
		this->data = data;
		this->color = RED;
		parent = left = right = NULL;
	}
};

class RBTree {
private:
	Node* root;
	
public:
	RBTree() {
		root = NULL;
	}

	Node* getRoot() {
		return root;
	}

	void secondCaseLeft(Node* pt) {
		Node* p = pt->parent;
		Node* gp = pt->parent->parent;

		if (pt->left != NULL) {
			p->right = pt->left;
			pt->left->parent = p;
		}
		else {
			p->right = NULL;
		}

		p->parent = pt;

		pt->left = p;
		pt->parent = gp;

		gp->left = pt;
		
		thirdCaseLeft(p);
	}

	void secondCaseRight(Node* pt) {
		Node* p = pt->parent;
		Node* gp = pt->parent->parent;

		if (pt->right != NULL) {
			p->left = pt->right;
			pt->right->parent = p;
		}
		else {
			p->right = NULL;
		}

		p->parent = pt;

		pt->right = p;
		pt->parent = gp;

		gp->right = pt;

		thirdCaseRight(p);
	}

	void thirdCaseLeft(Node* pt) {
		Node* gp = pt->parent->parent;
		Node* p = pt->parent;

		if (root == gp) {
			root = p;
			p->parent = NULL;
		}
		else {
			if (gp->parent->left == gp) {
				gp->parent->left = p;
			}
			else {
				gp->parent->right = p;
			}
			p->parent = gp->parent;
		}

		if (p->right != NULL) {
			gp->left = p->right;
			p->right->parent = gp;
		}
		else {
			gp->left = NULL;
		}

		gp->parent = p;
		gp->color = RED;

		p->right = gp;
		p->color = BLACK;
	}

	void thirdCaseRight(Node* pt) {
		Node* gp = pt->parent->parent;
		Node* p = pt->parent;

		if (root == gp) {
			root = p;
			p->parent = NULL;
		}
		else {
			if (gp->parent->left == gp) {
				gp->parent->left = p;
			}
			else {
				gp->parent->right = p;
			}
			p->parent = gp->parent;
		}

		if (p->left != NULL) {
			gp->right = p->left;
			p->left->parent = gp;
		}
		else {
			gp->right = NULL;
		}
		
		gp->parent = p;
		gp->color = RED;

		p->left = gp;
		p->color = BLACK;
	}

	void insertFix(Node* pt) {
		Node* uncle = NULL;
		if (pt->parent->color == RED) {
			if (pt->parent->parent->left == pt->parent) {
				uncle = pt->parent->parent->right;
				if (uncle == NULL || uncle->color == BLACK) {
					if (pt->parent->right == pt) {
						secondCaseLeft(pt);
					}
					else {
						thirdCaseLeft(pt);
					}
				}
				else {
					uncle->color = BLACK;
					pt->parent->color = BLACK;
					pt->parent->parent->color = RED;
					if (pt->parent->parent != root) {
						insertFix(pt->parent->parent);
					}
				}
			}
			else if (pt->parent->parent->right == pt->parent) {
				uncle = pt->parent->parent->left;
				if (uncle == NULL || uncle->color == BLACK) {
					if (pt->parent->left == pt) {
						secondCaseRight(pt);
					}
					else {
						thirdCaseRight(pt);
					}
				}
				else {
					uncle->color = BLACK;
					pt->parent->color = BLACK;
					pt->parent->parent->color = RED;
					if (pt->parent->parent != root) {
						pt = pt->parent->parent;
						insertFix(pt);
					}
				}
			}
		}
		root->color = BLACK;
	}

	void insert(int data) {
		if (root == NULL) {
			root = new Node(data);
			root->color = BLACK;
		}
		else {
			Node* pt = new Node(data);
			Node* temp = root;
			int isInserted = 0;
			while (isInserted == 0) {
				if (pt->data < temp->data) {
					if (temp->left != NULL) {
						temp = temp->left;
					}
					else {
						temp->left = pt;
						pt->parent = temp;
						insertFix(pt);
						isInserted = 1;
					}
				}
				else {
					if (temp->right != NULL) {
						temp = temp->right;
					}
					else {
						temp->right = pt;
						pt->parent = temp;
						insertFix(pt);
						isInserted = 1;
					}
				}
			}
		}
	}

	int maxDepth(Node* pt) {
		if (pt == NULL) {
			return -1;
		}
		else
		{
			int lDepth = maxDepth(pt->left);
			int rDepth = maxDepth(pt->right);

			if (lDepth > rDepth) {
				return(lDepth + 1);
			}
			else {
				return(rDepth + 1);
			}
		}
	}

	int minDepth(Node* pt) {
		if (pt == NULL) {
			return -1;
		}
		else {
			int lDepth = minDepth(pt->left);
			int rDepth = minDepth(pt->right);

			if (lDepth < rDepth) {
				return(lDepth + 1);
			}
			else {
				return(rDepth + 1);
			}
		}
	}

	int redNodes(Node* pt) {
		if (pt == NULL) {
			return 0;
		}
		else {
			int leftOnes = redNodes(pt->left);
			int rightOnes = redNodes(pt->right);

			if (pt->color == RED) {
				return leftOnes + rightOnes + 1;
			}
			else {
				return leftOnes + rightOnes;
			}
		}
	}

	void additional() {
		cout << "Maksymalna glebokosc lisci: " << maxDepth(root) << "\n";
		cout << "Minimalna glebokosc lisci: " << minDepth(root) << "\n";
		cout << "Liczba czerwonych wezlow: " << redNodes(root) << "\n\n";
	}

	void printLoop(Node* pt, string indent, bool last) {
		if (pt != NULL) {
			cout << indent;
			if (pt != root) {
				if (last) {
					cout << "R----";
					indent += "     ";
				}
				else {
					cout << "L----";
					indent += "|    ";
				}
			}

			string color;
			if (pt->color) {
				color = "RED";
			}
			else {
				color = "BLACK";
			}

			cout << pt->data << "(" << color << ")" << endl;
			printLoop(pt->left, indent, false);
			printLoop(pt->right, indent, true);
		}
	}

	void print() {
		if (root != NULL) {
			printLoop(root, "", true);
		}
		cout << endl;
	}

};

int main() {
	RBTree tree;
	tree.insert(38);
	tree.print();
	tree.additional();
	tree.insert(31);
	tree.print();
	tree.additional();
	tree.insert(22);
	tree.print();
	tree.additional();
	tree.insert(8);
	tree.print();
	tree.additional();
	tree.insert(20);
	tree.print();
	tree.additional();
	tree.insert(5);
	tree.print();
	tree.additional();
	tree.insert(10);
	tree.print();
	tree.additional();
	tree.insert(9);
	tree.print();
	tree.additional();
	tree.insert(21);
	tree.print();
	tree.additional();
	tree.insert(27);
	tree.print();
	tree.additional();
	tree.insert(29);
	tree.print();
	tree.additional();
	tree.insert(25);
	tree.print();
	tree.additional();
	tree.insert(28);
	tree.print();
	tree.additional();

	RBTree tree1000;
	for (int i = 1; i <= 1000; i++) {
		tree1000.insert(i);
	}
	tree1000.additional();


	return 0;
}