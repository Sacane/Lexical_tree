/**
 * \file parsing.c
 * \author Ramaroson Rakotomihamina Johan && Li Christine
 * File that manages the function which parse the tree.
 *
 */


#include "parsing.h"


/**
 * \fn static void print_child(Tree n, char buffer[MAX_LENGTH], int i, FILE *f)
 * \brief print the words of the tree in the file given as argument
 *
 * \param n Tree
 * \param buffer char[]
 * \param i int : index to insert in the buffer.
 * \param f FILE*
 */
static void print_child(Tree n, char buffer[MAX_LENGTH], int i, FILE *f)
{   

    if(!n)
    {
        return;
    }

    /* if the letter of the node is '\0' we add it into the buffer and print it */
    if(n->letter == '\0'){
        buffer[i] = '\0';
        fprintf(f, "%s\n", buffer);
    }

    /* Doing the prefix-parsing, if the index is > 0 and tree's left sibling exist, then parse it,
       add the letter into the buffer, parse the child and do the same thing for the right-sibling than the left-sibling. */


    if(n->leftSibling && i > 0){
        print_child(n->leftSibling, buffer, i, f);
    }

    buffer[i] = n->letter;

    print_child(n->child, buffer, i+1, f);

    if(n->rightSibling && i > 0){
        print_child(n->rightSibling, buffer, i, f);
    }
}


/**
 * \fn static int check_word_in_tree_aux(Tree t, char word[MAX_LENGTH], char buffer[MAX_LENGTH], int i)
 * \brief Auxiliary function that checks if a word is in the tree
 *
 * \param t Tree
 * \param word char[]
 * \param buffer char[] 
 * \param i int : Index of the buffer
 * \return int 1 if the word is in the tree, 0 if not.
 */
static int check_word_in_tree_aux(Tree t, char word[MAX_LENGTH], char buffer[MAX_LENGTH], int i){
    /* Stop condition */
    if(!t){
        return 0;
    }

    /** Algorithm : Prefix-parsing of the tree to check the words **/

    /* if we are in the end of the word, add it manually to prevent the errors */
    if(t->letter == '\0'){
        buffer[i] = '\0';
    }

    /* Positionning on the very left side of the tree without changing the index value */
    if(check_word_in_tree_aux(t->leftSibling, word, buffer, i)){
        return 1;
    }

    /* Main action : Using the buffer and insert the letter into it and keep parsing the tree*/
    buffer[i] = t->letter;

    /* goes down into the tree by iterating the index */
    if(check_word_in_tree_aux(t->child, word, buffer, i+1)){
        return 1;
    }
    /* After adding the tree and parsing the child, we check if the word inserted in the buffer is the given word */
    if(strcmp(buffer, word) == 0){
        return 1;
    }
    /* if there is a right-Sibling allocated left and the given word is still not found, parse it to check if the word given is in-there */
    if(check_word_in_tree_aux(t->rightSibling, word, buffer, i)){
        return 1;
    }

    /* the word isn't in the tree */
    return 0;
}



/**
 * \fn int check_word_in_tree(Tree t, char word[MAX_LENGTH])
 * \brief Checks if a word is in the tree given as parameter. 
 *
 * \param t Tree
 * \param word char[] word to check.
 * \return int 1 if the word is in the tree, 0 if not.
 */
int check_word_in_tree(Tree t, char word[MAX_LENGTH]){

    /* Buffer using to store the word and use "strcmp" function */
    char buffer[MAX_LENGTH];

    if(!t){
        return 0;
    }

    /* Use the auxiliary function to all the nodes of the tree */
    return (check_word_in_tree_aux(t->leftSibling, word, buffer, 0) || check_word_in_tree_aux(t, word, buffer, 0) || 
        check_word_in_tree_aux(t->rightSibling, word, buffer, 0));
}



/**
 * \fn void test_check_word(Tree t, char word[MAX_LENGTH])
 * \brief print in the stdout if the word is in the tree given as parameter.
 *
 * \param t A tree to parse
 * \param word char[]
 */
void test_check_word(Tree t, char word[MAX_LENGTH]){
    if(check_word_in_tree(t, word)){
        printf("The word '%s' is in the File\n", word);
    }
    else{
        printf("The word '%s' isn't in the File\n", word);
    }
}

/**
 * \fn void parse_and_print_in_file(Tree t, FILE *f)
 * \brief Parse the tree and print the words in the file given as argument
 *
 * \param t A Tree
 * \param f FILE*
 */
void parse_and_print_in_file(Tree t, FILE *f)
{   
    /* Use a buffer to store the word to print */
    char buffer[MAX_LENGTH];
    
    if(!t){
        return;
    }

    if(t->leftSibling){
        parse_and_print_in_file(t->leftSibling, f);
    }

    print_child(t, buffer, 0, f);

    if(t->rightSibling){
        parse_and_print_in_file(t->rightSibling, f);
    }

}


