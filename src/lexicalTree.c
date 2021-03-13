/**
 * \file lexicalTree.c
 * \author Ramaroson Rakotomihamina Johan && Li Christine
 * 
 * File containing the functions node allocation and add word functions 
 *
 */


#include "lexicalTree.h"

/**
 * \fn Tree allocate_node(char letter)
 * \brief Allocate a node of the tree 
 *
 * \param letter char to insert.
 * \return The allocated node with the letter inserted
 */
Tree allocate_node(char letter){
    Tree tmp;

    tmp = (Tree)malloc(sizeof(Node));

    if(!tmp){           
        fprintf(stderr, "Erreur lors de l'allocation");
        exit(1);
    } 

    tmp->letter = letter;

    tmp->child = NULL;
    tmp->leftSibling = NULL;
    tmp->rightSibling = NULL;

    return tmp;

}

/**
 * \fn void free_all_tree(Tree *t)
 * \brief Parse and free each node of the tree.
 *
 * \param t Tree* 
 * \return 
 */
void free_all_tree(Tree *t){
    Tree tmp = *t;

    if(!tmp){
        return;
    }

    /* First we parse the entire tree (left, child, right), then we free the memory allocated. 
        this way, it will free the tree from the bottom to the top */
    if((*t)->leftSibling) free_all_tree(&tmp->leftSibling);
    if((*t)->child) free_all_tree(&tmp->child);
    if((*t)->rightSibling) free_all_tree(&tmp->rightSibling);
    
    free(tmp);
}

/**
 * \fn static int add_word_bis(Tree *t, char word[512], int i)
 * \brief Auxiliaire function, add a word into the tree given as argument
 *
 * \param t Tree * where the word is added.
 * \param word char[] word to add in the tree.
 * \param i int index of the word which represent the character to add.
 * \return int : 1 if addition went well, 0 if not
 */
static int add_word_aux(Tree *t, char word[512], int i){ 
    Tree tmp; /*  */ 
    
    if(!(*t)){
        *t = allocate_node(word[i]);
    }

    tmp = *t;

    /* if word[i] is '\0', the word is added correctly in the tree (return 1) */
    if(word[i] == '\0'){
        return 1;
    }

    
    /* First we check if the letter to add is equals to the current node's letter (*t->letter), this case means we can continue to add the word by parsing the child */
    
    if(tmp->letter == word[i]){
        return add_word_aux(&(*t)->child, word, i+1);
    }

    /* Second we check if the letter is > or < to the current node's letter. 
    Depending of the comparaison, we goes to the left or right side of the tree */
    if(word[i] > tmp->letter || tmp->letter == '\0'){
        return add_word_aux(&(*t)->rightSibling, word, i);
    }

    if(word[i] < tmp->letter){
        return add_word_aux(&(*t)->leftSibling, word, i);
    }
    
    return 0;
}

/**
 * \fn int add_word(Tree *t, char word[MAX_LENGTH])
 * \brief Add the word in the given Tree
 *
 * \param t Tree * where the word is added.
 * \param word char[] to insert in the tree.
 * \return int : 1 if addition went well, 0 if not
 */
int add_word(Tree *t, char word[MAX_LENGTH]){
    /* We call the auxiliary function by putting the index to 0 */
    return add_word_aux(&(*t), word, 0);
}
