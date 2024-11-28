#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED
#define LIM 200


typedef struct medico
{
    int id;
    char nome[50];
    char especialidade[20];
    int horas_trab;

}medico;

typedef struct especialidade
{
    char nome[30];
    medico* medicos[LIM];
    int num_medicos;
}especialidade;

typedef struct hospital
{
    especialidade* especialidades [LIM];
    int num_especialidades;
}hospital;

typedef struct s sala;
struct s
{
    int id;
    int medico_id;
    int horarios[10];

};

typedef struct s_c salas;

struct s_c{
    int qtd;
    sala* guia[LIM];
};

typedef struct info infoarc;

struct info
{
    int valores[10];
};

typedef struct sem semana;

infoarc* info_arq();
sala* cria_sala();
void compara_M_S(infoarc* p);
salas* le_salas();
hospital* ler_dados();



#endif // ESTRUTURAS_H_INCLUDED
