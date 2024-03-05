/*
Group Number - 10
ID:	2021A7PS1463P			Name: Dhyey Italiya
ID:	2021A7PS2434P			Name: LAKSHIT SETHI
ID:	2021A7PS0523P			Name: Abir Abhyankar
ID:	2021A7PS2414P			Name: Saksham Verma
ID:	2021A7PS2412P			Name: Saurabh Bhandari
*/

#include "utils.h"


bool append_endline(char *file_name)
{
    // open the file in read mode, if the last character is not a newline character, open the file in append mode and append a newline character
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL)
    {
        cyan("File not found\n");
        return 0;
    }
    fseek(fp, -1, SEEK_END);
    char ch;
    fread(&ch, 1, 1, fp);
    if (ch != '\n')
    {
        fclose(fp);
        fp = fopen(file_name, "a");
        fprintf(fp, "\n");
        fclose(fp);
    }
    else
    {
        fclose(fp);
    }
    return 1;
}