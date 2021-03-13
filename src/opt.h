#ifndef __OPT__H__
#define __OPT__H__
#include "save.h"
#include "parsing.h"
#include "gui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

/**
 * Management of all options
 * \param argc : number of arguments called by the user.
 * \param argv : arguments used by the user.
 */
void opt(int argc, char * argv[]);


#endif