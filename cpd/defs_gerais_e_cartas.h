
#ifndef CPD_DEFS_GERAIS_E_CARTAS_H
#define CPD_DEFS_GERAIS_E_CARTAS_H
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

#define ERR -1
#define ATOMIC_CARDS "AtomicCards.json"
#define MAIN_FILE "lista-das-cartas.bin"
#define INDEX_FILE "lista-dos-index.bin"
#define MAX_CARDS "MAX_CARDS"


using namespace std;


class Carta {
public:
    //variaveis
    int id;
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

    //metodos
    void print() const;//print no terminal
    void clear();//clear, auto explicativo
    int to_main_file();//escreve para o arquivo primario, retorna ERR se o arquivo falhar em abrir, retorna uma posicao em outros casos
    bool from_main_file(int where);//recebe uma posicao do arquivo e le para a carta
private:
    string aux_from_mf(fstream *file, int *n);
};

class Indexador {
    public:
    //variaveis
    int id;
    long long pos;

    //metodos
    bool to_index();
    bool from_index();
    bool to_index_f(string file_name);
};

#endif //CPD_DEFS_GERAIS_E_CARTAS_H