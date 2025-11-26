//
// Created by Jordi on 11/22/2025.
//

#ifndef CPD_STRUCT_E_PARSING_H
#define CPD_STRUCT_E_PARSING_H
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cjson/cJSON.h>

#define ATOMIC_CARDS "C:/Users/Jordi/OneDrive/Documentos/GitHub/TrabalhoFinalCPD/cpd/cmake-build-debug/AtomicCards.json"
#define DATA_CARDS "data"
#define COLORS_CARDS "colors"
#define TEXT_CARDS "text"
#define TYPES_CARDS "types"
#define SUPERTYPES_CARDS "supertypes"
#define SUBTYPES_CARDS "subtypes"
#define MANA_CARDS "manaValue"
#define NOME "name"

using namespace std;

class Carta {
    public:
        int name_sz;
        string name;
        int types_sz;
        string types;
        int subtypes_sz;
        string subtypes;
        int supertype_sz;
        string supertypes;
        int text_sz;
        string text;
        int colors_sz;
        string colors;
        int mana_value;
        Carta *next;
        Carta *prev;
        void print() const;
        void clear();
};



string get_from_AtomicCards(fstream *entrada);
bool parse_carta(Carta *out, cJSON *jsonCard, int n);//checar -1 no mana_value de out para saber see o fim


#endif //CPD_STRUCT_E_PARSING_H