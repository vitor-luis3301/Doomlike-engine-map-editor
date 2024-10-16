#ifndef FILEREAD_H
#define FILEREAD_H

/*

******************************************************************************
This is where we will read the `level.txt` file and interpret it's information
******************************************************************************

*/

#include <cstring>
#include <stdio.h>
#include <stdlib.h>

#include "globalvars.h"

class fileRead {
    public:
        fileRead() {}
        int init(char *filepath, char *filename);
        Global interpret();
};

#endif