#include "pessoas.h"
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "../utils/utils.h"

void cadastrar_pessoa()
{
    Pessoa p;
    char *args[11];
    char padrao[400];

    /* Recebe o padrão como input */

    printf("Dados: ");

    int i;
    scanf("%d", &i);
    getchar();

    if (i == 1)
        strcpy(padrao, "Daniel;Saad;1;Passaporte;Chile;10/12/1984;0;1234;1;p");
    else
        strcpy(padrao, "matheus;santiago;0;14163386750;3950638;19/07/1999;1;laudo medico;71015112;0;m");
    puts(padrao);

    // ler(padrao, sizeof(padrao));

    extract_arguments_from_string(args, padrao);

    // /* TODO error handling - enforçar digitação correta dos argumentos */

    /* Designa os atributos */
    strncpy(p.nome, args[0], sizeof(p.nome) - 1);
    strncpy(p.sobrenome, args[1], sizeof(p.sobrenome) - 1);
    p.brasileiro_ou_estrangeiro = atoi(args[2]);
    if (p.brasileiro_ou_estrangeiro == 0) // Se for brasileiro
    {
        strncpy(p.cpf, args[3], sizeof(p.cpf) - 1);
        strncpy(p.rg, args[4], sizeof(p.rg) - 1);
    }
    else
    {
        strncpy(p.passaporte, args[3], sizeof(p.passaporte) - 1);
        strncpy(p.pais_de_origem, args[4], sizeof(p.pais_de_origem) - 1);
    }

    sscanf(args[5], "%d/%d/%d", &p.nascimento.dia, &p.nascimento.mes, &p.nascimento.ano);

    p.é_pcd = atoi(args[6]);
    if (p.é_pcd) // Se for pessoa com deficiência
        strncpy(p.laudo_medico, args[7], sizeof(p.laudo_medico) - 1);

    strncpy(p.cep, args[7 + p.é_pcd], sizeof(p.cep) - 1);

    p.aluno_ou_professor = atoi(args[8 + p.é_pcd]);
    if (p.aluno_ou_professor == 0) // Se for alluno
        strncpy(p.matricula, args[9 + p.é_pcd], sizeof(p.matricula) - 1);
    else
        strncpy(p.pis, args[9 + p.é_pcd], sizeof(p.pis) - 1);

    // Verificar se há espaço suficiente para inserir o aluno/professor
    if (p.aluno_ou_professor == 0)
    {
        if (len_alunos_escola() == MAX_ALUNOS_ESCOLA)
        {
            puts("\nAtingiu o limite máximo (30) de alunos. Voltando para o menu principal...");
            sleep(SLEEP);
            return;
        }

        for (int i = 0; i < MAX_ALUNOS_ESCOLA; i++)
            if (strlen(escola.alunos[i].matricula) == 0)
            {
                escola.alunos[i] = p;

                // puts("\nAluno cadastrado com sucesso!");
                sleep(SLEEP);
                return;
            }
    }
    else
    {
        if (len_professores() == MAX_PROFESSORES_ESCOLA)
        {
            puts("\nAtingiu o limite máximo (5) de professores. Voltando para o menu principal...");
            sleep(SLEEP);
            return;
        }

        for (int i = 0; i < 5; i++)
            if (strlen(escola.professores[i].matricula) == 0)
            {
                escola.professores[i] = p;

                // puts("\nProfessor cadastrado com sucesso!");
                sleep(SLEEP);
                return;
            }
    }
}

void exibir_dados_de_uma_pessoa()
{

    Pessoa *pessoa = buscar_pessoa();

    if (pessoa == NULL)
    {
        puts("\nNão consta na base de dados. Retornando ao menu principal...");
        sleep(SLEEP);
        return;
    }

    Pessoa p = *pessoa;

    puts("\n****************************************");
    printf("- Nome: %s\n", p.nome);
    printf("- Sobrenome: %s\n", p.sobrenome);
    if (p.brasileiro_ou_estrangeiro == 0)
    {
        puts("- Brasileiro");
        printf("  - CPF: %s\n", p.cpf);
        printf("  - RG: %s\n", p.rg);
    }
    else
    {
        puts("- Extrangeiro");
        printf("  - Passaporte: %s\n", p.passaporte);
        printf("  - País de origem: %s\n", p.pais_de_origem);
    }
    printf("- Data de Nascimento: %d/%d/%d\n", p.nascimento.dia, p.nascimento.mes, p.nascimento.ano);
    if (p.é_pcd == 1)
    {
        puts("- Pessoa com Deficiência (PcD)");
        printf("  - Laudo médico: %s\n", p.laudo_medico);
    }

    printf("- CEP: %s\n", p.cep);
    if (p.aluno_ou_professor == 0)
    {
        puts("- Aluno");
        printf("  - Matricula: %s\n", p.matricula);
    }
    else
    {
        puts("- Professor");
        printf("  - PIS: %s\n", p.pis);
    }

    puts("****************************************");
    printf("Aperte qualquer tecla para voltar: ");
    getchar();
}

Pessoa *buscar_pessoa()
{
    char indentificacao[50];
    Pessoa *pessoa = NULL;

    if (escolher("Alvo: ", "Aluno", "Professor") == 0)
    { /* Busca por aluno */

        /* TODO Formato da matricula escolar => 22 (Ano) + 001 (id do primeiro aluno cadastrado)  */
        printf("Número da matrícula escolar: ");
        scanf("%50s", indentificacao);
        getchar();

        pessoa = buscar_aluno(indentificacao);
    }
    else
    { /* Busca por professor */

        /* TODO O PIS deve seguir o padrão oficial, atualmente utilizado. */
        printf("Número do Programa de Integração Social (PIS): ");
        scanf("%50s", indentificacao);
        getchar();

        pessoa = buscar_professor(indentificacao);
    }

    return pessoa;
}

Pessoa *buscar_professor(char *pis)
{
    Pessoa *professor = NULL;

    for (int i = 0; i < 5; i++)
    {
        char *_pis = escola.professores[i].pis;
        if (strlen(_pis) != 0 && strcmp(pis, _pis) == 0)
            professor = &(escola.professores[i]);
    }
    return professor;
}

Pessoa *buscar_aluno(char *matricula)
{
    Pessoa *aluno = NULL;

    for (int i = 0; i < MAX_ALUNOS_ESCOLA; i++)
    {
        char *_matricula = escola.alunos[i].matricula;
        if ((strlen(_matricula) != 0) && (strcmp(matricula, _matricula) == 0))
            aluno = &(escola.alunos[i]);
    }

    return aluno;
}

void alterar_dados_de_pessoa()
{
    Pessoa *aux_p, p;
    int opcao;

    aux_p = buscar_pessoa();
    if (aux_p == NULL)
    {
        puts("\nPessoa não consta na base de dados. Retornando ao menu principal...");
        sleep(SLEEP);
        return;
    }

    p = *aux_p;
    do
    {
        puts("\n(1) Alterar pessoa com deficiência (PcD);");
        puts("(2) Alterar código do laudo médico;");
        puts("(3) Alterar CEP;");
        puts("(4) Voltar");

        printf("\nEscolha uma das opções: ");
        scanf("%d", &opcao);
        getchar();
        switch (opcao)
        {
        case 1:
            if (escolher("É pessoa com deficiência (PcD)?", "Sim", "Não"))
                p.é_pcd = true;
            else
                p.é_pcd = false;
            return;
        case 2:
            printf("Código do laudo médico: ");
            ler(p.laudo_medico, sizeof(p.laudo_medico));
            return;
        case 3:
            printf("CEP: ");
            ler(p.cep, sizeof(p.cep));
            return;
        case 4:
            puts("\nVoltando...");
            sleep(SLEEP);
            return;
        default:
            break;
        }
    } while (true);
}

void remover_pessoa()
{
    Pessoa *p = buscar_pessoa();

    if (p == NULL)
    {
        puts("\nPessoa não consta na base de dados...");
        sleep(SLEEP);
        return;
    }

    if ((*p).aluno_ou_professor == 0)
        strcpy(p->matricula, "");
    else
        strcpy(p->pis, "");

    puts("\nRemocação bem sucedida!");
}