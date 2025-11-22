//
// Created by Jordi on 11/22/2025.
//

#ifndef CPD_STRUCT_E_PARSING_H
#define CPD_STRUCT_E_PARSING_H
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
//defines para tratar texto
#define VIRGULA ','
#define A_COLCHETE '['
#define F_COLCHETE ']'
#define A_CHAVE '{'
#define F_CHAVE '}'
#define ASPAS '"'
#define D_PONTOS ':'
#define PONTO '.'
#define CONTRA '\\'
#define ZERO '0'

//defines para as cores
#define B_NUM 0
#define B_CHAR 'B'
#define W_NUM 1
#define W_CHAR 'W'
#define R_NUM 2
#define R_CHAR 'R'
#define G_NUM 3
#define G_CHAR 'G'
#define U_NUM 4
#define U_CHAR 'U'



using namespace std;

const string entry_name = "C:/Users/Jordi/OneDrive/Documentos/GitHub/TrabalhoFinalCPD/cpd/AtomicCards.json";
const string exit_name = "sei_la.bin";
const string s_name = "name";
const string s_types = "types";
const string s_subtypes = "subtypes";
const string s_supertypes = "supertypes";
const string s_text = "text";
const string s_colors = "colors";
const string s_mana = "manaValue";
const string s_keywords = "keywords";
const string foreign_data = "foreignData";


struct Carta {
    string name;
    string text;
    int mana_value;
    bool* cores;
    int num_cores;
    string supertypes;
    string types;
    string subtypes;
    string keywords;
};

void todas_cartas();
Carta parse_carta(string s);
Carta tratar_carta(Carta c, string tipo, string escrita);
bool *tratar_cores(string s);
int tratar_mana(string s);
void guardar_carta(Carta c, ofstream &archivo);



#endif //CPD_STRUCT_E_PARSING_H