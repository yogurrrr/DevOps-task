#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#define SIZE 1000
#include <string.h>
#include "structures.h"
#include "functions.h"


int main()
{
    // добавляйте пустую строку пожалуйста
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
    int c = 0;
    while (!feof(input))
    {
        fgets(variables[c], 100, input);
        int varlen = strlen(variables[c]);
        if (varlen != 0) { variables[c++][varlen - 1] = '\0'; }
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
    //        // нужно переписать строку в с2 в массиве variables, начиная с символа l, заполнив ее числом Lokal_rez


    //    }
    //    c2 -= 1;
    //}
    COMPLEX Itog = itog(polsk, vivod, variables, str, len, tsifri, znaki, c);
     printf("\nResult:\n%.4lf %.4lfj", Itog.real, Itog.imag); 
}