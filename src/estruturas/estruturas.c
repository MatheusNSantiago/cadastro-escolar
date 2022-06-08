#include "estruturas.h"
#include "../disciplina/disciplina.h"

void init_escola()
{
    for (int i = 0; i < MAX_ALUNOS_ESCOLA; i++)
        strcpy(escola.alunos[i].matricula, "");

    for (int i = 0; i < MAX_DISCIPLINAS_ESCOLA; i++)
    {
        strcpy(escola.disciplinas[i].codigo, "");

        for (int j = 0; j < MAX_ALUNOS_DISCIPLINA; j++)
        {
            strcpy(escola.disciplinas[i].alunos[j].matricula, "");
            strcpy(escola.disciplinas[i].alunos[j].pis, "");
        }
    }

    for (int i = 0; i < MAX_PROFESSORES_ESCOLA; i++)
        strcpy(escola.professores[i].pis, "");
}

int len_alunos_escola()
{
    int count = 0;
    for (int i = 0; i < MAX_ALUNOS_ESCOLA; i++)
        if (strlen(escola.alunos[i].matricula) != 0)
            count++;

    return count;
}

int len_alunos_disciplina(char *codigo)
{

    Disciplina *d = buscar_disciplina(codigo);

    if (d == NULL)
        return 0;

    int count = 0;
    for (int i = 0; i < MAX_ALUNOS_DISCIPLINA; i++)
    {
        if (strlen(d->alunos[i].matricula) != 0)
        {
            count++;
            printf("%s\n", d->alunos[i].nome);
        }
    }

    return count;
}

int len_disciplinas()
{
    int count = 0;
    for (int i = 0; i < MAX_DISCIPLINAS_ESCOLA; i++)
        if (strlen(escola.disciplinas[i].codigo) != 0)
            count++;

    return count;
}

int len_professores()
{
    int count = 0;
    for (int i = 0; i < MAX_PROFESSORES_ESCOLA; i++)
        if (strlen(escola.professores[i].pis) != 0)
            count++;

    return count;
}