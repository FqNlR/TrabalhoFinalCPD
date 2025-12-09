#include "defs_gerais_e_cartas.h"

void Carta::print() const{
    cout<< "Nome da carta: "<< this->name << endl;
    cout<< "Cores da carta: "<< this->colors << endl;
    cout<< "Tipos da carta: "<< this->types << endl;
    cout<< "Custo de mana da carta: "<< this->mana_value << endl;
    cout<< "Supertipos da carta: "<< this->supertypes << endl;
    cout<< "Subtipos da carta: "<< this->subtypes << endl;
    cout<< "Texto da carta: "<< this->text << endl;
    cout<<endl;
    cout<<endl;
}

void Carta::clear() {
    this->mana_value = 0;
    this->supertypes.clear();
    this->subtypes.clear();
    this->colors.clear();
    this->text.clear();
    this->name.clear();
    this->types.clear();
}


int Carta::to_main_file() {
    fstream file;
    int where;
    file.open(MAIN_FILE, ios::app | ios::binary);
    file.seekp(0, ios::end);
    if (!file.is_open()) {
        return ERR;
    }
    where = file.tellp();
    if (where == -1) {
        return ERR;
    }
    file.write(reinterpret_cast<char *>(&this->id), sizeof(this->id));
    file.write(reinterpret_cast<char *>(&this->name_sz), sizeof(this->name_sz));
    file.write(this->name.c_str(), this->name_sz*sizeof(char));
    file.write(reinterpret_cast<char *>(&this->types_sz), sizeof(this->types_sz));
    file.write(this->types.c_str(), this->types_sz*sizeof(char));
    file.write(reinterpret_cast<char *>(&this->subtypes_sz), sizeof(this->subtypes_sz));
    file.write(this->subtypes.c_str(), this->subtypes_sz*sizeof(char));
    file.write(reinterpret_cast<char *>(&this->supertype_sz), sizeof(this->supertype_sz));
    file.write(this->supertypes.c_str(), this->supertype_sz*sizeof(char));
    file.write(reinterpret_cast<char *>(&this->text_sz), sizeof(this->text_sz));
    file.write(this->text.c_str(), this->text_sz*sizeof(char));
    file.write(reinterpret_cast<char *>(&this->colors_sz), sizeof(this->colors_sz));
    file.write(this->colors.c_str(), this->colors_sz*sizeof(char));
    file.write(reinterpret_cast<char *>(&this->mana_value), sizeof(this->id));

    file.close();
    return where;
}

bool Carta::from_main_file(int where){
    fstream file;
    file.open(MAIN_FILE, ios::in | ios::binary);
    if (!file.is_open()) {
        return false;
    }
    file.seekg(where*sizeof(char), ios::beg);
    file.read(reinterpret_cast<char *>(&this->id), sizeof(this->id));
    this->name = this->aux_from_mf(&file, &this->name_sz);
    this->types = this->aux_from_mf(&file, &this->types_sz);
    this->subtypes = this->aux_from_mf(&file, &this->subtypes_sz);
    this->supertypes = this->aux_from_mf(&file, &this->supertype_sz);
    this->text = this->aux_from_mf(&file, &this->text_sz);
    this->colors = this->aux_from_mf(&file, &this->colors_sz);
    file.read(reinterpret_cast<char *>(&this->mana_value), sizeof(this->id));

    return true;
}


string Carta::aux_from_mf(fstream *file, int *n) {
    char *aux;
    string s;
    int put = file->tellg();
    file->read(reinterpret_cast<char *>(n), sizeof(int));
    int whatever = *n;
    aux = static_cast<char *>(malloc(whatever*sizeof(char)));
    file->read(aux, whatever*sizeof(char));
    s.clear();
    for (int i = 0; i < whatever; i++) {
        s += aux[i];
    }
    free(aux);
    put = file->tellg();
    return s;
}


bool Indexador::to_index() {
    fstream file;
    file.open(INDEX_FILE, ios::app | ios::binary);
    if (!file.is_open()) {
        return false;
    }
    file.seekg(0, ios::end);
    file.write(reinterpret_cast<char *>(this), sizeof(*this));
    return true;
}

bool Indexador::from_index() {
    fstream file;
    file.open(INDEX_FILE, ios::in | ios::binary);
    if (!file.is_open()) {
        return false;
    }
    file.seekg(this->id*sizeof(Indexador), ios::beg);
    file.read(reinterpret_cast<char *>(this), sizeof(*this));
    return true;
}

bool Indexador::to_index_f(string file_name) {
    fstream file;
    file.open(file_name, ios::app | ios::binary);
    if (!file.is_open()) {
        return false;
    }
    file.seekg(0, ios::end);
    file.write(reinterpret_cast<char *>(this), sizeof(*this));
    return true;
}
