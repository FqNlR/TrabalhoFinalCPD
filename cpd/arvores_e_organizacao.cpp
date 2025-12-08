#include "arvores_e_organizacao.h"

#include "colors.h"

void Radix_node::clear() {
    this->complete = false;
    this->leaf = false;
    this->root = false;
    this->parent = nullptr;
    this->child_number = -1;
    this->where_father = -1;
    this->str_sz = 0;
    this->str = "";
    this->children = *new list<Radix_node*>;
    this->children_list = *new list<int>;
    this->main_index = *new list<Indexador>;
}

bool Radix_node::to_file(string file_path, int father) {
    fstream file;
    int loc = -1;
    this->file_path = file_path;
    file.open(this->file_path, ios::app | ios::binary);
    if (!file.is_open()) {
        cerr << "Error opening file " << this->file_path << endl;
        return false;
    }
    this->where_father = father;
    while (loc == -1) {
        file.seekp(0, ios::end);
        loc = file.tellp();
    }
    if (father != -1) {
        file.seekg(father, ios::beg);
        file.seekg(3*sizeof(bool), ios::cur);
        file.seekg(sizeof(char), ios::cur);
        file.seekg(sizeof(int), ios::cur);
        int str_sz;
        file.read(reinterpret_cast<char *>(&str_sz), sizeof(int));
        file.seekp(str_sz*sizeof(char), ios::cur);
        file.seekp(this->child_number*sizeof(int), ios::cur);
        file.write(reinterpret_cast<char *>(&loc), sizeof(int));
    }
    file.close();
    file.open(this->file_path, ios::app | ios::binary);
    loc = -1;
    while (loc == -1) {
        file.seekp(0, ios::end);
        loc = file.tellp();
    }
    file.write(reinterpret_cast<char *>(&this->complete), sizeof(this->complete));
    file.write(reinterpret_cast<char *>(&this->leaf), sizeof(this->leaf));
    file.write(reinterpret_cast<char *>(&this->root), sizeof(this->root));
    file.write(&this->letra, sizeof(this->letra));
    file.write(reinterpret_cast<char *>(&this->where_father), sizeof(this->where_father));
    file.write(reinterpret_cast<char *>(&this->str_sz), sizeof(this->str_sz));
    file.write(reinterpret_cast<char *>(&this->str), this->str_sz*sizeof(char));
    int a = this->children.size();
    file.write(reinterpret_cast<char *>(&a), sizeof(int));
    for (int i = 0; i < a; i++) {
        int b = 0;
        file.write(reinterpret_cast<char *>(&b), sizeof(int));
    }
    a = this->main_index.size();
    file.write(reinterpret_cast<char *>(&a), sizeof(int));
    for (Indexador entrada : this->main_index) {
        file.write(reinterpret_cast<char *>(&entrada), sizeof(entrada));
    }
    file.close();
    if (!this->leaf) {
        for (Radix_node *maybe : this->children) {
            maybe->to_file(file_path, loc);
        }
    }
    this->children.clear();
    return true;
}

void Radix_node::from_file(int loc) {
    fstream file;
    file.open(this->file_path, ios::in | ios::binary);
    file.seekg(loc*sizeof(char), ios::beg);
    file.read(reinterpret_cast<char *>(&this->complete), sizeof(this->complete));
    file.read(reinterpret_cast<char *>(&this->leaf), sizeof(this->leaf));
    file.read(reinterpret_cast<char *>(&this->root), sizeof(this->root));
    file.read(&this->letra, sizeof(this->letra));
    file.read(reinterpret_cast<char *>(&this->where_father), sizeof(this->where_father));
    file.read(reinterpret_cast<char *>(&this->str_sz), sizeof(int));
    file.read(reinterpret_cast<char *>(&this->str), this->str_sz*sizeof(char));
    int a;
    file.read(reinterpret_cast<char *>(&a), sizeof(int));
    int *ind = static_cast<int *>(malloc(a * sizeof(int)));
    for (int i = 0; i < a; i++) {
        int b;
        file.read(reinterpret_cast<char *>(&b), sizeof(int));
        this->children_list.push_back(b);
        ind[i] = b;
    }
    file.read(reinterpret_cast<char *>(&a), sizeof(int));
    for (int i = 0; i < a; i++) {
        Indexador b;
        file.read(reinterpret_cast<char *>(&b), sizeof(int));
        this->main_index.push_back(b);
    }
    if (!this->leaf) {
        for (int yeah : this->children_list) {
            auto *maybe = new Radix_node();
            maybe->from_file(yeah);
            this->children.push_back(maybe);
        }
    }
}

bool Radix_node::add_to_tree(Indexador find_later, string what, int pos) {
    int cont = 0;
    if (this->root) {
        if (!this->children.empty()) {
            for (Radix_node *maybe : this->children) {
                if (maybe->add_to_tree(find_later, what, pos)) {
                    return true;
                }
                cont++;
            }
        }
        auto *maybe = new Radix_node();
        maybe->child_number = cont - 1;
        maybe->clear();
        maybe->letra = what[pos];
        maybe->main_index.push_back(find_later);
        maybe->parent = this;
        maybe->complete = true;
        maybe->leaf = true;
        maybe->str_sz = what.size();
        maybe->str = what;
        maybe->file_path = this->file_path;
        if (this->children.size() == 0) {
            this->children.push_back(maybe);
            return true;
        }
        int tam = this->children.size();
        Radix_node* a[tam+1];
        int i = 0;
        for (i = 0; i < tam + 1; i++) {
            a[i] = new Radix_node();
        }
        i = 0;
        bool did = false;
        for (Radix_node *b : this->children) {
            if (b->letra < maybe->letra || did) {
                a[i] = b;
                i++;
            }
            else {
                a[i] = maybe;
                i++;
                a[i] = b;
                i++;
                did = true;
            }
        }
        if (i == tam) {
            a[i] = maybe;
        }
        this->children.clear();
        for (i =  0; i < tam + 1; i++) {
            a[i]->child_number = i;
            this->children.push_back(a[i]);
        }
        return true;
    }
    if (pos == what.size()) {
        this->complete = true;
        this->str_sz = what.size();
        this->str = what;
        this->letra = what[pos];
        this->main_index.push_back(find_later);
    }
    if (this->letra != what[pos]) {
        return false;
    }
    if (this->leaf) {
        if (this->str == what) {
            this->main_index.push_back(find_later);
            return true;
        }
        this->complete = false;
        this->leaf = false;
        auto *tmp1 = new Radix_node();
        auto *tmp2 = new Radix_node();
        tmp1->clear();
        tmp2->clear();
        tmp2->letra = what[pos + 1];
        tmp2->main_index.push_back(find_later);
        tmp2->parent = tmp1->parent = this;
        tmp2->complete = tmp1->complete = true;
        tmp2->leaf = tmp1->leaf = true;
        tmp1->str = this->str;
        tmp1->str_sz = this->str_sz;
        tmp2->str_sz = what.size();
        tmp2->str = what;
        tmp2->file_path = tmp1->file_path = this->file_path;
        int i = 0;
        while (this->str[i] != this->letra) {
            i++;
        }
        if (i == this->str_sz - 1) {
            delete tmp1;
            this->complete = true;
            this->children.push_back(tmp2);
            return true;
        }
        i++;
        tmp1->letra = this->str[i];
        if (tmp1->letra == tmp2->letra) {
            this->children.remove(tmp1);
            this->children.push_back(tmp1);
            delete tmp2;
            tmp1->add_to_tree(find_later, what, pos + 1);
            return true;
        }
        if (tmp1->letra < tmp2->letra) {
            this->children.push_back(tmp1);
            this->children.push_back(tmp2);
            return true;
        }
        this->children.push_back(tmp2);
        this->children.push_back(tmp1);
        return true;
    }
    if (this->children.size() == 0) {
        auto *maybe = new Radix_node();
        maybe->child_number = cont - 1;
        maybe->clear();
        maybe->letra = what[pos + 1];
        maybe->main_index.push_back(find_later);
        maybe->parent = this;
        maybe->complete = true;
        maybe->leaf = true;
        maybe->str_sz = what.size();
        maybe->str = what;
        maybe->file_path = this->file_path;
        if (this->children.size() == 0) {
            this->children.push_back(maybe);
            return true;
        }
        int tam = this->children.size();
        Radix_node* a[tam+1];
        int i = 0;
        for (i = 0; i < tam + 1; i++) {
            a[i] = new Radix_node();
        }
        i = 0;
        bool did = false;
        for (Radix_node *b : this->children) {
            if (b->letra < maybe->letra || did) {
                a[i] = b;
                i++;
            }
            else {
                a[i] = maybe;
                i++;
                a[i] = b;
                i++;
                did = true;
            }
        }
        if (i == tam) {
            a[i] = maybe;
        }
        this->children.clear();
        for (i =  0; i < tam + 1; i++) {
            a[i]->child_number = i;
            this->children.push_back(a[i]);
        }
        return true;
    }
    for (Radix_node *maybe : this->children) {
        if (maybe->add_to_tree(find_later, what, pos+1)) {
            return true;
        }
        cont++;
    }
    auto *maybe = new Radix_node();
    maybe->child_number = cont - 1;
    maybe->clear();
    maybe->letra = what[pos + 1];
    maybe->main_index.push_back(find_later);
    maybe->parent = this;
    maybe->complete = true;
    maybe->leaf = true;
    maybe->str_sz = what.size();
    maybe->str = what;
    maybe->file_path = this->file_path;
    if (this->children.size() == 0) {
        this->children.push_back(maybe);
        return true;

    }
    int tam = this->children.size();
    Radix_node* a[tam+1];
    int i = 0;
    for (i = 0; i < tam + 1; i++) {
        a[i] = new Radix_node();

    }
    i = 0;
    bool did = false;
    for (Radix_node *b : this->children) {
        if (b->letra < maybe->letra || did) {
            a[i] = b;
            i++;
        }
        else {
            a[i] = maybe;
            i++;
            a[i] = b;
            i++;
            did = true;
        }
    }
    if (i == tam) {
        a[i] = maybe;
    }
    this->children.clear();
    for (i =  0; i < tam + 1; i++) {
        a[i]->child_number = i;
        this->children.push_back(a[i]);
    }
    return true;
}

void add_to_all_radix(Radix_node *all, Carta what, Indexador where) {
    string aux;
    int i = 0;
    while (i < what.name_sz) {
        aux = token(what.name, &i);
        if (!aux.empty()) {
            all[NAMES].add_to_tree(where, aux, 0);
        }
    }
    i = 0;
    while (i < what.types_sz) {
        aux = token(what.types, &i);
        if (!aux.empty()) {
            all[TYPES].add_to_tree(where, aux, 0);
        }
    }
    i = 0;
    while (i < what.subtypes_sz) {
        aux = token(what.subtypes, &i);
        if (!aux.empty()) {
            all[SUBTYPES].add_to_tree(where, aux, 0);
        }
    }
    i = 0;
    while (i < what.supertype_sz) {
        aux = token(what.supertypes, &i);
        if (!aux.empty()) {
            all[SUPERTYPES].add_to_tree(where, aux, 0);
        }
    }
    while (i < what.text_sz) {
        aux = token(what.text, &i);
        if (!aux.empty()) {
            all[TEXT].add_to_tree(where, aux, 0);
        }
    }
}

string token(string str, int *loc) {
    string aux;
    while (!isalnum(str[*loc]) && *loc < str.size()) {
        *loc = *loc + 1;
    }
    while (isalnum(str[*loc]) && *loc < str.size()) {
        aux += tolower(str[*loc]);
        *loc = *loc + 1;
    }
    return aux;
}

bool Radix_node::from_file_specific(int loc, string what, int pos) {
    fstream file;
    file.open(this->file_path, ios::in | ios::binary);
    file.seekg(loc*sizeof(char), ios::beg);
    file.read(reinterpret_cast<char *>(&this->complete), sizeof(this->complete));
    file.read(reinterpret_cast<char *>(&this->leaf), sizeof(this->leaf));
    file.read(reinterpret_cast<char *>(&this->root), sizeof(this->root));
    file.read(&this->letra, sizeof(this->letra));
    if (what[pos] != this->letra) {
        return false;
    }
    file.read(reinterpret_cast<char *>(&this->where_father), sizeof(this->where_father));
    file.read(reinterpret_cast<char *>(&this->str_sz), sizeof(int));
    file.read(reinterpret_cast<char *>(&this->str), this->str_sz*sizeof(char));
    int a;
    file.read(reinterpret_cast<char *>(&a), sizeof(int));
    int *ind = static_cast<int *>(malloc(a * sizeof(int)));
    for (int i = 0; i < a; i++) {
        int b;
        file.read(reinterpret_cast<char *>(&b), sizeof(int));
        this->children_list.push_back(b);
        ind[i] = b;
    }
    file.read(reinterpret_cast<char *>(&a), sizeof(int));
    for (int i = 0; i < a; i++) {
        Indexador b;
        file.read(reinterpret_cast<char *>(&b), sizeof(int));
        this->main_index.push_back(b);
    }
    if (!this->leaf) {
        for (int yeah : this->children_list) {
            auto *maybe = new Radix_node();
            if (maybe->from_file_specific(yeah, what, pos+1)) {
                this->children.push_back(maybe);
            }
        }
    }
    return true;
}
