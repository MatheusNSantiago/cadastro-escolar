#include "pessoas.h"
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "../utils/utils.h"

/* Padrões:
Caso seja Brasileiro, não PcD e é um aluno:
    - nome;sobrenome;0;CPF;RG;DD/MM/AAAA;0;CEP;0
Caso seja Brasileiro, PcD e é um aluno:
    - nome;sobrenome;0;CPF;RG;DD/MM/AAAA;1;LAUDO;CEP;0
Caso seja Brasileiro, não PcD e é um professor:
    - nome;sobrenome;0;CPF;RG;DD/MM/AAAA;0;CEP;1;PIS
Caso seja Brasileiro, PcD e é um professor:
    - nome;sobrenome;0;CPF;RG;DD/MM/AAAA;1;LAUDO;CEP;1;PIS
Para pessoa estrangeira altera-se apenas o terceiro, quarto e quinto elemento
ao invés de 0;CPF;RG deve ser fornecido NUMPassaporte;PaisOrigem */
void cadastrar_pessoa()
{
    Pessoa p;

    /* Designa os atributos */
    printf("Nome: ");
    ler(p.nome, 50);

    printf("Sobrenome: ");
    ler(p.sobrenome, 50);

    p.is_estrangeiro = escolher("É estrangeiro?", "sim", "não");

    if (p.is_estrangeiro)
    {
        printf("Número do passaporte: ");
        ler(p.passaporte, 50);

        printf("Páis de origem: ");
        ler(p.pais_de_origem, 50);
    }
    else
    {
        printf("CPF (apenas dígitos): ");
        ler(p.cpf, 12);

        /* Valida o CPF */
        for (int i = 0; i < strlen(p.cpf) - 1; i++)
            if (!isdigit(p.cpf[i]))
            {
                puts("\nCPF deve conter 11 digitos (sem pontos ou traços)");
                sleep(SLEEP);
                return;
            }

        printf("RG (apenas dígitos): ");
        ler(p.rg, 8);

        /* Valida o RG */
        for (int i = 0; i < strlen(p.rg) - 1; i++)
            if (!isdigit(p.rg[i]))
            {
                puts("\nRG deve conter 7 dígitos (sem pontos ou traços)");
                sleep(SLEEP);
                return;
            }
    }

    printf("Data de nascimento (DD/MM/AAAA): ");
    char tmpDate[11];
    ler(tmpDate, 11);
    sscanf(tmpDate, "%d/%d/%d", &p.nascimento.dia, &p.nascimento.mes, &p.nascimento.ano);

    p.is_pcd = escolher("É Pessoa com Deficiência?", "sim", "não");
    if (p.is_pcd)
    {
        printf("Laudo médico: ");
        ler(p.laudo_medico, 50);
    }

    printf("CEP (apenas dígitos): ");
    ler(p.cep, 9);

    /* Valida CEP */
    for (int i = 0; i < strlen(p.cep); i++)
        if (!isdigit(p.cep[i]))
        {
            puts("\nCEP deve conter 8 dígitos (sem pontos ou traços)");
            sleep(SLEEP);
            return;
        }

    p.is_professor = escolher("É professor?", "sim", "não");
    if (p.is_professor)
    {
        printf("PIS: ");
        ler(p.pis, 50);

        // Verificar se há espaço suficiente para inserir o professor
        if (qnt_professores() == MAX_PROFESSORES_ESCOLA)
        {
            puts("\nAtingiu o limite máximo (30) de professores. Voltando para o menu principal...");
            sleep(SLEEP);
            return;
        }

        /* Inserir o professor na escola */
        for (int i = 0; i < MAX_PROFESSORES_ESCOLA; i++)
            if (strlen(escola.professores[i].matricula) == 0)
            {
                escola.professores[i] = p;

                puts("\nProfessor cadastrado com sucesso!");
                sleep(SLEEP);
                return;
            }
    }
    else // Se for aluno
    {
        int qnt_alunos = qnt_alunos_escola();

        if (qnt_alunos == 0)
            strcpy(p.matricula, "22001");
        else
        {
            /* a nova matrícula vai ser a matricula do último aluno + 1  */
            char *ultima_matricula = escola.alunos[qnt_alunos - 1].matricula;
            int n_ultima_matricula = atoi(ultima_matricula);

            sprintf(p.matricula, "%d", n_ultima_matricula + 1);
        }

        // Verificar se há espaço suficiente para inserir o aluno
        if (qnt_alunos == MAX_ALUNOS_ESCOLA)
        {
            puts("\nAtingiu o limite máximo (30) de alunos. Voltando para o menu principal...");
            sleep(SLEEP);
            return;
        }

        /* Insere o aluno na escola */
        for (int i = 0; i < MAX_ALUNOS_ESCOLA; i++)
            if (strlen(escola.alunos[i].matricula) == 0)
            {
                escola.alunos[i] = p;

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
    if (p.is_estrangeiro)
    {
        puts("- Estrangeiro");
        printf("  - Passaporte: %s\n", p.passaporte);
        printf("  - País de origem: %s\n", p.pais_de_origem);
    }
    else
    {
        puts("- Brasileiro");
        printf("  - CPF: %s\n", p.cpf);
        printf("  - RG: %s\n", p.rg);
    }
    printf("- Data de Nascimento: %d/%d/%d\n", p.nascimento.dia, p.nascimento.mes, p.nascimento.ano);
    if (p.is_pcd)
    {
        puts("- Pessoa com Deficiência (PcD)");
        printf("  - Laudo médico: %s\n", p.laudo_medico);
    }

    printf("- CEP: %s\n", p.cep);
    if (p.is_professor)
    {
        puts("- Professor");
        printf("  - PIS: %s\n", p.pis);
    }
    else // É aluno
    {
        puts("- Aluno");
        printf("  - Matricula: %s\n", p.matricula);
    }

    puts("****************************************");
    printf("Aperte qualquer tecla para voltar: ");
    getchar();
}

Pessoa *buscar_pessoa()
{
    char indentificacao[50];
    Pessoa *pessoa = NULL;
    bool is_busca_por_aluno = escolher("Buscar por: ", "Aluno", "Professor");

    if (is_busca_por_aluno)
    { /* Busca por aluno */

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
    Pessoa *p;
    int opcao;

    p = buscar_pessoa();
    if (p == NULL)
    {
        puts("\nPessoa não consta na base de dados. Retornando ao menu principal...");
        sleep(SLEEP);
        return;
    }

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
                p->is_pcd = true;
            else
                p->is_pcd = false;
            strcpy(p->laudo_medico, "");
            return;
        case 2:
            printf("Código do laudo médico: ");
            ler(p->laudo_medico, sizeof(p->laudo_medico));
            return;
        case 3:
            printf("CEP: ");
            ler(p->cep, sizeof(p->cep));
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

    /* Um aluno ou professor só pode ser removido se este não está presente em nenhuma das disciplinas cadastradas */
    if (p->is_professor)
    {
        for (int i = 0; i < MAX_DISCIPLINAS_ESCOLA; i++)
        {
            Disciplina d = escola.disciplinas[i];
            if (!strcmp(d.professor.pis, p->pis))
            {
                strcpy(p->pis, "");
                puts("\nRemocação bem sucedida!");
                return;
            }
        }
        puts("\nProfessor está presente em uma ou mais disciplinas. Não é possível remover...\n");
        sleep(SLEEP);
        return;
    }
    else
    {
        for (int i = 0; i < MAX_DISCIPLINAS_ESCOLA; i++)
        {
            Disciplina d = escola.disciplinas[i];

            for (int j = 0; j < MAX_ALUNOS_DISCIPLINA; j++)
            {
                if (!strcmp(d.alunos[j].matricula, p->matricula))
                {
                    strcpy(p->matricula, "");
                    puts("\nRemocação bem sucedida!");
                    return;
                }
            }
        }
        puts("\nAluno está presente em uma ou mais disciplinas. Não é possível remover...\n");
        sleep(SLEEP);
        return;
    }
}