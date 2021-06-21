#define _CRT_SECURE_NO_WARNINGS
#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define M_PI 3.14159265358979323846

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

void printStack(const STACK* head, char polsk[])
{
    STACK* polskaya = 0; int i = 0;
    while (head) {
        polskaya = Push(polskaya, head->value);
        head = head->pnext;
    }
    while (polskaya)
    {
        printf("%c", polskaya->value); polsk[i] = polskaya->value; i += 1; polskaya = polskaya->pnext;
    }
}
void Iz_char_v_double (char polsk[], double rez[], int i, int i2)
{
    if (polsk[i] == '-')i += 1;
    if (polsk[i - 1] != '-' || (polsk[i - 1] == '-' && polsk[i - 2] == '-')) {
                rez[i2] = (int)polsk[i] - 48; i += 1;

                while (polsk[i] >= '0' && polsk[i] <= '9')
                {
                    rez[i2] = rez[i2] * 10 + ((int)polsk[i] - 48); i += 1;
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
                    rez[i2] = rez[i2] + x;
                }
            }
            else
            {
                rez[i2] = -((int)polsk[i] - 48); i += 1;
                while (polsk[i] >= '0' && polsk[i] <= '9')
                {
                    rez[i2] = rez[i2] * 10 - ((int)polsk[i] - 48); i += 1;
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
                    rez[i2] = rez[i2] - x;
                }
            }
            i2 += 1;
            if (polsk[i] == '+' || polsk[i] == '-' || polsk[i] == '/' || polsk[i] == '*')
            {
                i -= 1;
            }
}
double rezultat(char polsk[])
{
    double rez[1000] = { 0 };//массив подсчета результата
    int i = 0;
    int i2 = 0;
    while (polsk[i] != '\0')
    {
        if (polsk[i] == '+')
        {
            rez[i2 - 2] = rez[i2 - 2] + rez[i2 - 1];
            rez[i2 - 1] = 0;
            i2 -= 1;
        }
        if (polsk[i] == '-' && polsk[i + 1] == ' ')
        {
            rez[i2 - 2] = rez[i2 - 2] - rez[i2 - 1];
            rez[i2 - 1] = 0;
            i2 -= 1;
        }
        if (polsk[i] == '*')
        {
            rez[i2 - 2] = rez[i2 - 2] * rez[i2 - 1];
            rez[i2 - 1] = 0;
            i2 -= 1;
        }
        if (polsk[i] == '/')
        {
            rez[i2 - 2] = rez[i2 - 2] / rez[i2 - 1];
            rez[i2 - 1] = 0;
            i2 -= 1;
        }
        if (polsk[i] >= '0' && polsk[i] <= '9')
        {
           // Iz_char_v_double(polsk, rez, i, i2);
            if (polsk[i - 1] != '-' || (polsk[i - 1] == '-' && polsk[i - 2] == '-')) {
                rez[i2] = (int)polsk[i] - 48; i += 1;

                while (polsk[i] >= '0' && polsk[i] <= '9')
                {
                    rez[i2] = rez[i2] * 10 + ((int)polsk[i] - 48); i += 1;
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
                    rez[i2] = rez[i2] + x;
                }
            }
            else
            {
                rez[i2] = -((int)polsk[i] - 48); i += 1;
                while (polsk[i] >= '0' && polsk[i] <= '9')
                {
                    rez[i2] = rez[i2] * 10 - ((int)polsk[i] - 48); i += 1;
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
                    rez[i2] = rez[i2] - x;
                }
            }
            i2 += 1;
            if (polsk[i] == '+' || polsk[i] == '-' || polsk[i] == '/' || polsk[i] == '*')
            {
                i -= 1;
            }
        }
        if (polsk[i]=='s' && polsk[i+1] == 'i' && polsk[i+2] == 'n')
        {
        i += 3;
        Iz_char_v_double(polsk, rez, i, i2);
        rez[i2] = sin(rez[i2]);
        i2 += 1;
        }
        if (polsk[i] == 'c' && polsk[i + 1] == 'o' && polsk[i + 2] == 's')
        {
            i += 3;
            Iz_char_v_double(polsk, rez, i, i2);
            rez[i2] = cos(rez[i2]);
            i2 += 1;
        }
        if (polsk[i] == 't' && polsk[i + 1] == 'g')
        {
            i += 2;
            Iz_char_v_double(polsk, rez, i, i2);
            rez[i2] = tan(rez[i2]);
            i2 += 1;
        }
        if (polsk[i] == 'l' && polsk[i + 1] == 'o' && polsk[i + 2] == 'g')
        {
            i += 3;
            Iz_char_v_double(polsk, rez, i, i2);
            rez[i2] = log(rez[i2]);
            i2 += 1;
        }
        if (polsk[i] == 'l' && polsk[i + 1] == 'n')
        {
            i += 2;
            Iz_char_v_double(polsk, rez, i, i2);
            rez[i2] = sin(rez[i2]);
            i2 += 1;
        }
        if (polsk[i] == 's' && polsk[i + 1] == 'q' && polsk[i + 2] == 'r' && polsk[i+3]=='t')
        {
            i += 4;
            Iz_char_v_double(polsk, rez, i, i2);
            rez[i2] = sqrt(rez[i2]);
            i2 += 1;
        }
        if (polsk[i] == 'a' && polsk[i + 1] == 'b' && polsk[i + 2] == 's')
        {
            i += 3;
            Iz_char_v_double(polsk, rez, i, i2);
            if (rez[i2] < 0) { rez[i2] = -(rez[i2]); }
            i2 += 1;
        }
        if (polsk[i] == 'e' && polsk[i + 1] == 'x' && polsk[i + 2] == 'p')
        {
            i += 3;
            
            Iz_char_v_double(polsk, rez, i, i2);
            rez[i2] = exp(rez[i2]);
            i2 += 1;
        }
        i += 1;
    }
    return  rez[0];
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
