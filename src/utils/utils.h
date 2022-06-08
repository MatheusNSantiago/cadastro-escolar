#if !defined(_UTILS_H)
#define _UTILS_H

#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define SLEEP 0

int escolher(char *m0, char *m1, char *m2);

void ler(char *input, int len);

void extract_arguments_from_string(char **dest, char *str);
#endif // _UTILS_H
