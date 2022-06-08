#include "tela_sistema_de_disciplinas.h"
#include "../../disciplina/disciplina.h"

enum opcoes_sistema_de_pessoas
{
    CADASTRAR_DISCIPLINA = 1,
    ALTERAR_PROFESSOR_DE_UMA_DISCIPLINA,
    ADICIONAR_UM_ALUNO_A_UMA_DISCIPLINA,
    REMOVER_UM_ALUNO_DE_UMA_DISCIPLINA,
    EXIBIR_DADOS_DE_UMA_DISCIPLINA,
    VOLTAR_AO_MENU_PRINCIPAL,
};

void tela_sistema_de_disciplinas(Escola *escola)
{
    int opcao;

    do
    {
        puts("\n**************SISTEMA DE DISCIPLINAS**************");
        puts("\n(1) Cadastrar disciplina");
        puts("(2) Alterar professor de uma disciplina");
        puts("(3) Adicionar um aluno a uma disciplina");
        puts("(4) Remover um aluno de uma disciplina");
        puts("(5) Exibir dados de uma disciplina");
        puts("(6) Voltar ao menu principal");

        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case CADASTRAR_DISCIPLINA:
            cadastrar_disciplina();
            break;
        case ALTERAR_PROFESSOR_DE_UMA_DISCIPLINA:
            alterar_professor_de_uma_disciplina();
            break;
        case ADICIONAR_UM_ALUNO_A_UMA_DISCIPLINA:
            adicionar_um_aluno_a_uma_disciplina();
            break;
        case REMOVER_UM_ALUNO_DE_UMA_DISCIPLINA:
            remover_aluno_de_uma_disciplina();
            break;
        case EXIBIR_DADOS_DE_UMA_DISCIPLINA:
            exibir_dados_de_uma_disciplina();
            break;
        case VOLTAR_AO_MENU_PRINCIPAL:
            return;
        default:
            break;
        }
    } while (1);
}