#include "tela_sistema_de_pessoas.h"

enum opcoes_sistema_de_pessoas
{
    CADASTRAR_PESSOA = 1,
    EXIBIR_DADOS_DE_UMA_PESSOA,
    ALTERAR_DADOS_DE_PESSOA,
    REMOVER_PESSOA,
    VOLTAR_AO_MENU_ANTERIOR,
};

void tela_sistema_de_pessoas()
{
    int opcao;

    do
    {
        puts("\n**************SISTEMA DE PESSOAS**************");
        puts("\n(1) Cadastrar pessoa");
        puts("(2) Exibir dados de uma pessoa");
        puts("(3) Alterar dados de pessoa");
        puts("(4) Remover pessoa");
        puts("(5) Voltar ao menu anterior");

        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case CADASTRAR_PESSOA:
            cadastrar_pessoa();
            break;
        case EXIBIR_DADOS_DE_UMA_PESSOA:
            exibir_dados_de_uma_pessoa();
            break;
        case ALTERAR_DADOS_DE_PESSOA:
            alterar_dados_de_pessoa();
            break;
        case REMOVER_PESSOA:
            remover_pessoa();
            break;
        case VOLTAR_AO_MENU_ANTERIOR:
            printf("\n");
            return;
        default:
            break;
        }
    } while (1);
}