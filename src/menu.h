#ifndef __MENU__H__
#define __MENU__H__
#include "save.h"
#include "parsing.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <getopt.h>


/**
 * Displays a menu if there is no option
 * \param argc
 */
void menu(int argc);

#endif