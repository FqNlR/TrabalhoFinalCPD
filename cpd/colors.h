
#ifndef CPD_COLORS_H
#define CPD_COLORS_H

#include "defs_gerais_e_cartas.h"

#define COLOR_PATH "COLORS/"

#define UNCOLORED 0

#define RED_CHAR 'R'
#define RED 1

#define GREEN_CHAR 'G'
#define GREEN 2

#define BLUE_CHAR 'U'
#define BLUE 3

#define WHITE_CHAR 'W'
#define WHITE 4

#define BLACK_CHAR 'B'
#define BLACK 5


void color_store(string cores_carta, Indexador local);
int *color_search(int *quantas, string cores_carta);

#endif //CPD_COLORS_H