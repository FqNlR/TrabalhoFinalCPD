#include "search.h"

Indexador *merge(Indexador *left, Indexador *right, int *numerol, int numeror, int tipo){
    list<Indexador> lista_ambos;
    list<Indexador> lista_interseccao;
    int i = 0;
    int j = 0;
    while (i < *numerol && j < numeror) {
        if (left[i].id == right[j].id) {
            lista_ambos.push_back(left[i]);
            lista_interseccao.push_back(left[i]);
            j++;
            i++;
        }
        else if (left[i].id > right[j].id) {
            lista_ambos.push_back(right[j]);
            j++;
        }
        else {
            lista_ambos.push_back(left[i]);
            i++;
        }
    }
    for (i; i < *numerol; i++) {
        lista_ambos.push_back(left[i]);
    }
    for (j; j < numeror; j++) {
        lista_ambos.push_back(right[j]);
    }
    if (tipo == 0) {
        Indexador *merged = static_cast<Indexador *>(malloc(lista_ambos.size()*sizeof(Indexador)));
        i = 0;
        *numerol = lista_ambos.size();
        for (Indexador l : lista_ambos) {
            merged[i] = l;
        }
        return merged;
    }
    if (tipo == 1) {
        Indexador *merged = static_cast<Indexador *>(malloc(lista_interseccao.size()*sizeof(Indexador)));
        i = 0;
        *numerol = lista_interseccao.size();
        for (Indexador l : lista_interseccao) {
            merged[i] = l;
        }
        return merged;
    }
    Indexador *vazio = nullptr;
    *numerol = -1;
    return vazio;
}

Indexador *busca_radix(Radix_node* nos, string busca, int tipo, int *numero) {
    list<Indexador> lista;
    if (busca != "NAO") {
        nos->from_file_specific(0, busca, 0);
    }
    Radix_node *temp = nos;
    while (!temp->complete) {
        temp = temp->children.front();
    }
    lista = temp->main_index;
    Indexador *merged = static_cast<Indexador *>(malloc(lista.size()*sizeof(Indexador)));
    Indexador *help;
    int *helper;
    int i = 0;
    for (Indexador l : lista) {
        merged[i] = l;
    }
    for (Radix_node *l : nos->children) {
        help = busca_radix(l, "NAO",tipo, helper);
        merged = merge(merged, help, numero, *helper, tipo);
    }
    return merged;
}

Indexador *busca_color(char busca, int *numero) {
    list<Indexador> lista;
    Indexador aux;
    string path = COLOR_PATH;
    if (toupper(busca) == 'R') {
        path += "Red.bin";
        ifstream arquivo(path);
        if (!arquivo) {
            cerr << "ERRO AO ABRIR ARQUIVO DE CORES PARA BUSCA";
        }
        arquivo.seekg(0, arquivo.beg);
        while (!arquivo.eof()) {
            arquivo.read(reinterpret_cast<char*>(&aux), sizeof(aux));
            lista.push_back(aux);
        }
        *numero = lista.size();
        Indexador *merged = static_cast<Indexador *>(malloc(lista.size()*sizeof(Indexador)));
        int i = 0;
        for (Indexador l : lista) {
            merged[i] = l;
        }
        return merged;
    }
    if (toupper(busca) == 'G') {
        path += "Green.bin";
        ifstream arquivo(path);
        if (!arquivo) {
            cerr << "ERRO AO ABRIR ARQUIVO DE CORES PARA BUSCA";
        }
        arquivo.seekg(0, arquivo.beg);
        while (!arquivo.eof()) {
            arquivo.read(reinterpret_cast<char*>(&aux), sizeof(aux));
            lista.push_back(aux);
        }
        *numero = lista.size();
        Indexador *merged = static_cast<Indexador *>(malloc(lista.size()*sizeof(Indexador)));
        int i = 0;
        for (Indexador l : lista) {
            merged[i] = l;
        }
        return merged;
    }
    if (toupper(busca) == 'U') {
        path += "Blue.bin";
        ifstream arquivo(path);
        if (!arquivo) {
            cerr << "ERRO AO ABRIR ARQUIVO DE CORES PARA BUSCA";
        }
        arquivo.seekg(0, arquivo.beg);
        while (!arquivo.eof()) {
            arquivo.read(reinterpret_cast<char*>(&aux), sizeof(aux));
            lista.push_back(aux);
        }
        *numero = lista.size();
        Indexador *merged = static_cast<Indexador *>(malloc(lista.size()*sizeof(Indexador)));
        int i = 0;
        for (Indexador l : lista) {
            merged[i] = l;
        }
        return merged;
    }
    if (toupper(busca) == 'W') {
        path += "White.bin";
        ifstream arquivo(path);
        if (!arquivo) {
            cerr << "ERRO AO ABRIR ARQUIVO DE CORES PARA BUSCA";
        }
        arquivo.seekg(0, arquivo.beg);
        while (!arquivo.eof()) {
            arquivo.read(reinterpret_cast<char*>(&aux), sizeof(aux));
            lista.push_back(aux);
        }
        *numero = lista.size();
        Indexador *merged = static_cast<Indexador *>(malloc(lista.size()*sizeof(Indexador)));
        int i = 0;
        for (Indexador l : lista) {
            merged[i] = l;
        }
        return merged;
    }
    if (toupper(busca) == 'B') {
        path += "Black.bin";
        ifstream arquivo(path);
        if (!arquivo) {
            cerr << "ERRO AO ABRIR ARQUIVO DE CORES PARA BUSCA";
        }
        arquivo.seekg(0, arquivo.beg);
        while (!arquivo.eof()) {
            arquivo.read(reinterpret_cast<char*>(&aux), sizeof(aux));
            lista.push_back(aux);
        }
        *numero = lista.size();
        Indexador *merged = static_cast<Indexador *>(malloc(lista.size()*sizeof(Indexador)));
        int i = 0;
        for (Indexador l : lista) {
            merged[i] = l;
        }
        return merged;
    }
    if (toupper(busca) == 'D') {
        path += "Uncolored.bin";
        ifstream arquivo(path);
        if (!arquivo) {
            cerr << "ERRO AO ABRIR ARQUIVO DE CORES PARA BUSCA";
        }
        arquivo.seekg(0, arquivo.beg);
        while (!arquivo.eof()) {
            arquivo.read(reinterpret_cast<char*>(&aux), sizeof(aux));
            lista.push_back(aux);
        }
        *numero = lista.size();
        Indexador *merged = static_cast<Indexador *>(malloc(lista.size()*sizeof(Indexador)));
        int i = 0;
        for (Indexador l : lista) {
            merged[i] = l;
        }
        return merged;
    }
    Indexador *nao = nullptr;
    return nao;
}
