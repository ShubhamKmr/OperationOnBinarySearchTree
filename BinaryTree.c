#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct node
{
    int data;
    struct node * left;
    struct node * right;
};
#define MAX_SIZE 20
struct node * queue[MAX_SIZE];
int front = -1;
int rear = -1;
struct node * value= NULL;
struct node *newnode = NULL;
struct node * create_node(int data);
struct node * insert_node(struct node *root,int data);
void postorder_traversal(struct node * root);
void preorder_traversal(struct node * root);
void inorder_traversal(struct node * root);
void breadth_first_traversal(struct node * root);
bool search_in_tree(struct node * root,int data);
int total_no_of_nodes(struct node * root);
int total_no_of_leaf_nodes(struct node * root);
int total_no_of_non_leaf_nodes(struct node * root);
int height_of_tree(struct node * root);
struct node * findMaxinLeftSubtree(struct node * root);
bool DeleteNodeinTree(struct node *root,int val);
int deepth_of_node(struct node * root,int value);
//bool check_tree_is_bst_or_not(struct node * root);
//struct node * successor_of_a_node(struct node * root);
//struct node * predessor_of_a_node(struct node * root);
void enqueue(struct node* address);
struct node * dequeue();
void main()
{
    struct node * root = NULL;
    root = insert_node(root,10);
    root = insert_node(root,13);
    root = insert_node(root,9);
    root = insert_node(root,5);
    root = insert_node(root,8);
    root = insert_node(root,4);
    root = insert_node(root,12);
    root = insert_node(root,14);
    root = insert_node(root,11);
    root = insert_node(root,18);
    root = insert_node(root,17);
    root = insert_node(root,16);
    postorder_traversal(root);
    printf("Postorder traversal\n");
    preorder_traversal(root);
    printf("Preorder traversal\n");
    inorder_traversal(root);
    printf("Inorder traversal\n");
    breadth_first_traversal(root);
    printf("Breadth first traversal\n");
    bool res = search_in_tree(root,8);
    if (res == true)printf("Data in present\n");
    else printf("Data is not present :-(\n");
    printf("%d Total no of nodes in tree\n",total_no_of_nodes(root));
    printf("%d Total no of leaf nodes in tree\n",total_no_of_leaf_nodes(root));
    printf("%d Total no of non-leaf nodes in tree\n",total_no_of_non_leaf_nodes(root));
    printf("%d Height of tree\n",height_of_tree(root)-1);
    /*For recursive process to find the depth of a node use below 2 lines*/
    if (search_in_tree(root,10))printf("Depth of node is %d\n",deepth_of_node(root,10));
    else printf("Value not in Tree\n");
    /*For iterative process to find the depth of a node use below 2 lines*/
    #if 0
    int depth = deepth_of_node(root,10); 
    if (depth || (root->data == 10))printf("Depth is %d\n",depth);
    #endif
    if (DeleteNodeinTree(root,14))printf("Value deleted sucessfully\n");inorder_traversal(root);
    if (DeleteNodeinTree(root,18))printf("\nValue deleted sucessfully\n");inorder_traversal(root);
}

struct node * insert_node(struct node *root,int data)
{
    if (root == NULL)
    {
        newnode = create_node(data);
        return newnode;
    }
    else if(data <= root->data) 
    {
        root->left = insert_node(root->left,data);
    }
    else
    {
        root->right  = insert_node(root->right,data);
    }
    return root;
}

struct node * create_node(int data)
{
    newnode = (struct node *)malloc(sizeof(struct node *));
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

void postorder_traversal(struct node * root)
{
    if (root == NULL)return;
    postorder_traversal(root->left);
    postorder_traversal(root->right);
    printf("%d\t",root->data);
}
void preorder_traversal(struct node * root)
{
    if (root == NULL)return;
    printf("%d\t",root->data);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}
void inorder_traversal(struct node * root)
{
    if (root == NULL)return;
    inorder_traversal(root->left);
    printf("%d\t",root->data);
    inorder_traversal(root->right);
}

void breadth_first_traversal(struct node * root)
{
    enqueue(root);
    while (rear != front)
    {
        value = dequeue();
        printf("%d\t",value->data);
        if (value->left != NULL)enqueue(value->left);
        if (value->right!= NULL)enqueue(value->right);
    }
}

bool search_in_tree(struct node * root,int data)
{
    if (root == NULL)return;
    else if (data < root->data)search_in_tree(root->left,data); 
    else if (data > root->data)search_in_tree(root->right,data); 
    else if (data == root->data)return true;
    else return false; 
}

int total_no_of_nodes(struct node * root)
{
    if (root == NULL)return 0;
    return  1 + total_no_of_nodes(root->left) + total_no_of_nodes(root->right);
}

int total_no_of_leaf_nodes(struct node * root)
{
    if (root == NULL)return 0;
    else if(root->left == NULL && root->right == NULL)return 1;
    return total_no_of_leaf_nodes(root->left) + total_no_of_leaf_nodes(root->right);      
}
int total_no_of_non_leaf_nodes(struct node * root)
{
    if (root == NULL || (root->left == NULL && root->right == NULL))return 0;
    return 1 + total_no_of_non_leaf_nodes(root->left) + total_no_of_non_leaf_nodes(root->right);
}

int height_of_tree(struct node * root)
{
    if (root == NULL)return 0;
    int left_height = 1 + height_of_tree(root->left);
    int right_height = 1 + height_of_tree(root->right);
    if (left_height > right_height)return left_height;
    else return right_height;
}

struct info

{

    struct node * parentNode;

    struct node * childNode;

    bool flag;

};

struct info obj;

struct info * searchNode(struct node * root,int val , struct node * rootParent)
{
	if (root->data == val)
	{
		obj.childNode = root;
		obj.parentNode = rootParent;
		obj.flag = true;
		return &obj;
	}
	else if (val < root->data)
	{   
		rootParent = root;
		searchNode(root->left ,val ,rootParent);
	}

	else if (val > root->data)
	{   
		rootParent = root;
		searchNode(root->right ,val ,rootParent);
	}
}

bool DeleteNodeinTree(struct node *root,int val)
{
    struct info * address = searchNode(root,val,root);
    if (address->flag == true)
    {
        /*leaf node*/
        if (address->childNode->left == NULL && address->childNode->right == NULL)
        {
            if (address->childNode->data < address->parentNode->data )address->parentNode->left = NULL;
            else address->parentNode->right = NULL ;
            free(address->childNode);
        }
        /*node with 1 node*/
        else if (address->childNode->left == NULL || address->childNode->right == NULL)
        {
            if (address->childNode->data < address->parentNode->data)
            {                
                if (address->childNode->left != NULL)
                {
                    address->parentNode->left = address->childNode->left;
                }

                else
                {
                    address->parentNode->left = address->childNode->right;
                }

            }
            else
            {
                if (address->childNode->left != NULL)
                {
                    address->parentNode->right = address->childNode->left;
                }
                else
                {
                    address->parentNode->right = address->childNode->right;
                }

            }

    		free(address->childNode);
        }

        /*node with two children*/
        else if (address->childNode->left != NULL && address->childNode->right != NULL )
        {
    		address = searchNode(root,val,root);
		struct node * temp   =    findMaxinLeftSubtree(address->childNode->left);
                int data = temp->data;
		temp = address->childNode;
		DeleteNodeinTree(root,data);
                temp->data = data ;
        }
         
        return true;
    }
    else
    {
        printf("Data not in record\n");
        return false;
    }

}
struct node * findMaxinLeftSubtree(struct node * root)
{
    if (root == NULL)return findMaxinLeftSubtree(root->right);
}

int deepth_of_node(struct node * root,int value)
{
/*Iterative code to find depth of a node start*/
#if 0	
	unsigned short depth = 0;  
	if (search_in_tree(root,value))
	{
		while(root->data != value)
		{
			if (value < root->data)
			{
				root = root->left;
			}
			else
			{
				root = root->right;
			}
                   depth++;
		}
         
	return depth; 
      
	}
	else
	{
		printf("Value not present in tree\n");
                return 0;
	}
#endif	
/*Iterative code to find depth of a node end*/
	
	/*Recursive code to find depth of a node start*/
	if(root->data == value)return 0;
	else if ( value < root->data ) return 1 + deepth_of_node(root->left,value);
	else if (value > root->data ) return 1 + deepth_of_node(root->right,value);
	/*Recursive code to find depth of a node end*/
}

void enqueue(struct node * address)
{
    if (rear == MAX_SIZE -1)
    {
        printf("Queue is already full\n");
    }
    queue[++rear] =  address;
}
struct node * dequeue()
{
    if (rear == -1 && front == -1)
    {
        printf("Queue is already empty\n");
    }
    return queue[++front];
}

