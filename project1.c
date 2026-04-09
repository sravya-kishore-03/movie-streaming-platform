#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char name[50];
    struct Node* child;
    struct Node* sibling;
} Node;

// Create node
Node* createNode(char name[]) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

// Add child (subgenre)
void addChild(Node* parent, char name[]) {
    Node* newNode = createNode(name);

    if (parent->child == NULL) {
        parent->child = newNode;
    } else {
        Node* temp = parent->child;
        while (temp->sibling != NULL)
            temp = temp->sibling;
        temp->sibling = newNode;
    }
}

// Search node
Node* search(Node* root, char name[]) {
    if (root == NULL) return NULL;

    if (strcmp(root->name, name) == 0)
        return root;

    Node* found = search(root->child, name);
    if (found) return found;

    return search(root->sibling, name);
}

// Display tree
void displayTree(Node* root, int level) {
    if (root == NULL) return;

    for (int i = 0; i < level; i++)
        printf("    ");

    printf("( %s )\n", root->name);

    if (root->child != NULL) {
        for (int i = 0; i < level; i++)
            printf("    ");
        printf("   |\n");

        for (int i = 0; i < level; i++)
            printf("    ");
        printf("   v\n");

        displayTree(root->child, level + 1);
    }

    displayTree(root->sibling, level);
}

// Update node
void update(Node* root, char oldName[], char newName[]) {
    Node* node = search(root, oldName);
    if (node)
        strcpy(node->name, newName);
    else
        printf("Node not found!\n");
}

// Delete node
void deleteNode(Node* parent, char name[]) {
    if (parent == NULL || parent->child == NULL) return;

    Node* temp = parent->child;
    Node* prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            if (prev == NULL)
                parent->child = temp->sibling;
            else
                prev->sibling = temp->sibling;

            free(temp);
            printf("Deleted successfully\n");
            return;
        }
        prev = temp;
        temp = temp->sibling;
    }

    printf("Node not found!\n");
}

// Free memory
void freeTree(Node* root) {
    if (root == NULL) return;

    freeTree(root->child);
    freeTree(root->sibling);
    free(root);
}

// MAIN
int main() {
    Node* root = NULL;
    int choice;
    char name[50], parent[50], newName[50];

    while (1) {
        printf("\n===== Movie Streaming Platform =====\n");
        printf("1. Add Genre\n");
        printf("2. Add Subgenre\n");
        printf("3. Update Node\n");
        printf("4. Delete Node\n");
        printf("5. Search\n");
        printf("6. Display\n");
        printf("7. Reset Tree\n");
        printf("8. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

        // ✅ FIXED PART
        case 1:
            printf("Enter Genre name: ");
            scanf("%s", name);

            Node* newGenre = createNode(name);

            if (root == NULL) {
                root = newGenre;
            } else {
                Node* temp = root;
                while (temp->sibling != NULL)
                    temp = temp->sibling;
                temp->sibling = newGenre;
            }
            break;

        case 2:
            if (root == NULL) {
                printf("Add Genre first!\n");
                break;
            }
            printf("Enter parent name: ");
            scanf("%s", parent);

            Node* p = search(root, parent);
            if (p == NULL) {
                printf("Parent not found!\n");
                break;
            }

            printf("Enter subgenre name: ");
            scanf("%s", name);
            addChild(p, name);
            break;

        case 3:
            printf("Enter old name: ");
            scanf("%s", name);
            printf("Enter new name: ");
            scanf("%s", newName);
            update(root, name, newName);
            break;

        case 4:
            printf("Enter parent name: ");
            scanf("%s", parent);
            printf("Enter node to delete: ");
            scanf("%s", name);

            Node* par = search(root, parent);
            if (par)
                deleteNode(par, name);
            else
                printf("Parent not found!\n");
            break;

        case 5:
            printf("Enter name to search: ");
            scanf("%s", name);
            if (search(root, name))
                printf("Found!\n");
            else
                printf("Not Found!\n");
            break;

        case 6:
            printf("\n--- Genre Tree ---\n\n");
            displayTree(root, 0);
            break;

        case 7:
            freeTree(root);
            root = NULL;
            printf("Tree reset done\n");
            break;

        case 8:
            printf("Exited!\n");
            exit(0);

        default:
            printf("Invalid choice\n");
        }
    }
}
