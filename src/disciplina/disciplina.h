#if !defined(_DISCIPLINA_H)
#define _DISCIPLINA_H
#include "../estruturas/estruturas.h"

extern Escola escola;

/*
Recebe o seguinte padrão de entrada: "código;nome;carga;PIS"
- Caso não exista este professor, deve-se exibir uma mensagem de erro, e voltar ao menu principal.
- Caso já exista esta disciplina, ou exceda o máximo de disciplinas, deve-se exibir uma mensagem de erro e voltar ao menu principal.
*/
void cadastrar_disciplina();

/* Receber do usuário o código da disciplina e o PIS do novo professor desta disciplina. */
void alterar_professor_de_uma_disciplina();

/* Receber do usuário o código da disciplina e o número de matrícula do aluno a ser integrante da turma (um aluno não pode se matricular mais de uma vez na mesma turma e deve já ter sido cadastrado pelo sistema). */
void adicionar_um_aluno_a_uma_disciplina();

/* recebe do usuário o código da disciplina e o número de matrícula do aluno a ser removido da disciplina */
void remover_aluno_de_uma_disciplina();

/*
Receber do usuário o código da disciplina e então deve ser exibido:
- Código da Disciplina;
- Nome da Disciplina;
- Nome do Professor;
- Matrícula e nome de cada aluno da disciplina (um por linha)
 */
void exibir_dados_de_uma_disciplina();

void voltar_ao_menu_principal();

/* |────────────────────────────||────────────────────────────||────────────────────────────| */

Disciplina *buscar_disciplina(char *codigo);

void append_aluno_disciplina(Disciplina *d, Pessoa *aluno);

void append_disciplina(Disciplina d);

#endif // _DISCIPLINA_H
