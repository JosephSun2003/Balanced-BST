#include<stdio.h>
#include<stdlib.h>

typedef struct BST_node_struct
{
    int key;
    struct BST_node_struct* left;
    struct BST_node_struct* right;
}BST_node;

BST_node *new_BST_Node(int input_int){
    /**
     * @brief Creating a new node given an input value
     * 
     */

    BST_node *new_node = (BST_node *)calloc(1,sizeof(BST_node));

    //there's no more space chief
    if(new_node == NULL) {
        printf("No more space in Memory! \n");
        return NULL;
    }

    //setting values
    new_node->key = input_int;

    return new_node;
}

BST_node* search_for(BST_node *root, int key){
    if(root->key == key) return root;
    else if(root->left != NULL && root->key > key) return search_for(root->left, key);
    else if(root->right != NULL && root->key < key) return search_for(root->right, key);

    return NULL;
}

BST_node *balance(BST_node *root){
    /**
     * @brief Balances the BST to ensure optimal search complexity
     */

    /**
     * Function Notes:
     * Recusrion can be used, although tail recursion should be done if possible (unlikely will given the algorithm implemented)
     * Post-order operation (left, centre, right)
     * Switching of data, not the node itself (too messy)
     * Assumption of no duplicates
     */

    //go left if it isn't empty & check left vs. centre
    if(root->left != NULL){
        root->left = balance(root->left);
        if(root->left->key > root->key){
            int temp = root->left->key;
            root->left->key = root->key;
            root->key = temp;
        }
    }
    //check right if it isn't empty and right vs. centre
    if(root->right != NULL && root->right->key < root->key){
        int temp = root->right->key;
        root->right->key = root->key;
        root->key = temp;
        root->right = balance(root->right);
    }

    return root;
}

//Queue System needed for insert

typedef struct Queue_node_struct
{
    BST_node *node_ptr;
    struct Queue_node_struct *next;
}Queue_node;

Queue_node* new_queue_node(BST_node* BST_node){
    Queue_node* new = (Queue_node *) calloc(1, sizeof(Queue_node));
    new->node_ptr = BST_node;
    new->next = NULL;
    return new; 
}

Queue_node* insert_node_queue(Queue_node* root, BST_node* new_BST_Node){

    if(root->next != NULL) root->next = insert_node_queue(root->next, new_BST_Node);
    else root->next = new_queue_node(new_BST_Node);

    return root;
}

Queue_node* delete_queue(Queue_node *root){
    if(root->next != NULL) root->next = delete_queue(root->next);
    free(root);
    return NULL;
}

//end of queue system


BST_node *insert_node(BST_node *root, BST_node *new_node){
    /**
     * @brief Insert a made node into the tree
     * 
     */
    /**
     * Plan:
     * - Width first search
     * - make a queue
     * - check for the first available space from left to right, visually speaking
     * */
    return root;
}