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
     * Assumption of duplicates
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
    BST_node* node_ptr;
    struct Queue_node_struct *next;
}Queue_node;

Queue_node* new_queue_node(BST_node* input_BST_node){
    Queue_node* new = (Queue_node *) calloc(1, sizeof(Queue_node));
    new->node_ptr = input_BST_node;
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

Queue_node* remove_queue_node(Queue_node *root){
    Queue_node *old = root;
    Queue_node* new = root->next;
    free(old);
    return new;
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
    Queue_node* head = new_queue_node(root);
    BST_node* current = root;
    while(current->right != NULL && current->left != NULL){
        head = insert_node_queue(head, current->left);
        head = insert_node_queue(head, current->right);
        head = remove_queue_node(head);
        current = head->node_ptr;
    }
    if(current->left == NULL){
        current->left = new_node;
    }
    else{
        current->right = new_node;
    }
    root = balance(root);

    return root;
}

BST_node* find_replacement(BST_node* root){
    /**
     * @brief find the replacement node (the left most node of the right subtree)
     */
    if(root->left != NULL) return find_replacement(root->left);
    return root;
}

BST_node* find_parent_node(BST_node* root, BST_node* child_node){
    /**
     * @brief find the parent node to the given child node
     * 
     */

    if(root->left == child_node || root->right == child_node) return root;
    else if(child_node->key > root->key) return find_parent_node(root->right, child_node);
    else if(child_node->key <= root->key) return find_parent_node(root->left, child_node);
    else retrun NULL;
}

BST_node* find_one_connection(BST_node* main_node){
    /**
     * @brief return which node is remaining, assumes one connection
     * 
     */

    if(main_node->left != NULL) return main_node->left;
    
    return main_node->right;
}

BST_node* delete_BST_node(BST_node* root, int key){
    /**
     * @brief Delete a node from the tree (possibly the first found duplicate)
     * Plan:
     * - case 1: leaf node delete (both are null)
     * - case 2: stick node delete (2.1: left null, 2.2: right null)
     * - case 3: root node delete (balance function will be called)
     * - check if node exists and its parent
     */

    //search section
    BST_node* to_be_deleted = search_for(root, key);
    BST_node* parent_node = NULL;
    if(root != to_be_deleted) parent_node = find_parent_node(root, to_be_deleted);
    //case 1:
    if(to_be_deleted->left == NULL && to_be_deleted->right == NULL){

        //unlink from tree
        if(parent_node != NULL && parent_node->right == to_be_deleted) parent_node->right = NULL;
        else if(parent_node != NULL) parent_node->left = NULL;
        else root = NULL;

        //deletion of itself
        free(to_be_deleted);
        to_be_deleted = NULL;
    }
    //case 2:
    else if (to_be_deleted->left == NULL || to_be_deleted->right == NULL){
        //unlink from tree
        if(parent_node != NULL && parent_node->right == to_be_deleted) {
            parent_node->right = find_one_connection(to_be_deleted);
        }
        else if(parent_node != NULL) {
            parent_node->right = find_one_connection(to_be_deleted);
        }
        else {
            root = find_one_connection(to_be_deleted);
        }

        //deletion of itself
        free(to_be_deleted);
        to_be_deleted = NULL;
    }
    //case 3:


    return root;
}

void print_node_in_order(BST_node* root, int level){
    if(root->left != NULL){
        print_node_in_order(root->left, level + 1);
    }
    printf("node: %d at level %d.", root->key , level);
    if(root->right != NULL){
        print_node_in_order(root->right, level + 1);
    }
}
void print_node_pre_order(BST_node* root, int level){
    printf("node: %d at level %d.", root->key , level);
    if(root->left != NULL){
        print_node_in_order(root->left, level + 1);
    }
    if(root->right != NULL){
        print_node_in_order(root->right, level + 1);
    }
}
void print_node_post_order(BST_node* root, int level){
    if(root->left != NULL){
        print_node_in_order(root->left, level + 1);
    }
    if(root->right != NULL){
        print_node_in_order(root->right, level + 1);
    }
    printf("node: %d at level %d.", root->key , level);
}