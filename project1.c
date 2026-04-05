#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for Genre / Subgenre Node
typedef struct Node {
    char name[50];
    struct Node *child;     // first subgenre
    struct Node *sibling;   // next genre/subgenre
} Node;

//Reset tree
void deleteTree(Node* root) {
    if (root == NULL) return;

    // delete child subtree
    deleteTree(root->child);

    // delete sibling subtree
    deleteTree(root->sibling);

    // free current node
    free(root);
}

// Function to create a new node (CREATE)
Node* createNode(char name[]) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL){
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(newNode->name, name);
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

// Add Genre (root level)
Node* addGenre(Node* root, char name[]) {
    Node* newNode = createNode(name);

    if (root == NULL) {
        return newNode;
    }

    Node* temp = root;
    while (temp->sibling != NULL) {
        temp = temp->sibling;
    }
    temp->sibling = newNode;

    return root;
}

// Add Subgenre under a Genre
void addSubgenre(Node* root, char parent[], char name[]) {
    if (root == NULL) return;

    if (strcmp(root->name, parent) == 0) {
        Node* newNode = createNode(name);

        if (root->child == NULL) {
            root->child = newNode;
        } else {
            Node* temp = root->child;
            while (temp->sibling != NULL) {
                temp = temp->sibling;
            }
            temp->sibling = newNode;
        }
        return;
    }

    addSubgenre(root->child, parent, name);
    addSubgenre(root->sibling, parent, name);
}

// Display Tree (READ)
void display(Node* root, int level) {
    if (root == NULL) return;

    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    printf("- %s\n", root->name);

    display(root->child, level + 1);
    display(root->sibling, level);
}

// Function to print node in round style
void printCircle(char name[]) {
    int len = strlen(name);

    // Top curve
    printf("   ");
    for (int i = 0; i < len + 2; i++) {
        printf("_");
    }
    printf("\n");

    // Middle (name)
    printf("  ( %s )\n", name);

    // Bottom curve
    printf("   ");
    for (int i = 0; i < len + 2; i++) {
        printf("-");
    }
    printf("\n");
}

// Main display function
void displayTree(Node* root, int level) {
    if (root == NULL) return;

    // Indentation
    for (int i = 0; i < level; i++) {
        printf("      ");
    }

    // Print current node
    printCircle(root->name);

    Node* child = root->child;

    while (child != NULL) {

        // Draw connection line
        for (int i = 0; i < level; i++) {
            printf("      ");
        }
        printf("     |\n");

        for (int i = 0; i < level; i++) {
            printf("      ");
        }
        printf("     v\n");

        // Recursive call
        displayTree(child, level + 1);

        child = child->sibling;
    }
}


// Search Node
Node* search(Node* root, char name[], char path[]) {
    if (root == NULL) return NULL;

    // Save current path
    char newPath[200];

    if (strlen(path) == 0)
        sprintf(newPath, "%s", root->name);
    else
        sprintf(newPath, "%s -> %s", path, root->name);

    // Check if found
    if (strcmp(root->name, name) == 0) {
        printf("Found at: %s\n", newPath);
        return root;
    }

    // Search in child
    Node* found = search(root->child, name, newPath);
    if (found != NULL) return found;

    // Search in sibling
    return search(root->sibling, name, path);
}

// Update Node (UPDATE)
void updateNode(Node* root, char oldName[], char newName[]) {
    char path[200]="";
    Node* node = search(root, oldName,path);

    if (node != NULL) {
        strcpy(node->name, newName);
        printf("Updated successfully!\n\n");
    } else {
        printf("Node not found!\n");
    }
}

// Delete Node (DELETE)
Node* deleteNode(Node* root, char name[]) {
    if (root == NULL) return NULL;

    // If root node itself matches
    if (strcmp(root->name, name) == 0) {
        deleteTree(root);
        printf("Deleted successfully!\n\n");
        return NULL;
    }

    Node* temp = root;


    // Check children
    Node* prev = NULL;
    Node* curr = root->child;

    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0) {
            if (prev == NULL) {
                root->child = curr->sibling;
            } else {
                prev->sibling = curr->sibling;
            }
            deleteTree(curr);
            printf("Deleted successfully!\n");
            return root;
        }
        prev = curr;
        curr = curr->sibling;
    }

    // Recursive delete
    root->child = deleteNode(root->child, name);
    root->sibling = deleteNode(root->sibling, name);

    return root;
}

// MAIN MENU
int main() {
    Node* root = NULL;
    int choice;
    char name[50], parent[50];

    while (1) {
        printf("\n\n===== Movie Streaming Platform =====\n");
        printf("1. Add Genre\n");
        printf("2. Add Subgenre\n");
        printf("3. Update Node\n");
        printf("4. Delete Node\n");
        printf("5. Search\n");
        printf("6. Display\n");
        printf("7.Reset tree\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {

        case 1:
            printf("Enter Genre name: ");
            scanf("%s", name);
            root = addGenre(root, name);
            break;

        case 2:
            printf("Enter Parent Genre: ");
            scanf("%s", parent);
            printf("Enter Subgenre name: ");
            scanf("%s", name);
            addSubgenre(root, parent, name);
            break;

        case 3:
            printf("Enter old name: ");
            scanf("%s", name);
            printf("Enter new name: ");
            scanf("%s", parent);
            updateNode(root, name, parent);
            break;

        case 4:
            printf("Enter name to delete: ");
            scanf("%s", name);
            root = deleteNode(root, name);
            break;

        case 5:
            printf("Enter name to search: ");
            scanf("%s", name);
            if (root == NULL){
                printf("Tree is empty\n");
                break;
            }
            char path[200]="";
            if (search(root, name,path)==NULL)
                printf("Not Found!\n");
            break;

        case 6:
            if(root == NULL){
                printf("tree is empty\n");
            }else{
            printf("\n--- Genre Tree ---\n\n");
            displayTree(root, 0);
            }
            break;

        case 7:
            deleteTree(root);
            root=NULL;
            printf("Tree reset successfully!\n");
            break;

        case 8:
            printf("Exiting...\n");
            exit(0);

        
        default:
            printf("Invalid choice!\n");
        }
    }
}