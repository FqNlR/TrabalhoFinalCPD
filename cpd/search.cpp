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
    list<Indexador>* lista;
    if (busca != "NAO") {
        nos->from_file_specific(0, busca, 0);
    }
    Radix_node *temp = nos;
    while (!temp->complete) {
        temp = temp->children->front();
    }
    lista = temp->main_index;
    Indexador *merged = static_cast<Indexador *>(malloc(lista->size()*sizeof(Indexador)));
    Indexador *help;
    int *helper;
    int i = 0;
    for (Indexador l : *lista) {
        merged[i] = l;
    }
    for (Radix_node *l : *nos->children) {
        help = busca_radix(l, "NAO",tipo, helper);
        merged = merge(merged, help, numero, *helper, 0);
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

Indexador *busca_value(int busca, int *numero) {
    fstream file_check, file;
    file_check.open(VALUES_PATH, ios::in);
    int aux = -1;
    while (busca != aux && !file_check.eof()) {
        file_check.read(reinterpret_cast<char*>(&aux), sizeof(aux));
    }
    if (aux != busca) {
        Indexador *ret = nullptr;
        return ret;
    }
    string num;
    itoa(busca, num.data(), 0);
    string path = VALUE_PATH;
    path += num;
    file.open(path, ios::in | ios::binary);
    list<Indexador> lista;
    while (!file.eof()) {
        Indexador aux2000;
        file.read(reinterpret_cast<char*>(&aux2000), sizeof(aux2000));
        lista.push_back(aux2000);
    }
    *numero = lista.size();
    Indexador *ret = static_cast<Indexador *>(malloc(lista.size()*sizeof(Indexador)));
    int i = 0;
    for (Indexador l : lista) {
        ret[i] = l;
        i++;
    }
    return ret;
}

Indexador *busca(string busca, int *num) {
    Indexador *ret = static_cast<Indexador *>(malloc(sizeof(Indexador)**num));
    for (int i = 0; i < *num; i++) {
        ret[i].id = busca[i];
    }
    string aux;
    aux.clear();
    for (int i = 0; i < busca.size(); i++) {
        if (isalnum(busca[i])) {
            while (isalnum(busca[i])) {
                aux += busca[i];
                i++;
                if (i == busca.size()) {
                    break;
                }
            }
            auto *no = new Radix_node();
            no->file_path = FILE_FOR_NAMES;
            int size;
            ret = merge(ret, busca_radix(no, aux, 0, &size), num, size, 1);
        }
        if (i == busca.size()) {
            break;
        }
        switch (tolower(busca[i])) {
            case SEP_COLOR:
                i++;
                if (i == busca.size()) {
                    break;
                }
                int size;
                ret = merge(ret, busca_color(busca[i], &size), num, size, 1);
                i++;
                i++;
                break;
            case SEP_TEXT:
                aux = token(busca, &i);
                if (!aux.empty()) {
                    auto *no = new Radix_node();
                    no->file_path = FILE_FOR_TEXT;
                    ret = merge(ret, busca_radix(no, aux, 0, &size), num, size, 1);
                }
                break;
            case SEP_SUB:
                aux = token(busca, &i);
                if (!aux.empty()) {
                    auto *no = new Radix_node();
                    no->file_path = FILE_FOR_SUB;
                    ret = merge(ret, busca_radix(no, aux, 0, &size), num, size, 1);
                }
                break;
            case SEP_VAL:
                aux = token(busca, &i);
                int inteiro;
                if (!aux.empty()) {
                    inteiro = atoi(aux.c_str());
                    ret = merge(ret, busca_value(inteiro, &size), num, size, 1);
                }
                break;
            case SEP_TYP:
                aux = token(busca, &i);
                if (!aux.empty()) {
                    auto *no = new Radix_node();
                    no->file_path = FILE_FOR_TYPES;
                    ret = merge(ret, busca_radix(no, aux, 0, &size), num, size, 1);
                }
                break;
            case SEP_SUPER:
                aux = token(busca, &i);
                if (!aux.empty()) {
                    auto *no = new Radix_node();
                    no->file_path = FILE_FOR_SUPER;
                    ret = merge(ret, busca_radix(no, aux, 0, &size), num, size, 1);
                }
                break;
        }
        return ret;
    }
}

void imprimir(Indexador *no, int tam) {
    list<Carta*> lista;
    for (int i = 0; i <tam; i++) {
        auto *uma = new Carta();
        no[i].from_index();
        uma->from_main_file(no[i].pos);
        lista.push_back(uma);
    }
    auto *prim = new Carta();
    prim = lista.front();
    int i = 0;
    int j = 10;
    char aux = 0;
    do {
        while (i < j) {
            auto *uma = new Carta();
            uma = lista.front();
            lista.pop_front();
            uma->print();
            if (prim == uma) {
                i = 0;
                j = j - tam;
            }
            lista.push_back(uma);
        }
        cout << i << "/" << tam << endl;
        cout<<"aperte enter para encerrar ou outra tecla para as proximas cartas(a lista e circular): "<<endl;
        while (aux == 0) {
            cin.get(aux);
        }
    }while (cin.get() != '\n'&& aux != '\n');
}

void imprimir_help() {
    cout <<"**********************************************************************************"<< endl;
    cout <<"MENSAGEM DE AJUDA"<<endl;
    cout << "Para pesquisar:"<<endl;
    cout << "Escrever uma linha de pesquisa"<<endl;
    cout << "Pesquisa por nome e feita automaticamente"<< endl;
    cout << "Pesquisa por cor: separar por ^ e digitar RGUWBD para as diferentes cores entre ^"<<endl;
    cout << "Pesquisa por tipo: separar por # e digitar um tipo entre #"<< endl;
    cout << "Pesquisa por subtipo: separar por * e digitar um subtipo entre *"<< endl;
    cout << "Pesquisa por supertipo: separar por @ e digitar um supertipo entre @"<< endl;
    cout << "Pesquisa por valor de mana: separar por & e digitar um inteiro"<< endl;
    cout << "Pesquisa por texto: separar por \" e digitar uma palavra entre \""<< endl;
    cout << "Digite 'H' para mostrar esse tutorial novamente ou enter para sair"<<endl;
}
