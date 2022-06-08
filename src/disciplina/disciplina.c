#include "disciplina.h"
#include "../pessoas/pessoas.h"
#include "../utils/utils.h"

void cadastrar_disciplina()
{
    char *args[11], padrao[400];
    Disciplina d, aux;

    // printf("Dados: ");
    // ler(padrao, sizeof(padrao));
    strcpy(padrao, "cod;nome;1;p");
    puts(padrao);

    extract_arguments_from_string(args, padrao);

    strcpy(d.codigo, args[0]);

    /* Verifica se excedeu o limite de disciplinas e se a disciplina já consta na base de dados */
    bool tem_vaga = false, e_duplicada = false;
    for (int i = 0; i < MAX_DISCIPLINAS_ESCOLA; i++)
    {
        aux = escola.disciplinas[i];

        if (strlen(aux.codigo) == 0)
            tem_vaga = true;
        if (aux.codigo == d.codigo)
            e_duplicada = true;
    }
    if (!tem_vaga)
    {
        puts("\nO limite máximo de 5 disciplinas já foi alcançado...");
        sleep(SLEEP);
        return;
    }
    if (e_duplicada)
    {
        puts("\nJá existe uma disciplina com o mesmo código...");
        sleep(SLEEP);
        return;
    }

    strcpy(d.nome, args[1]);
    d.carga_horaria = atoi(args[2]);

    if (buscar_professor(args[3]))
        d.professor = *buscar_professor(args[3]);
    else
    {
        puts("\nProfessor não consta na base de dados...");
        sleep(SLEEP);
        return;
    }

    /* Inserir disciplina */
    append_disciplina(d);

    // puts("\nDisciplina cadastrada com sucesso.");
    sleep(SLEEP);
}

void alterar_professor_de_uma_disciplina()
{
    char pis[50], codigo[50];
    Pessoa *prof;
    Disciplina *disc;

    printf("Código da disciplina: ");
    ler(codigo, sizeof(codigo));

    disc = buscar_disciplina(codigo);
    if (disc == NULL)
    {
        puts("\nDisciplina não consta na base de dados...");
        sleep(SLEEP);
        return;
    }

    printf("PIS do novo professor: ");
    ler(pis, sizeof(pis));

    prof = buscar_professor(pis);
    if (prof == NULL)
    {
        puts("\nPIS não consta na base de dados...");
        sleep(SLEEP);
        return;
    }

    (*disc).professor = *prof;

    puts("\nO professor foi alterado com sucesso!");
    sleep(SLEEP);
}

void adicionar_um_aluno_a_uma_disciplina()
{
    char matricula[50], codigo[50];
    Pessoa *aluno;
    Disciplina *disciplina;

    // printf("Matricula do aluno: ");
    // ler(matricula, sizeof(matricula));
    strcpy(matricula, "m");

    aluno = buscar_aluno(matricula);
    /* Confere se o aluno existe */
    if (aluno == NULL)
    {
        puts("\nO aluno não consta na base de dados...");
        sleep(SLEEP);
        return;
    }

    // printf("Código da disciplina: ");
    // ler(codigo, sizeof(codigo));
    strcpy(codigo, "cod");

    disciplina = buscar_disciplina(codigo);
    /* Confere se a disciplina existe */
    if (disciplina == NULL)
    {
        puts("\nCódigo da disciplina não consta na base de dados...");
        sleep(SLEEP);
        return;
    }

    /* Confere se o número de alunos para a disciplina foi execedido */
    if (len_alunos_disciplina(codigo) == MAX_ALUNOS_DISCIPLINA)
    {
        puts("\nA disciplina já está em sua capacidade máxima de 10 alunos...");
        sleep(SLEEP);
        return;
    }

    /* Confere se o aluno já está cadastrado na disciplina */
    for (int i = 0; i < MAX_ALUNOS_DISCIPLINA; i++)
        if (strcmp(disciplina->alunos[i].matricula, matricula) == 0)
        {
            puts("\nO Aluno já está cadastrado nessa disciplina...");
            sleep(SLEEP);
            return;
        }

    /* Insere o aluno na disciplina */
    append_aluno_disciplina(disciplina, aluno);

    puts("\nAluno foi adicionado a disciplina com sucesso!");
    return;
}

void remover_aluno_de_uma_disciplina()
{
    char codigo[50], matricula[50];
    Pessoa *aluno;
    Disciplina *disciplina;

    printf("Matricula do aluno: ");
    ler(matricula, sizeof(matricula));

    /* Confere se o aluno existe */
    aluno = buscar_aluno(matricula);
    if (aluno == NULL)
    {
        puts("\nO aluno não consta na base de dados...");
        sleep(SLEEP);
        return;
    }

    printf("Código da disciplina: ");
    ler(codigo, sizeof(codigo));

    disciplina = buscar_disciplina(codigo);

    /* Confere se a disciplina existe */
    if (disciplina == NULL)
    {
        puts("\nCódigo da disciplina não consta na base de dados...");
        sleep(SLEEP);
        return;
    }

    /* Confere se a disciplina não está vazia */
    if (len_alunos_disciplina(codigo) == 0)
    {
        puts("\nEssa disciplina não possui nenhum aluno...");
        sleep(SLEEP);
        return;
    }

    /* Remove o aluno da disciplina */
    for (int i = 0; i < MAX_ALUNOS_DISCIPLINA; i++)
        if (strcpy((*disciplina).alunos[i].matricula, matricula) == 0)
        {
            puts("\nAluno removido da disciplina com sucesso!");
            sleep(SLEEP);
            return;
        }

    /* Se o código chegou até aqui, significa que o aluno não está presente na disciplina */
    puts("\nO aluno não está cadastrado na disciplina...");
    sleep(SLEEP);
    return;
}

void exibir_dados_de_uma_disciplina()
{
    char codigo[50];
    Disciplina *disciplina, d;

    printf("Código da disciplina: ");
    ler(codigo, sizeof(codigo));

    disciplina = buscar_disciplina(codigo);

    if (disciplina == NULL)
    {
        puts("\nO código da disciplina não consta na base de dados...");
        sleep(SLEEP);
        return;
    }

    d = *disciplina;

    puts("\n****************************************");
    printf("- Código da disciplina: %s\n", d.codigo);
    printf("- Disciplina: %s\n", d.nome);
    printf("- Professor: %s %s\n", d.professor.nome, d.professor.sobrenome);
    puts("- Alunos:");

    int qnt_alunos = len_alunos_disciplina(d.codigo);
    if (qnt_alunos > 0)
        for (int i = 0; i < qnt_alunos; i++)
            printf("  - %s (%s)\n", d.alunos[i].nome, d.alunos[i].matricula);

    puts("****************************************");
    printf("Aperte qualquer tecla para voltar: ");
    getchar();
}

Disciplina *buscar_disciplina(char *codigo)
{
    Disciplina *d = NULL;

    for (int i = 0; i < MAX_DISCIPLINAS_ESCOLA; i++)
    {
        if (strcmp(escola.disciplinas[i].codigo, codigo) == 0)
            d = &escola.disciplinas[i];
    }

    return d;
}

void append_aluno_disciplina(Disciplina *d, Pessoa *aluno)
{
    for (int i = 0; i < MAX_ALUNOS_DISCIPLINA; i++)
        if (strlen(d->alunos[i].matricula) == 0)
        {
            d->alunos[i] = *aluno;
            return;
        }
}

void append_disciplina(Disciplina d)
{
    /* Inicia os alunos como vazio (len 0) */
    for (int i = 0; i < MAX_ALUNOS_DISCIPLINA; i++)
        strcpy(d.alunos[i].matricula, "");

    for (int i = 0; i < MAX_DISCIPLINAS_ESCOLA; i++)
        if (strlen(escola.disciplinas[i].codigo) == 0)
        {
            escola.disciplinas[i] = d;
            return;
        }
}