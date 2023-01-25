#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>


void enter(char fileaddress[])
{
    int i = 0;
    char c;
    c = getchar();
    while(c != '\n' && c != '"')
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
}

void space(char fileaddress[])
{
    int i = 0;
    char c;
    c = getchar();
    while(c != ' ')
    {
        if(c == '"')
        {
            if(i == 0)
            {
                break;
            }
        }
        fileaddress[i] = c;
        i++;
        c = getchar();
    }
    char temp;
    if(c == '"')
    {
        c = getchar();
        while(1)
        {
            if(c == '\\')
            {
                temp = getchar();
                if(temp == '"')
                {
                    fileaddress[i] = temp;
                    i++;
                    c = getchar();
                }
                else if(temp != '\\')
                {
                    fileaddress[i] = c;
                    fileaddress[i+1] = temp;
                    i += 2;
                    c = getchar();
                }
                else
                {
                    fileaddress[i] = c;
                    i++;
                    c = temp;
                }
            }
            else if(c != '"')
            {
                fileaddress[i] = c;
                i++;
                c = getchar();
            }
            else
            {
                c =getchar();
                break;
            }
        }
    }
    fileaddress[i] = '\0';
}

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
    if(strcmp(tag, "-file"))
    {
        printf("%s", tag);
        printf("invalid command");
    }
    else
    {
        FILE* filename;
        if(!fopen(fileaddress, "r") == 0)
        {
            printf("a file with this name already exist\n");
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
    if(strcmp(tag, "-file"))
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
    int i, x, count;
    int char_num;
    char str[100];

    while(1)
    {
        if(!strcmp(command, "exit"))
        {
            return 0;
        }
        if(!strcmp(command, "createfile"))
        {
            scanf("%s", tag);
            getchar();
            enter(fileaddress);
            createfile(tag, fileaddress);
        }

        if(!strcmp(command, "cat"))
        {
            scanf("%s", tag);
            getchar();
            enter(fileaddress);
            cat(tag, fileaddress);
        }

        if(!strcmp(command, "copystr"))
        {
            scanf("%s", tag);
            getchar();
            space(fileaddress);
            scanf("%s", tag);
            scanf("%d:%d ", &line_pos, &start_pos);
            scanf("%s", tag);
            scanf("%d ", &char_num);
            FILE* filename;
            filename = fopen(fileaddress, "r");
            FILE* copy;
            scanf("%s", tag);
            if(!strcmp(tag, "-f"))
            {
                copy = fopen("clipboard.txt", "w");
                while(line_pos > 1)
                {
                    line_pos--;
                    fgets(str, 100, filename);
                }
                while(start_pos > 0)
                {
                    start_pos--;
                    c = fgetc(filename);
                }
                while(char_num > 0)
                {
                    c = fgetc(filename);
                    fputc(c, copy);
                    char_num--;
                }
                fclose(copy);
                fclose(filename);
            }
            else if(!strcmp(tag, "-b"))
            {
                count = 0;
                copy = fopen("clipboard.txt", "w");
                while(line_pos > 1)
                {
                    line_pos--;
                    c = fgetc(filename);
                    while(c != '\n')
                    {
                        count++;
                        c = fgetc(filename);
                    }
                    count++;
                }
                while(start_pos > 0)
                {
                    start_pos--;
                    c = fgetc(filename);
                    count++;
                }
                fclose(filename);
                filename = fopen(fileaddress, "r");
                x = count-char_num;
                while(x > 0)
                {
                    c = fgetc(filename);
                    x--;
                }
                while(char_num > 0)
                {
                    c = fgetc(filename);
                    fputc(c, copy);
                    char_num--;
                }
                fclose(copy);
                fclose(filename);
            }
        }
        if(!strcmp(command, "insertstr"))
        {
            int check = 0;
            scanf("%s", tag);
            getchar();
            space(fileaddress);
            scanf("%s", tag);
            getchar();
            space(passage);
            scanf("%s", tag);
            scanf("%d:%d", &line_pos, &start_pos);
            FILE* filename;
            if(fopen(fileaddress, "r") == 0)
            {
                printf("there isn't any file with this name\n");
                check = 1;
            }
            if(check == 0)
            {
                filename = fopen(fileaddress, "r");
                FILE* copy;
                copy = fopen("clipboard.txt", "w");
                while(line_pos > 1)
                {
                    line_pos--;
                    fgets(str, 100, filename);
                    fputs(str, copy);
                }
                while(start_pos > 0)
                {
                    c = fgetc(filename);
                    fputc(c, copy);
                    start_pos--;
                }
                i = 0;
                c = passage[0];
                while(c != '\0')
                {
                    if(c == '\\' && (passage[i-1] != '\\'))
                    {
                        if(passage[i+1] == 'n')
                        {
                            fputc('\n', copy);
                            i += 2;
                        }
                        else
                        {
                            fputc(c, copy);
                            i++;
                        }
                    }
                    else
                    {
                        fputc(c, copy);
                        i++;
                    }
                    c = passage[i];
                }
                c = fgetc(filename);
                while(c != EOF)
                {
                    fputc(c, copy);
                    c = fgetc(filename);
                }
                fclose(copy);
                fclose(filename);
                filename = fopen(fileaddress, "w");
                copy = fopen("clipboard.txt", "r");
                c = fgetc(copy);
                while(c != EOF)
                {
                    fputc(c, filename);
                    c = fgetc(copy);
                }
                fclose(copy);
                fclose(filename);
            }
        }
        if(!strcmp(command, "removestr"))
        {
            scanf("%s", tag);
            getchar();
            space(fileaddress);
            scanf("%s", tag);
            scanf("%d:%d ", &line_pos, &start_pos);
            scanf("%s", tag);
            scanf("%d ", &char_num);
            FILE* filename;
            filename = fopen(fileaddress, "r");
            FILE* copy;
            scanf("%s", tag);
            if(!strcmp(tag, "-f"))
            {
                copy = fopen("clipboard.txt", "w");
                while(line_pos > 1)
                {
                    line_pos--;
                    fgets(str, 100, filename);
                    fputs(str, copy);
                }
                while(start_pos > 0)
                {
                    start_pos--;
                    c = fgetc(filename);
                    fputc(c, copy);
                }
                while(char_num > 0)
                {
                    c = fgetc(filename);
                    char_num--;
                }
                c = fgetc(filename);
                while(c != EOF)
                {
                    fputc(c, copy);
                    c = fgetc(filename);
                }
                fclose(copy);
                fclose(filename);
                filename = fopen(fileaddress, "w");
                copy = fopen("clipboard.txt", "r");
                c = fgetc(copy);
                while(c != EOF)
                {
                    fputc(c, filename);
                    c = fgetc(copy);
                }
                fclose(copy);
                fclose(filename);
            }
            else if(!strcmp(tag, "-b"))
            {
                count = 0;
                copy = fopen("clipboard.txt", "w");
                while(line_pos > 1)
                {
                    line_pos--;
                    c = fgetc(filename);
                    while(c != '\n')
                    {
                        count++;
                        c = fgetc(filename);
                    }
                    count++;
                }
                while(start_pos > 0)
                {
                    start_pos--;
                    c = fgetc(filename);
                    count++;
                }
                fclose(filename);
                filename = fopen(fileaddress, "r");
                x = count-char_num;
                while(x > 0)
                {
                    c = fgetc(filename);
                    fputc(c, copy);
                    x--;
                }
                while(char_num > 0)
                {
                    c = fgetc(filename);
                    char_num--;
                }
                c = fgetc(filename);
                while(c != EOF)
                {
                    fputc(c, copy);
                    c = fgetc(filename);
                }
                fclose(copy);
                fclose(filename);
                filename = fopen(fileaddress, "w");
                copy = fopen("clipboard.txt", "r");
                c = fgetc(copy);
                while(c != EOF)
                {
                    fputc(c, filename);
                    c = fgetc(copy);
                }
                fclose(copy);
                fclose(filename);
            }
        }
        if(!strcmp(command, "cutstr"))
        {
            scanf("%s", tag);
            getchar();
            space(fileaddress);
            scanf("%s", tag);
            scanf("%d:%d ", &line_pos, &start_pos);
            scanf("%s", tag);
            scanf("%d ", &char_num);
            FILE* filename;
            filename = fopen(fileaddress, "r");
            FILE* copy;
            FILE* help;
            scanf("%s", tag);
            if(!strcmp(tag, "-f"))
            {
                copy = fopen("clipboard.txt", "w");
                help = fopen("help.txt", "w");
                while(line_pos > 1)
                {
                    line_pos--;
                    fgets(str, 100, filename);
                    fputs(str, help);
                }
                while(start_pos > 0)
                {
                    start_pos--;
                    c = fgetc(filename);
                    fputc(c, help);
                }
                while(char_num > 0)
                {
                    c = fgetc(filename);
                    fputc(c, copy);
                    char_num--;
                }
                c = fgetc(filename);
                while(c != EOF)
                {
                    fputc(c, help);
                    c = fgetc(filename);
                }
                fclose(help);
                fclose(copy);
                fclose(filename);
                filename = fopen(fileaddress, "w");
                help = fopen("help.txt", "r");
                c = fgetc(help);
                while(c != EOF)
                {
                    fputc(c, filename);
                    c = fgetc(help);
                }
                fclose(help);
                fclose(filename);
            }
            else if(!strcmp(tag, "-b"))
            {
                count = 0;
                copy = fopen("clipboard.txt", "w");
                help = fopen("help.txt", "w");
                while(line_pos > 1)
                {
                    line_pos--;
                    c = fgetc(filename);
                    while(c != '\n')
                    {
                        count++;
                        c = fgetc(filename);
                    }
                    count++;
                }
                while(start_pos > 0)
                {
                    start_pos--;
                    c = fgetc(filename);
                    count++;
                }
                fclose(filename);
                filename = fopen(fileaddress, "r");
                x = count-char_num;
                while(x > 0)
                {
                    c = fgetc(filename);
                    fputc(c, help);
                    x--;
                }
                while(char_num > 0)
                {
                    c = fgetc(filename);
                    fputc(c, copy);
                    char_num--;
                }
                c = fgetc(filename);
                while(c != EOF)
                {
                    fputc(c, help);
                    c = fgetc(filename);
                }
                fclose(help);
                fclose(copy);
                fclose(filename);
                filename = fopen(fileaddress, "w");
                help = fopen("help.txt", "r");
                c = fgetc(help);
                while(c != EOF)
                {
                    fputc(c, filename);
                    c = fgetc(help);
                }
                fclose(filename);
                fclose(help);
            }
        }
        if(!strcmp(command, "pastestr"))
        {
            scanf("%s", tag);
            getchar();
            space(fileaddress);
            scanf("%s", tag);
            scanf("%d:%d", &line_pos, &start_pos);
            FILE* filename;
            filename = fopen(fileaddress, "r");
            FILE* help;
            help = fopen("help.txt", "w");
            FILE* copy;
            copy = fopen("clipboard.txt", "r");
            while(line_pos > 1)
            {
                line_pos--;
                fgets(str, 100, filename);
                fputs(str, help);
            }
            while(start_pos > 0)
            {
                c = fgetc(filename);
                fputc(c, help);
                start_pos--;
            }
            c = fgetc(copy);
            while(c != EOF)
            {
                fputc(c, help);
                c = fgetc(copy);
            }
            c = fgetc(filename);
            while(c != EOF)
            {
                fputc(c, help);
                c = fgetc(filename);
            }
            fclose(help);
            fclose(filename);
            fclose(copy);
            help = fopen("help.txt", "r");
            filename = fopen(fileaddress, "w");
            c = fgetc(help);
            while(c != EOF)
            {
                fputc(c, filename);
                c = fgetc(help);
            }
            fclose(filename);
            fclose(help);
        }
        scanf("%s", command);
    }
    return 0;
}
