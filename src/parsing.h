#ifndef __PARSING__H__
#define __PARSING__H__

#include "lexicalTree.h"



/**
 * Checks if a word is in the tree given as parameter. 
 * \param t : Tree to parse.
 * \param word : char[] to check.
 */
int check_word_in_tree(Tree t, char word[MAX_LENGTH]);


/**
 * Parse the tree and print the words in the file given as argument
 * \param t : Tree to parse.
 * \param f : FILE * to write in.
 * 
 */
void parse_and_print_in_file(Tree t, FILE *f);

/**
 * Print in the stdout if the word is in the tree given as parameter.
 * \param t : Tree to parse and check.
 * \param word : Word to check the belonging.
 */
void test_check_word(Tree t, char word[MAX_LENGTH]);



#endif

