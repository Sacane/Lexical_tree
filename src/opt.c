/**
 * \file opt.c
 * \author Ramaroson Rakotomihamina Johan && Li Christine
 * File containing functions which manage the options in the command line. 
 */

#include "opt.h"



/**
 * \fn static void opt_l(int argc, char * argv[], int optind)
 * \brief Manage the program when the user enter "-l" as argument, display the component in the stdout of the file given as argument
 *  schema : ./Lexique -l <nameFile>
 * \param argc int
 * \param argv char *[]
 * \param optind int
 */
static void opt_l(int argc, char * argv[], int optind){

    Tree t = NULL;

    FILE* in;

    
    in = fopen(argv[optind], "r");
    t = fill_saved(argv[optind]);

    parse_and_print_in_file(t, stdout);

    
    free_all_tree(&t);
    fclose(in);
}

/**
 * schema : ./Lexique -d <nameFile> <file.dot> 
 */
static void opt_d(int argc, char *argv[], int optind){
    Tree tree = NULL;

    tree = fill_saved(argv[2]);
    create_pdf(argv[3], "visualise.pdf", tree);
    printf("dot : %s\n", argv[3]);
	free_all_tree(&tree);
}

/**
 * \fn static void opt_s(int argc, char* argv[], int optind)
 * \brief Manage the program when the user enter "-s" as argument:
  - read the file given as argument and create a new one which contains the words by the lexical order.
  - The file created has the same name of the file given but with the extension ".LEX"
 * schema : ./Lexique -s <nameFile>
 *
 * \param argc int
 * \param argv char*[]
 * \param optind int
 */
static void opt_s(int argc, char* argv[], int optind){

    char* name_formatted = NULL;
    Tree t = NULL;
    FILE *out;

    name_formatted = (char*)malloc(strlen(argv[optind])+1);
    strcpy(name_formatted, argv[optind]);                       
    replace_extension(name_formatted, ".LEX");
    
    out = fopen(name_formatted, "w");
    t = fill_saved(argv[optind]);

    parse_and_print_in_file(t, out);

    free_all_tree(&t);
    fclose(out);
    free(name_formatted);

}


/**
 * \fn static void opt_r(int argc, char* argv[], int optind)
 * \brief Manage the program when the user enter "-r" as argument:
 -  read the file given as argument and check if it contains the specified word.
 -  schema : ./Lexique -r <Word> <name_file>
 *
 * \param argc 
 * \param argv 
 * \param optind
 */
static void opt_r(int argc, char* argv[], int optind){

    Tree t = NULL;
    

    if(argc < 4 || argc > 4){
        fprintf(stderr, "invalid Number of arguments\n");
        exit(1);
    }

    t = fill_saved(argv[optind+1]);
    test_check_word(t, argv[optind]);

    free_all_tree(&t);

}

/**
 * \fn static void opt_S(int argc, char* argv[], int optind)
 * \brief Manage the program when the user enter "-S" as argument : read the file given as argument and encode it to another file with the same name but with the extension ".DIC"
 * schema : ./Lexique -S <nameFile>
 *
 * \param argc int, number of argument.
 * \param argv char*[]
 * \param optind int
 */
static void opt_S(int argc, char* argv[], int optind){
    char* name_formatted = NULL;
    Tree t = NULL;
    FILE *in;
    FILE *out;

    name_formatted = (char*)malloc(strlen(argv[optind])+1);
    strcpy(name_formatted, argv[optind]);
    replace_extension(name_formatted, ".DIC");

    in = fopen(argv[optind], "r");
    out = fopen(name_formatted, "w");

    if(!in || !out){
        fprintf(stderr, "Error while opening files\n");
        exit(1);
    }

    fill(in, &t);  
    encode(out, t);


    free(name_formatted);
    free_all_tree(&t);
    fclose(in);
    fclose(out);
}


/**
 * \fn void opt_help()
 * \brief display in the stdout a notice of all the options possible.
 * \return void
 * 
 */ 
static void opt_help(){
    printf("\n");
    printf("================= HELP =================\n\n");
    printf("You can execute this program with or without option specified :\n\n");
    printf("-l <filename> : display on the stdout all the words of the file according to their lexical order.\n");
    printf("-S <filename> : build a tree according the file given as argument and save it into a file 'filname.DIC'.\n");
    printf("-s <filename> : save the words of the file given as argument in lexical order into the file 'filename.L'.\n");
    printf("-r <Word> <filename> : check if the word is present in the file given as argument.\n\n");
    printf("-d <filename> <file.dot>");
    printf("If you don't specify any argument, you can open a menu that will drive you into the options.\n");
    printf("\n");
}


/**
 * \fn void opt(int argc, char * argv[])
 * \brief Management of all options
 *
 * \param argc int
 * \param argv char *[]
 */
void opt(int argc, char * argv[]) {
    const char * optstring = ":hi:S::l::r::s::d::";

    int val;

    while (EOF != (val = getopt(argc,argv,optstring))) {
        switch (val) {
            case 'h':
                opt_help(); break;
            case 'S':   
                opt_S(argc, argv, optind); break;
            case 'l':
                opt_l(argc, argv, optind); break;
            case 'r':
                opt_r(argc, argv, optind); break;
            case 's':
                opt_s(argc, argv, optind);break;
            case 'd':
                opt_d(argc, argv, optind); break;
            case ':':
                printf("arg missing for option %c\n",optopt); break;
            case '?':
                printf("unknown option %c\n",optopt); break;
            default:
                printf("default : unknown option %c\n",optopt); break;
        }
    }
}