#include "tela_menu_inicial.h"
#include "../sistema_de_pessoas/tela_sistema_de_pessoas.h"
#include "../sistema_de_disciplinas/tela_sistema_de_disciplinas.h"

enum opcoes_menu_inicial
{
    SISTEMA_DE_PESSOAS = 1,
    SISTEMA_DE_DISCIPLINAS,
    SAIR_DO_SISTEMA,
};

void tela_menu_inicial()
{
    int opcao;

    do
    {
        puts("**************MENU PRINCIPAL**************");
        puts("\n(1) Sistema de Pessoas");
        puts("(2) Sistema de Disciplinas");
        puts("(3) Sair do sistema");

        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);
        getchar();
        switch (opcao)
        {
        case SISTEMA_DE_PESSOAS:
            tela_sistema_de_pessoas();
            break;
        case SISTEMA_DE_DISCIPLINAS:
            tela_sistema_de_disciplinas();
            break;
        default:
            break;
        }
    } while (opcao != 3);
}