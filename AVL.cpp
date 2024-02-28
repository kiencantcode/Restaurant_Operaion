#include <iostream>
#include <queue>
using namespace std;

struct Node
{
	int result;
	int ID;
	int num;
	Node *left;
	Node *right;
	int height;
};

class AVLTree
{
public:
	Node *root;

	AVLTree()
	{
		root = nullptr;
	}

	int height(Node *node)
	{
		if (node == nullptr)
			return 0;
		return node->height;
	}

	Node *rotateRight(Node *y)
	{
		Node *x = y->left;
		Node *T2 = x->right;

		x->right = y;
		y->left = T2;

		y->height = max(height(y->left), height(y->right)) + 1;
		x->height = max(height(x->left), height(x->right)) + 1;

		return x;
	}

	Node *rotateLeft(Node *x)
	{
		Node *y = x->right;
		Node *T2 = y->left;

		y->left = x;
		x->right = T2;

		x->height = max(height(x->left), height(x->right)) + 1;
		y->height = max(height(y->left), height(y->right)) + 1;

		return y;
	}
	int getBalance(Node *node)
	{
		if (node == nullptr)
			return 0;
		return height(node->left) - height(node->right);
	}

	int countNode(Node *node){
		if(node == nullptr)
			return 0;
		return countNode(node->left) + countNode(node->right) + 1;
	}

	Node *insert(Node *node, int result, int ID, int num)
	{
		
		if (node == nullptr)
		{
			Node *newNode = new Node();
			newNode->result = result;
			newNode->ID = ID;
			newNode->num = num;
			newNode->left = nullptr;
			newNode->right = nullptr;
			newNode->height = 1;
			return newNode;
		}

		if (result < node->result)
		{
			node->left = insert(node->left, result, ID, num);
		}
		else if (result > node->result)
		{
			node->right = insert(node->right, result, ID, num);
		}
		else
		{
			node->right = insert(node->right, result, ID, num);
		}

		node->height = 1 + max(height(node->left), height(node->right));

		int balance = getBalance(node);

		if (balance > 1 && result < node->left->result)
		{
			return rotateRight(node);
		}

		if (balance < -1 && result > node->right->result)
		{
			return rotateLeft(node);
		}

		if (balance > 1 && result > node->left->result)
		{
			node->left = rotateLeft(node->left);
			return rotateRight(node);
		}

		if (balance > 1 && result == node->left->result){
			node->left = rotateLeft(node->left);
			return rotateRight(node);
		}

		if (balance < -1 && result < node->right->result)
		{
			node->right = rotateRight(node->right);
			return rotateLeft(node);
		}

		return node;
	}
	bool traversal(Node *node, int ID)
	{
		if (node == nullptr)
			return false;
		if (node->ID == ID)
			return true;
		return traversal(node->left, ID) || traversal(node->right, ID);
	}

	Node *minValueNode(Node* node){
		Node* current = node;
		while(current->left != nullptr){
			current = current->left;
		}
		return current;
	}

	Node *deleteNode(Node* node, int result, int ID){
		if(node == nullptr) return node;
		if(result < node->result){
			node->left = deleteNode(node->left, result, ID);
		}
		else if(result > node->result){
			node->right = deleteNode(node->right, result, ID);
		}
		else{
			if(node->result == result && node->ID == ID){
				//no child
				if(node->left == nullptr && node->right == nullptr){
					delete node;
					return nullptr;
				}
				//just has right child
				else if(node->left == nullptr){
					Node* temp = node;
					node = node->right;
					delete temp;
					return node;
				}
				//just has left child
				else if(node->right == nullptr){
					Node* temp = node;
					node = node->left;
					delete temp;
					return node;
				}
				else{
					Node* smallestOnRight = minValueNode(node->right);
					node->result = smallestOnRight->result;
					node->ID = smallestOnRight->ID;
					node->right = deleteNode(node->right, smallestOnRight->result, smallestOnRight->ID);
				}
			}
			else{
				node->left = deleteNode(node->left, result, ID);
				node->right = deleteNode(node->right, result, ID);
			}
		}

		// if ((node->left == nullptr) || node->right == nullptr){
			// 	Node* temp = node->left ? node->left : node->right;
			// 	if(temp == nullptr) {
			// 		temp = node;
			// 		node = nullptr;
			// 	}
			// 	else{
			// 		*node  = *temp;
			// 	}
			// 	delete temp;
			// }
			// else{
			// 	Node* temp = minValueNode(node->right);
			// 	node->result = temp->result;
			// 	node->right	= deleteNode(node->right, temp->result, temp->ID);
			// }
		if(node == nullptr) return node;
		node->height = 1 + max(height(node->left), height(node->right));
		int balance = getBalance(node);
		//Left left case
		if(balance > 1 && getBalance(node->left) >= 0){
			return rotateRight(node);
		}
		//Left right case
		if(balance > 1 && getBalance(node->left) < 0){
			node->left = rotateLeft(node->left);
			return rotateRight(node);
		}
		//Right right case
		if(balance < -1 && getBalance(node->right) <= 0){
			return rotateLeft(node);
		}
		//Right left case
		if(balance < -1 && getBalance(node->right) > 0){
			node->right = rotateRight(node->right);
			return rotateLeft(node);
		}
		return node;
	}

	void getResult(Node *node, int ID, int &result)
	{
		if (node == nullptr)
			return;
		if (node->ID == ID)
			result = node->result;
		getResult(node->left, ID, result);
		getResult(node->right, ID, result);
	}

	void updateNum(Node *node, int ID, int num){
		if(node == nullptr) return;
		if(node->ID == ID){
			node->num = num;
			return;
		}
		updateNum(node->left, ID, num);
		updateNum(node->right, ID, num);
	}

	void clear(Node *node){
		if(node == nullptr) return;
		clear(node->left);
		clear(node->right);
		delete node;
	}

	void display(Node* root) {
    if (!root) {
        return;
    }
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            Node* curr = q.front();
            q.pop();
            cout << curr->ID << "-" << curr->result << "-" << curr->num << endl;
            if (curr->left) {
                q.push(curr->left);
            }
            if (curr->right) {
                q.push(curr->right);
            }
        }
    }
	}
};

int main() {

    AVLTree tree;

    Node *root = nullptr;
    root = tree.insert(root, 22454, 1, 1);
    root = tree.insert(root, 0, 2, 1);
	root = tree.insert(root, 0, 3, 1);
	root = tree.insert(root, 9682, 4, 1);
	root = tree.insert(root, 10922, 5, 1);
	root = tree.insert(root, 9362, 6, 1);
	for(int i = 0; i < 10; i++){
		cout << tree.traversal(root, i+1) << endl;
	}
	tree.display(root);
    return 0;
}
