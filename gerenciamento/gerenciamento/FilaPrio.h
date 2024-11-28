#ifndef FILAPRIO_H_INCLUDED
#define FILAPRIO_H_INCLUDED
#define MAX 1000

typedef struct fila_prioridade FilaPrio;

FilaPrio* cria_FilaPrio();
void libera_FilaPrio(FilaPrio* fp);
int consulta_FilaPrio(FilaPrio* fp, char* nome, int* id,char* especialista);
int insere_FilaPrio(FilaPrio* fp,char* nome, int ID, int prio, int idade, int telefone,  float peso, float altura, char* sintomas, char* medicamentos, char* especialista);
int remove_FilaPrio(FilaPrio* fp);
int tamanho_FilaPrio(FilaPrio* fp);
int estaCheia_FilaPrio(FilaPrio* fp);
int estaVazia_FilaPrio(FilaPrio* fp);
FilaPrio* recebe_pacientes();

//Declaração completa :D

#endif // FILAPRIO_H_INCLUDED
