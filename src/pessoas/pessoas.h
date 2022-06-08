#if !defined(_PESSOAS_H)
#define _PESSOAS_H
#include "../estruturas/estruturas.h"

extern Escola escola;

/* TODO  Tirar testes */
void cadastrar_pessoa();

void exibir_dados_de_uma_pessoa();

Pessoa *buscar_pessoa();
Pessoa *buscar_professor(char *pis);

Pessoa *buscar_aluno(char *matricula);

void alterar_dados_de_pessoa();
void remover_pessoa();

#endif // _PESSOAS_H
