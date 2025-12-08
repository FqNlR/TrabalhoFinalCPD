
#ifndef CPD_SEARCH_H
#define CPD_SEARCH_H

#include <bits/ios_base.h>
#include <ios>
#include "arvores_e_organizacao.h"
#include "colors.h"

Indexador *busca_radix(Radix_node* nos, string busca, int tipo, int *numero);
Indexador *busca_color(char busca, int *numero);
Indexador *busca_value(int busca, int tipo, int *numero);
Indexador *merge(Indexador *left, Indexador *right, int *numerol, int numeror, int tipo);//retorna o valor de merge se tipo = 0 e os index que aparecem em ambos se 0

#endif //CPD_SEARCH_H
