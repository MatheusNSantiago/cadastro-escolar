#if !defined(_ESTRUTURAS_H)
#define _ESTRUTURAS_H
#include <stdio.h>
#include <string.h>

#define MAX_ALUNOS_DISCIPLINA 5
#define MAX_ALUNOS_ESCOLA 30
#define MAX_PROFESSORES_ESCOLA 30
#define MAX_DISCIPLINAS_ESCOLA 5


typedef struct data
{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct pessoa
{
    char nome[50];
    char sobrenome[50];

    int brasileiro_ou_estrangeiro;
    char cpf[50];            // caso seja brasileiro
    char rg[50];             // caso seja brasileiro
    char passaporte[50];     // caso seja estrangeiro
    char pais_de_origem[50]; // caso seja estrangeiro

    Data nascimento;

    int é_pcd;
    char laudo_medico[11]; // caso seja pcd

    char cep[50];

    int aluno_ou_professor;
    char matricula[50]; // caso seja aluno
    char pis[50];       // caso seja professor (número do programa de integração social)
} Pessoa;

typedef struct disciplina
{
    char codigo[50];
    char nome[50];
    int carga_horaria;
    Pessoa professor;
    Pessoa alunos[MAX_ALUNOS_DISCIPLINA];
} Disciplina;

typedef struct escola
{
    Pessoa alunos[MAX_ALUNOS_ESCOLA];
    Pessoa professores[MAX_PROFESSORES_ESCOLA];
    Disciplina disciplinas[MAX_DISCIPLINAS_ESCOLA];
} Escola;

/* |────────────────────────────||────────────────────────────||────────────────────────────| */

extern Escola escola;

void init_escola();
int len_alunos_escola();
int len_alunos_disciplina(char *codigo);
int len_disciplinas();
int len_professores();

#endif // _ESTRUTURAS_H
