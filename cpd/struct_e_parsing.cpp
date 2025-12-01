//
// Created by Jordi on 11/22/2025.
//
#include "struct_e_parsing.h"

string get_from_AtomicCards(fstream *entrada){
    string buffer;
    entrada->in;
    while(entrada->good()) {
        buffer+=entrada->get();
    }
    return buffer;
}

bool parse_carta(Carta *out, cJSON *jsonCard, int n) {
    cJSON *card = cJSON_GetArrayItem(jsonCard,n);//seleciona uma carta
    if (card == nullptr) {
        return false;
    }
    card = cJSON_GetArrayItem(card,0);//pula um campo vazio do AtomicCards.json
    if (card == nullptr) {
        return false;
    }
    cJSON *tmp = cJSON_GetObjectItem(card, NOME);//coleta dos dados simples
    out->name = tmp->valuestring;
    tmp = cJSON_GetObjectItem(card, TEXT_CARDS);
    if (tmp != nullptr) out->text = tmp->valuestring;
    tmp = cJSON_GetObjectItem(card, MANA_CARDS);
    double temp_double = cJSON_GetNumberValue(tmp);
    out->mana_value = static_cast<int>(temp_double);

    /*
     * a partir daqui os dados estao em estruturas auxiliares que tem de ser acessadas
     * usando um acesso com duas variaveis temporarias,
     * tmp2 guarda a estrutura que contem os dados
     * tmp coleta os dados
     */

    cJSON *tmp2 = cJSON_GetObjectItem(card, COLORS_CARDS);//retorna um char por vez
    int i = 0;
    tmp = cJSON_GetArrayItem(tmp2, 0);
    while (tmp != nullptr) {
        out->colors += tmp->valuestring;
        out->colors += ";";
        i++;
        tmp = cJSON_GetArrayItem(tmp2, i);
    }

    tmp2 = cJSON_GetObjectItem(card, SUBTYPES_CARDS);
    tmp = cJSON_GetArrayItem(tmp2, 0);
    i = 0;
    while (tmp != nullptr) {
        out->subtypes += tmp->valuestring;
        out->subtypes += ";";
        i++;
        tmp = cJSON_GetArrayItem(tmp2, i);
    }

    tmp2 = cJSON_GetObjectItem(card, TYPES_CARDS);
    tmp = cJSON_GetArrayItem(tmp2, 0);
    i = 0;
    while (tmp != nullptr) {
        out->types += tmp->valuestring;
        out->types += ";";
        i++;
        tmp = cJSON_GetArrayItem(tmp2, i);
    }

    tmp2 = cJSON_GetObjectItem(card, SUPERTYPES_CARDS);
    tmp = cJSON_GetArrayItem(tmp2, 0);
    while (tmp != nullptr) {
        out->supertypes += tmp->valuestring;
        out->supertypes += ";";
        i++;
        tmp = cJSON_GetArrayItem(tmp2, i);
    }

    out->id = n;
    out->name_sz = out->name.size();
    out->types_sz = out->types.size();
    out->subtypes_sz = out->subtypes.size();
    out->colors_sz = out->colors.size();
    out->supertype_sz = out->supertypes.size();
    out->text_sz = out->text.size();
    return true;
}

