# Movie-streaming-platform
-This project is a simple C program that manages movie genres and subgenres using a tree structure. Users can add, view, search, update, and delete genres through a menu-based system. The tree structure helps organize data in a clear parent–child format, making it easy to understand relationships between genres.

# Problem statement

In a movie streaming platform, movies are organized into genres and subgenres (for example: Action → Thriller → Spy). Managing this hierarchical data using simple lists is difficult and inefficient.

This project solves the problem by using a Tree Data Structure to store and manage genres. It allows users to perform operations like adding, viewing, searching, updating, and deleting genres in an organized way.

# Data structure used

This project uses a Tree Data Structure (Child-Sibling Representation).

Structure:

Each node represents a genre or subgenre.

Child pointer → points to the first subgenre.

Sibling pointer → points to the next genre/subgenre at the same level.

Why this structure?

Efficient for hierarchical data.

Easy to add and delete nodes.

Saves memory compared to multi-child trees.

# Algorithm explanation

1. Create Node
   
Allocate memory using malloc().

Store the genre name.

Initialize child and sibling as NULL.

2. Add Genre (Root Level)
   
If tree is empty → create root node.

Otherwise → traverse sibling nodes and insert at the end.

3. Add Subgenre
   
Search for the parent genre.

If found:

If no child → add as first child.

Else → add as last sibling of child nodes.

4. Display Tree
   
Use recursion.

Print current node with indentation.

Recursively display:

Child (next level).

Sibling (same level)

5. Search Node
   
Traverse the tree recursively.

Maintain a path string.

If node is found → print full path.

6. Update Node
   
Search for the node.

Replace old name with new name.

7. Delete Node
   
Locate the node.

Remove it from parent.

Delete entire subtree using recursion (deleteTree()).

8.Reset Tree

Delete all nodes using deleteTree().

Set root to NULL.

# Compilation instructions

Requirements:

1. Install the C/C++ extension.


2. Install MinGW or any C compiler.

C compiler(GCC recommended).

Steps to Compile and Run:

1.Save the file as:

project1.c.

2.Open terminal / command prompt

3.Compile the program:

gcc project1.c -o project1

4.Run the program:

./project1
./project1
Sample output:
