#include "utils.h"
#include <stdio.h>
#include <string.h>

bool escolher(char *m0, char *m1, char *m2)
{
    int opcao;
    do
    {
        printf("%s (1- %s, 2- %s): ", m0, m1, m2);
        scanf("%d", &opcao);
        getchar();

    } while ((opcao != 1) && (opcao != 2));

    if (opcao == 1)
        return true;

    return false;
}

void ler(char *input, int len)
{
    int user_input_len;
    do
    {
        if (fgets(input, len, stdin) != 0)
        {
            user_input_len = strlen(input);

            if (user_input_len > 0 && input[user_input_len - 1] != '\n')
            {
                char c;
                while ((c = getchar()) != '\n' && c != EOF)
                    user_input_len++;
            }
            if (user_input_len > len - 1)
            {
                printf("Input deve conter no máximo %d caracteres.\nDigite novamente: ", len - 1);
                sleep(SLEEP);
            }
            else
            {
                input[strcspn(input, "\n")] = 0;
                return;
            }
        }
        else
            puts("Input invalido. Digite novamente: ");
    } while (true);
}
