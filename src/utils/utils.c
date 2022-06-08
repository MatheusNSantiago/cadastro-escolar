#include "utils.h"
#include <stdio.h>
#include <string.h>

int escolher(char *m0, char *m1, char *m2)
{
    int opcao;
    do
    {
        printf("%s (0- %s, 1- %s): ", m0, m1, m2);
        scanf("%d", &opcao);
        getchar();

    } while ((opcao != 0) && (opcao != 1));

    return opcao;
}

void ler(char *input, int len)
{
    do
    {
        if (fgets(input, len, stdin))

            if (sscanf(input, "%[^\n]s", input) == 1)
                return;
        printf("Input inválido. Digite novamente: ");
    } while (true);
}

void extract_arguments_from_string(char **dest, char *str)
{
    char *token = strtok(str, ";");
    for (int arg_count = 0; token != NULL; arg_count++)
    {
        dest[arg_count] = token;
        token = strtok(NULL, ";");
    }
}