
#ifndef CPD_ARVORES_E_ORGANIZACAO_H
#define CPD_ARVORES_E_ORGANIZACAO_H

#include <list>
#include <cctype>
#include "defs_gerais_e_cartas.h"

#define FILE_FOR_NAMES "NAMES/TREE.bin"
#define NAMES 0
#define FILE_FOR_TYPES "TYPES/TREE.bin"
#define TYPES 1
#define FILE_FOR_SUB "SUBTYPES/TREE.bin"
#define SUBTYPES 2
#define FILE_FOR_SUPER "SUPERTYPES/TREE.bin"
#define SUPERTYPES 3
#define FILE_FOR_TEXT "TEXT/TREE.bin"
#define TEXT 4

class Radix_node {
public:
    //variaveis
    bool complete;
    bool leaf;
    bool root;
    char letra;
    int child_number;
    string file_path;
    int where_father;
    Radix_node *parent;
    int str_sz;
    string str;
    list<int> children_list;
    list<Radix_node *> children;
    list<Indexador> main_index;

    //metodos
    void clear();
    bool to_file(string file_path, int father);//coloca no arquivo denotado por file path a arvore completa ao ser usado no head e desaloca
    void from_file(int loc);//tira uma arvore completa do arquivo em file path, se torna o root ao usar is_root = true
    bool add_to_tree(Indexador find_later, string what, int pos);

    private:
    void aux_to_father(int son, int child, int where, fstream *file);//volta no arquivo e informa a posicao do nodo ao nodo pai
};

string token(string str, int *loc);
void add_to_all_radix(Radix_node *all, Carta what, Indexador where);
void delete_old_create_new();


#endif //CPD_ARVORES_E_ORGANIZACAO_H