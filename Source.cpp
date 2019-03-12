//Program Name: BST, AVL, Splay Tree
//Programmer Name: Tristan Wojtas
//Description: Inserts, Searches, and Deletes from all 3 Trees
//Date Created: 2/14/19
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#define FILENAME1 "bstoutput.txt"
#define FILENAME2 "avloutput.txt"
#define FILENAME3 "splayoutput.txt"
using namespace std;

int bstOperations = 0;
int avlOperations = 0;
int splayOperations = 0;
//Print File Function
void log(const std::string &input, int logFileNumber) {
	string fileName = "";
	if (logFileNumber == 1) {
		fileName = FILENAME1;
	}
	else if (logFileNumber == 2) {
		fileName = FILENAME2;
	}
	else if (logFileNumber == 3) {
		fileName = FILENAME3;
	}
	else {
		// some error message
	}
	ofstream filestream(fileName, std::ios_base::app | std::ios_base::out);
	filestream.flush();
	cout.flush();
	std::cout << input << endl;
	filestream << input << endl;
	filestream.close();
}

//Max Function
bool max(int a, int b)
{
	if (a < b)
		return b;
	else
		return a;
}


//Binary Search Trees
class BinarySearchTree
{
private:
	struct TreeNode {
		int value;
		TreeNode* left;
		TreeNode* right;

		//Constructor for node
		TreeNode(int value, TreeNode*left = NULL, TreeNode*right = NULL) {
			//assign parameters
			this->value = value;
			this->left = left;
			this->right = right;
		}

	};

	//private root
	TreeNode *root;

	//Inserting values
	void insert(TreeNode*& tree, int value) {


		//if the tree is empty(Base Case 1)
		if (tree == NULL) {
			tree = new TreeNode(value);
			return;
		}

		//if value is already in tree(Base Case 2)
		if (value == tree->value) {
			cout << "Value is already in tree" << endl;
			return;
		}
		//if value being inserted is smaller than current
		if (value < tree->value) {
			insert(tree->left, value);
		}
		//if value is greater than current node
		else {
			insert(tree->right, value);
		}
	}


	void displayInOrder(TreeNode*tree) {
		if (tree == NULL) {
			return;
		}
		//recursive function to display
		else {
			displayInOrder(tree->left);
			cout << tree->value << " ";
			displayInOrder(tree->right);
		}
	}

	string visualizeTree(TreeNode* root, int spacing) {
		string temp;
		if (root != NULL) {
			spacing += 5;
			temp += visualizeTree(root->right, spacing);
			temp += "\n";
			for (int i = 0; i < spacing; i++) {
				temp += " ";
			}
			ostringstream str1;
			str1 << root->value;

			temp += str1.str();
			temp += visualizeTree(root->left, spacing);
		}
		return temp;
	}

	// compute height of the tree
	int getHeight(TreeNode *root) {
		if (root == NULL)
			return 0;

		// find the height of each subtree
		int lh = getHeight(root->left);
		int rh = getHeight(root->right);

		return 1 + max(lh, rh);
	}


public:
	//constructor
	BinarySearchTree() {
		root = NULL;
	}
	void find(int item, TreeNode **par, TreeNode **loc)
	{
		TreeNode *ptr, *ptrsave;
		if (root == NULL)
		{
			*loc = NULL;
			*par = NULL;
			return;
		}
		if (item == root->value)
		{
			*loc = root;
			*par = NULL;
			return;
		}
		if (item < root->value)
			ptr = root->left;
		else
			ptr = root->right;
		ptrsave = root;
		while (ptr != NULL)
		{
			if (item == ptr->value)
			{
				*loc = ptr;
				*par = ptrsave;
				return;
			}
			ptrsave = ptr;
			if (item < ptr->value)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}
		*loc = NULL;
		*par = ptrsave;
	}
	void findFunction(int item){

		TreeNode *ptr, *ptrsave;
		if (root == NULL) {

			return;
		}
		if (item < root->value)
			ptr = root->left;
		else
			ptr = root->right;
		ptrsave = root;
		while (ptr != NULL)
		{
			if (item == ptr->value)
			{

				log("item found", 1);
				return;
			}
			ptrsave = ptr;
			if (item < ptr->value)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}
	}
	void del(int item)
	{
		TreeNode *parent, *location;
		if (root == NULL)
		{
			cout << "Tree empty" << endl;
			return;
		}
		find(item, &parent, &location);
		if (location == NULL)
		{
			cout << "Item not present in tree" << endl;
			return;
		}
		if (location->left == NULL && location->right == NULL)
			case_a(parent, location);
			++bstOperations;
			log("Additional BST Op", 1);
		if (location->left != NULL && location->right == NULL)
			case_b(parent, location);
			++bstOperations;
			log("Additional BST Op", 1);
		if (location->left == NULL && location->right != NULL)
			case_b(parent, location);
			++bstOperations;
			log("Additional BST Op", 1);
		if (location->left != NULL && location->right != NULL)
			case_c(parent, location);
			++bstOperations;
			log("Additional BST Op", 1);
		free(location);
	}
	void case_a(TreeNode *par, TreeNode *loc)
	{
		if (par == NULL)
		{
			root = NULL;
		}
		else
		{
			if (loc == par->left)
				par->left = NULL;
			else
				par->right = NULL;
		}
	}

	/*
	 * Case B
	 */
	void case_b(TreeNode *par, TreeNode *loc)
	{
		TreeNode *child;
		if (loc->left != NULL)
			child = loc->left;
		else
			child = loc->right;
		if (par == NULL)
		{
			root = child;
		}
		else
		{
			if (loc == par->left)
				par->left = child;
			else
				par->right = child;
		}
	}

	/*
	 * Case C
	 */
	void case_c(TreeNode *par, TreeNode *loc)
	{
		TreeNode *ptr, *ptrsave, *suc, *parsuc;
		ptrsave = loc;
		ptr = loc->right;
		while (ptr->left != NULL)
		{
			ptrsave = ptr;
			ptr = ptr->left;
		}
		suc = ptr;
		parsuc = ptrsave;
		if (suc->left == NULL && suc->right == NULL)
			case_a(parsuc, suc);
		else
			case_b(parsuc, suc);
		if (par == NULL)
		{
			root = suc;
		}
		else
		{
			if (loc == par->left)
				par->left = suc;
			else
				par->right = suc;
		}
		suc->left = loc->left;
		suc->right = loc->right;
	}
	void insert(int value) {
		insert(root, value);
	}

	void showInOrder() {
		displayInOrder(root);
	}
	string visualizeTreePublic() {
		string tree = visualizeTree(root, 0);
		return tree;
	}
	string getHeightHelper() {
		int x = getHeight(root);
		string height = "Height is: ";
		height += std::to_string(x);
		return height;
	}
	// get the max of two no.s
	int max(int a, int b) {
		return ((a > b) ? a : b);
	}

};

class AVL
{
public:
	AVL() {
		root = nullptr;
	}
	~AVL() {
		destroy(root);
	}

	//Struct Node within AVL class
	struct Node {
		int data;
		Node *left;
		Node *right;
		int height;

		Node(int d) {
			data = d;
			left = nullptr;
			right = nullptr;
			height = 0;
		}

		void updateHeight() {
			int lHeight = 0;
			int rHeight = 0;
			if (left != nullptr) {
				lHeight = left->height;
			}
			if (right != nullptr) {
				rHeight = right->height;
			}
			int max = (lHeight > rHeight) ? lHeight : rHeight;
			height = max + 1;
		}
	};

	void insert(int val) {
		insert(val, root);
	}
	void findFunction(int item) {

		Node *ptr, *ptrsave;
		if (root == NULL) {

			return;
		}
		if (item < root->data)
			ptr = root->left;
		else
			ptr = root->right;
		ptrsave = root;
		while (ptr != NULL)
		{
			if (item == ptr->data)
			{

				log("item found", 1);
				return;
			}
			ptrsave = ptr;
			if (item < ptr->data)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}
	}


	//Rotate a Node branch to the left, in order to balance things
	Node* rotateLeft(Node *&leaf) {
		Node* temp = leaf->right;
		leaf->right = temp->left;
		temp->left = leaf;

		//update the Nodes new height
		leaf->updateHeight();

		return temp;
	}

	//Rotate a Node branch to the right, in order to balance things
	Node* rotateRight(Node *&leaf) {
		Node* temp = leaf->left;
		leaf->left = temp->right;
		temp->right = leaf;

		//update the Nodes new height
		leaf->updateHeight();

		return temp;
	}
	Node * minValueNode(Node* node)
	{
		struct Node* current = node;

		/* loop down to find the leftmost leaf */
		while (current->left != NULL)
			current = current->left;

		return current;
	}
	int height(Node *N)
	{
		if (N == NULL)
			return 0;
		return N->height;
	}

	int getBalance(Node *N)
	{
		if (N == NULL)
			return 0;
		return height(N->left) - height(N->right);
	}

	void remove(int x) {
		root = deleteNode(root,x);
	}


	Node* deleteNode(Node* root, int key)
	{
		
		//Step1: Standard BST delete first then adjust
		if (root == NULL)
			return root;

		//If the key item is less then root its in left sub
		if (key < root->data)
			root->left = deleteNode(root->left, key);

		//If the key item is greater than root its in right sub
		else if (key > root->data)
			root->right = deleteNode(root->right, key);

		//if key is same as root then this is the node
		else
		{
			// node with only one child or no child 
			if ((root->left == NULL) || (root->right == NULL))
			{
				struct Node *temp = root->left ? root->left :
					root->right;

				// No child case 
				if (temp == NULL)
				{
					temp = root;
					root = NULL;
				}
				else // One child case 
					*root = *temp; // Copy the contents of 
								   // the non-empty child 
				free(temp);
			}
			else
			{
				// node with two children
				// successor (smallest in the right subtree) 
				struct Node* temp = minValueNode(root->right);

				// Copy the inorder successor's data to this node 
				root->data = temp->data;

				// Delete the inorder successor 
				root->right = deleteNode(root->right, temp->data);
			}
		}

		// If the tree had only one node then return 
		if (root == NULL)
			return root;

		//Step2: Update height of current node 
		root->height = 1 + max(height(root->left),
			height(root->right));

		//Step3: Check if balanced
		int balance = getBalance(root);

		// If this node becomes unbalanced, then there are 4 cases 

		// Left Left Case 
		if (balance > 1 && getBalance(root->left) >= 0)
			return rotateRight(root);

		// Left Right Case 
		if (balance > 1 && getBalance(root->left) < 0)
		{
			root->left = rotateLeft(root->left);
			return rotateRight(root);
		}

		// Right Right Case 
		if (balance < -1 && getBalance(root->right) <= 0)
			return rotateLeft(root);

		// Right Left Case 
		if (balance < -1 && getBalance(root->right) > 0)
		{
			root->right = rotateRight(root->right);
			return rotateLeft(root);
		}

		return root;
	}
	//Rotate a Node branch to the right then the left, in order to balance things
	Node* rotateRightLeft(Node *&leaf) {
		Node* temp = leaf->right;
		leaf->right = rotateRight(temp);
		return rotateLeft(leaf);
	}

	//Rotate a Node branch to the left then the right, in order to balance things
	Node* rotateLeftRight(Node *&leaf) {
		Node* temp = leaf->left;
		leaf->left = rotateLeft(temp);
		return rotateRight(leaf);
	}

	//Function that checks each Node's left and right branches to determine if they are unbalanced
	//If they are, we rotate the branches
	void rebalance(Node *&leaf) {
		int hDiff = getDiff(leaf);
		if (hDiff > 1) {
			if (getDiff(leaf->left) > 0) {
				leaf = rotateRight(leaf);
				log("Right Rotate ", 2);
				++avlOperations;
			}
			else {
				leaf = rotateLeftRight(leaf);
				log("LeftRight Rotate ", 2);
				++avlOperations;
			}
		}
		else if (hDiff < -1) {
			if (getDiff(leaf->right) < 0) {
				leaf = rotateLeft(leaf);
				log("Left Rotate ", 2);
				++avlOperations;
			}
			else {
				leaf = rotateRightLeft(leaf);
				log("RightLeft Rotate ", 2);
				++avlOperations;
			}
		}
	}
	string visualizeTreePublicAVL() {
		string tree = displayAVL(root, 0);
		return tree;
	}
	string getHeightHelperAVL() {
		int x = avlheight(root);
		string height = "Height is: ";
		height += std::to_string(x);
		return height;
	}

private:
	Node *root;
	//Insert a Node (very similar to BST, except we need to update Node height and then check for rebalance)
	void insert(int d, Node *&leaf) {
		if (leaf == nullptr) {
			leaf = new Node(d);
			leaf->updateHeight();
		}
		else {
			if (d < leaf->data) {
				insert(d, leaf->left);
				++avlOperations;
				leaf->updateHeight();
				rebalance(leaf);
			}
			else {
				insert(d, leaf->right);
				leaf->updateHeight();
				rebalance(leaf);
			}
		}
	}

	//Same as BST
	void destroy(Node *&leaf) {
		if (leaf != nullptr) {
			destroy(leaf->left);
			destroy(leaf->right);
			delete leaf;
		}
	}

	//Get the difference between Node right and left branch heights, if it returns positive
	//We know the left side is greater, if negative, we know the right side is greater
	int getDiff(Node *leaf) {
		int lHeight = 0;
		int rHeight = 0;
		if (leaf->left != nullptr) {
			lHeight = leaf->left->height;
		}
		if (leaf->right != nullptr) {
			rHeight = leaf->right->height;
		}
		return lHeight - rHeight;
	}

	string displayAVL(Node* root, int spacing) {
		string temp;
		if (root != NULL) {
			spacing += 5;
			temp += displayAVL(root->right, spacing);
			temp += "\n";
			for (int i = 0; i < spacing; i++) {
				temp += " ";
			}
			ostringstream str1;
			str1 << root->data;

			temp += str1.str();
			temp += displayAVL(root->left, spacing);
		}
		return temp;
	}
	int avlheight(Node *temp) {
		int h = 0;
		if (temp != NULL)
		{
			int l_height = avlheight(temp->left);
			int r_height = avlheight(temp->right);
			int max_height = max(l_height, r_height);
			h = max_height + 5;
		}
		return h;
	}
};

//Struct for SplayTree Class
struct Node {
	Node* father;
	Node* rightSon;
	Node* leftSon;
	int value;
};

class SplayTree {
	//Private attributes
	Node* root;
	//Private Methods
	bool isEmpty() {
		return root == NULL;
	}
	bool search_if_not_empty(int element) {

		Node* actualNode = root;

		//This loop won't stop until a return statement is executed.
		while (true) {
			//If the node we're studying has the value we want we stop
			if (actualNode->value == element) {
				floation(actualNode);
				//We've found what we were looking for, return true
				log("Found Item", 2);
				return true;
			}
			else if (actualNode->value < element) {
				if (actualNode->rightSon == NULL) {
					//If it doesn't have a right son, we won't find anything.
					log("Item Does Not Exist", 2);
					floation(actualNode);
					return false;
				}
				else {
					//If it has a right son, the next node we're going to study it's going to be his right son.
					actualNode = actualNode->rightSon;
				}
			}
			else {
				if (actualNode->leftSon == NULL) {
					//If it doesn't have a left son, we won't find anything.
					floation(actualNode);
					return false;
				}
				else {
					//If it has a left son, the next node we're going to study it's going to be his left son.
					actualNode = actualNode->leftSon;
				}
			}
		}
	}
	bool remove_if_not_empty(int elem) {

		Node* actualNode = root;
		//This loop won't stop until a return statement is executed.
		while (true) {

			//If the node we're studying has the value we're looking for, we proceed to remove the element transforming the subtree. 
			if (actualNode->value == elem) {
				return remove_node(actualNode);
			}
			else if (actualNode->value < elem) {
				//If it doesn't have a right son, we won't find what we are looking for.
				if (actualNode->rightSon == NULL) {
					//If we don't find the node we are trying to remove, we only floate the last node visited.
					floation(actualNode);
					return false;
				}
				else {
					//If it has a right son, the next node we're going to study it's going to be his right son.
					actualNode = actualNode->rightSon;
				}
			}
			else {
				//If it doesn't have a left son, we won't find what we are looking for.
				if (actualNode->leftSon == NULL) {
					//If we don't find the node we are trying to remove, we only floate the last node visited.
					floation(actualNode);
					return false;
				}
				else {
					//If it has a left son, the next node we're going to study it's going to be his left son.
					actualNode = actualNode->leftSon;
				}
			}
		}
	}
	void get_biggest(Node* &actualNode){
		//If it has a left son, we look for the node that's more to the right from his right son.
		actualNode = root->leftSon;

	while (actualNode->rightSon != NULL) {
		//While it has a right son...
		actualNode = actualNode->rightSon;
	}
	//Once this finished, actualNode is going to point to a node that it hasn't a right son (it's going to be the bigger from the original actualNode's left son).
	}
	bool remove_node(Node* &actualNode) {
		floation(actualNode);
		//If it doesn't have a left son.
		if (root->leftSon == NULL) {
			if (root->rightSon != NULL)	root->rightSon->father = NULL;
			root = root->rightSon;
			return true;
		}
		//If it has a left son, we look for the node that's more to the right from his right son.
		get_biggest(actualNode);
		//Once this finished, actualNode is going to point to a node that it hasn't a right son (it's going to be the bigger from the original actualNode's left son).
		//Root's right son, if it existed, it's going to be new actualNode's right son.
		if (root->rightSon != NULL) {
			actualNode->rightSon = root->rightSon;
			root->rightSon->father = actualNode;
		}
		//Root's left son will be the new root.
		root = root->leftSon;
		root->father = NULL;

		return true;
	}
	bool insert_if_empty(int element) {
		//We create a node in the root. We put the correct values in every field ( references=NULL and value=element).
		root = new  Node;
		root->rightSon = NULL;
		root->leftSon = NULL;
		root->father = NULL;
		root->value = element;
		//There's no need to fload, because the tree has only one node.
		//Everything worked correctly, so we return true.
		return true;
	}
	bool insert_if_not_empty(int element) {
		/*Pointer we are going to use to move through the tree. Points to the node we are studying every moment.
		It's going to start pointing to the root.*/
		Node* actualNode;
		actualNode = root;
		//This loop won't stop until a return statement is executed.
		while (true) {
			if (actualNode->value == element) {
				//Insertion didn't work correctly, we've found the element that we are trying to insert. We return false.
				floation(actualNode);
				return false;
			}
			else if (actualNode->value < element) {
				//If the node we are evaluating has a lower value than the one we want to introduce, we study his right son.
				if (study_right_son(actualNode, element)) return true;
			}
			else {
				//If the node we are evaluating has a bigger value than the one we want to introduce, we study his left son.
				if (study_left_son(actualNode, element)) return true;
			}
		}
	}
	bool study_right_son(Node* &actualNode, int element) {
		//If it has not a right son, we have a place to put it.
		if (actualNode->rightSon == NULL) {
			insert_to_right_son(actualNode, element);
			return true;
		}
		//If not, we change the node we are studying. Now it's going to be his right son.
		actualNode = actualNode->rightSon;
		return false;

	}
	bool study_left_son(Node* &actualNode, int element) {
		//If the node we are evaluating has a bigger value than the one we want to introduce, we study his right son.
		if (actualNode->leftSon == NULL) {
			insert_to_left_son(actualNode, element);
			return true;
		}
		//If not, we change the node we are studying. Now it's going to be his left son.
		actualNode = actualNode->leftSon;
		return false;
	}
	void insert_to_right_son(Node* &actualNode, int element) {
		actualNode->rightSon = new Node;
		actualNode->rightSon->rightSon = NULL;
		actualNode->rightSon->leftSon = NULL;
		actualNode->rightSon->father = actualNode;
		actualNode->rightSon->value = element;

		floation(actualNode->rightSon);
	}
	void insert_to_left_son(Node* &actualNode, int element) {
		actualNode->leftSon = new Node;
		actualNode->leftSon->rightSon = NULL;
		actualNode->leftSon->leftSon = NULL;
		actualNode->leftSon->father = actualNode;
		actualNode->leftSon->value = element;

		floation(actualNode->leftSon);
	}
	void updateParents(Node* &n, Node* &aux) {
		aux = n->father;
		n->father = n->father->father;
		aux->father = n;
	}
	void updateGrandpa(Node* &n, Node* &aux) {
		if (n->father != NULL) {
			if (n->father->rightSon == aux) {
				//If the father was grandpa's right son...
				n->father->rightSon = n;
			}
			else {
				//If the father was grandpa's left son...
				n->father->leftSon = n;
			}
		}
	}
	void L(Node* n) {
		Node* aux;
		updateParents(n, aux);
		aux->rightSon = n->leftSon;
		if (n->leftSon != NULL) {
			aux->rightSon->father = aux;
		}
		n->leftSon = aux;
		updateGrandpa(n, aux);
	}
	void R(Node* n) {
		Node* aux;
		updateParents(n, aux);
		aux->leftSon = n->rightSon;
		if (aux->leftSon != NULL) {
			aux->leftSon->father = aux;
		}
		n->rightSon = aux;
		updateGrandpa(n, aux);
	}
	bool rotate_if_father(Node* &actualNode) {
		//If it's father's right son.
		if (actualNode->father->rightSon == actualNode) {
			L(actualNode);
			++splayOperations;
			log("Zig ", 3);
			root = actualNode;
			//After the rotation, we've finished.
			return true;
		}
		//If it's father's left son.
		else if (actualNode->father->leftSon == actualNode) {
			R(actualNode);
			++splayOperations;
			log("Zag ", 3);
			root = actualNode;
			//After the rotation, we've finished.
			return true;
		}
		return false;
	}
	void rotate_if_grandpa(Node* &actualNode) {
		//We use it to avoid the entrance to both ifs.
		bool entered = false;
		//If it has a grandpa and his father is his grandpa's left son.
		if (actualNode->father->father->leftSon != NULL) {
			//If actualNode is the left son from the grandpa's left son...
			if (actualNode->father->father->leftSon->leftSon == actualNode) {
				R(actualNode->father);
				R(actualNode);
				++splayOperations;
				log("ZigZig ", 3);
				entered = true;
			}
			//If actualNode is the right son from grandpa's left son.
			else if (actualNode->father->father->leftSon->rightSon == actualNode) {
				L(actualNode);
				R(actualNode);
				++splayOperations;
				log("ZigZag ", 3);
				entered = true;
			}
		}
		//If it has a grandpa and his father is his grandpa's right son.
		if (!entered && actualNode->father->father->rightSon != NULL) {
			//If actualNode is the right son from grandpa's right son.
			if (actualNode->father->father->rightSon->rightSon == actualNode) {
				L(actualNode->father);
				L(actualNode);
				log("ZagZag ", 3);
				++splayOperations;
			}
			//If actualNode is the left son from grandpa's right son.
			else if (actualNode->father->father->rightSon->leftSon == actualNode) {
				R(actualNode);
				L(actualNode);
				log("ZagZig ", 3);
				++splayOperations;
			}
		}
	}
	void floation(Node* n) {
		//Pointer we are going to use to move through the tree. Points to the node we are studying every moment
		Node* actualNode = n;
		//This loop won't stop until a return statement is executed.
		while (true) {
			//If a node has a grandpa, we will float differently ( consult link above).
			if (actualNode->father != NULL && actualNode->father->father != NULL) {
				rotate_if_grandpa(actualNode);
			}
			//If it has a father but not a grandpa...
			else if (actualNode->father != NULL) {
				if (rotate_if_father(actualNode)) break;
			}
			else {
				//If it doesn't have father, it means we've finished.
				root = actualNode;
				break;
			}
		}
	}
	string visualizeTree(Node* root, int spacing) {
		string temp;
		if (root != NULL) {
			spacing += 5;
			temp += visualizeTree(root->rightSon, spacing);
			temp += "\n";
			for (int i = 0; i < spacing; i++) {
				temp += " ";
			}
			ostringstream str1;
			str1 << root->value;

			temp += str1.str();
			temp += visualizeTree(root->leftSon, spacing);
		}
		return temp;
	}

public:
	//Public Methods
	SplayTree();

	//Remove, if it exists, a node with value=elem from the SplayTree. It returns true if it existed and it has been removed.
	bool remove(int elem) {
		//If its empty, we can't remove anything.
		if (isEmpty()) return false;
		return remove_if_not_empty(elem);
	}
	//Looks for a node with value = elem. It returns true if its on the tree. False if not.
	bool search(int elem) {
		//If it's empty, we won't find it.
		if (isEmpty()) return false;
		return search_if_not_empty(elem);
	}
	//Inserts a node with value= elem. If there's another node with the same value, it returns false. True if not.
	bool insert(int element) {
		if (isEmpty()) return insert_if_empty(element);
		return insert_if_not_empty(element);
	}
	string visualizeTreePublic() {
		string tree = visualizeTree(root, 0);
		return tree;
	}

};

SplayTree::SplayTree() {
	root = NULL;
}



int main() {

	ifstream infile;

	//Code inserts and prints inorder

	BinarySearchTree tree;
	AVL avl;
	SplayTree s;

	infile.open("text.txt");
	if (infile.fail()) {
		cout << "Input File did not open" << endl;
	}
	int x;

	//Read
	while (infile >> x) {

		//Prints Insert at the top
		ostringstream tempx;
		tempx << x;
		string insert = "Insert: ";
		insert += tempx.str();
		log(insert, 1);

		//Inserts in tree
		tree.insert(x);
		avl.insert(x);
		s.insert(x);

		//Prints tree
		log("BST: ", 1);
		log(tree.visualizeTreePublic(), 1);
		log(tree.getHeightHelper(), 1);
		cout << endl << endl;
		log(insert, 2);
		log("AVL Tree: ", 2);
		log(avl.visualizeTreePublicAVL(), 2);
		log(avl.getHeightHelperAVL(), 2);
		log("Splay Tree: ", 3);
		log(s.visualizeTreePublic(), 3);
		

		cout << endl;
		tempx.str("");
	}
	ifstream fin;
	char input;
	int y;
	fin.open("text1.txt");
	if (fin.fail()) {
		cout << "Input File 1 did not open" << endl;
	}
	while (!fin.eof()) {
		fin >> input;
		//cout << input;
		if (input == 'S') {
			fin >> y;
			cout << y << endl;
			tree.findFunction(y);
			avl.findFunction(y);
			s.search(y);
			continue;
		}

		else if (input == 'I') {
			fin >> y;
			cout << y << endl; 
			tree.insert(y);
			avl.insert(y);
			s.insert(y);
			log("Inserted in BST", 1);
			log("Inserted in AVL", 2);
			log("Inserted in SPLAY", 3);
			log(tree.visualizeTreePublic(), 1);
			log(avl.visualizeTreePublicAVL(), 2);
			continue;
		}
		else if (input == 'D') {
			fin >> y;
			tree.del(y);
			avl.remove(y);
			s.remove(y);
			log("Deleted in BST", 1);
			log("Deleted in AVL", 2);
			log("Deleted in SPLAY", 3);
			log(tree.visualizeTreePublic(), 1);
			log(avl.visualizeTreePublicAVL(), 2);
			log(s.visualizeTreePublic(), 3);
			continue;
		}
		else
		{
			log("invalid input", 1);

		}
	}

	stringstream ss1;
	ss1 << bstOperations;
	string str1 = ss1.str();

	stringstream ss2;
	ss2 << avlOperations;
	string str2 = ss2.str();

	stringstream ss3;
	ss3 << splayOperations;
	string str3 = ss3.str();

	string table[6] = { "BST Operations: ",str1,"Avl Operations: ",str2,"Splay Operations: ",str3 };
	for (int i = 0; i < 6; i++) {
		cout << table[i] << endl;
	}
		system("pause");
		return 0;
	}

