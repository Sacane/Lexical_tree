/**
 * \file save.c
 * \author Ramaroson Rakotomihamina Johan && Li Christine
 * 
 * File containing the functions usefull to save a tree or its component in a file 
 *
 */

#include "save.h"


/**
 * \fn void check_error_file(FILE *f)
 * \brief Check if there is an error while opening the file
 *
 * \param f FILE *
 */
void check_error_file(FILE *f){
    if(!f){
        fprintf(stderr, "error while opening the file\n");
        exit(1);
    }
}

/**
 * \fn static void replace_extension(char* name_file, char* name_extension)
 * \brief Turns a character which has an extension to another extension
 *
 * \param name_file  char * name of the file.
 * \param name_extension char * name of the extension of the final name.
 */
void replace_extension(char* name_file, char* name_extension){

    char *pDot = strchr(name_file, '.');
    if(pDot){
        *pDot = '\0';
    }
    strcat(name_file, name_extension);
}

/**
 * \fn void encode(FILE *out, Tree t)
 * \brief Encodes a tree by displaying the letter according to the prefix order of the tree.
 * 
 *
 * \param out FILE *
 * \param t Tree
 */
void encode(FILE *out, Tree t){
    /* If the tree is null : put spaces character into the file */
    if(!t)
    {
        fprintf(out, "%c", ' ');
        return;
    }
    
    /* If the letter of the node is '\0', put the charactère '\n' in the file instead */

    if(t->letter == '\0')
    {
        fprintf(out, "%c", '\n');
        encode(out, t->rightSibling);
        return;
    }

    /* Elsewhere we put the letter of the node */

    fprintf(out, "%c", t->letter);
    
    /* Proceed by the prefix-parsing : check if leftSibling is allocated and encode it, same with the child and then the right sibling */
    /* If they are not allocated, put the spaces (' ') character instead*/

    if(t->leftSibling) 
        encode(out, t->leftSibling);
    else{
        fprintf(out, "%c", ' ');
    }
    if(t->child) 
    {
        encode(out, t->child);
    }
    else{
        fprintf(out, "%c", ' ');
    }
    
    if(t->rightSibling) 
    {
        encode(out, t->rightSibling);
    }
    else{
        fprintf(out, "%c", ' ');
    }
}

/**
 * \fn Tree decode(FILE *in)
 * \brief Decodes a file and fill the tree according to it.
 *
 * \param in FILE *
 * \return Tree filled by decoding the file given as argument.
 */
Tree decode(FILE *in){
    char get;
    Tree tmp = NULL;  

    /* Scan the file at his pointer's current position (the pointer will be incremented automatically after several 
        recursive calls of the function) */

    if(fscanf(in, "%c", &get) == EOF){
        return tmp;
    }

    /* There are several possibilities :  

        -If the scan read a spaces, return NULL (at this point, tmp == NULL) : 
            the encoding algorithms specifies to put a spacies when we find an no allocated node in the tree.

        -If the scan read '\n', put a '\0' in the node tmp to return. At this point, the node can't have a left Sibling because '\n' is the smallest
        character in the lexical order, it can't have a child either.

        -Elsewhere we can put the character into the current node and parse it as prefix-order. 
        
    */

    if(get == ' '){
        return tmp;
    }
    if(get == '\n'){
        tmp = allocate_node('\0');
        tmp->rightSibling = decode(in);
    }
    else{
        tmp = allocate_node(get);
        tmp->leftSibling = decode(in);
        tmp->child = decode(in);
        tmp->rightSibling = decode(in);
    }

    /* return the final node. */
    return tmp;
}

/**
 * \fn int fill(FILE *in, Tree *t)
 * \brief Fill the tree according to the file
 *
 * \param in FILE*
 * \param t Tree*
 * \return int 1 if the fill of the tree went well, 0 if not.
 */
int fill(FILE *in, Tree *t){

    char word[MAX_LENGTH];
    /* Fill the tree by adding the words of the file */
    while(fscanf(in, "%s", word) != EOF){
        if(!add_word(t, word)){
            return 0;
        }
    }
    return 1;
}

/**
 * \fn Tree fill_saved(char *name_file)
 * \brief If the file <name_file>.DIC exists, return a tree decoded by this file, otherwise return a Tree filled according to the file.
 * 
 *
 * \param char char* name of the file.
 * \return Tree filled by the file given as argument.
 */
Tree fill_saved(char *name_file){

    char *name_dic = NULL;
    Tree t = NULL;
    FILE *in;
    FILE *dic;

    name_dic = (char*)malloc(sizeof(char)*strlen(name_file)); 

    /****** ALWAYS CHECK IF THE ALLOCATION WENT WELL ******/
    if(!name_dic){
        fprintf(stderr, "Error of allocation\n");
        exit(1);
    }

    strcpy(name_dic, name_file);
    replace_extension(name_dic, ".DIC"); 

    dic = fopen(name_dic, "r");

    if(dic){ 
    
        printf("==========");
        printf("     Decoding of %s", name_dic);
        printf("     ==========\n");

        t = decode(dic);
        fclose(dic);
    }
    else{ 
        printf("==========");
        printf("     Treat of %s, .DIC doesn't exist yet.", name_file);
        printf("     ==========\n");
        in = fopen(name_file, "r");
        check_error_file(in);


        fill(in, &t); /* Fill the tree according to the given file */
        
        fclose(in);

    }
    
    free(name_dic);
    return t;
}

