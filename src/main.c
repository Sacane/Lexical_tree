/**
 * \file main.c
 * \author Ramaroson Rakotomihamina Johan && Li Christine
 * Main program
 *
 */

#include "opt.h"
#include "menu.h"




int main(int argc, char *argv[])
{   
    if(argc >= 2){
        opt(argc, argv);
    }

    if(argc < 2){
        menu(argc);
    }

    return 0;
}
