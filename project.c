#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAX_SIZE 10000

void tedad_curly_brackets(char str[], int bra[], int ket[])
{
    int j = 0;
    for(int i = 0; i < strlen(str); i++)
    {
        ket[i] = -1;
    }
    ket[strlen(str)] = '\0';
    for(int i = 0; i < strlen(str); i++)
    {
        if(str[i] == '{')
        {
            bra[j] = i;
            j++;
        }
        if(str[i] == '}')
        {
            for(int k = j-1; k >= 0; k--)
            {
                if(ket[k] == -1)
                {
                    ket[k] = i;
                    break;
                }
            }
        }
    }
    bra[j] = -1;
    ket[j] = -1;
}

void space_remover(char str[], char jaygozin[], int bra[], int ket[])
{
    int count = 0;
    int i = 0;
    int temp = 0;
    int aghabgard = 0;
    int x, y;
    while(str[i] != '\0')
    {
        x = search(i, bra);
        y = search(i, ket);
        if(str[i] == '{' && ket[x] != -1)
        {
            int counting = 0;
            aghabgard = temp-1;
            while(jaygozin[aghabgard] == ' ' && aghabgard != -1)
            {
                aghabgard--;
                counting++;
            }
            if(aghabgard != -1)
            {
                if(str[i-counting] != '{' && str[i-counting] != '}' )
                {
                    aghabgard++;
                    jaygozin[aghabgard] = ' ';
                }
                if(str[i-1] == '}')
                {
                    y = search(i-1, ket);
                    if(y == -1)
                    {
                        aghabgard++;
                        jaygozin[aghabgard] = ' ';
                    }
                }
            }
            aghabgard++;
            jaygozin[aghabgard] = '{';
            aghabgard++;
            temp = aghabgard;
            i++;
            x = search(i, bra);
            while(str[i] == ' ')
            {
                i++;
                x = search(i, bra);
            }
            if(str[i] == '{')
            {
                continue;
            }
            jaygozin[temp] = str[i];
            i++;
            temp++;
            continue;
        }
        else if(str[i] == '}' && y != -1)
        {
            aghabgard = temp-1;
            while(jaygozin[aghabgard] == ' ' && aghabgard != -1)
            {
                aghabgard--;
            }
            aghabgard++;
            jaygozin[aghabgard] = '}';
            temp = ++aghabgard;
            i++;
            while(str[i] == ' ')
            {
                i++;
            }
            if(str[i] == '{')
            {
                    continue;
            }
            jaygozin[temp] = str[i];
            temp++;
            i++;
            continue;
        }
        else
        {
            jaygozin[temp] = str[i];
            i++;
            temp++;
        }
    }
    jaygozin[temp] = '\0';
}

int search(int a, int array[])
{
    int i = 0;
    while(array[i] != -1)
    {
        if(array[i] == a)
        {
            return i;
        }
        i++;
    }
    return -1;
}

void convert_to_indent(char str[], char jaygozin[], int ket[], int bra[])
{
    int i = 0;
    int check = 0;
    int x;
    int temp = 0;
    int tmp = 0;
    int count = 0;
    while(str[i] != '\0')
    {
        if(str[i] == '{')
        {
            jaygozin[temp] = '{';
            temp++;
            if(ket[search(i, bra)] != -1)
            {
                jaygozin[temp] = '\n';
                temp++;
            }
        }
        else if(str[i] == '}')
        {
            x = search(i, ket);
            if(x != -1)
            {
                x = search(i-1, ket);
                if(str[i-1] != '{' && search(i-1, ket) == -1)
                {
                    jaygozin[temp] = '\n';
                    temp++;
                }
                jaygozin[temp] = '}';
                temp++;
                jaygozin[temp] = '\n';
                temp++;
            }
            else
            {
                jaygozin[temp] = '}';
                temp++;
            }
        }
        else
        {
            jaygozin[temp] = str[i];
            temp++;
        }
        i++;
    }
    jaygozin[temp] = '\0';
}


void put_tab(char str[], char jaygozin[])
{
    int i = 0;
    int count = 0;
    int tmp, temp = 0;
    while(str[i] != '\0')
    {
        jaygozin[temp] = str[i];
        temp++;
        if(str[i] == '\n')
        {
            if(str[i-1] == '{')
            {
                if(str[i+1] != '}')
                {
                    count++;
                    tmp = count;
                    while(tmp > 0)
                    {
                        jaygozin[temp] = '\t';
                        temp++;
                        tmp--;
                    }
                }
                else
                {
                    tmp = count;
                    while(tmp > 0)
                    {
                        jaygozin[temp] = '\t';
                        temp++;
                        tmp--;
                    }
                }

            }
            else if(str[i-1] == '}')
            {
                if(str[i+1] == '}')
                {
                    if(count > 0)
                    {
                        count--;
                    }
                    tmp = count;
                    while (tmp > 0)
                    {
                        jaygozin[temp] = '\t';
                        temp++;
                        tmp--;
                    }
                }
                else
                {
                    tmp = count;
                    while (tmp > 0)
                    {
                        jaygozin[temp] = '\t';
                        temp++;
                        tmp--;
                    }
                }
            }
            else
            {
                if(str[i+1] == '}')
                {
                    if(count > 0)
                    {
                        count--;
                    }
                    tmp = count;
                    while (tmp > 0)
                    {
                        jaygozin[temp] = '\t';
                        temp++;
                        tmp--;
                    }
                }
                else
                {
                    tmp = count;
                    while (tmp > 0)
                    {
                        jaygozin[temp] = '\t';
                        temp++;
                        tmp--;
                    }
                }
            }
        }
        i++;
    }
    if(jaygozin[temp-1] == '\n')
    {
        jaygozin[temp-1] = '\0';
    }
    else
    {
        jaygozin[temp] = '\0';
    }
}

int line_number(FILE* filename, char fileaddress[])
{
    int count = 0;
    char c;
    filename = fopen(fileaddress, "r");
    c = fgetc(filename);
    while(c != EOF)
    {
        if(c == '\n')
        {
            count++;
        }
        c = fgetc(filename);
    }
    count++;
    fclose(filename);
    return count;
}

int str_find(char str[], char substr[])
{
    int j;
    int i = 0;
    int check = 0;
    if(strlen(str) < strlen(substr))
    {
        return 0;
    }
    while(i <= strlen(str)-strlen(substr))
    {
        j = 0;
        while(j < strlen(substr))
        {
            if(substr[j] != str[i+j])
            {
                break;
            }
            else
            {
                j++;
            }
        }
        if(j == strlen(substr))
        {
            check = 1;
            return check;
        }
        i++;
    }
    return check;
}

int find_count(FILE* filename, char fileaddress[], char passage[], int output)
{
    long long int count, khoruji, check;
    char c;
    int i = 0;
    khoruji = 0;
    count = 0;
    int counter = 0;
    long long int remember = 0;
    filename = fopen(fileaddress, "r");
    c = fgetc(filename);
    while(c != EOF)
    {
        check = 0;
        i = 0;
        if(c == ' ' || c == '\0' || c == EOF)
        {
            remember = count+1;
        }
        if(c == passage[0])
        {
            khoruji = count;
            while(c == passage[i])
            {
                c = fgetc(filename);
                count++;
                i++;
                if(passage[i] == '\0')
                {
                    check = 1;
                    break;
                }
                if(c == EOF)
                {
                    check = 1;
                    break;
                    khoruji = -1;
                }
            }
        }
        else
        {
            c = fgetc(filename);
            count++;
        }
        if(output == 1 && check == 1)
        {
            if(c == ' ' || c == EOF || c == '\0')
            {
                khoruji = -1;
                check = 0;
            }
            else
            {
                if(khoruji != -1)
                {
                    counter++;
                }
            }
        }
        if(check == 1 && output == 0)
        {
            if(khoruji != -1)
            {
                counter++;
            }
        }
        if(output == -1 && check == 1)
        {
            if(remember == khoruji)
            {
                khoruji = -1;
                check = 0;
            }
            else
            {
                if(khoruji != -1)
                {
                    counter++;
                }
            }
        }
    }
    if(check == 0 && khoruji == -1)
    {
        counter--;
    }
    fclose(filename);
    return counter;
}


int byword(FILE* filename, char fileaddress[], int input)
{
    filename = fopen(fileaddress, "r");
    int i = 0;
    char c;
    int ret = 0;
    int check = 0;
    c = fgetc(filename);
    i++;
    while(i <= input)
    {
        while(c == ' ')
        {
            if(i > input)
            {
                break;
                check = 1;
            }
            c = fgetc(filename);
            i++;
        }
        if(check == 1)
        {
            break;
        }
        ret++;
        if(i > input)
        {
            break;
        }
        while(c != ' ')
        {
            c = fgetc(filename);
            i++;
            if(i > input)
            {
                break;
            }
        }
    }
    fclose(filename);
    if(input == 0)
    {
        return 1;
    }
    else
    {
        return ret;
    }
}


int find(FILE* filename, char fileaddress[], char passage[], int output, int counter)
{
    long long int count, khoruji, check;
    char c;
    int i = 0;
    count = 0;
    int ret = 0;
    long long int remember = 0;
    filename = fopen(fileaddress, "r");
    int check_counter = counter;
    while(counter >= 1)
    {
        c = fgetc(filename);
        if(check_counter != counter)
        {
            count++;
        }
        check = 0;
        khoruji = -1;
        while(c != EOF)
        {
            i = 0;
            if(c == ' ' || c == '\0' || c == EOF)
            {
                remember = count+1;
            }
            if(c == passage[0])
            {
                khoruji = count;
                while(c == passage[i])
                {
                    c = fgetc(filename);
                    count++;
                    i++;
                    if(passage[i] == '\0')
                    {
                        check = 1;
                        break;
                    }
                    if(c == EOF)
                    {
                        check = 1;
                        khoruji = -1;
                        break;
                    }
                }
            }
            else
            {
                c = fgetc(filename);
                count++;
            }
            if(output == 1 && check == 1)
            {
                if(c == ' ' || c == EOF || c == '\0')
                {
                    khoruji = -1;
                    check = 0;
                }
                else
                {
                    if(counter == 1)
                    {
                        fclose(filename);
                        return khoruji;
                    }
                    break;
                }
            }
            if(check == 1 && output == 0)
            {
                if(counter == 1)
                {
                    fclose(filename);
                    return khoruji;
                }
                break;
            }
            if(output == -1 && check == 1)
            {
                if(remember == khoruji)
                {
                    khoruji = -1;
                    check = 0;
                }
                else
                {
                    if(counter == 1)
                    {
                        fclose(filename);
                        return remember;
                    }
                    break;
                }

            }
        }
        if(check == 0 && counter == 1)
        {
            fclose(filename);
            return -1;
        }
        counter--;
    }
}


int replace(FILE* filename, char fileaddress[], char passage[], int output, int counter, int* func_output)
{
    long long int count, khoruji, check;
    char c;
    int i = 0;
    count = 0;
    int last_index;
    int ret = 0;
    long long int remember = 0;
    filename = fopen(fileaddress, "r");
    int check_counter = counter;
    while(counter >= 1)
    {
        c = fgetc(filename);
        if(check_counter != counter)
        {
            count++;
        }
        check = 0;
        khoruji = -1;
        while(c != EOF)
        {
            i = 0;
            if(c == ' ' || c == '\0' || c == EOF)
            {
                remember = count+1;
            }
            if(c == passage[0])
            {
                khoruji = count;
                while(c == passage[i])
                {
                    c = fgetc(filename);
                    count++;
                    i++;
                    if(passage[i] == '\0')
                    {
                        check = 1;
                        break;
                    }
                    if(c == EOF)
                    {
                        check = 1;
                        khoruji = -1;
                        break;
                    }
                }
            }
            else
            {
                c = fgetc(filename);
                count++;
            }
            if(output == 1 && check == 1)
            {
                if(c == ' ' || c == EOF || c == '\0')
                {
                    khoruji = -1;
                    check = 0;
                }
                else
                {
                    if(counter == 1 && khoruji != -1)
                    {
                        while(c != EOF && c != ' ')
                        {
                            c = fgetc(filename);
                            count++;
                        }
                        last_index = count-1;
                        *func_output = last_index;
                        fclose(filename);
                        return khoruji;
                    }
                    break;
                }
            }
            if(check == 1 && output == 0)
            {
                if(counter == 1)
                {
                    fclose(filename);
                    last_index = count-1;
                    *func_output = last_index;
                    return khoruji;
                }
                break;
            }
            if(output == -1 && check == 1)
            {
                if(remember == khoruji)
                {
                    khoruji = -1;
                    check = 0;
                }
                else
                {
                    if(counter == 1)
                    {
                        fclose(filename);
                        last_index = count-1;
                        *func_output = last_index;
                        return remember;
                    }
                    break;
                }
            }
        }
        if(check == 0 && counter == 1)
        {
            fclose(filename);
            return -1;
        }
        counter--;
    }
}


int vorud(char fileaddress[])
{
    int i = 0;
    char c;
    c = getchar();
    while(c != '\n' && c != '"' && c != ' ')
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
        c = getchar();
    }
    fileaddress[i] = '\0';
    if(c == '\n')
    {
        return 0;
    }
    if(c == ' ')
    {
        return 1;
    }
}


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
    char temp;
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
        if(c == '\\')
        {
            temp = getchar();
            if(temp == '"')
            {
                fileaddress[i] = temp;
                i++;
                c = getchar();
            }
            else
            {
                fileaddress[i] = c;
                i++;
                fileaddress[i] = temp;
                i++;
                c = getchar();
            }
        }
        else
        {
            fileaddress[i] = c;
            i++;
            c = getchar();
        }
    }
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

int space_wildcard(char fileaddress[])
{
    int output = 0;
    int i = 0;
    char c;
    char temp;
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
        if(c == '\\')
        {
            temp = getchar();
            if(temp == '*')
            {
                fileaddress[i] = temp;
                i++;
                c = getchar();
            }
            else if(temp == '"')
            {
                fileaddress[i] = temp;
                i++;
                c = getchar();
            }
            else
            {
                fileaddress[i] = c;
                i++;
                fileaddress[i] = temp;
                i++;
                c = getchar();
            }
        }
        else if(c == '*')
        {
            if(i == 0)
            {
                output = -1;
                c = getchar();
            }
            else
            {
                output = 1;
                c = getchar();
            }
        }
        else
        {
            fileaddress[i] = c;
            i++;
            c = getchar();
        }
    }
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
                else if(temp == '*')
                {
                    fileaddress[i] = temp;
                    i++;
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
            else if(c == '*')
            {
                if(i == 0)
                {
                    output = -1;
                }
                else
                {
                    output = 1;
                }
            }
            else
            {
                c =getchar();
                break;
            }
        }
    }
    fileaddress[i] = '\0';
    return output;
}


int createfile(char tag[], char fileaddress[])
{
    int i = 0;
    char dir_name[MAX_SIZE];
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
        printf("invalid command\n");
        return 0;
    }
    else
    {
        FILE* filename;
        if(!fopen(fileaddress, "r") == 0)
        {
            printf("a file with this name already exist\n");
            return 0;
        }
        else
        {
            filename = fopen(fileaddress, "w");
            fclose(filename);
            return 1;
        }
    }
}

void createfile_undo(char fileaddress[])
{
    int i = 0;
    char dir_name[MAX_SIZE];
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


void cat(char tag[], char fileaddress[])
{
    char c;
    if(strcmp(tag, "--file"))
    {
        printf("invalid command\n");
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
        printf("\n");
        fclose(fptr);
    }
}

void create_undo(char fileaddress[], char ufileaddress[])
{
    char c;
    int i = 0;
    while(fileaddress[i] != '/')
    {
        i++;
    }
    int j = 4;
    ufileaddress[0] = 'u';
    ufileaddress[1] = 'n';
    ufileaddress[2] = 'd';
    ufileaddress[3] = 'o';
    while(fileaddress[i] != '\0')
    {
        ufileaddress[j] = fileaddress[i];
        i++;
        j++;
    }
    ufileaddress[j] = '\0';
}

void copy(FILE* x, FILE* y)
{
    char c;
    c = fgetc(x);
    while(c != EOF)
    {
        fputc(c, y);
        c = fgetc(x);
    }
}

void copy_f(FILE* x, FILE* y, char fileaddress[], char str[], int line_pos, int start_pos, int size)
{
    char c;
    x = fopen(fileaddress, "r");
    y = fopen("clipboard.txt", "w");
    while(line_pos > 1)
    {
        line_pos--;
        fgets(str, MAX_SIZE, x);
    }
    while(start_pos > 0)
    {
        start_pos--;
        c = fgetc(x);
    }
    while(size > 0)
    {
        c = fgetc(x);
        fputc(c, y);
        size--;
    }
    fclose(y);
    fclose(x);
}

void copy_b(FILE* x, FILE* y, char fileaddress[], int line_pos, int start_pos, int size)
{
    char c;
    int count = 0, u;
    x = fopen(fileaddress, "r");
    y = fopen("clipboard.txt", "w");
    while(line_pos > 1)
    {
        line_pos--;
        c = fgetc(x);
        while(c != '\n')
        {
            count++;
            c = fgetc(x);
        }
        count++;
    }
    while(start_pos > 0)
    {
        start_pos--;
        c = fgetc(x);
        count++;
    }
    fclose(x);
    x = fopen(fileaddress, "r");
    u = count-size;
    while(u > 0)
    {
        c = fgetc(x);
        u--;
    }
    while(size > 0)
    {
        c = fgetc(x);
        fputc(c, y);
        size--;
    }
    fclose(y);
    fclose(x);
}

void insert(FILE* filename, FILE* copy, int line_pos, int start_pos, char passage[], char str[], char fileaddress[])
{
    char c;
    int i;
    filename = fopen(fileaddress, "r");
    copy = fopen("clipboard.txt", "w");
    while(line_pos > 1)
    {
        line_pos--;
        fgets(str, MAX_SIZE, filename);
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

void remove_f(FILE* filename, FILE* copy, int line_pos, int start_pos, char fileaddress[], char str[], int char_num)
{
    char c;
    filename = fopen(fileaddress, "r");
    copy = fopen("clipboard.txt", "w");
    while(line_pos > 1)
    {
        line_pos--;
        fgets(str, MAX_SIZE, filename);
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
void remove_b(FILE* filename, FILE* coping, char fileaddress[], int line_pos, int start_pos, int char_num)
{
    int count, x;
    char c;
    count = 0;
    filename = fopen(fileaddress, "r");
    coping = fopen("clipboard.txt", "w");
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
        fputc(c, coping);
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
        fputc(c, coping);
        c = fgetc(filename);
    }
    fclose(coping);
    fclose(filename);
    filename = fopen(fileaddress, "w");
    coping = fopen("clipboard.txt", "r");
    c = fgetc(coping);
    while(c != EOF)
    {
        fputc(c, filename);
        c = fgetc(coping);
    }
    fclose(coping);
    fclose(filename);
}

void tree(int depth, char address[], int remember)
{
    char temp[MAX_SIZE];
    int tab;
    int x;
    struct dirent *fd;
    DIR *dir = opendir(address);
    while((fd = readdir(dir)) != NULL)
    {
        if(!strcmp(fd->d_name, ".") || !strcmp(fd->d_name, ".."))
        {
            continue;
        }
        tab = remember - depth;
        while(tab > 0)
        {
            printf("\t");
            tab--;
        }
        if(depth != remember)
        {
            printf("|---");
        }
        printf("%s\n", fd->d_name);
        if(depth > 0)
        {
            strcpy(temp, address);
            strcat(temp, "/");
            strcat(temp, fd->d_name);
            tree(depth-1, temp, remember);
        }
        if(depth == -1)
        {
            strcpy(temp, address);
            strcat(temp, "/");
            strcat(temp, fd->d_name);
            tree(depth, temp, remember+1);
        }
    }
    closedir(dir);
}

void directory_show(char *fileaddress)
{
    struct dirent *fd;
    *fileaddress = strcat(*fileaddress, "./");
    DIR *dir = opendir(*fileaddress);
    while((fd = readdir(dir)) != NULL)
    {
        printf("%s", fd->d_name);
    }
    closedir(dir);
}


int main()
{
    char command[MAX_SIZE];
    scanf("%s", command);
    char c;
    char tag[MAX_SIZE];
    char tag_new[MAX_SIZE];
    char passage[MAX_SIZE];
    char passage_new[MAX_SIZE];
    int start_pos, line_pos;
    char fileaddress[MAX_SIZE];
    int i, x, count;
    int char_num;
    char str[MAX_SIZE];
    char comparing[MAX_SIZE];
    char str1[MAX_SIZE];
    char str2[MAX_SIZE];
    char c1, c2;
    char ufileaddress[MAX_SIZE];
    int check_command, check_exist;
    char jaygozin[MAX_SIZE];
    char str_zegond[MAX_SIZE];
    char str_prime[MAX_SIZE];
    int bra[MAX_SIZE];
    int ket[MAX_SIZE];
    char new_face[MAX_SIZE];

    while(1)
    {
        if(!strcmp(command, "exit"))
        {
            return 0;
        }
        if(!strcmp(command, "auto-indent"))
        {
            getchar();
            enter(fileaddress);
            create_undo(fileaddress, ufileaddress);
            FILE* filename;
            filename = fopen(fileaddress, "r");
            FILE* undo;
            undo = fopen(ufileaddress, "w");
            copy(filename, undo);
            fclose(filename);
            fclose(undo);
            FILE* helper;
            helper = fopen("help.txt", "w");
            filename = fopen(fileaddress, "r");
            c = fgetc(filename);
            int i = 0;
            while(c != EOF)
            {
                str[i] = c;
                i++;
                c = fgetc(filename);

            }
            str[i] = '\0';
            tedad_curly_brackets(str, bra, ket);
            space_remover(str, str_prime, bra, ket);
            tedad_curly_brackets(str_prime, bra, ket);
            convert_to_indent(str_prime, str_zegond, ket, bra);
            put_tab(str_zegond, new_face);
            fputs(new_face, helper);
            fclose(filename);
            fclose(helper);
            filename = fopen(fileaddress, "w");
            helper = fopen("help.txt", "r");
            copy(helper, filename);
            fclose(filename);
            fclose(helper);
        }
        if(!strcmp(command, "createfile"))
        {
            scanf("%s", tag);
            getchar();
            enter(fileaddress);
            create_undo(fileaddress, ufileaddress);
            int u;
            u = createfile(tag, fileaddress);
            if(u == 1)
            {
                createfile_undo(ufileaddress);
            }
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
            check_command = 0;
            check_exist = 0;
            scanf("%s", tag);
            if(strcmp(tag, "--file"))
            {
                check_command = 1;
            }
            getchar();
            space(fileaddress);
            scanf("%s", tag);
            if(strcmp(tag, "--pos"))
            {
                check_command = 1;
            }
            scanf("%d:%d ", &line_pos, &start_pos);
            scanf("%s", tag);
            if(strcmp(tag, "--size"))
            {
                check_command = 1;
            }
            scanf("%d ", &char_num);
            if(fopen(fileaddress, "r") == 0)
            {
                check_exist = 1;
            }
            FILE* filename;
            FILE* copy;
            scanf("%s", tag);
            if(strcmp(tag, "--f") && strcmp(tag, "--b"))
            {
                check_command = 1;
            }
            if(!strcmp(tag, "--f") && check_command == 0 && check_exist == 0)
            {
                copy_f(filename, copy, fileaddress, str, line_pos, start_pos, char_num);
            }
            else if(!strcmp(tag, "--b") && check_command == 0 && check_exist == 0)
            {
                copy_b(filename, copy, fileaddress, line_pos, start_pos, char_num);
            }
            else if(check_command == 1)
            {
                printf("invalid command\n");
            }
            else if(check_command == 0 && check_exist == 1)
            {
                printf("there isn't any file with this name\n");
            }
        }
        if(!strcmp(command, "insertstr"))
        {
            check_exist = 0;
            check_command = 0;
            scanf("%s", tag);
            if(strcmp(tag, "--file"))
            {
                check_command = 1;
            }
            getchar();
            space(fileaddress);
            create_undo(fileaddress, ufileaddress);
            FILE* filename;
            scanf("%s", tag);
            if(strcmp(tag, "--str"))
            {
                check_command = 1;
            }
            getchar();
            space(passage);
            scanf("%s", tag);
            if(strcmp(tag, "--pos"))
            {
                check_command = 1;
            }
            scanf("%d:%d", &line_pos, &start_pos);
            if(fopen(fileaddress, "r") == 0)
            {
                check_exist = 1;
            }
            if(check_exist == 0 && check_command == 0)
            {
                filename = fopen(fileaddress, "r");
                FILE* undo;
                undo = fopen(ufileaddress, "w");
                copy(filename, undo);
                fclose(filename);
                fclose(undo);
                FILE* copy;
                insert(filename, copy, line_pos, start_pos, passage, str, fileaddress);
            }
            else if(check_command == 1)
            {
                printf("invalid command\n");
            }
            else if(check_command == 0 && check_exist == 1)
            {
                printf("there isn't any file with this name\n");
            }
        }
        if(!strcmp(command, "removestr"))
        {
            check_command = 0;
            check_exist = 0;
            scanf("%s", tag);
            if(strcmp(tag, "--file"))
            {
                check_command = 1;
            }
            getchar();
            space(fileaddress);
            create_undo(fileaddress, ufileaddress);
            if(fopen(fileaddress, "r") == 0)
            {
                check_exist = 1;
            }
            FILE* filename;
            if(fopen(fileaddress, "r") == 0)
            {
                check_exist = 1;
            }
            scanf("%s", tag);
            if(strcmp(tag, "--pos"))
            {
                check_command = 1;
            }
            scanf("%d:%d ", &line_pos, &start_pos);
            scanf("%s", tag);
            if(strcmp(tag, "--size"))
            {
                check_command = 1;
            }
            scanf("%d ", &char_num);
            FILE* coping;
            scanf("%s", tag);
            if(strcmp(tag, "--f") && strcmp(tag, "--b"))
            {
                check_command = 1;
            }
            if(!strcmp(tag, "--f") && check_command == 0 && check_exist == 0)
            {
                filename = fopen(fileaddress, "r");
                FILE* undo;
                undo = fopen(ufileaddress, "w");
                copy(filename, undo);
                fclose(filename);
                fclose(undo);
                remove_f(filename, coping, line_pos, start_pos, fileaddress, str, char_num);
            }
            else if(!strcmp(tag, "--b") && check_command == 0 && check_exist == 0)
            {
                filename = fopen(fileaddress, "r");
                FILE* undo;
                undo = fopen(ufileaddress, "w");
                copy(filename, undo);
                fclose(filename);
                fclose(undo);
                remove_b(filename, coping, fileaddress, line_pos, start_pos, char_num);
            }
            else if(check_command == 1)
            {
                printf("invalid command\n");
            }
            else if(check_exist == 1 && check_command == 0)
            {
                printf("there isn't any file with this name\n");
            }
        }
        if(!strcmp(command, "cutstr"))
        {
            scanf("%s", tag);
            getchar();
            space(fileaddress);
            create_undo(fileaddress, ufileaddress);
            FILE* filename;
            filename = fopen(fileaddress, "r");
            FILE* undo;
            undo = fopen(ufileaddress, "w");
            copy(filename, undo);
            fclose(filename);
            fclose(undo);
            scanf("%s", tag);
            scanf("%d:%d ", &line_pos, &start_pos);
            scanf("%s", tag);
            scanf("%d ", &char_num);
            filename = fopen(fileaddress, "r");
            FILE* copy;
            FILE* help;
            scanf("%s", tag);
            if(!strcmp(tag, "--f"))
            {
                copy = fopen("clipboard.txt", "w");
                help = fopen("help.txt", "w");
                while(line_pos > 1)
                {
                    line_pos--;
                    fgets(str, MAX_SIZE, filename);
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
            else if(!strcmp(tag, "--b"))
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
            create_undo(fileaddress, ufileaddress);
            FILE* filename;
            filename = fopen(fileaddress, "r");
            FILE* undo;
            undo = fopen(ufileaddress, "w");
            copy(filename, undo);
            fclose(filename);
            fclose(undo);
            scanf("%s", tag);
            scanf("%d:%d", &line_pos, &start_pos);
            filename = fopen(fileaddress, "r");
            FILE* help;
            help = fopen("help.txt", "w");
            FILE* copy;
            copy = fopen("clipboard.txt", "r");
            while(line_pos > 1)
            {
                line_pos--;
                fgets(str, MAX_SIZE, filename);
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
        if(!strcmp(command, "find"))
        {
            int y;
            check_exist = 0;
            scanf("%s", tag);
            getchar();
            x = space_wildcard(passage);
            scanf("%s", tag);
            getchar();
            int counter;
            int java_b;
            FILE* filename;
            y = vorud(fileaddress);
            if(fopen(fileaddress, "r") == 0)
            {
                check_exist = 1;
                printf("there isn't any file with this address\n");
            }
            if(y == 0 && check_exist == 0)
            {
                java_b = find(filename, fileaddress, passage, x, 1);
                printf("%d\n", java_b);
            }
            if(y == 1 && check_exist == 0 )
            {
                scanf("%s", tag);
                if(!strcmp(tag, "-at"))
                {
                    getchar();
                    scanf("%d", &counter);
                    c = getchar();
                    java_b = find(filename, fileaddress, passage, x, counter);
                    if(c == ' ')
                    {
                        scanf("%s", tag_new);
                        if(!strcmp(tag_new, "-byword"))
                        {
                            java_b = byword(filename, fileaddress, java_b);
                            printf("%d\n", java_b);
                        }
                        else if(!strcmp(tag_new, "-all") || !strcmp(tag_new, "-count"))
                        {
                            printf("you can't use this attributes at a moment\n");
                        }
                    }
                    else
                    {
                            printf("%d\n", java_b);
                    }
                }
                if(!strcmp(tag, "-count"))
                {
                    c = getchar();
                    if(c == '\n')
                    {
                        java_b = find_count(filename, fileaddress, passage, x);
                        printf("%d\n", java_b);
                    }
                    if(c == ' ')
                    {
                        scanf("%s", tag_new);
                        if(!strcmp(tag_new, "-all") || !strcmp(tag_new, "-at"))
                        {
                            printf("you can't use this attributes at a moment\n");
                        }
                        else if(!strcmp(tag_new, "-byword"))
                        {
                            int z = find_count(filename, fileaddress, passage, x);
                            int i = 1;
                            int number = 0;
                            int remembering = 0;
                            while(z > i)
                            {
                                java_b = find(filename, fileaddress, passage, x, i);
                                java_b = byword(filename, fileaddress, java_b);
                                if(remembering != java_b)
                                {
                                    remembering = java_b;
                                    number++;
                                }
                                i++;
                            }
                            printf("%d\n", number);
                        }
                    }
                }
                if(!strcmp(tag, "-byword"))
                {
                    c = getchar();
                    if(c == '\n')
                    {
                        java_b = find(filename, fileaddress, passage, x, 1);
                        java_b = byword(filename, fileaddress, java_b);
                        printf("%d\n", java_b);
                    }
                    if(c == ' ')
                    {
                        scanf("%s", tag_new);
                        if(!strcmp(tag_new, "-all"))
                        {
                            int z = find_count(filename, fileaddress, passage, x);
                            int i = 1;
                            while(z > i)
                            {
                                java_b = find(filename, fileaddress, passage, x, i);
                                java_b = byword(filename, fileaddress, java_b);
                                printf("%d, ", java_b);
                                i++;
                            }
                            java_b = find(filename, fileaddress, passage, x, i);
                            java_b = byword(filename, fileaddress, java_b);
                            printf("%d\n", java_b);
                        }
                        if(!strcmp(tag_new, "-at"))
                        {
                            getchar();
                            scanf("%d", &counter);
                            java_b = find(filename, fileaddress, passage, x, counter);
                            java_b = byword(filename, fileaddress, java_b);
                            printf("%d\n", java_b);
                        }
                        if(!strcmp(tag_new, "-count"))
                        {
                            int z = find_count(filename, fileaddress, passage, x);
                            int i = 1;
                            int number = 0;
                            int remembering = 0;
                            while(z > i)
                            {
                                java_b = find(filename, fileaddress, passage, x, i);
                                java_b = byword(filename, fileaddress, java_b);
                                if(remembering != java_b)
                                {
                                    remembering = java_b;
                                    number++;
                                }
                                i++;
                            }
                            printf("%d\n", number);
                        }
                    }
                }
                if(!strcmp(tag, "-all"))
                {
                    c = getchar();
                    if(c == '\n')
                    {
                        int z = find_count(filename, fileaddress, passage, x);
                        int i = 1;
                        while(z > i)
                        {
                            java_b = find(filename, fileaddress, passage, x, i);
                            printf("%d, ", java_b);
                            i++;
                        }
                        java_b = find(filename, fileaddress, passage, x, i);
                        printf("%d\n", java_b);
                    }
                    if(c == ' ')
                    {
                        scanf("%s", tag);
                        if(!strcmp(tag, "-at") || !strcmp(tag, "-count"))
                        {
                            printf("you can't use this attributes at a moment\n");
                        }
                        else if(!strcmp(tag, "-byword"))
                        {
                            int z = find_count(filename, fileaddress, passage, x);
                            int i = 1;
                            while(z > i)
                            {
                                java_b = find(filename, fileaddress, passage, x, i);
                                java_b = byword(filename, fileaddress, java_b);
                                printf("%d, ", java_b);
                                i++;
                            }
                            java_b = find(filename, fileaddress, passage, x, i);
                            java_b = byword(filename, fileaddress, java_b);
                            printf("%d\n", java_b);
                        }
                    }
                }
            }
        }
        if(!strcmp(command, "compare"))
        {
            getchar();
            space(fileaddress);
            enter(comparing);
            FILE* filename;
            FILE* filecompare;
            filename = fopen(fileaddress, "r");
            filecompare = fopen(comparing, "r");
            c1 = fgetc(filename);
            c2 = fgetc(filecompare);
            int line_count1, line_count2;
            line_count1 = 0;
            line_count2 = 0;
            while(c1 != EOF)
            {
                if(c1 == '\n')
                {
                    line_count1++;
                }
                c1 = fgetc(filename);
            }
            line_count1++;
            while(c2 != EOF)
            {
                if(c2 == '\n')
                {
                    line_count2++;
                }
                c2 = fgetc(filecompare);
            }
            line_count2++;
            fclose(filename);
            filename = fopen(fileaddress, "r");
            fclose(filecompare);
            filecompare = fopen(comparing, "r");
            int counter1 = 1;
            int counter2 = 1;
            while(line_count2 >= counter2 && line_count1 >= counter2)
            {
                c1 = fgetc(filename);
                i = 0;
                while(c1 != '\n' && c1 != EOF)
                {
                    str1[i] = c1;
                    i++;
                    c1 = fgetc(filename);
                }
                str1[i] = '\0';
                c2 = fgetc(filecompare);
                i = 0;
                while(c2 != '\n' && c2 != EOF)
                {
                    str2[i] = c2;
                    i++;
                    c2 = fgetc(filecompare);
                }
                str2[i] = '\0';
                if(strcmp(str1, str2))
                {
                    printf("============#%d============\n", counter1);
                    printf("%s\n", str1);
                    printf("%s\n", str2);
                }
                counter1++;
                counter2++;
            }
            if(counter2 <= line_count2 && counter1 > line_count1)
            {
                printf(">>>>>>>>>>>>#%d - #%d>>>>>>>>>>>>\n", counter2, line_count2);
                while(counter2 <= line_count2)
                {
                    counter2++;
                    fgets(str2, MAX_SIZE, filecompare);
                    printf("%s", str2);
                }
                printf("\n");
            }
            if(counter1 <= line_count1 && counter2 > line_count2)
            {
                printf("<<<<<<<<<<<<#%d - #%d<<<<<<<<<<<<\n", counter1, line_count1);
                while(counter1 <= line_count1)
                {
                    counter1++;
                    fgets(str1, MAX_SIZE, filename);
                    printf("%s", str1);
                }
                printf("\n");
            }
            fclose(filename);
            fclose(filecompare);
        }
        if(!strcmp(command, "undo"))
        {
            scanf("%s", tag);
            getchar();
            enter(fileaddress);
            create_undo(fileaddress, ufileaddress);
            FILE* filename;
            FILE* help;
            help = fopen("undo.txt", "w");
            filename = fopen(fileaddress, "r");
            copy(filename, help);
            fclose(filename);
            fclose(help);
            filename = fopen(fileaddress, "w");
            FILE* undo;
            undo = fopen(ufileaddress, "r");
            copy(undo, filename);
            fclose(filename);
            fclose(undo);
            help = fopen("undo.txt", "r");
            undo = fopen(ufileaddress, "w");
            copy(help, undo);
            fclose(help);
            fclose(undo);
        }
        if(!strcmp(command, "grep"))
        {
            int count = 0;
            scanf("%s", tag);
            if(!strcmp(tag, "-c"))
            {
                scanf("%s", tag);
                getchar();
                space(passage);
                scanf("%s", tag);
                getchar();
                int khoruji;
                int x = vorud(fileaddress);
                while(x != 0)
                {
                    FILE* filename;
                    int tedad_lines = line_number(filename, fileaddress);
                    filename = fopen(fileaddress, "r");
                    while(tedad_lines > 0)
                    {
                        fgets(str, MAX_SIZE, filename);
                        khoruji = str_find(str ,passage);
                        if(khoruji == 1)
                        {
                            count++;
                        }
                        tedad_lines--;
                    }
                    fclose(filename);
                    x = vorud(fileaddress);
                }
                FILE* filename;
                int tedad_lines = line_number(filename, fileaddress);
                filename = fopen(fileaddress, "r");
                while(tedad_lines > 0)
                {
                    fgets(str, MAX_SIZE, filename);
                    khoruji = str_find(str ,passage);
                    if(khoruji == 1)
                    {
                        count++;
                    }
                    tedad_lines--;
                }
                fclose(filename);
                printf("%d\n", count);
            }
            else if(!strcmp(tag, "--str"))
            {
                getchar();
                space(passage);
                scanf("%s", tag);
                getchar();
                int khoruji;
                int x = vorud(fileaddress);
                while(x != 0)
                {
                    FILE* filename;
                    int shart = 0;
                    int tedad_lines = line_number(filename, fileaddress);
                    filename = fopen(fileaddress, "r");
                    while(tedad_lines > 0)
                    {
                        fgets(str, MAX_SIZE, filename);
                        khoruji = str_find(str ,passage);
                        if(khoruji == 1 && tedad_lines != 1)
                        {
                            printf("%s: %s", fileaddress, str);
                        }
                        if(khoruji == 1 && tedad_lines == 1)
                        {
                            printf("%s: %s\n", fileaddress, str);
                        }
                        tedad_lines--;
                    }
                    fclose(filename);
                    x = vorud(fileaddress);
                }
                FILE* filename;
                int tedad_lines = line_number(filename, fileaddress);
                filename = fopen(fileaddress, "r");
                while(tedad_lines > 0)
                {
                    fgets(str, MAX_SIZE, filename);
                    khoruji = str_find(str ,passage);
                    if(khoruji == 1)
                    {
                        printf("%s: %s\n", fileaddress, str);
                    }
                    tedad_lines--;
                }
                fclose(filename);
            }
            else if(!strcmp(tag, "-l"))
            {
                scanf("%s", tag);
                getchar();
                space(passage);
                scanf("%s", tag);
                getchar();
                int khoruji;
                int x = vorud(fileaddress);
                while(x != 0)
                {
                    FILE* filename;
                    int tedad_lines = line_number(filename, fileaddress);
                    filename = fopen(fileaddress, "r");
                    while(tedad_lines > 0)
                    {
                        fgets(str, MAX_SIZE, filename);
                        khoruji = str_find(str ,passage);
                        if(khoruji == 1 && tedad_lines != 1)
                        {
                            printf("%s\n", fileaddress);
                            break;
                        }
                        if(khoruji == 1 && tedad_lines == 1)
                        {
                            printf("%s\n", fileaddress);
                            break;
                        }
                        tedad_lines--;
                    }
                    fclose(filename);
                    x = vorud(fileaddress);
                }
                FILE* filename;
                int tedad_lines = line_number(filename, fileaddress);
                filename = fopen(fileaddress, "r");
                while(tedad_lines > 0)
                {
                    fgets(str, MAX_SIZE, filename);
                    khoruji = str_find(str ,passage);
                    if(khoruji == 1)
                    {
                        printf("%s\n", fileaddress);
                        break;
                    }
                    tedad_lines--;
                }
                fclose(filename);
            }
        }
        if(!strcmp(command, "tree"))
        {
            int depth;
            scanf("%d", &depth);
            if(depth < -1)
            {
                printf("invalid depth\n");
            }
            else
            {
                tree(depth, "./root", depth);
            }
        }
        if(!strcmp(command, "replace"))
        {
            scanf("%s", tag);
            getchar();
            x = space_wildcard(passage);
            scanf("%s", tag);
            getchar();
            space(passage_new);
            scanf("%s", tag);
            getchar();
            int counter;
            int y = vorud(fileaddress);
            create_undo(fileaddress, ufileaddress);
            FILE* filename;
            filename = fopen(fileaddress, "r");
            FILE* undo;
            undo = fopen(ufileaddress, "w");
            copy(filename, undo);
            fclose(filename);
            fclose(undo);
            FILE* helper;
            if(fopen(fileaddress, "r") == 0)
            {
                check_exist = 1;
                printf("there isn't any file with this address\n");
            }
            if(check_exist == 0 && y == 0)
            {
                int end_pos = 0;
                start_pos = replace(filename, fileaddress, passage, x, 1, &end_pos);
                counter = 0;
                filename = fopen(fileaddress, "r");
                helper = fopen("help.txt", "w");
                if(start_pos != -1)
                {
                    while(counter < start_pos)
                    {
                        c = fgetc(filename);
                        fputc(c, helper);
                        counter++;
                    }
                    while(counter <= end_pos)
                    {
                        c = fgetc(filename);
                        counter++;
                    }
                    fputs(passage_new, helper);
                    while(c != EOF)
                    {
                        c = fgetc(filename);
                        fputc(c, helper);
                    }
                    fclose(filename);
                    fclose(helper);
                    filename = fopen(fileaddress, "w");
                    helper = fopen("help.txt", "r");
                    copy(helper, filename);
                    fclose(filename);
                    fclose(helper);
                    printf("replacing was successfuly\n");
                }
                else
                {
                    printf("pattern not found :|\n");
                }
            }
            if(check_exist == 0 && y == 1)
            {
                scanf("%s", tag);
                if(!strcmp(tag, "-at"))
                {
                    c = getchar();
                    scanf("%d", &counter);
                    c = getchar();
                    if(c == ' ')
                    {
                        scanf("%s", tag);
                        if(!strcmp(tag, "-all"))
                        {
                            printf("you can't use this attributes at a moment\n");
                        }
                        else
                        {
                            printf("invalid command\n");
                        }
                    }
                    if(c == '\n')
                    {
                        int end_pos = 0;
                        start_pos = replace(filename, fileaddress, passage, x, counter, &end_pos);
                        counter = 0;
                        filename = fopen(fileaddress, "r");
                        helper = fopen("help.txt", "w");
                        if(start_pos != -1)
                        {
                            while(counter < start_pos)
                            {
                                c = fgetc(filename);
                                fputc(c, helper);
                                counter++;
                            }
                            while(counter <= end_pos)
                            {
                                c = fgetc(filename);
                                counter++;
                            }
                            fputs(passage_new, helper);
                            while(c != EOF)
                            {
                                c = fgetc(filename);
                                fputc(c, helper);
                            }
                            fclose(filename);
                            fclose(helper);
                            filename = fopen(fileaddress, "w");
                            helper = fopen("help.txt", "r");
                            copy(helper, filename);
                            fclose(filename);
                            fclose(helper);
                            printf("replacing was successfuly\n");
                        }
                        else
                        {
                            printf("pattern not found :|\n");
                        }
                    }
                }
                if(!strcmp("-all", tag))
                {
                    c = getchar();
                    if(c == ' ')
                    {
                        scanf("%s", tag);
                        if(!strcmp(tag, "-at"))
                        {
                            printf("you can't use this attributes at a moment\n");
                        }
                        else
                        {
                            printf("invalid command\n");
                        }
                    }
                    if(c == '\n')
                    {
                        int z = find_count(filename, fileaddress, passage, x);
                        while(z > 0)
                        {
                            int end_pos = 0;
                            start_pos = replace(filename, fileaddress, passage, x, z, &end_pos);
                            counter = 0;
                            if(start_pos != -1)
                            {
                                filename = fopen(fileaddress, "r");
                                helper = fopen("help.txt", "w");
                                while(counter < start_pos)
                                {
                                    c = fgetc(filename);
                                    fputc(c, helper);
                                    counter++;
                                }
                                while(counter <= end_pos)
                                {
                                    c = fgetc(filename);
                                    counter++;
                                }
                                fputs(passage_new, helper);
                                while(c != EOF)
                                {
                                    c = fgetc(filename);
                                    fputc(c, helper);
                                }
                                fclose(filename);
                                fclose(helper);
                                filename = fopen(fileaddress, "w");
                                helper = fopen("help.txt", "r");
                                copy(helper, filename);
                                fclose(filename);
                                fclose(helper);
                            }
                            z--;
                        }
                        printf("replacing was successfuly\n");
                    }
                }
            }
        }
        scanf("%s", command);
    }
    return 0;
}
