#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define EPS 0.0000001
#define M_PI 3.14159265358979323846
#define M_E 2.71828182845904523536

int prior(char zn)
{
    if (zn == '(')
        return 0;
    if (zn == '+' || zn == '-')
        return 1;
    if (zn == '*' || zn == '/')
        return 2;
}

int IsEmptyZn(STACKzn* phead)
{
    if (phead)
        return 0;
    return 1;
}

STACK* Push(STACK* tsifri, char v)
{
    STACK* pnew = (STACK*)malloc(sizeof(STACK));
    pnew->pnext = tsifri;
    pnew->value = v;
    return pnew;
}

STACK* Pop(STACK* phead)
{
    STACK* pnew = phead->pnext;
    free(phead);
    return pnew;
}

int IsEmpty(STACK* phead)
{
    if (phead)
        return 0;
    return 1;
}

STACKzn* PushZn(STACKzn* phead, char v)
{
    STACKzn* pnew = (STACKzn*)malloc(sizeof(STACKzn));
    pnew->pnext = phead;
    pnew->value = v;
    return pnew;
}

STACKzn* PopZn(STACKzn* phead)
{
    STACKzn* pnew = phead->pnext;
    free(phead);
    return pnew;
}

void printStack(const STACK* head, char polsk[], int q)
{
    STACK* polskaya = 0; int i = 0;
    while (head) {
        polskaya = Push(polskaya, head->value);
        head = head->pnext;
    }

    while (polskaya)
    {
        if (!q) { printf("%c", polskaya->value); }
        polsk[i] = polskaya->value;
        i += 1;
        polskaya = polskaya->pnext;
    }
}

void Iz_double_v_char(double num, char string_num[])
{
    double num_copy = num;
    int before_point = 0;
    int after_point = 0;
    int negative = 0;
    int less_than_one = 0;
    if (num < 0)
        ++negative;
    while (num_copy > 1 || num_copy < -1)
    {
        num_copy /= 10;
        ++before_point;
    }
    if (!before_point)
        ++less_than_one;
    num_copy = num;
    if (num_copy > 0)
    {
        while (num_copy < 100000000000 && fmod(num_copy * 10, 10.0) > EPS)
        {
            num_copy *= 10;
            ++after_point;
        }
    }
    else
    {
        while (num_copy > -100000000000 && fmod(num_copy * 10, -10.0) < -EPS)
        {
            num_copy *= 10;
            ++after_point;
        }
    }
    /*while ((num_copy < 100000000000 || (num_copy > -100000000000 && num_copy < 0)) && (fmod(num_copy * 10, 10.0) > EPS || fmod(num_copy * 10, -10.0) < -EPS))
    {
        num_copy *= 10;
        ++after_point;
    }*/
    long long num_copy_ = (long long)num_copy;
    for (int i = 0; i < after_point; ++i)
    {
        string_num[before_point + after_point - i + negative + less_than_one] = num_copy_ % 10 + '0';
        if (negative)
            string_num[before_point + after_point - i + negative + less_than_one] += -(num_copy_ % 10) * 2;
        num_copy_ /= 10;
    }
    for (int i = 0; i < before_point; ++i)
    {
        string_num[before_point - 1 - i + negative] = num_copy_ % 10 + '0';
        if (negative)
            string_num[before_point - 1 - i + negative] += -(num_copy_ % 10) * 2;
        num_copy_ /= 10;
    }
    if (negative)
        string_num[0] = '-';
    string_num[before_point + negative + less_than_one] = '.';
    if (!before_point)
        string_num[before_point + negative - 1 + less_than_one] = '0';
    if (!after_point)
        string_num[before_point + negative + 1 + less_than_one] = '0';
}
COMPLEX itog(char polsk[100], char vivod[100], char variables[30][100], char str[100], int len, STACK* tsifri, STACKzn* znaki, int c, int noprint)
{
    for (int i = 0; i < len; i++)
    {
        if ((str[i] >= '0' && str[i] <= '9') || (str[i] == '-' && (str[i + 1] >= '0' && str[i + 1] <= '9')))
        {
            if (str[i] == '-')
            {
                tsifri = Pop(tsifri);
                tsifri = Push(tsifri, str[i]);
                i += 1;
            }
            if ((str[i + 1] < '0' || str[i + 1] >'9') && str[i + 1] != '.')
            {
                tsifri = Push(tsifri, str[i]);
                if (str[i + 1] != '^')tsifri = Push(tsifri, ' ');
                else {
                    tsifri = Push(tsifri, '^'); i += 1;
                }
            }
            else {
                while ((str[i] >= '0' && str[i] <= '9') || str[i] == '.' || str[i] == '+' || str[i] == '-' || str[i] == '^')
                {
                    tsifri = Push(tsifri, str[i]);
                    i += 1;
                }
                if (str[i] == 'j' && str[i + 1] == '^')
                {
                    i += 1;
                    tsifri = Push(tsifri, str[i]);
                    i += 1;
                    while ((str[i] >= '0' && str[i] <= '9') || str[i] == '.' || str[i] == '+' || str[i] == '-')
                    {
                        tsifri = Push(tsifri, str[i]);
                        i += 1;
                    }
                }
                tsifri = Push(tsifri, ' ');
            }

        }
        if (str[i] == '(')
        {
            znaki = PushZn(znaki, '(');
            continue;
        }
        if ((str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') && str[i + 1] == ' ')
        {
            if (IsEmptyZn(znaki) || prior(str[i]) > prior(znaki->value))
            {
                if (str[i] == '-' && str[i + 2] == '-') { znaki = PushZn(znaki, '+'); i += 2; }
                else {
                    if (str[i] == '+' && str[i + 2] == '-') {
                        znaki = PushZn(znaki, '-'); i += 2;
                    }
                    else znaki = PushZn(znaki, str[i]);
                }
                
                
                continue;
            }
            else
            {
                while (!IsEmptyZn(znaki) && prior(str[i]) <= prior(znaki->value))
                {
                    tsifri = Push(tsifri, znaki->value);
                    tsifri = Push(tsifri, ' ');
                    znaki = PopZn(znaki);
                }
                znaki = PushZn(znaki, str[i]);
                continue;
            }
        }
        if (str[i] == ')')
        {
            while (znaki->value != '(')
            {
                tsifri = Push(tsifri, znaki->value);
                tsifri = Push(tsifri, ' ');
                znaki = PopZn(znaki);
            }
            znaki = PopZn(znaki); // минус скобка
        }
        if ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))
        {
            char peremennaya[10] = { 0 };
            int p = 0;
            if (str[i - 1] == '-')
            {
                tsifri = Push(tsifri, str[i - 1]);
                // i += 1;
            }
            while (str[i] != ' ' && str[i] != '\n' && str[i] != '\0' && str[i] != -52 && str[i] != '^')// после названи§ переменной пусть об§зательно будет пробел
            {
                peremennaya[p] = str[i];
                i += 1; p += 1;
            }
            if ((strcmp(peremennaya, "sin") == 0) || (strcmp(peremennaya, "cos") == 0) || (strcmp(peremennaya, "tg") == 0)
                || (strcmp(peremennaya, "log") == 0) || (strcmp(peremennaya, "ln") == 0) || (strcmp(peremennaya, "sqrt") == 0)
                || (strcmp(peremennaya, "pow") == 0) || (strcmp(peremennaya, "abs") == 0) || (strcmp(peremennaya, "exp") == 0)
                || (strcmp(peremennaya, "real") == 0) || (strcmp(peremennaya, "imag") == 0) || (strcmp(peremennaya, "mag") == 0)
                || (strcmp(peremennaya, "phase") == 0))
            {
                int r = 0;
                while (peremennaya[r])
                {
                    tsifri = Push(tsifri, peremennaya[r]);
                    r += 1;
                }

            }
            if ((strcmp(peremennaya, "Pi") == 0) || (strcmp(peremennaya, "PI") == 0) || (strcmp(peremennaya, "e") == 0))
            {
                if (peremennaya[0] == 'e') {
                    tsifri = Push(tsifri, '2');
                    tsifri = Push(tsifri, '.');
                    tsifri = Push(tsifri, '7');
                    tsifri = Push(tsifri, '1');
                    tsifri = Push(tsifri, '8');
                    tsifri = Push(tsifri, ' ');
                }
                else
                {
                    tsifri = Push(tsifri, '3');
                    tsifri = Push(tsifri, '.');
                    tsifri = Push(tsifri, '1');
                    tsifri = Push(tsifri, '4');
                    tsifri = Push(tsifri, '1');
                    tsifri = Push(tsifri, '5');
                    tsifri = Push(tsifri, ' ');


                }
            }
            for (int j = 0; j < c; ++j)
            {
                int k = 0; char vvod_p[10] = { 0 };
                while (variables[j][k] != ' ') { vvod_p[k] = variables[j][k]; k += 1; }
                if (strcmp(peremennaya, vvod_p) == 0)
                {

                    k += 3;
                    while (variables[j][k] != '\n' && variables[j][k] != '\0' && variables[j][k] != 'j')
                    {
                        tsifri = Push(tsifri, variables[j][k]);
                        k += 1;
                    }
                    if (str[i] != '^')tsifri = Push(tsifri, ' ');
                    else {
                        tsifri = Push(tsifri, '^'); //i += 1;
                    }
                }
            }
            //  if (strcmp(peremennaya, str2) == 0) сравню потом циклом, в зависимости от части Љрсени§


        }
        //!!!!!!if (str[i] == какой-нибудь букве), то (while str[i]!=' ')записываем ее в отдельную переменную до пробела 
        //и сравниваем с введенными переменными,  если совпадает, то записываем значение переменной в стек tsifri)
    }
    while (!IsEmptyZn(znaki))
    {
        tsifri = Push(tsifri, znaki->value);
        tsifri = Push(tsifri, ' ');
        znaki = PopZn(znaki);
    }
    if (!noprint)
    {
        printf("\nReverse Polish Notation:\n");
    }
    printStack(tsifri, polsk, noprint);

    polsk[strlen(polsk)] = '\0';

    COMPLEX Itog = rezultat(polsk);
    return Itog;
}
void Zapis_imag(COMPLEX rez[], int i, int i2, char polsk[])
{
    i += 1;
    if (polsk[i - 1] != '-' || (polsk[i - 1] == '-' && polsk[i - 2] == '-')) {
        rez[i2].imag = (int)polsk[i] - 48; i += 1;

        while (polsk[i] >= '0' && polsk[i] <= '9')
        {
            rez[i2].imag = rez[i2].imag * 10 + ((int)polsk[i] - 48); i += 1;
        }
        if (polsk[i] == '.')
        {
            i += 1;
            double x = 0;
            double z = 0.1;
            while (polsk[i] >= '0' && polsk[i] <= '9')
            {

                x = x + ((int)polsk[i] - 48) * z;
                i += 1;
                z = z / 10;
            }
            rez[i2].imag = rez[i2].imag + x;
        }
    }
    else
    {
        rez[i2].imag = -((int)polsk[i] - 48); i += 1;
        while (polsk[i] >= '0' && polsk[i] <= '9')
        {
            rez[i2].imag = rez[i2].imag * 10 - ((int)polsk[i] - 48); i += 1;
        }
        if (polsk[i] == '.')
        {
            i += 1;
            double x = 0;
            double z = 0.1;
            while (polsk[i] >= '0' && polsk[i] <= '9')
            {

                x = x + ((int)polsk[i] - 48) * z;
                i += 1;
                z = z / 10;
            }
            rez[i2].imag = rez[i2].imag - x;
        }
    }
}

void Iz_char_v_double(char polsk[], COMPLEX rez[], int i, int i2)
{
    if (polsk[i] == '-')i += 1;
    if (polsk[i - 1] != '-' || (polsk[i - 1] == '-' && polsk[i - 2] == '-')) {
        rez[i2].real = (int)polsk[i] - 48; i += 1;

        while (polsk[i] >= '0' && polsk[i] <= '9')
        {
            rez[i2].real = rez[i2].real * 10 + ((int)polsk[i] - 48); i += 1;
        }
        if (polsk[i] == '.')
        {
            i += 1;
            double x = 0;
            double z = 0.1;
            while (polsk[i] >= '0' && polsk[i] <= '9')
            {

                x = x + ((int)polsk[i] - 48) * z;
                i += 1;
                z = z / 10;
            }
            rez[i2].real = rez[i2].real + x;
        }
    }
    else
    {
        rez[i2].real = -((int)polsk[i] - 48); i += 1;
        while (polsk[i] >= '0' && polsk[i] <= '9')
        {
            rez[i2].real = rez[i2].real * 10 - ((int)polsk[i] - 48); i += 1;
        }
        if (polsk[i] == '.')
        {
            i += 1;
            double x = 0;
            while (polsk[i] >= '0' && polsk[i] <= '9')
            {
                double z = 0.1;
                x = x + ((int)polsk[i] - 48) * z;
                i += 1;
                z = z / 10;
            }
            rez[i2].real = rez[i2].real - x;
        }
    }
    i2 += 1;
    if (polsk[i] == '+' || polsk[i] == '-' || polsk[i] == '/' || polsk[i] == '*')
    {
        i -= 1;
    }
}

COMPLEX rezultat(char polsk[])
{
    COMPLEX rez[1000] = { 0 };//массив подсчета результата
    int i = 0;
    int i2 = 0;
    while (polsk[i] != '\0')
    {
        if (polsk[i] == '+')
        {
            rez[i2 - 2].real = rez[i2 - 2].real + rez[i2 - 1].real;
            rez[i2 - 1].real = 0;
            rez[i2 - 2].imag = rez[i2 - 2].imag + rez[i2 - 1].imag;
            rez[i2 - 1].imag = 0;
            i2 -= 1;
        }
        if (polsk[i] == '-' && polsk[i + 1] == ' ')
        {
            if (i2 != 1) {
                rez[i2 - 2].real = rez[i2 - 2].real - rez[i2 - 1].real;
                rez[i2 - 1].real = 0;
                rez[i2 - 2].imag = rez[i2 - 2].imag - rez[i2 - 1].imag;
                rez[i2 - 1].imag = 0;
                i2 -= 1;
            }
            else {
                rez[i2 - 1].real = -rez[i2 - 1].real;
                rez[i2 - 1].imag = -rez[i2 - 1].imag;
            }
        }
        if (polsk[i] == '*')
        {
            if (rez[i2 - 1].imag != 0 && rez[i2 - 2].imag != 0)
            {
                rez[i2 - 2] = multiplication(rez[i2 - 1], rez[i2 - 2]);
                rez[i2 - 1].real = 0;
                rez[i2 - 1].imag = 0;
            }
            else {
                rez[i2 - 2].real = rez[i2 - 2].real * rez[i2 - 1].real;
                rez[i2 - 1].real = 0;
                rez[i2 - 2].imag = rez[i2 - 2].imag * rez[i2 - 1].imag;
                rez[i2 - 1].imag = 0;
            }
            i2 -= 1;
        }
        if (polsk[i] == '/')
        {
            //if ((rez[i2 - 1].real != 0 && rez[i2-1].imag==0)||(rez[i2 - 1].real != 0 && rez[i2 - 1].imag != 0)|| (rez[i2 - 1].real == 0 && rez[i2 - 1].imag != 0))
           // {
            if (rez[i2 - 1].imag != 0 && rez[i2 - 2].imag != 0)
            {
                rez[i2 - 2] = division(rez[i2 - 1], rez[i2 - 2]);
                rez[i2 - 1].real = 0;
                rez[i2 - 1].imag = 0;
            }
            else {
                rez[i2 - 2].real = rez[i2 - 2].real / rez[i2 - 1].real;
                rez[i2 - 1].real = 0;
            }
            i2 -= 1;
            //  }
             // else //если это деление на ноль
           //   {
            if (rez[i2 - 1].real == INFINITY || rez[i2 - 1].imag == INFINITY)
            {
                printf("\n!!!!!!!!!!!DIVISION BY ZERO!!!!!!!!!!!\n");
                COMPLEX ZERO; ZERO.real = 8889; ZERO.imag = -9998;
                return ZERO;
            }
            //  }
        }
        if (polsk[i] >= '0' && polsk[i] <= '9')
        {
            // Iz_char_v_double(polsk, rez, i, i2);
            if (polsk[i - 1] != '-' || (polsk[i - 1] == '-' && polsk[i - 2] == '-')) {
                rez[i2].real = (int)polsk[i] - 48; i += 1;

                while (polsk[i] >= '0' && polsk[i] <= '9')
                {
                    rez[i2].real = rez[i2].real * 10 + ((int)polsk[i] - 48); i += 1;
                }
                if (polsk[i] == '.')
                {
                    i += 1;
                    double x = 0;
                    double z = 0.1;
                    while (polsk[i] >= '0' && polsk[i] <= '9')
                    {

                        x = x + ((int)polsk[i] - 48) * z;
                        i += 1;
                        z = z / 10;
                    }
                    rez[i2].real = rez[i2].real + x;
                }
                if (polsk[i] == '+' || polsk[i] == '-')
                {
                    Zapis_imag(rez, i, i2, polsk);
                    while (polsk[i] != ' ' && polsk[i] != '^') i += 1;
                }
                if (polsk[i] == '^')                                                                        // Чтепень числа
                {
                    i += 1;
                    double pow1; int minus = 0;
                    if (polsk[i] == '-') { i++; minus = 1; }
                    pow1 = (int)polsk[i] - 48; i += 1;

                    while (polsk[i] >= '0' && polsk[i] <= '9')
                    {
                        pow1 = pow1 * 10 + ((int)polsk[i] - 48); i += 1;
                    }
                    if (polsk[i] == '.')
                    {
                        i += 1;
                        double x = 0;
                        double z = 0.1;
                        while (polsk[i] >= '0' && polsk[i] <= '9')
                        {

                            x = x + ((int)polsk[i] - 48) * z;
                            i += 1;
                            z = z / 10;
                        }
                        pow1 = pow1 + x;
                    }
                    if (minus == 1) pow1 = pow1 * -1;
                    if (rez[i2].imag != 0) rez[i2] = pow_complex(rez[i2], pow1);
                    else { rez[i2].real = pow(rez[i2].real, pow1); }
                }
            }
            else
            {
                rez[i2].real = -((int)polsk[i] - 48); i += 1;
                while (polsk[i] >= '0' && polsk[i] <= '9')
                {
                    rez[i2].real = rez[i2].real * 10 - ((int)polsk[i] - 48); i += 1;
                }
                if (polsk[i] == '.')
                {
                    i += 1;
                    double x = 0;
                    double z = 0.1;
                    while (polsk[i] >= '0' && polsk[i] <= '9')
                    {

                        x = x + ((int)polsk[i] - 48) * z;
                        i += 1;
                        z = z / 10;
                    }
                    rez[i2].real = rez[i2].real - x;
                }
                if (polsk[i] == '+' || polsk[i] == '-')
                {
                    Zapis_imag(rez, i, i2, polsk);
                    while (polsk[i] != ' ' && polsk[i] != '^') i += 1;
                }
                if (polsk[i] == '^')                                                                        // Чтепень числа
                {
                    i += 1;
                    double pow1; int minus = 0;
                    if (polsk[i] == '-') { i++; minus = 1; }
                    pow1 = (int)polsk[i] - 48; i += 1;

                    while (polsk[i] >= '0' && polsk[i] <= '9')
                    {
                        pow1 = pow1 * 10 + ((int)polsk[i] - 48); i += 1;
                    }
                    if (polsk[i] == '.')
                    {
                        i += 1;
                        double x = 0;
                        double z = 0.1;
                        while (polsk[i] >= '0' && polsk[i] <= '9')
                        {

                            x = x + ((int)polsk[i] - 48) * z;
                            i += 1;
                            z = z / 10;
                        }
                        pow1 = pow1 + x;
                    }
                    if (minus == 1) pow1 = pow1 * -1;
                    if (rez[i2].imag != 0) rez[i2] = pow_complex(rez[i2], pow1);
                    else { pow(rez[i2].real, pow1); }
                }
            }
            i2 += 1;
            if (polsk[i] == '+' || polsk[i] == '-' || polsk[i] == '/' || polsk[i] == '*')
            {
                i -= 1;
            }
        }
        if (polsk[i] == 's' && polsk[i + 1] == 'i' && polsk[i + 2] == 'n')
        {
            i += 3;
            Iz_char_v_double(polsk, rez, i, i2);
            while ((polsk[i] >= '0' && polsk[i] <= '9') || polsk[i] == '.')i += 1;
            if (polsk[i] == '+' || polsk[i] == '-')
            {
                Zapis_imag(rez, i, i2, polsk);
                while (polsk[i] != ' ') i += 1;
                rez[i2] = complex_sin(rez[i2]);
            }
            else rez[i2].real = sin(rez[i2].real);
            i2 += 1;
        }
        if (polsk[i] == 'c' && polsk[i + 1] == 'o' && polsk[i + 2] == 's')
        {
            i += 3;
            Iz_char_v_double(polsk, rez, i, i2);
            while ((polsk[i] >= '0' && polsk[i] <= '9') || polsk[i] == '.')i += 1;
            if (polsk[i] == '+' || polsk[i] == '-')
            {
                Zapis_imag(rez, i, i2, polsk);
                while (polsk[i] != ' ') i += 1;
                rez[i2] = complex_cos(rez[i2]);
            }
            else

                rez[i2].real = cos(rez[i2].real);
            i2 += 1;

        }
        if (polsk[i] == 't' && polsk[i + 1] == 'g')
        {
            i += 2;
            Iz_char_v_double(polsk, rez, i, i2);
            while ((polsk[i] >= '0' && polsk[i] <= '9') || polsk[i] == '.')i += 1;
            if (polsk[i] == '+' || polsk[i] == '-')
            {
                Zapis_imag(rez, i, i2, polsk);
                while (polsk[i] != ' ') i += 1;
                rez[i2] = complex_tg(rez[i2]);
            }
            else
                rez[i2].real = tan(rez[i2].real);
            i2 += 1;
        }
        if (polsk[i] == 'l' && polsk[i + 1] == 'o' && polsk[i + 2] == 'g')
        {
            i += 3;
            Iz_char_v_double(polsk, rez, i, i2);
            while ((polsk[i] >= '0' && polsk[i] <= '9') || polsk[i] == '.')i += 1;
            if (polsk[i] == '+' || polsk[i] == '-')
            {
                Zapis_imag(rez, i, i2, polsk);
                while (polsk[i] != ' ') i += 1;
                rez[i2].real = log(rez[i2].real);
                rez[i2].imag = log(rez[i2].imag);
            }
            else
                rez[i2].real = log(rez[i2].real);
            i2 += 1;
        }
        if (polsk[i] == 'l' && polsk[i + 1] == 'n')
        {
            i += 2;
            Iz_char_v_double(polsk, rez, i, i2);
            while ((polsk[i] >= '0' && polsk[i] <= '9') || polsk[i] == '.')i += 1;
            if (polsk[i] == '+' || polsk[i] == '-')
            {
                Zapis_imag(rez, i, i2, polsk);
                while (polsk[i] != ' ') i += 1;
                rez[i2] = Complex_ln(rez[i2]);
            }
            else
                rez[i2].real = log(sqrt(rez[i2].real * rez[i2].real + rez[i2].imag * rez[i2].imag));
            i2 += 1;
        }
        if (polsk[i] == 's' && polsk[i + 1] == 'q' && polsk[i + 2] == 'r' && polsk[i + 3] == 't')
        {
            i += 4;
            Iz_char_v_double(polsk, rez, i, i2);
            while ((polsk[i] >= '0' && polsk[i] <= '9') || polsk[i] == '.')i += 1;
            if (polsk[i] == '+' || polsk[i] == '-')
            {
                Zapis_imag(rez, i, i2, polsk);
                while (polsk[i] != ' ') i += 1;
                rez[i2] = Complex_sqrt(rez[i2]);
            }
            else
                rez[i2].real = sqrt(rez[i2].real);
            i2 += 1;
        }
        if (polsk[i] == 'a' && polsk[i + 1] == 'b' && polsk[i + 2] == 's')
        {
            i += 3;
            Iz_char_v_double(polsk, rez, i, i2);
            while ((polsk[i] >= '0' && polsk[i] <= '9') || polsk[i] == '.')i += 1;
            if (polsk[i] == '+' || polsk[i] == '-')
            {
                Zapis_imag(rez, i, i2, polsk);
                while (polsk[i] != ' ') i += 1;
                rez[i2].real = Complex_abs(rez[i2]);
                rez[i2].imag = 0;
            }
            else {
                if (rez[i2].real < 0) { rez[i2].real = -(rez[i2].real); }
            }
            i2 += 1;
        }
        if (polsk[i] == 'e' && polsk[i + 1] == 'x' && polsk[i + 2] == 'p')
        {
            i += 3;
            Iz_char_v_double(polsk, rez, i, i2);
            while ((polsk[i] >= '0' && polsk[i] <= '9') || polsk[i] == '.')i += 1;
            if (polsk[i] == '+' || polsk[i] == '-')
            {
                Zapis_imag(rez, i, i2, polsk);
                while (polsk[i] != ' ') i += 1;
                rez[i2].real = Complex_exp(rez[i2]);
                rez[i2].imag = 0;
            }
            else {
                rez[i2].real = exp(rez[i2].real);
            }
            i2 += 1;
        }
        if (polsk[i] == 'm' && polsk[i + 1] == 'a' && polsk[i + 2] == 'g')
        {
            i += 3;
            Iz_char_v_double(polsk, rez, i, i2);
            while ((polsk[i] >= '0' && polsk[i] <= '9') || polsk[i] == '.')i += 1;
            if (polsk[i] == '+' || polsk[i] == '-')
            {
                Zapis_imag(rez, i, i2, polsk);
                while (polsk[i] != ' ') i += 1;
                rez[i2].real = Complex_mag(rez[i2]);
                rez[i2].imag = 0;
            }
            else {
                if (rez[i2].real < 0) { rez[i2].real = -(rez[i2].real); }
            }
            i2 += 1;
        }
        if (polsk[i] == 'r' && polsk[i + 1] == 'e' && polsk[i + 2] == 'a' && polsk[i + 3] == 'l')
        {
            i += 4;
            Iz_char_v_double(polsk, rez, i, i2);
            while ((polsk[i] >= '0' && polsk[i] <= '9') || polsk[i] == '.')i += 1;
            if (polsk[i] == '+' || polsk[i] == '-')
            {
                Zapis_imag(rez, i, i2, polsk);
                while (polsk[i] != ' ') i += 1;
                rez[i2].real = Complex_real(rez[i2]);
                rez[i2].imag = 0;
            }
            i2 += 1;
        }
        i += 1;
    }
    return rez[0];
}

COMPLEX complex_cos(COMPLEX num)
{
    COMPLEX result = { 0 };
    result.real = cos(num.real) * cosh(num.imag);
    result.imag = -1 * sin(num.real) * sinh(num.imag);
    return result;
}

COMPLEX complex_tg(COMPLEX num)
{
    COMPLEX result = { 0 };
    result.real = sin(2 * num.real) / (cos(2 * num.real) + cosh(2 * num.imag));
    result.imag = sinh(2 * num.imag) / (cos(2 * num.real) + cosh(2 * num.imag));
    return result;
}

double imag(COMPLEX num)
{
    return num.imag;
}

double phase(COMPLEX num)
{
    if (num.imag < 0)
        return -1 * (atan2(num.imag, num.real) * 180) / M_PI;
    return (atan2(num.imag, num.real) * 180) / M_PI;
}

COMPLEX addition(COMPLEX num1, COMPLEX num2)
{
    COMPLEX result = { 0 };
    result.real = num1.real + num2.real;
    result.imag = num1.imag + num2.imag;
    return result;
}

COMPLEX subtraction(COMPLEX num1, COMPLEX num2)
{
    COMPLEX result = { 0 };
    result.real = num1.real - num2.real;
    result.imag = num1.imag - num2.imag;
    return result;
}

COMPLEX multiplication(COMPLEX num1, COMPLEX num2)
{
    COMPLEX result = { 0 };
    result.real = num1.real * num2.real - num1.imag * num2.imag;
    result.imag = num1.real * num2.imag + num1.imag * num2.real;
    return result;
}

COMPLEX division(COMPLEX num1, COMPLEX num2)
{
    COMPLEX result = { 0 };
    result.real = (num1.real * num2.real + num1.imag * num2.imag) / (num2.real * num2.real + num2.imag * num2.imag);
    result.imag = (num1.imag * num2.real - num1.real * num2.imag) / (num2.real * num2.real + num2.imag * num2.imag);
    return result;
}

COMPLEX pow_complex(COMPLEX num, int power)
{
    COMPLEX result = { 0 };
    for (int i = 0; i < power - 1; ++i)
    {
        result = multiplication(num, num);
    }
    return result;
}

/////////////////////////////////////////////////////////////////////////////////
COMPLEX complex_sin(COMPLEX num)
{
    COMPLEX result = { 0 };
    result.real = sin(num.real) * cosh(num.imag);
    result.imag = cos(num.real) * sinh(num.imag);
    return result;
}

COMPLEX complex_ln(COMPLEX num)
{
    COMPLEX result = { 0 };
    result.real = log(sqrt(num.real * num.real + num.imag * num.imag));
    result.imag = atan(num.imag / num.real);
    return result;
}

double Complex_abs(COMPLEX num)
{
    return sqrt(num.real * num.real + num.imag * num.imag);
}

double Complex_real(COMPLEX num)
{
    return num.real;
}

double Complex_exp(COMPLEX num)
{
    return (exp(num.real) * (cos(num.imag) + sin(num.imag)));
}

double Complex_mag(COMPLEX num)
{
    return sqrt(num.real * num.real + num.imag * num.imag);
}

COMPLEX Complex_sqrt(COMPLEX num)
{
    double argz = 0;
    COMPLEX result = { 0 };
    if (num.real > 0)
    {
        if (num.imag >= 0)
        {
            argz = atan(num.imag / num.real);
        }
        else
            if (num.imag < 0)
            {
                argz = (2 * M_PI - tan(num.imag / num.real));
            }
    }
    else
        if (num.real < 0)
        {
            if (num.imag >= 0)
            {
                argz = M_PI - atan(num.imag / num.real);
            }
            else
                if (num.imag < 0)
                {
                    argz = (M_PI + tan(num.imag / num.real));
                }
        }
        else
            if (num.real == 0)
            {
                if (num.imag > 0)
                {
                    argz = M_PI / 2;
                }
                else
                    if (num.imag < 0)
                    {
                        argz = (3 * M_PI) / 2;
                    }
            }
    result.real = ((sqrt(sqrt(num.real * num.real + num.imag * num.imag))) * cos(argz / 2));
    result.imag = ((sqrt(sqrt(num.real * num.real + num.imag * num.imag))) * sin(argz / 2));
    return result;
}

COMPLEX Complex_ln(COMPLEX num)
{
    double argz = 0;
    COMPLEX result = { 0 };
    if (num.imag == 0)
    {
        result.real = log(num.real);
    }
    else
    {
        if (num.real > 0)
        {
            if (num.imag >= 0)
            {
                argz = atan(num.imag / num.real);
            }
            else
                if (num.imag < 0)
                {
                    argz = (2 * M_PI - tan(num.imag / num.real));
                }
        }
        else
            if (num.real < 0)
            {
                if (num.imag >= 0)
                {
                    argz = M_PI - atan(num.imag / num.real);
                }
                else
                    if (num.imag < 0)
                    {
                        argz = (M_PI + tan(num.imag / num.real));
                    }
            }
            else
                if (num.real == 0)
                {
                    if (num.imag > 0)
                    {
                        argz = M_PI / 2;
                    }
                    else
                        if (num.imag < 0)
                        {
                            argz = (3 * M_PI) / 2;
                        }
                }
        result.real = log(sqrt(num.real * num.real + num.imag * num.imag));
        result.imag = argz;
    }
    return result;
}

double Complex_log(COMPLEX num1, COMPLEX num2)
{
    return (log(num1.real) / log(num2.real));
}
