#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "structures.h"

int prior(char zn);
int IsEmptyZn(STACKzn* phead);
STACK* Push(STACK* tsifri, char v);
STACK* Pop(STACK* phead);
int IsEmpty(STACK* phead);
STACKzn* PushZn(STACKzn* phead, char v);
STACKzn* PopZn(STACKzn* phead);
void printStack(const STACK* head, char polsk[]);
double rezultat(char polsk[]);
COMPLEX complex_cos(COMPLEX num);
COMPLEX complex_tg(COMPLEX num);
double imag(COMPLEX num);
double phase(COMPLEX num);

#endif // !FUNCTIONS_H