#ifndef __LEXICALTREE__H__
#define __LEXICALTREE__H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 512

typedef struct lexicalTree{
    
    char letter;
    
    struct lexicalTree *leftSibling;
    struct lexicalTree *rightSibling;
    struct lexicalTree *child;

}Node, *Tree;

/**
 * Allocate a node of the tree 
 * \param letter : char to insert in the node.
 * \return : the allocated node with the letter inserted
 */
Tree allocate_node(char letter);


/**
 * Free the memory allocated by a tree  
 * \param t : Tree to free the memory allocated.
 * \return : A pointer to a tree  
 */ 
void free_all_tree(Tree *t);

/**
 * Add the word in the given Tree.
 * \param t : pointer to the tree to update.
 * \param word : char[] to insert into the given tree.
 * \return : int 1 if the addition went well, 0 if not. 
 */
int add_word(Tree *t, char word[512]);


#endif