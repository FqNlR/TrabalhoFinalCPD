#include "colors.h"
#include "struct_e_parsing.h"



int main()
{
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
    void limpa_aquivos();
    Carta uma_carta;
    Indexador onde;
    onde.id = 0;
    onde.pos = 0;
    int max_id = 0;
    while(parse_carta(&uma_carta, data, onde.id)) {
        cout << onde.id << endl;
        onde.pos = uma_carta.to_main_file();
        if (onde.pos == ERR) {
            cerr<<"ERRO NO NOVO METODO DE ESCRITA"<<endl;
            return 1;
        }
        color_store(uma_carta.colors, onde);
        uma_carta.clear();
        if (!onde.to_index()) {
            cerr<<"ERRO NO INDEX ESCRITA"<<endl;
        }
        onde.id++;
    }
    max_id = onde.id;
    for (onde.id = 0; onde.id <= max_id; onde.id++) {
        if (!onde.from_index()) {
            cerr<<"ERRO NO INDEX LEITURA"<<endl;
        }
        if (!uma_carta.from_main_file(onde.pos)) {
            cerr<<"ERRO NO NOVO METODO DE LEITURA"<<endl;
            return 1;
        }
        uma_carta.print();
        uma_carta.clear();
    }
    cJSON_Delete(json);
    return 0;
}

