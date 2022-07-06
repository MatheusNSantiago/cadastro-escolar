#if !defined(_ESTRUTURAS_H)
#define _ESTRUTURAS_H
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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

    bool is_estrangeiro;
    char cpf[12];            // caso seja brasileiro
    char rg[8];             // caso seja brasileiro
    char passaporte[50];     // caso seja estrangeiro
    char pais_de_origem[50]; // caso seja estrangeiro

    Data nascimento;
    bool is_pcd;
    char laudo_medico[1000]; // caso seja pcd

    char cep[9];

    bool is_professor;
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
int qnt_alunos_escola();
int qnt_alunos_disciplina(char *codigo);
int qnt_disciplinas();
int qnt_professores();

#endif // _ESTRUTURAS_H
