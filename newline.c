#include "newline.h"
void get_src(Nlfile* src, char* symbol);
Nlfile* set_dest(Nlfile* src, char* symbol);
file_type what_type(char* symbol);
void core(Nlfile* src, Nlfile* dest);
void error(int error_code);
int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        error(1);    
    }
    if (strcmp(argv[1], argv[3]) == 0)
    {
        return 0;
    }
    Nlfile* src = malloc(sizeof(Nlfile));
    src->file_path = strdup(argv[2]);
    get_src(src, argv[1]);
    Nlfile* dest = set_dest(src, argv[3]);
    core(src, dest);
    if (remove(src->file_path) != 0)
    {
        error(5);
    }
    if (rename(dest->file_path, src->file_path) != 0)
    {
        error(6);   
    }
    fclose(src->file);
    fclose(dest->file);
    free(src->file_path);
    free(src);
    free(dest->file_path);
    free(dest);
    return 0;
}
void get_src(Nlfile* src, char* symbol)
{
    src->file = fopen(src->file_path, "rb");
    if (!src->file)
    {
        error(2);
    }
    src->type = what_type(symbol);
}
Nlfile* set_dest(Nlfile* src, char* symbol)
{
    if (!src)
    {
        error(2);
    }
    Nlfile* dest = malloc(sizeof(Nlfile));
    int length = strlen(src->file_path);
    dest->file_path = malloc(length + 1 + 5);
    //1 +  5 ----- ".temp" (with '\0' in the end)
    memset(dest->file_path, '\0', length + 1 + 5);
    memcpy(dest->file_path, src->file_path, length);
    strcat(dest->file_path, ".temp");
    dest->file = fopen(dest->file_path, "wb");
    if (!dest->file)
    {
        error(4);
    }
    dest->type = what_type(symbol);
    return dest;
}
void core(Nlfile* src, Nlfile* dest)
{
    char CR = '\r';
    char LF = '\n';
    int buffer;
    while ((buffer = fgetc(src->file)) != EOF)
    {
        if (buffer == '\r')
        {
            if (dest->type == DOS_WIN)
            {
                fputc(CR, dest->file);
                fputc(LF, dest->file);
            }
            else if (dest->type == UNIX_LIKE)
            {
                fputc(LF, dest->file);
            }
            else if (dest->type == MAC_OS)
            {
                fputc(CR, dest->file);
            }
            if (src->type == DOS_WIN)
            {
                fgetc(src->file);
                //move forward to jump the LF
            }
        }
        else if (buffer == '\n')
        {
            //the condition that the DOS/WIN meet has been jumped.
            if (dest->type == DOS_WIN)
            {
                fputc(CR, dest->file);
                fputc(LF, dest->file);
            }
            else if (dest->type == UNIX_LIKE)
            {
                fputc(LF, dest->file);
            }
            else if (dest->type == MAC_OS)
            {
                fputc(CR, dest->file);
            }
        }
        else
        {
            fputc(buffer, dest->file); //not a newline
        }
    }
}
file_type what_type(char* symbol)
{
    if (strcmp(symbol, "-d") == 0)
    {
        return DOS_WIN;
    }
    else if (strcmp(symbol, "-u") == 0)
    {
        return UNIX_LIKE;
    }
    else if (strcmp(symbol, "-m") == 0)
    {
        return MAC_OS;
    }
    else
    {
        error(3);
    }
    return UNIX_LIKE; //for no warning.
}
void error(int error_code) //catch error
{
    printf("Error: ");
    switch (error_code)
    {
        case 1:
            printf("Invalid Input.\n");
            printf("Use: newline -(type) (sourcefile) -(type)\n");
            printf("-d Dos/Win.\n-u Unix-Like.\n-m Classic Mac-OS");
            break;
        case 2:
            printf("Cannot open source file");
            break;
        case 3:
            printf("Invalid type parameter");
            break;
        case 4:
            printf("Cannot create output file");
            break;
        case 5:
            printf("Cannot delete input file");
            break;
        case 6:
            printf("Cannot rename output file, but the file has been created yet, please check the path to find .temp output file.");
            break;
        default:
            printf("Unknown Error.");
            break;
    }
    printf(".\n");
    exit(error_code);
}
