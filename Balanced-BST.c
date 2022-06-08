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
     * Assumption of now duplicates
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

BST_node *insert_node(BST_node *root, BST_node *new_node){
    /**
     * @brief Insert a made node into the tree
     * 
     */

    return root;
}