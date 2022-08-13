//gonna copy a lot of code from the BST Assignment from CSCA48

#include<string.h>
#include"Balanced-BST.c"

int main()
{
    BST_node *root = NULL;
    int choice = -1;

    while (choice != 6){
        printf("Please select from among the following options:\n");
        printf("0 - Insert new note\n");
        printf("1 - Search for note\n");
        printf("2 - Delete note\n");
        printf("3 - Print notes in order\n");
        printf("4 - Print notes in pre-order\n");
        printf("5 - Print notes in post-order\n");
        printf("6 - Delete BST and exit\n");

        scanf("%d",&choice); //input proccessing
        getchar();// deal with  \n
        
        if(choice == 1){
            int value = 0;
            scanf("Value of the node: %d", &value);
            getchar();
            if(root != NULL){
                search_for(root, value);
            }
            else{
                printf("error, no tree created, yet. \n");
            }
        }
        else{
            printf("Command does not exist. \n");
        }
    }
}
