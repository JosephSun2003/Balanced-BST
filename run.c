//gonna copy a lot of code from the BST Assignment from CSCA48

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"Balanced-BST.c"

int main()
{
    BST_node *root = NULL;
    int choice = -1;

    while (choice != 6){
        printf("Please select from among the following options:\n");
        printf("0 - Insert new node\n");
        printf("1 - Search for node\n");
        printf("2 - Delete node\n");
        printf("3 - Print nodes in order\n");
        printf("4 - Print nodes in pre-order\n");
        printf("5 - Print nodes in post-order\n");
        printf("6 - Delete BST and exit\n");

        scanf("%d", &choice); //input proccessing
        getchar();
        
        if (choice == 0){
            int key = 0;
            printf("Value of the new node: \n");
            scanf("%d", &key);
            root = insert_node(root, new_BST_Node(key));
        }
        else if(choice == 1){
            int value = 0;
            printf("Value of the node: \n");
            scanf("%d", &value);
            getchar();
            if(root != NULL){ //if the root exists (AKA a tree exists)
                BST_node* found_node = search_for(root, value);
                if(found_node == NULL) printf("Node not found. \n"); //if the node is non-existent
                else{
                    printf("Node found!\n");
                    printf("Node key: %d\n", found_node->key);
                }
            }
            else{
                printf("error, no tree created, yet. \n");
            }
        }
        else if (choice == 2){
            int desired_key = 0;
            printf("Value of the desired key: \n");
            scanf("%d", &desired_key);
            getchar();
            if(root == NULL) printf("Tree does not exist. \n");
            else root = delete_BST_node(root, desired_key);
        }
        else if (choice == 3) print_BST_in_order(root, 1);
        else if (choice == 4) print_BST_pre_order(root, 1);
        else if (choice == 5) print_BST_post_order(root, 1);
        else if (choice == 6){

            if(root != NULL) root = delete_BST(root);
            printf("BST Deleted. \n");

        }
        else{
            printf("Command not recognised. \n");
        }
    }

    return 0; //main finished
}
