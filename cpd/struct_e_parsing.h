//
// Created by Jordi on 11/22/2025.
//

#ifndef CPD_STRUCT_E_PARSING_H
#define CPD_STRUCT_E_PARSING_H
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

#define VIRGULA ','
#define A_COLCHETE '['
#define F_COLCHETE ']'
#define A_CHAVE '{'
#define F_CHAVE '}'
#define ASPAS '"'
#define D_PONTOS ':'

using namespace std;

const string entry_name = "";

struct Carta {
    string name;
    string text;
    char cores[6];
    string supertypes;
    string types;
    string subtypes;
};

Carta *todas_cartas();
Carta parse_carta(string s);
Carta tratar_carta(Carta c, string tipo, string escrita);
void guardar_carta(Carta c, ofstream &archivo);



#endif //CPD_STRUCT_E_PARSING_H