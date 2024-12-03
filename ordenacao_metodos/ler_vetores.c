#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <math.h>
#include "Sort.h"
#include "ler_vetores.h"

struct vetor{
    int fim;
    int valores[MAX];
    int* pai;
    int* peso;
};

void exibir(vetor* v);

int find(vetor* v, int x);
void uniao(vetor* v, int x, int y);
void exUnionFind(vetor* v);

int part;
int tam;

int main ()
{
    setlocale(LC_ALL,"");
    vetor* p = arquivo();
    //exibir(p);
    //bubblesort(p);
    //insertionsort(p);
    //mergesort(p->valores, 0, p->fim);
    //quicksort(p->valores, 0, p->fim);
    exUnionFind(p);

    /*for(int i = 1; i <= tam; i++){
        printf("%d \n",find(p, i));
        if(find(p, i) == r){
            aux->valores[aux->fim] = i;
            aux->fim = aux->fim + 1;
        }
    }*/


    /*
    for(int i = 0; i < aux->fim; i++)
        printf("Valor %d: %d\n", i, aux->valores[i]);
    */

    //Até aqui, tá tudo 100%

    int escolha;
    do{
        printf("\nMENU\n");
        printf("1. Encontrar representante\n");
        printf("2. União de conjuntos\n");
        printf("3. Ordenar subconjunto\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch(escolha)
        {
        case 1:
            {
            int x;
            printf("Digite o elemento: ");
            scanf("%d", &x);
            printf("Representante de %d: %d\n", x, find(p, x));
            break;
            }
        case 2:
            {
            int x, y;
            printf("Digite dois elementos para unir: ");
            scanf("%d %d", &x, &y);
            uniao(p, x, y);
            printf("Conjuntos unidos!\n");
            break;
            }
        case 3:
            {
            vetor* aux= (vetor*) malloc(sizeof(vetor));
            aux->fim = 0;
            int r;
            printf("Defina um representante para efetuar a ordenação: \n");
            scanf("%d", &r);
            tam = p->fim;
            for(int i = tam; i >= 1; i--){
                if(find(p, i) == r){
                    aux->valores[aux->fim] = i;
                    aux->fim = aux->fim + 1;
                }
            }

            aux->fim = aux->fim - 1;

            //Escolher o método de ordenação
            printf("Escolha um método de ordenação!\n");
            printf("1. Bubblesort;\n");
            printf("2. Insertionsort;\n");
            printf("3. Mergesort;\n");
            printf("4. Quicksort;\n");
            int sesc;
            scanf("%d", &sesc);

            if(sesc == 1)
                bubblesort(aux);
            else if(sesc == 2)
                insertionsort(aux);
            else if(sesc == 3)
                mergesort(aux->valores, 0, aux->fim);
            else if(sesc == 4)
                quicksort(aux->valores, 0, aux->fim);

            printf("Subconjunto ordenado: ");
            exibir(aux);
            printf("\n");
            break;
            }
        case 4:
            {
            printf("Saido...\n");
            break;
            }
        default:
            printf("Opção inválida!\n");
        }


    }while (escolha != 4);



    free(p->valores);
    free(p->pai);
    free(p->peso);
    free(p);

    return 0;
}


//Exibe todos os valores de um vetor V
void exibir(vetor* v){
    for (int i = 0; i <= v->fim; i++)
        {
            printf(" %d", v->valores[i]);
        }
}

//Lê um arquivo do vetor.
vetor* arquivo()
{
    FILE* csv = fopen("Vetores.csv", "r");
    char linha[400];
    vetor* v = (vetor*) malloc(sizeof(vetor));
    int i = 0;
    char *token;

    if(csv == NULL)
        printf("Não foi possível abrir o arquivo!\n");

    //Leitura para ignorar a primeira linha do arquivo CSV...
    fgets(linha, sizeof(linha),csv);
    char* teste = strtok(linha, "¿");
    teste = strtok(linha, ";");
    part = atoi(teste);
    teste = strtok(NULL, ";");
    tam = atoi(teste);

    //printf("%d \n", part);
    //printf("%d \n", tam);


    //Captura a primeira linha do arquivo e posiciona dentro de "linha".
    fgets(linha, sizeof(linha),csv);
    linha[strcspn(linha, "\n")] = '\0';
    //printf("%s\n", linha);

    //Primeira captura só pra ele aceitar

    //Aqui é só uma atribuição do primeiro valor...
    token = strtok(linha, ";");
    //printf("Token: %s \n", token);
    v->valores[i] = atoi(token);;
    i++;
    while (token != NULL)
        {
            token = strtok(NULL, ";");
            v->valores[i] = atoi(token);
            i++;
        }
    //A função "strtok" pega um último valor antes de voltar o valor de NULL, sendo o valor 0 adicionado ao final de cada vetor.
    //A seguinte subtração define o fim do vetor como sendo o valor anterior ao 0 adicionado ao fim do vetor. Deixando o tamanho certo.
    //Isso para movimentações sobre o vetor nos índices de 0 até o seu fim (Essa leitura está sendo feita automaticamente, ainda que exista)
    //Um valor para passagem no arquivo. Foi mais uma questão de preferência...
    //Aceito o valor da leitura, mas acabei fazendo a minha própria.

    v->fim = i - 2;
    //printf("Tamanho: %d. \nÚltimo valor: %d ", v->fim, v->valores[v->fim]);
    //token = strtok(NULL, "");
    //printf("%s", token);


    //Inicializações para o UNION-FIND
    v->pai = (int *) malloc((tam+1) * sizeof(int));
    v->peso = (int *) malloc((tam+1) * sizeof(int));

    for(int j = 1; j <= tam; j++)
        {
            v->pai[j] = j;
            v->peso[j] = 0;
        }

    fclose(csv);
    return v;
}

int find(vetor* v, int x)
{
    if (v->pai[x] != x){
        v->pai[x] = find(v, v->pai[x]);
    }
    return v->pai[x];
}

void uniao(vetor* v, int x, int y)
{
    int raizx = find(v, x);
    int raizy = find(v, y);

    if (raizx != raizy){
        if(v->peso[raizx] > v->peso[raizy])
            v->pai[raizy] = raizx;
        else if (v->peso[raizx] < v->peso[raizy])
            v->pai[raizx] = raizy;
        else
            {
            v->pai[raizy] = raizx;
            v->peso[raizx] ++;
        }

    }
}


void exUnionFind(vetor* v)
{
    //printf("Exemplinho de cria \n");

    uniao(v, 1, 2);
    uniao(v, 4, 3);
    uniao(v, 2, 3);

    uniao(v, 41, 2);
    uniao(v, 13, 2);
    uniao(v, 21, 2);
    uniao(v, 51, 2);
    uniao(v, 12, 2);
    uniao(v, 31, 2);
    //for (int i = 1; i <= v->fim+1; i++)
    //   printf("O elemento %d pertence ao conjunto com representante: %d\n", i, find(v, i));
}



//Implementação do Bubblesort funcionando :D
void bubblesort(vetor* v)
{
    int fim = v->fim;
    for (int i = 0; i < fim; i++)
        {
            for(int j = 0; j < fim ; j++)
                {
                    if(v->valores[j] > v->valores[j+1])
                        {
                            int temp = v->valores[j];
                            v->valores[j] = v->valores[j+1];
                            v->valores[j+1] = temp;
                        }
                }
        }
}

//Implementação do InsertionSort funcionando :D
void insertionsort(vetor* v)
{
    int fim = v->fim;
    for(int i = 1; i <= fim; i++)
        {
            int chave = v->valores[i];
            int j = i - 1;

            while(j >= 0 && v->valores[j] > chave)
                {
                    v->valores[j+1] = v->valores[j];
                    j--;
                }
            v->valores[j + 1] = chave;
        }

}

//Implementação do Mergesort funcionando! :D
void merge(int *v, int inicio, int meio, int fim)
{
    int *temp, p1, p2, tamanho, i, j, k;
    int fim1 = 0, fim2 = 0;

    tamanho = fim - inicio + 1;

    p1 = inicio;
    p2 = meio + 1;

    temp = (int *) malloc(tamanho*sizeof(int));
    if(temp != NULL){
        for(i = 0; i < tamanho; i++){
            if(!fim1 && !fim2){
                if (v[p1] < v[p2])
                    temp[i] = v[p1++];
                else
                    temp[i] = v[p2++];
                if(p1 > meio)
                    fim1 = 1;
                if(p2 > fim)
                    fim2 = 1;
                }else{
                    if(!fim1)
                        temp[i] = v[p1++];
                    else
                        temp[i] = v[p2++];
                }
        }
        for (j = 0, k = inicio; j < tamanho; j++, k++)
                v[k] = temp[j];
    }
    free(temp);
}
void mergesort(int *v, int inicio, int fim)
{
    int meio;
    if (inicio < fim)
        {
            meio = floor((inicio + fim)/2);
            mergesort(v, inicio, meio);
            mergesort(v, meio+1, fim);
            merge(v, inicio, meio, fim);

        }

}

//Implementação do Quicksort funcionando! :D
int particiona(int *v, int inicio, int fim){
    int esq, dir, pivo, aux;
    esq = inicio;
    dir = fim;
    pivo = v[inicio];

    while(esq < dir){
        while (esq <= fim && v[esq] <= pivo)
            esq++;
        while (dir >= 0 && v[dir] > pivo)
            dir--;
        if(esq < dir){
            aux = v[esq];
            v[esq] = v[dir];
            v[dir] = aux;
        }
    }
    v[inicio] = v[dir];
    v[dir] = pivo;
    return dir;
}

void quicksort(int *v, int inicio, int fim)
{
    int pivo;
    if(fim > inicio){
        pivo = particiona(v, inicio, fim);
        quicksort(v, inicio, pivo-1);
        quicksort(v, pivo+1, fim);
    }
}


