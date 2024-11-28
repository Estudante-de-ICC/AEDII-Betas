#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "Estruturas.h"

infoarc* info_arq();
sala* cria_sala();
void compara_M_S(infoarc* p);
salas* le_salas();
hospital* ler_dados();

void compara_M_S(infoarc* p)
{
    int medicos = 0;
    for (int i = 3; i<= 8; i++)
        {
            medicos += p->valores[i];
        }
    if (medicos < p->valores[1])
        {
            p->valores[9] = 0;
            printf("Qtd médicos menor qtd salas\nEntrada inválida! Mais médicos são necessários para eficiência máxima!\n");
            printf("Médicos = %d; Salas = %d;", medicos, p->valores[1]);
        }
    else
        {
            p->valores[9] = 1;
            printf("Qtd médicos maior ou igual qtd salas\n");
            printf("Médicos = %d; Salas = %d;", medicos, p->valores[1]);
        }
}

infoarc* info_arq()
{
    char linha[100];
    infoarc* inf;
    inf =(infoarc*) malloc(sizeof(struct info));
    FILE *leitura = fopen("pacientes_320.csv", "r");
    if (!leitura)
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    //Ignora os dados presentes na primeira linha do arquivo em C 'i>>¿'
    fgets(linha, sizeof(linha), leitura);
    char* teste = strtok(linha, "¿");

    //Leitura dos primeiros dados de quantidade de pacientes e salas.

    //Quantidade de pacientes
    teste = strtok(NULL, ";");
    inf->valores[0] = atoi(teste);
    //Quantidade de salas
    teste = strtok(NULL, ";");
    inf->valores[1] = atoi(teste);
    //Quantidade de especialidades
    teste = strtok(NULL, ";");
    inf->valores[2] = atoi(teste);
    //Quantidade de especialistas tipo 1
    teste = strtok(NULL, ";");
    inf->valores[3] = atoi(teste);
    //Quantidade de especialistas tipo 2
    teste = strtok(NULL, ";");
    inf->valores[4] = atoi(teste);
    //Quantidade de especialistas tipo 3
    teste = strtok(NULL, ";");
    inf->valores[5] = atoi(teste);
    //Quantidade de especialistas tipo 4
    teste = strtok(NULL, ";");
    inf->valores[6] = atoi(teste);
    //Quantidade de especialistas tipo 5
    teste = strtok(NULL, ";");
    inf->valores[7] = atoi(teste);
    //Quantidade de especialistas tipo 6
    teste = strtok(NULL, ";");
    inf->valores[8] = atoi(teste);

    fclose(leitura);
    return inf;
}

salas* le_salas()
{
    salas* q = (salas*) malloc(sizeof(struct s_c));
    q->qtd = 0;

    FILE *csv = fopen("pacientes_320.csv", "r");
    if (!csv)
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    char linha[1024];
    int branco = 0;

    while (branco < 1)
        {
            fgets(linha, sizeof(linha), csv);
            if (strlen(linha) == 1){
                branco += 1;
            }
        }
    fgets(linha, sizeof(linha), csv);
    while (fgets(linha, sizeof(linha), csv))
        {
            if (strlen(linha) == 1){
                branco += 1;
            }
            linha[strcspn(linha, "\n")] = '\0';
            sala* p = (sala*) malloc(sizeof( struct s));
            p->id = atoi(linha);
            q->guia[q->qtd] = p;
            q->qtd ++;
            if (branco == 2){
                return q;
            }

        }
        return q;
}

hospital* ler_dados()
{
    FILE *csv = fopen("pacientes_320.csv", "r");
    if (!csv)
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }
    hospital* hosp = (hospital*)malloc(sizeof(struct hospital));;

    char linha[1024];
    int branco = 0;

    int i = 0;
    while (branco < 2)
        {
            fgets(linha, sizeof(linha), csv);
            if (strlen(linha) == 1){
                branco += 1;
                i++;
            }
        }

    hosp = (hospital*)malloc(sizeof(struct hospital));
    hosp->num_especialidades = 0;

    especialidade* e = (especialidade*)malloc(sizeof(struct especialidade));

    fgets(linha, sizeof(linha), csv);
    while(fgets(linha, sizeof(linha), csv))
        {
            medico* m = (medico*)malloc(sizeof(struct medico));
            linha[strcspn(linha, "\n")] = '\0';

            char *token = strtok(linha, ";");
            m->id = atoi(token);
            //printf("Id dos médicos: %d \n", m->id);

            token = strtok(NULL, ";");
            strncpy(m->nome, token, 30);
            //printf("Nome dos médicos: %s \n", m->nome);

            token = strtok(NULL, ";");
            strncpy(m->especialidade, token, 30);


            /*Completinho - Fragmentos funcionais


            Sobre especialidade: -> Tá funcionando bem!
            printf("-------------------------------------------------------------------- \n");
            strcpy(e->nome, m->especialidade);
            printf("Especialidade: %s \n", e->nome);
            e->medicos[e->num_medicos] = m;
            strcpy(e->medicos[e->num_medicos]->especialidade, m->especialidade);
            printf("Dr %s ",e->medicos[e->num_medicos]->nome);
            printf("Qtd: %d\n", e->num_medicos);
            e->num_medicos = e->num_medicos+1;
            printf("-------------------------------------------------------------------- \n");*/
        }
    return hosp;
}
