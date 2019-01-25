#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int value;
	struct node* left;
	struct node* right;
} node;

//helper function to create a new node with a given value
node* createNode(int value)
{
	node* newNode = (node*) malloc(sizeof(node));
	newNode->value = value;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
	
}

//insert a new node to a given tree
void insert(node** rootPtr, int value)
{
	//base case
	if (*rootPtr==NULL)
	{
		node* newNode = createNode(value);
		*rootPtr = newNode;
	}
	else
	{
		//if value is smaller than or equal to the value of the current root
		//go to the left subtree
		if (value <= (*rootPtr)->value)
		{
			insert(&((*rootPtr)->left),value);
		}
		//if value is greater than the value of the current roott
		//go to the right subtree
		else
		{
			insert(&((*rootPtr)->right),value);
		}
	}
}

//searh for a given value in a tree
//returns 1 if found, -1 if not found
int search(node* root, int value)
{
	//base case for not found
	if (root == NULL)
	{
		return -1;
	}
	//base case for found
	else if (root->value == value)
	{
		return 1;
	}
	//if value is smaller than the current value of the root
	//go to the left subtree
	else if (value < root->value)
	{
		return search(root->left,value);
	}
	//if value is greater than the current value of the root
	//go to the right subtree
	else
	{
		return search(root->right,value);
	}
}

//healper function to find the inorder succesor of the root of a tree
//returns the value of the inorder successor
int inorderSuccessor(node* root)
{
	while (root->left != NULL)
	{
        root = root->left;
	}
  
    return root->value;
}

//deletes the node with a given value in a tree
//does nothing if the node does not exist
void delete(node** rootPtr, int value)
{
	//if node does not exist
	//does nothing
    if (search(*rootPtr,value)==-1)
	{
		return;
	}
	//if value is smaller than the current value of the root
	//go to the left subtree
    else if (value < (*rootPtr)->value) 
	{
        delete(&(*rootPtr)->left, value); 
	}
	//if value is greater than the current value of the root
	//go to the left subtree
    else if (value > (*rootPtr)->value) 
	{
        delete(&(*rootPtr)->right, value); 
	}
	//when found the correct node
    else
    { 
		//if the node only has right subtree
		//deletes the node by setting the pointer to its right subtree
        if (((*rootPtr)->left == NULL)&&((*rootPtr)->right != NULL)) 
        { 
        	node* temp = (*rootPtr)->right;
        	free(*rootPtr);
            *rootPtr = temp; 
        } 
		//if the node only has left subtree
		//deletes the node by setting the pointer to its left subtree
        else if (((*rootPtr)->right == NULL)&&((*rootPtr)->left != NULL))
        { 
        	node* temp = (*rootPtr)->left;
        	free(*rootPtr);
            *rootPtr = temp;  
        }
		//if the node has no children
		//deletes the node by setting the pointer to NULL
		else if (((*rootPtr)->left == NULL)&&((*rootPtr)->right == NULL))
		{
			free(*rootPtr);
			*rootPtr = NULL;
		}
		//if the node has two subtrees
		//find its corresponding inorder successor from the right subtree
		//deletes the node by setting the valaue of the node to its inorder successor
		//then deletes the inorder successor from its right subtree
		else
		{
       		int key = inorderSuccessor((*rootPtr)->right);
			(*rootPtr)->value = key;
			delete(&(*rootPtr)->right,key);
		}
    } 
}

//return the size of a tree
int size(node* root)
{
	if (root==NULL)
	{
		return 0;
	}
	else
	{
		return (size(root->left)+1+size(root->right));
	}
}

//helper funtion to copy a tree into an existing pointer to a tree
void copyTree(node** copy, node* root)
{
	if (root != NULL)
	{
		insert(copy,root->value);
	}
	
	if (root->left != NULL)
	{
		copyTree(copy,root->left);
	}
	
	if (root->right != NULL)
	{
		copyTree(copy,root->right);
	}
	
}

//concatonate two trees (using tree1 as the root)
//return a pointer to the root of the new tree
node* concatonate(node* tree1,node* tree2)
{
	node* root = NULL;
	copyTree(&root,tree1);
	copyTree(&root,tree2);
	return root;
}

//traverse and print the tree inorder
void printInorder(node* root)
{
	if (root != NULL){
		printInorder(root->left);
		printf("%d ",root->value);
		printInorder(root->right);
	}
}

//traverse and print the tree preorder
void printPreorder(node* root)
{
	if (root != NULL){
		printf("%d ",root->value);
		printPreorder(root->left);
		printPreorder(root->right);
	}
}

//traverse and print the tree preorder
void printPostorder(node* root)
{
	if (root != NULL){
		printPostorder(root->left);
		printPostorder(root->right);
		printf("%d ",root->value);
	}
}

//free the tree
void freeTree(node** rootPtr)
{
	node* left = (*rootPtr)->left;
	node* right = (*rootPtr)->right;
	if (*rootPtr != NULL)
	{
		free(*rootPtr);
		*rootPtr = NULL;
	}

	if (left != NULL)
	{
		freeTree(&left);
	}

	if (right != NULL)
	{
		freeTree(&right);
	}
}

int main()
{
	printf("------Test------\n");
	node* root = NULL;
	printf("Insert elements 15,8,20,16,21 into tree1 respectively:\n");
	insert(&root,15);
	insert(&root,8);
	insert(&root,20);
	insert(&root,16);
	insert(&root,21);
	printf("tree1:\n");
	printf("Expected(inorder): 8 15 16 20 21 size: 5\n");
	printf("Actual(inorder): ");
	printInorder(root);
	printf("size: %d", size(root));
	printf("\n");
	printf("Expected(preorder): 15 8 20 16 21 size: 5\n");
	printf("Actual(preorder): ");
	printPreorder(root);
	printf("size: %d", size(root));
	printf("\n");
	printf("Expected(postorder): 8 16 21 20 15 size: 5\n");
	printf("Actual(postorder): ");
	printPostorder(root);
	printf("size: %d", size(root));
	printf("\n");

	printf("\n");
	printf("Delete element 20 from tree1: \n");
	delete(&root,20);
	printf("tree1:\n");
	printf("Expected(inorder): 8 15 16 21 size: 4\n");
	printf("Actual(inorder): ");
	printInorder(root);
	printf("size: %d", size(root));
	printf("\n");
	printf("Expected(preorder): 15 8 16 21 size: 4\n");
	printf("Actual(preorder): ");
	printPreorder(root);
	printf("size: %d", size(root));
	printf("\n");
	printf("Expected(postorder): 8 16 21 15 size: 4\n");
	printf("Actual(postorder): ");
	printPostorder(root);
	printf("size: %d", size(root));
	printf("\n");

	printf("\n");
	printf("Delete element 9 from tree1: \n");
	delete(&root,9);
	printf("tree1:\n");
	printf("Expected(inorder): 8 15 16 21 size: 4\n");
	printf("Actual(inorder): ");
	printInorder(root);
	printf("size: %d", size(root));
	printf("\n");
	printf("Expected(preorder): 15 8 21 16 size: 4\n");
	printf("Actual(preorder): ");
	printPreorder(root);
	printf("size: %d", size(root));
	printf("\n");
	printf("Expected(postorder): 8 16 21 15 size: 4\n");
	printf("Actual(postorder): ");
	printPostorder(root);
	printf("size: %d", size(root));
	printf("\n");

	node* root2 = NULL;
	printf("\n");
	printf("Insert elements 10,4,19 into tree2 respectively:\n");
	insert(&root2,10);
	insert(&root2,4);
	insert(&root2,19);
	printf("tree2:\n");
	printf("Expected(inorder): 4 10 19 size: 3\n");
	printf("Actual(inorder): ");
	printInorder(root2);
	printf("size: %d", size(root2));
	printf("\n");
	printf("Expected(preorder): 10 4 19 size: 3\n");
	printf("Actual(preorder): ");
	printPreorder(root2);
	printf("size: %d", size(root2));
	printf("\n");
	printf("Expected(postorder): 4 19 10 size: 3\n");
	printf("Actual(postorder): ");
	printPostorder(root2);
	printf("size: %d", size(root2));
	printf("\n");

	printf("\n");
	printf("Concatonate tree 1 and tree 2: \n");
	node* newTree = concatonate(root,root2);
	printf("new Tree:\n");
	printf("Expected(inorder): 4 8 10 15 16 19 21 size: 7\n");
	printf("Actual(inorder): ");
	printInorder(newTree);
	printf("size: %d", size(newTree));
	printf("\n");
	printf("Expected(preorder): 15 8 4 10 21 16 19 size: 7\n");
	printf("Actual(preorder): ");
	printPreorder(newTree);
	printf("size: %d", size(newTree));
	printf("\n");
	printf("Expected(postorder): 4 10 8 19 16 21 15 size: 7\n");
	printf("Actual(postorder): ");
	printPostorder(newTree);
	printf("size: %d", size(newTree));
	printf("\n");
	
	printf("\n");
	printf("Free the new Tree: \n");
	freeTree(&newTree);
	printf("new Tree:\n");
	printf("Expected(inorder): size: 0\n");
	printf("Actual(inorder): ");
	printInorder(newTree);
	printf("size: %d", size(newTree));
	printf("\n");
	printf("------Test Finished------\n");
	
	freeTree(&root);
	freeTree(&root2);
}
