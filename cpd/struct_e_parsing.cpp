//
// Created by Jordi on 11/22/2025.
//
#include "struct_e_parsing.h"


Carta *todas_cartas() {
    int quantas_cartas = 0;
    ifstream file(entry_name);
    string s;


    Carta *all = static_cast<Carta *>(malloc(sizeof(Carta)*quantas_cartas));
    return all;
}



Carta parse_carta(string s) {
    Carta c;
    string sub_s1;
    string sub_s2;
    sub_s1.clear();
    sub_s2.clear();
    int i = 0;
    while (i < s.length()) {
        if (s[i] == ASPAS) {
            i++;
            while (i < s.length() && s[i] != ASPAS) {
                sub_s1.push_back(s[i]);
                i++;
            }
            i++;
            while (i < s.length() && s[i] != VIRGULA) {
                if (s[i] == D_PONTOS) {
                    i++;
                }
                if (s[i] == A_COLCHETE) {
                    while (i < s.length() && s[i] != F_COLCHETE) {
                        sub_s2.push_back(s[i]);
                        i++;
                    }
                }
                sub_s2.push_back(s[i]);
                i++;
            }
            tratar_carta(c, sub_s1, sub_s2);
        }
    }
    return c;
}