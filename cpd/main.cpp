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
    Carta uma_carta;
    parse_carta(&uma_carta, data, 33041);
    int i = 0;
    while(parse_carta(&uma_carta, data, i)) {
        cout << i << endl;
        uma_carta.print();
        uma_carta.clear();
        i++;
    }
    cJSON_Delete(json);
    return 0;
}