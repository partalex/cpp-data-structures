//#include<bits/stdc++.h>
#include<iostream>

struct node
{
	int data;
	struct node* left;
	struct node* right;
};
using namespace std;

struct Node {
	int data;
	struct Node* left;
	struct Node* right;

	Node(int val)
	{
		data = val;
		left = NULL;
		right = NULL;
	}
};

int main()
{

	/*create root*/
	struct Node* root = new Node(1);
	/* following is the tree after above statement

			1
			/ \
		NULL NULL
	*/

	root->left = new Node(2);
	root->right = new Node(3);
	/* 2 and 3 become left and right children of 1
					1
				/ \
				2	 3
			/ \	 / \
			NULL NULL NULL NULL
	*/

	root->left->left = new Node(4);
	/* 4 becomes left child of 2
			1
			/	 \
		2	 3
		/ \	 / \
		4 NULL NULL NULL
		/ \
	NULL NULL
	*/

	return 0;
}
