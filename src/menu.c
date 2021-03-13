/**
 * \file menu.c
 * 
 * File containing the functions which manage the menu.
 * \author Ramaroson Rakotomihamina Johan && Li Christine
 */


#include "menu.h"


/**
 * \fn static void menu_l(char *name_file)
 * \brief Displays words from the file in lexical order
 *
 * \param name_file A pointer to a character
 */
static void menu_l(char *name_file){

    Tree t = NULL;

    t = fill_saved(name_file);
    
    parse_and_print_in_file(t, stdout);

    free_all_tree(&t);

}


/**
 * \fn static void menu_s(char *name_file)
 * \brief Displays words from the file in lexical order
 *
 * \param name_file A pointer to a character
 */
static void menu_s(char *name_file){
    


    FILE *out;
    char* name_formatted = NULL;
    Tree t = NULL;
    
    name_formatted = (char*)malloc(strlen(name_file)+1);
    strcpy(name_formatted, name_file);
    replace_extension(name_formatted, ".LEX");

    out = fopen(name_formatted, "w");
    check_error_file(out);
    t = fill_saved(name_file);

    parse_and_print_in_file(t, out);

    free_all_tree(&t);
    free(name_formatted);
    fclose(out);

}


/**
 * \fn static void menu_S(FILE *in, char *name_file)
 * \brief Function save the tree in file in lexical order
 *
 * \param in A pointer to the file  
 * \param name_file A pointer to a character
 */
static void menu_S(FILE *in, char *name_file){


    FILE *out;
    char* name_formatted = NULL;
    Tree t = NULL;

    in = fopen(name_file, "r");
    if(fill(in, &t) == 0)
        return;
    
    name_formatted = (char*)malloc(strlen(name_file)+1);
    strcpy(name_formatted, name_file);
    replace_extension(name_formatted, ".DIC");

    out = fopen(name_formatted, "w");
    check_error_file(out);
    encode(out, t);
    free_all_tree(&t);
    free(name_formatted);
    fclose(out);
    fclose(in);


}

/**
 * \fn static void menu_r(char *name_file)
 * \brief Displays words from the file in lexical order
 *
 * \param name_file A pointer to a character
 */
static void menu_r(char *name_file){
    
    Tree t = NULL; 
    char word[MAX_LENGTH];

    printf("Word to search : \n");
    scanf("%s", word);

    t = fill_saved(name_file);

    test_check_word(t, word);
    free_all_tree(&t);

}


/**
 * \fn void menun(int argc)
 * \brief Displays a menu in the shell if no option was given as argument.
 *
 * \param argc  
 */
void menu(int argc){

    int dump; /* To dump the buffer of the stdout */
    char a = '\0';
    char c = '\0';
    FILE *f = NULL;
    char * name_file = NULL;


    if (argc > 1)
        return;

    /* Launch of the program */
    
    do{
        printf("\n");
        printf("=========================================");
        printf("\n");
        printf("Open a file or quit the program ? (o/q)\n");
        printf("=========================================\n");
        printf("-> ");

        scanf("%c", &a);
        while ((dump = getchar() != '\n') && dump != EOF);
        if(a == 'q'){
            return;
        }
    }while(a != 'o');

    /* Select a file */

    name_file = (char *)malloc(sizeof(char)*MAX_LENGTH); 
    

    do{
        printf("-> Name of file : ");
        scanf("%s", name_file); 
        while ((dump = getchar() != '\n') && dump != EOF);
        f = fopen(name_file, "r");
    }while(!f);
    
    

    while(c != 'q'){
        printf("------------------------------------------\n");
        printf("Choose an option : \n");
        printf(" l : displays words from the file in lexical order\n");
        printf(" s : save words from file in lexical order\n");
        printf(" r : check if the word is in the file\n");
        printf(" S : save tree in file\n");
        printf(" a : open another file\n");
        printf(" q : Quit the program \n");
        printf("------------------------------------------\n");
        scanf("%c", &c);
        
        while ((dump = getchar() != '\n') && dump != EOF); /* Dump of the buffer */

        /* Choose an option depending of the selection*/
        
        switch (c)
        {
        case 'l':
            menu_l(name_file);
            break;
        case 's':
            menu_s(name_file);
            break;
        case 'S':
            menu_S(f, name_file);
            break;
        case 'r':
            menu_r(name_file);
            break;
        case 'a':
            menu(argc);
            break;
        default:
            break;
        }

        if(c == 'c'){
            break;
        }
    }


    fclose(f);
    
    free(name_file);
}