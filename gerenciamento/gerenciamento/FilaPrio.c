#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "FilaPrio.h"
#include "Estruturas.h"

struct paciente
{
    int id;
    int prio;
    char nome[30];
    int idade;
    int telefone;
    float peso;
    float altura;
    char sintomas[1000];
    char medicamentos[200];
    char especialista[20];
    int faltou;
    int retorno;
};

struct fila_prioridade
{
    int qtd;
    struct paciente dados[MAX];
};

FilaPrio* cria_FilaPrio()
{
    FilaPrio *fp;
    fp = (FilaPrio*) malloc(sizeof(struct fila_prioridade));
    if (fp != NULL)
    {
        fp->qtd = 0;
    }

    return fp;
}

void libera_FilaPrio(FilaPrio* fp)
{
    free(fp);
}

int estaCheia_FilaPrio(FilaPrio* fp)
{
    if(fp == NULL)
        return -1;
    return(fp->qtd == MAX);
}

int estaVazia_FilaPrio(FilaPrio* fp)
{
    if(fp == NULL){
        return -1;
    }
    return (fp->qtd == 0);
}

void promoverElemento(FilaPrio* fp, int filho)
{
    int pai;
    struct paciente temp;
    pai = filho-1 / 2;
    while((filho > 0) && (fp->dados[pai].prio <= fp->dados[filho].prio))
    {
        temp = fp->dados[filho];
        fp->dados[filho] = fp->dados[pai];
        fp->dados[pai] = temp;

        filho = pai;
        pai = (pai-1)/2;
    }
}

int insere_FilaPrio(FilaPrio* fp,char* nome, int ID, int prio, int idade, int telefone,  float peso, float altura, char* sintomas, char* medicamentos, char* especialista)
{
    if(fp == NULL)
        return 0;
    if(fp->qtd == MAX)
        return 0;

    strcpy(fp->dados[fp->qtd].nome, nome);
    strcpy(fp->dados[fp->qtd].sintomas, sintomas);
    strcpy(fp->dados[fp->qtd].medicamentos, medicamentos);
    strcpy(fp->dados[fp->qtd].especialista, especialista);
    fp->dados[fp->qtd].prio = prio;
    fp->dados[fp->qtd].id = ID;
    fp->dados[fp->qtd].idade = idade;
    fp->dados[fp->qtd].telefone = telefone;
    fp->dados[fp->qtd].peso = peso;
    fp->dados[fp->qtd].altura = altura;
    fp->dados[fp->qtd].faltou = 0;
    fp->dados[fp->qtd].retorno = rand() % 31;

    promoverElemento(fp, fp->qtd);
    fp->qtd++;
    return 1;
}

void rebaixarElemento(FilaPrio* fp, int pai)
{
    struct paciente temp;
    int filho = 2 * pai + 1;
    while(filho < fp->qtd)
    {
        if(filho < fp->qtd-1)
            if(fp->dados[filho].prio < fp->dados[filho+1].prio)
                filho++;

        if(fp->dados[pai].prio >= fp->dados[filho].prio)
            break;

        temp = fp->dados[pai];
        fp->dados[pai] = fp->dados[filho];
        fp->dados[filho] = temp;

        pai = filho;
        filho = 2 * pai + 1;
    }
}

int remove_FilaPrio(FilaPrio* fp)
{
    if(fp == NULL)
        return 0;
    if(fp->qtd == 0)
        return 0;

    fp->qtd--;
    fp->dados[0] = fp->dados[fp->qtd];
    rebaixarElemento(fp, 0);
    return 1;

}

int consulta_FilaPrio(FilaPrio* fp, char* nome, int* id,char* especialista)
{
    if(fp == NULL || fp->qtd == 0)
        return 0;
    strcpy(nome, fp->dados[0].nome);
    strcpy(especialista, fp->dados[0].especialista);
    id = &fp->dados[0].id;
    return 1;
}


struct infoarc *leitura_valores();

FilaPrio* recebe_pacientes();

int main ()
{
	setlocale(LC_ALL,"Portuguese");

	//Criando a fila de prioridade com os pacientes!
	FilaPrio* fp = cria_FilaPrio();
	fp = recebe_pacientes();

    //Recebendo valores de parâmetro!

    infoarc* info = info_arq();

    hospital* hosp = ler_dados();


    for (int i = 0; i < info->valores[0]; i++){
        printf("Nome do paciente: %s ID: %d\nPrioridade - %d\nRetorno: %d\n\n",fp->dados[i].nome,fp->dados[i].id ,fp->dados[i].prio, fp->dados[i].retorno);
    }

    salas* p = le_salas();

    for (int i = 0; i < info->valores[1]; i++){
        printf("%d \n", p->guia[i]->id);
    }


	remove_FilaPrio(fp);


	system("pause");
	return 0;
}

//Você adiciona todos os valores de pacientes em uma fila!
FilaPrio* recebe_pacientes()
{
    //struct infoarc* info = leitura_valores();
    FilaPrio* fp;
    FILE *csv = fopen("pacientes_320.csv", "r");
    if (!csv)
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    fp = cria_FilaPrio();

    char linha[1024];
    int id, prio, idade, faltou;
    int telefone;
    float altura, peso;
    char nome[60], sintomas[100], medicamentos[100], especialista[30];

    //Pular primeira linha
    fgets(linha, sizeof(linha), csv);

    while (fgets(linha, sizeof(linha), csv))
    {
        // Limpar quebra de linha ao final

        if(strlen(linha) == 1){
            return fp;
        }

        linha[strcspn(linha, "\n")] = '\0';

        // Separar os campos usando strtok
        char *token = strtok(linha, ";");
        id = atoi(token);

        token = strtok(NULL, ";");
        prio = atoi(token);

        token = strtok(NULL, ";");
        strncpy(nome, token, sizeof(nome));

        token = strtok(NULL, ";");
        idade = atoi(token);

        token = strtok(NULL, ";");
        telefone = atoi(token);

        token = strtok(NULL, ";");
        altura = atof(token);

        token = strtok(NULL, ";");
        peso = atof(token);

        token = strtok(NULL, ";");
        strncpy(sintomas, token, sizeof(sintomas));

        token = strtok(NULL, ";");
        strncpy(medicamentos, token, sizeof(medicamentos));

        token = strtok(NULL, ";");
        strncpy(especialista, token, sizeof(especialista));

        token = strtok(NULL, ";");
        faltou = atoi(token);
        insere_FilaPrio(fp, nome, id, prio, idade, telefone, peso, altura, sintomas, medicamentos, especialista);
    }
    fclose(csv);
    return fp;
}

