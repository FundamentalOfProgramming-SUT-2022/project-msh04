#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

void createfile(char tag[], char fileaddress[])
{
    int i = 0;
    char dir_name[100];
    int check = 0;
    int dir_name_length;
    dir_name_length = 0;
    char c;
    c = fileaddress[0];
    while(c != '\0')
    {
        if(c == '/' && check == 0)
        {
            check = 1;
        }
        else if(c == '/' && check == 1)
        {
            for(int j = 0; j < dir_name_length; j++)
            {
                dir_name[j] = fileaddress[j];
            }
            dir_name[dir_name_length] = '\0';
            mkdir(dir_name);
        }
        i++;
        c = fileaddress[i];
        dir_name_length++;
    }
    if(strcmp(tag, "--file"))
    {
        printf("%s", tag);
        printf("invalid command");
    }
    else
    {
        FILE* filename;
        if(!fopen(fileaddress, "r") == 0)
        {
            printf("a file with this name already exist");
        }
        else
        {
            filename = fopen(fileaddress, "w");
            fclose(filename);
        }
    }
}

void cat(char tag[], char fileaddress[])
{
    char c;
    if(strcmp(tag, "--file"))
    {
        printf("invalid command");
    }
    else
    {
        FILE* fptr;
        fptr = fopen(fileaddress, "r");
        c = fgetc(fptr);
        while(c != EOF)
        {
            printf("%c", c);
            c = fgetc(fptr);
        }
        fclose(fileaddress);
    }
}


int main()
{
    char command[100];
    scanf("%s", command);
    char c;
    char tag[100];
    char passage[100];
    int start_pos, line_pos;
    char fileaddress[100];
    int i;

    if(!strcmp(command, "createfile"))
    {
        i = 0;
        scanf("%s", tag);
        getchar();
        c = getchar();
        while(c != '"' && c != '\n')
        {
            fileaddress[i] = c;
            i++;
            c = getchar();
        }
        if(c == '"')
        {
            c = getchar();
            while(c != '"')
            {
                fileaddress[i] = c;
                i++;
                c = getchar();
            }
        }
        fileaddress[i] = '\0';
        createfile(tag, fileaddress);
    }

    if(!strcmp(command, "cat"))
    {
        i = 0;
        scanf("%s", tag);
        getchar();
        c = getchar();
        while(c != '"' && c != '\n')
        {
            fileaddress[i] = c;
            i++;
            c = getchar();
        }
        if(c == '"')
        {
            c = getchar();
            while(c != '"')
            {
                fileaddress[i] = c;
                i++;
                c = getchar();
            }
        }
        fileaddress[i] = '\0';
        cat(tag, fileaddress);
    }
    return 0;
}
