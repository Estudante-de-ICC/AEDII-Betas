#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED
#include "ler_vetores.h"
void bubblesort(vetor* v);
void insertionsort(vetor* v);
void merge_sort(vetor* v);
//Parte recursiva do Merge sort
void merg_e(int v[], int l, int r);
//Parte de dar merge nas arrays já ordenadas.
void merg_i(int v[], int l, int m, int r);

#endif // SORT_H_INCLUDED
