#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "FilaPrio.h"

struct semana
{
    char dia[20];
    int horas;
};

typedef struct semana semana;

semana* cria_semana()
{
    semana* sem;
    char dias [7] [15] = {"Segunda-Feira", "Terça-Feira", "Quarta-Feira", "Quinta-Feira","Sexta-Feira", "Sábado", "Domingo"};
    sem = (semana* ) malloc(sizeof(struct semana));
    for (int i = 0; i < 7; i++)
        {
            strcpy(sem[i].dia, dias[i]);
        }
    return sem;
}

void cria_arquivo(semana* sem)
{
    FILE *ps = NULL;
    ps = fopen("Cronograma-Semana.txt", "w");

    if(ps == NULL)
        {
            printf("Não consegui criar o arquivo. \n");
            exit(EXIT_FAILURE);
        }
    for (int i = 0; i < 7; i++)
        {
            if(i > 0)
                fputs("\n", ps);
            fputs(sem[i].dia, ps);
        }
    fclose(ps);

}


/*int main ()
{
	setlocale(LC_ALL,"Portuguese");

    cria_arquivo(cria_semana());

	system("pause");
	return 0;
}*/

