#include "arvores_e_organizacao.h"
#include "colors.h"
#include "struct_e_parsing.h"



int main()
{
    clear_files();
    fstream entrada;
    entrada.open(ATOMIC_CARDS, ios::in);
    if(!entrada) {
        cerr<<"ERRO AO ABRIR JSON";
        return 1;
    }
    string json_text = get_from_AtomicCards(&entrada);
    cJSON *json = cJSON_Parse(json_text.c_str());
    if(!json) {
        cerr<<"ERRO AO LER JSON";
        cJSON_Delete(json);
        return 1;
    }
    cJSON *data = cJSON_GetObjectItem(json, DATA_CARDS);
    if(!data) {
        cerr<<"JSON INVALIDO: SEM 'data'"<<endl;
        cJSON_Delete(json);
        return 1;
    }
    Carta uma_carta;
    Indexador onde;
    onde.id = 0;
    onde.pos = 0;
    int max_id = 0;
    while(parse_carta(&uma_carta, data, onde.id)) {
        onde.pos = uma_carta.to_main_file();
        if (onde.pos == ERR) {
            cerr<<"ERRO NO NOVO METODO DE ESCRITA"<<endl;
            return 1;
        }
        if (!onde.to_index()) {
            cerr<<"ERRO NO INDEX ESCRITA"<<endl;
        }
        uma_carta.clear();
        onde.id++;
    }
    cJSON_Delete(json);
    max_id = onde.id;
    Radix_node all[5];
    for (int i = 0; i < 5; i++) {
        all[i].clear();
        all[i].root = true;
    }
    for (onde.id = 0; onde.id < max_id; onde.id+=1) {
        if (!onde.from_index()) {
            cerr<<"ERRO NO INDEX LEITURA"<<endl;
        }
        if (!uma_carta.from_main_file(onde.pos)) {
            cerr<<"ERRO NO NOVO METODO DE LEITURA"<<endl;
            return 1;
        }
        color_store(uma_carta.colors, onde);
        add_to_all_radix(all, uma_carta, onde);
        uma_carta.print();
        uma_carta.clear();
    }
    all[NAMES].file_path = FILE_FOR_NAMES;
    all[TYPES].file_path = FILE_FOR_TYPES;
    all[SUBTYPES].file_path = FILE_FOR_SUB;
    all[SUPERTYPES].file_path = FILE_FOR_SUPER;
    all[TEXT].file_path = FILE_FOR_TEXT;

    for (int i = 0; i < 5; i++) {
        all[i].to_file(all[i].file_path, -1);
    }
    auto *super = new Radix_node();
    super->clear();
    super->root = true;
    super->file_path = FILE_FOR_SUPER;
    super->from_file(0);

    return 0;
}

