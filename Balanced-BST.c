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