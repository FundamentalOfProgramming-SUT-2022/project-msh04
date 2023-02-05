#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "conio.c"
#include <unistd.h>

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

void move(int *x, int *y, char c, int *line_number, int tedad_kol, int str[])
{
    if(c == 'f')
    {
        *line_number = 1;
        *y = 1;
        *x = 7;
        gotoxy(*x, *y);
    }
    if(c == 'e')
    {
        *line_number = tedad_kol-27;
        *y = 28;
        *x = 6+str[tedad_kol-1];
        gotoxy(*x, *y);
    }
    if(c == 'h')
    {
        if(*x == 7)
        {
            gotoxy(*x, *y);
        }
        else
        {
            *x -= 1;
            gotoxy(*x, *y);
        }
    }
    if(c == 'j')
    {
        if((*x-6) > str[*line_number+*y-1] && (*line_number+*y) < tedad_kol)
        {
            *y += 1;
            *x = 6+str[*line_number+*y-2];
            gotoxy(*x, *y);
        }
        else if(*y == 24 && (*line_number+27) < tedad_kol)
        {
            *line_number += 1;
            gotoxy(*x, *y);
        }
        else if(*y == 28 && (*line_number+27) == tedad_kol)
        {
            gotoxy(*x, *y);
        }
        else
        {
            *y += 1;
            gotoxy(*x, *y);
        }
    }
    if(c == 'k')
    {
        if((*x-6) > str[*line_number+*y-3] && *y > 1)
        {
            *y -= 1;
            *x = 6+str[*line_number+*y-2];
            gotoxy(*x, *y);
        }
        else if(*y == 5 && *line_number >= 2)
        {
            *line_number -= 1;
            gotoxy(*x, *y);
        }
        else if(*y == 1 && *line_number == 1)
        {
            gotoxy(*x, *y);
        }
        else
        {
            *y -= 1;
            gotoxy(*x, *y);
        }
    }
    if(c == 'l')
    {
        if(str[*line_number+*y-2] == (*x-6))
        {
            gotoxy(*x, *y);
        }
        else
        {
            *x += 1;
            gotoxy(*x, *y);
        }
    }
}



void print_mode_border(char mode[])
{
    gotoxy(1, 29);
    int i = 0;
    cprintf(" ");
    while(mode[i] != '\0')
    {
        cprintf("%c", mode[i]);
        i++;
    }
    cprintf(" ");
}

void filename_bar(char filename[], int line_number)
{
    gotoxy(9, 29);
    int i = 0;
    while(filename[i] != '\0')
    {
        cprintf("%c", filename[i]);
        i++;
    }
}

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
                if(str[i-counting-1] != '{' && str[i-counting-1] != '}' )
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

void readfile(FILE* filename, char fileaddress[], int line_number, int tedad_kol)
{
    int line_counter = 0;
    char str[1000];
    filename = fopen(fileaddress, "r");
    int temp = line_number;
    while(temp > 1)
    {
        fgets(str, 1000, filename);
        temp--;
    }
    char c = fgetc(filename);
    cprintf("%4d  ", line_number);
    line_counter++;
    while(c != EOF)
    {
        if(c == '{' || c == '}')
        {
            textcolor(RED);
            cprintf("%c", c);
            textcolor(WHITE);
        }
        else if(c == '[' || c == ']')
        {
            textcolor(GREEN);
            cprintf("%c", c);
            textcolor(WHITE);
        }
        else if(c == '(' || c == ')')
        {
            textcolor(LIGHTBLUE);
            cprintf("%c", c);
            textcolor(WHITE);
        }
        else
        {
            cprintf("%c", c);
        }
        if(c == '\n')
        {
            printf("%4d  ", line_number+line_counter);
            line_counter++;
        }
        if(line_counter >= 29)
        {
            break;
        }
        c = fgetc(filename);
    }
    fclose(filename);
}

int tedad_line(FILE* filename, char fileaddress[])
{
    int tedad = 0;
    filename = fopen(fileaddress, "r");
    char c = fgetc(filename);
    while(c != EOF)
    {
        if(c == '\n')
        {
            tedad++;
        }
        c = fgetc(filename);
    }
    fclose(filename);
    tedad++;
    return tedad;
}

void vorud(char fileaddress[])
{
    char c;
    int i = 0;
    c = getchar();
    while(c != '\n')
    {
        fileaddress[i] = c;
        c = getchar();
        i++;
    }
    fileaddress[i] = '\0';
}

void vorud_open(char fileaddress[])
{
    char c;
    int i = 0;
    c = getchar();
    while(c != '\n')
    {
        fileaddress[i] = c;
        c = getchar();
        i++;
    }
    fileaddress[i] = '\0';
}

void backslash_n(FILE* filename, char fileaddress[], int str[])
{
    int j = 0;
    int count = 0;
    filename = fopen(fileaddress, "r");
    char c = fgetc(filename);
    while(c != EOF)
    {
        if(c == '\n')
        {
            str[j] = ++count;
            j++;
            count = 0;
        }
        else
        {
            count++;
        }
        c = fgetc(filename);
    }
    str[j] = count;
    fclose(filename);
}

void insert(FILE *filename, char fileaddress[], int line_num, int char_num)
{

}

int main()
{
    char c;
    char temp;
    int bra[1000];
    int ket[1000];
    char str1[10000];
    char str_prime[10000];
    char str_zegond[10000];
    char new_face[10000];
    char fileaddress[1000];
    FILE* filename;
    vorud(fileaddress);
    char command[1000];
    int flag = 0;
    while(fopen(fileaddress, "r") == 0)
    {
        if(!strcmp(fileaddress, "quit"))
        {
            return 0;           
        }
        printf("There isn't any file with this address\n");
        printf("Try again with another address or write quit to exit program ...\n");
        vorud(fileaddress);
    }
    while(fopen(fileaddress, "r") != 0)
    {
        system("CLS");
        int x, y;
        int line_number = 1;
        int tedad_kol = tedad_line(filename, fileaddress);
        int str[tedad_kol];
        backslash_n(filename, fileaddress, str);
        textbackground(BLACK);
        readfile(filename, fileaddress, line_number, tedad_kol);
        textbackground(BLUE);
        print_mode_border("NORMAL");
        textbackground(LIGHTBLUE);
        filename_bar(fileaddress, line_number);
        textbackground(BLACK);
        gotoxy(7, 1);
        x = wherex();
        y = wherey();
        c = getch();
        while((int)c != 27)
        {
            while(c == 'h' || c == 'j' || c == 'k' || c == 'l' || c == 'e' || c == 'f')
            {
                move(&x, &y, c, &line_number, tedad_kol, str);
                x = wherex();
                y = wherey();
                system("CLS");
                textbackground(BLACK);
                readfile(filename, fileaddress, line_number, tedad_kol);
                textbackground(BLUE);
                print_mode_border("NORMAL");
                textbackground(LIGHTBLUE);
                filename_bar(fileaddress, line_number);
                textbackground(BLACK);
                gotoxy(x, y);
                c = getch();
                gotoxy(x, y);
            }
            /*while(c == 'v')
            {
                temp = getch();
                if(temp == 's')
                {
                    while(c == 'h' || c == 'j' || c == 'k' || c == 'l' || c == 'e' || c == 'f')
                    {
                        count_select += move_select(&x, &y, c, &line_number, tedad_kol, str);
                        x = wherex();
                        y = wherey();
                        system("CLS");
                        textbackground(BLACK);
                        fileselect(filename, fileaddress, line_number, tedad_kol, );
                        textbackground(BLUE);
                        print_mode_border("VISUAL");
                        textbackground(YELLOW);
                        filename_bar(fileaddress, line_number);
                        textbackground(BLACK);
                        gotoxy(x, y);
                        c = getch();
                        gotoxy(x, y);
                    }
                }

            }*/
            if(c == '=')
            {
                system("CLS");
                FILE* helper;
                helper = fopen("help.txt", "w");
                filename = fopen(fileaddress, "r");
                char tmp = fgetc(filename);
                int i = 0;
                while(tmp != EOF)
                {
                    str1[i] = tmp;
                    i++;
                    tmp = fgetc(filename);
                }
                str1[i] = '\0';
                tedad_curly_brackets(str1, bra, ket);
                space_remover(str1, str_prime, bra, ket);
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
                x = wherex();
                y = wherey();
                int tedad_kol_new = tedad_line(filename, fileaddress);
                int str2[tedad_kol];
                backslash_n(filename, fileaddress, str2);
                textbackground(BLACK);
                readfile(filename, fileaddress, 1, tedad_kol_new);
                textbackground(BLUE);
                print_mode_border("NORMAL");
                textbackground(LIGHTBLUE);
                filename_bar(fileaddress, 1);
                textbackground(BLACK);
                gotoxy(7, 1);
                c = getch();
            }
            while(c == ':' || c == '/')
            {    
                gotoxy(1, 30);
                scanf("%s", command);
                if(!strcmp(command, "open"))                    
                {
                    getchar();
                    vorud_open(fileaddress);
                    if(fopen(fileaddress, "r") == 0)
                    {
                        gotoxy(1, 30);
                        printf("There isn't any file with this address");
                        usleep(3000000);
                        delline();
                        gotoxy(1, 30);
                    }
                    if(!fopen(fileaddress, "r") == 0)
                    {
                        flag = 1;
                        break;
                    }
                }
                if(!strcmp(command, "auto-indent"))
                {
                    getchar();
                    vorud(fileaddress);
                    FILE* helper;
                    helper = fopen("help.txt", "w");
                    filename = fopen(fileaddress, "r");
                    char tmp = fgetc(filename);
                    int i = 0;
                    while(tmp != EOF)
                    {
                        str1[i] = tmp;
                        i++;
                        tmp = fgetc(filename);
                    }
                    str1[i] = '\0';
                    tedad_curly_brackets(str1, bra, ket);
                    space_remover(str1, str_prime, bra, ket);
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
                else
                {
                    printf("invalid command");
                    usleep(3000000);
                    delline();
                    gotoxy(1, 30);
                }
            }
            if(flag == 1)
            {
                flag = 0;
                break;
            }
            else
            {
                c = getch();
            }
        }
        if((int)c == 27)
        {
            break;
        }
    }
    system("CLS");
    return 0;
}