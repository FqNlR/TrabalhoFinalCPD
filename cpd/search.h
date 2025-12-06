
#ifndef CPD_SEARCH_H
#define CPD_SEARCH_H
#include <ios>
#include <bits/ios_base.h>

#include "defs_gerais_e_cartas.h"

Indexador *busca_radix(string file_path, string busca, int tipo, int *numero);
Indexador *busca_color(char busca, int *numero);
Indexador *busca_value(int busca, int tipo, int *numero);
Indexador *merge(Indexador *left, Indexador *right, int *numero);

#endif //CPD_SEARCH_H
