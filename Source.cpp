#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#define SIZE 1000
#include <string.h>
#include "structures.h"
#include "functions.h"


int main()
{
    // добавл¤йте пустую строку пожалуйста
    FILE* input = fopen("input.txt", "rt");
    printf("Expression:\n");
    //char* str = (char*)malloc(sizeof(STACK));
    char str[100] = { 0 };
    fgets(str, SIZE, input);
    int len = strlen(str);
    str[len] = '\0';
    printf("%s\n", str);
    STACK* tsifri = NULL;  //стек с числами
    STACKzn* znaki = 0; //стек со знаками oper
    char polsk[100] = { 0 };
    char vivod[100];
    char variables[30][100] = { 0 };
    int c = 0; int c2 = 0; int zero = 0;
    int noprint = 1;
    while (!feof(input))
    {
        fgets(variables[c], 100, input);
        int varlen = strlen(variables[c]);
        if (varlen != 0)
        {
            variables[c++][varlen - 1] = '\0';
            printf("%s\n", variables[c - 1]);
        }
    }
    if (c > 0) {
        c2 = c - 1;
        while (c2 != -1)
        {
            char str2[1000] = { 0 };
            int i = 0; int len2 = 0;
            while (variables[c2][i] != '=')i++; i += 2; int perezap = i; // с этого знака начнем перезаписывать выражение
            while (variables[c2][i] != '/n' && variables[c2][i] != '/0' && variables[c2][i] != 0) {
                str2[len2] = variables[c2][i]; len2++; i++;
            }
            char variables2[30][100] = { 0 };
            len2 = strlen(str2);
            str2[len2] = '\0';
            STACK* tsifri2 = NULL;  //стек с числами
            STACKzn* znaki2 = 0; //стек со знаками oper
            char polsk2[1000] = { 0 };
            char vivod2[1000];
            int i2 = 0;
            for (int i = c2 + 1; i < c; ++i)
            {
                strcpy(variables2[i2], variables[i]);
                i2++;
            }

            COMPLEX Itog2 = itog(polsk2, vivod2, variables2, str2, len2, tsifri2, znaki2, i2, noprint);//это переменна¤ в комплексном виде, котора¤ была получена из выражени¤
            if (Itog2.real == 8889 && Itog2.imag == -9998) {
                zero = 1; break;
            }
            // здесь нужно сообразить функцию, котора¤ преобразует Itog2 из double в char и перезаписать строку в variables[c2];
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////!!!!!!!!!!!! нужно обнулить вариэйблз
            for (int i = perezap; i < 100; i++) { variables[c2][i] = '\0'; }
            char string_num1[20] = { 0 }; char string_num2[20] = { 0 };
            Iz_double_v_char(Itog2.real, string_num1); int sn1 = 0;
            while (string_num1[sn1] != -52 && string_num1[sn1] != '\0')
            {
                variables[c2][perezap] = string_num1[sn1];
                perezap++; sn1++;
            }
            if (Itog2.imag < 0)variables[c2][perezap] = '-';
            else variables[c2][perezap] = '-';
            perezap++; sn1 = 0;
            Iz_double_v_char(Itog2.imag, string_num2);
            while (string_num2[sn1] != -52 && string_num2[sn1] != '\0')
            {
                variables[c2][perezap] = string_num2[sn1];
                perezap++; sn1++;
            }
            //string_num1[strlen(string_num1)] = '\0';
           // printf("%s", string_num1);
           /* if (Itog2.real < 0)
            {
                variables[c2][perezap] = '-';
                perezap += 1;
                Itog2.real = -Itog2.real;
            }*/
            ///////////////////////////
            c2 = c2 - 1;
        }
    }
    //int c2 = c-1;
    //while (c2 >= 0)
    //{
    //    char strl[100];
    //    strcpy(strl, variables[c2]);
    //    int l = 0; int p = 0; char peremen[30];
    //    while (strl[l] != '=') { peremen[l] = strl[l]; l++; } l += 2;
    //    char str2[100];
    //    int l2 = l;
    //    while (strl[l2] != '\0' && strl[l2] != '\n') { str2[p] = strl[l2]; p += 1; l2 += 1; }
    //     int len2 = p; str2[len2] = '\0'; p = 0;
    //    while (strl[l] != '\0' && strl[l] != '\n') { if (strl[l] == ' ') p += 1; l += 1; }
    //    if (p > 0)
    //    {
    //        int c3 = c2; int c4 = 0;
    //        char variabels2[30][100];
    //        while (c3 <= c) { strcpy(variabels2[c4], variables[c3]); c4 += 1; c3 += 1; }
    //        char polsk2[100] = { 0 };
    //        char vivod2[100]; STACK* tsifri2 = NULL;  //стек с числами
    //        STACKzn* znaki2 = 0;
    //        COMPLEX Lokal_rez= itog(polsk2, vivod2, variabels2, str2, len2, tsifri2, znaki2, c4);
    //        l = 0;
    //        while (peremen[l - 1] != '=') { variables[c2][l] = peremen[l]; l + 1; } variables[c2][l] = ' ';
    //        // нужно переписать строку в с2 в массиве variables, начина¤ с символа l, заполнив ее числом Lokal_rez


    //    }
    //    c2 -= 1;
    //}
    noprint = 0;
    if (zero == 0) {
        COMPLEX Itog = itog(polsk, vivod, variables, str, len, tsifri, znaki, c, noprint);
        if (Itog.real == 8889 && Itog.imag == -9998) { printf("correct the input"); }
        else
        {
            if (Itog.imag == 0) {
                printf("\nResult:\n%.4lf", Itog.real);
            }
            else { printf("\nResult:\n%.4lf %.4lfj", Itog.real, Itog.imag); }
        }
        /* printf("\nResult:\n%.4lf %.4lfj", Itog.real, Itog.imag);*/
    }
}

