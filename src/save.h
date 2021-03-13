#ifndef __SAVE__H__
#define __SAVE__H__


#include "lexicalTree.h"




/**
 * Encodes a tree out a file
 * \param in : FILE* where you want to encode the tree
 * \param t : Tree to encode in the file
 * \return : void
 */
void encode(FILE *out, Tree t);

/**
 * Decode the file in and create the Tree t
 * \param in : FILE* encoded to translate into a tree
 * \return : Builded tree after the decoding
 */
Tree decode(FILE *in);


/**
 * Fill the tree according to the file
 * \param in : A pointer on file
 * \param t : A tree
 * \return : int
 */
int fill(FILE *in, Tree *t);

/**
 * Check if there is an error opening the file
 * \param in : f A pointer to the file
 */
void check_error_file(FILE *f);

/**
 * Turns a character which has an extension to another extension
 * \param name_file : A pointer on the name of file that we want to change the extension
 * \param name_extension : A pointer on the name_file to turn in
 */
void replace_extension(char* name_file, char* name_extension);

/**
 * If the file <name_file>.DIC exists, return a tree decoded by this file, otherwise return a Tree filled according to the file.
 * \param char : A pointer on an array of character
 * \return : int
 */
Tree fill_saved(char *name_file);

#endif