#ifndef LER_VETORES_H_INCLUDED
#define LER_VETORES_H_INCLUDED
#define MAX 250

typedef struct vetor vetor;

void exibir(vetor* v);
vetor* arquivo();
//Mergesort
void merge(int *v, int inicio, int meio, int fim);
void mergesort(int *v, int inicio, int fim);
//Bubble
void bubblesort(vetor* v);
//Insertion
void insertionsort(vetor* v);
//Quicksort
int particiona(int *v, int inicio, int fim);
void quicksort(int *v, int inicio, int fim);


#endif // LER_VETORES_H_INCLUDED
