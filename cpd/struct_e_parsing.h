//
// Created by Jordi on 11/22/2025.
//

#ifndef CPD_STRUCT_E_PARSING_H
#define CPD_STRUCT_E_PARSING_H
#include "defs_gerais_e_cartas.h"
#include <cjson/cJSON.h>


#define DATA_CARDS "data"
#define COLORS_CARDS "colors"
#define TEXT_CARDS "text"
#define TYPES_CARDS "types"
#define SUPERTYPES_CARDS "supertypes"
#define SUBTYPES_CARDS "subtypes"
#define MANA_CARDS "manaValue"
#define NOME "name"



string get_from_AtomicCards(fstream *entrada);
bool parse_carta(Carta *out, cJSON *jsonCard, int n);//checar -1 no mana_value de out para saber see o fim


#endif //CPD_STRUCT_E_PARSING_H