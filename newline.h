#ifndef __NEWLINE__
#define __NEWLINE__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef enum file_type
{
    DOS_WIN = 0,
    UNIX_LIKE = 1,
    MAC_OS = 2
}file_type;
typedef struct newline_file
{
    FILE* file;
    char* file_path;
    file_type type;
}Nlfile;
#endif
