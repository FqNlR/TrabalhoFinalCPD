//
// Created by Jordi on 11/22/2025.
//
#include "struct_e_parsing.h"

#include <variant>


void todas_cartas() {
    Carta c;
    ifstream file(entry_name);
    char control[2] = {"0"};
    ofstream out(exit_name);
    if (!out) cerr << "Error opening output file" << endl;
    string s;
    s.clear();
    bool should = false;
    while(true) {
        bool nerase = true;
        control[0] = control[1];
        control[1] = file.get();
        if(!file) break;
        if (control[1] == A_CHAVE && control[0] == A_COLCHETE) should = true;
        if(control[0] == F_CHAVE && control[1] == F_COLCHETE) {
            int i =  s.find(foreign_data);
            if (i != -1) {
                s.erase(i);
                nerase = false;
            }
            if (!s.empty() && i == -1) {
                c = parse_carta(s);
                s.clear();
                if (!c.name.empty()) {
                    guardar_carta(c, out);
                    cout << c.name<< endl;
                    cout << c.mana_value<< endl;
                    cout << c.text<< endl;
                    cout << c.supertypes<< endl;
                    cout << c.types<< endl;
                    cout << c.subtypes<< endl;
                    should = false;
                }
            }
        }
        if (should && nerase) s.push_back(control[1]);
    }
    file.close();
    out.close();
}



Carta parse_carta(string s) {//recebe uma string correspondente a exatamente uma carta
    Carta c;
    string sub_s1;
    string sub_s2;
    sub_s1.clear();
    sub_s2.clear();
    char control[2] = {"0"};
    int i = 0;
    while (i < s.length()) {
        if (s[i] == ASPAS) {
            i++;
            while (i < s.length() && s[i] != ASPAS) {//pega a string correspondente ao campo
                sub_s1.push_back(s[i]);
                i++;
            }
            i++;
            while (i < s.length()) {//pega a string correspondente aos dados do campo
                control[0] = control[1];
                control[1] = s[i];
                if (s[i] == D_PONTOS) {
                    i++;
                }
                if (s[i] == A_COLCHETE) {
                    while (i < s.length() && s[i] != F_COLCHETE) {//lida com cartas atributos entre colchetes
                        sub_s2.push_back(s[i]);
                        i++;
                    }
                }
                if (s[i] == A_CHAVE) {//lida com cartas atributos entre chaves
                    while (i < s.length() && s[i] != F_CHAVE) {
                        sub_s2.push_back(s[i]);
                        i++;
                    }
                }
                if (s[i] == CONTRA) {//lida com cartas atributos entre chaves
                    i++;
                    while (i < s.length() && s[i] != CONTRA) {
                        sub_s2.push_back(s[i]);
                        i++;
                    }
                    i++;
                }
                if (s[i] == ASPAS) {
                    while (i < s.length() && s[i] != ASPAS) {
                        sub_s2.push_back(s[i]);
                        i++;
                    }
                }
                if (control[0] == ASPAS && control[1] == VIRGULA) break;
                if (control[0] == ZERO && control[1] == VIRGULA) break;
                if (control[0] == F_CHAVE && control[1] == VIRGULA) break;
                sub_s2.push_back(s[i]);
                i++;
            }
            c = tratar_carta(c, sub_s1, sub_s2);//checa qual campo e armazena em c
            sub_s1.clear();
            sub_s2.clear();
        }
        i++;
    }
    return c;
}



Carta tratar_carta(Carta c, string tipo, string escrita) {
    if (tipo == s_mana) {
        c.mana_value = tratar_mana(escrita);
        return c;
    }
    if (tipo == s_colors) {
        c.cores = tratar_cores(escrita);
        return c;
    }
    if (tipo == s_keywords) {
        c.keywords = escrita;
        return c;
    }
    if (tipo == s_name) {
        c.name = escrita;
        return c;
    }
    if (tipo == s_supertypes) {
        c.supertypes = escrita;
        return c;
    }
    if (tipo == s_types) {
        c.types = escrita;
        return c;
    }
    if (tipo == s_subtypes) {
        c.subtypes = escrita;
        return c;
    }
    if (tipo == s_text) {
        c.text = escrita;
        return c;
    }
    return c;
}



bool *tratar_cores(string s) {
    bool *all = static_cast<bool *>(malloc(sizeof(bool)*5));
    for (int i = 0; i < 5; i++) {
        all[i] = false;
    }
    int a = 0;
    if (s.find(B_CHAR) != -1) {
        all[B_NUM] = true;
    }
    if (s.find(W_CHAR) != -1) {
        all[W_NUM] = true;
    }
    if (s.find(R_CHAR) != -1) {
        all[R_NUM] = true;
    }
    if (s.find(G_CHAR) != -1) {
        all[G_NUM] = true;
    }
    if (s.find(U_CHAR) != -1) {
        all[U_NUM] = true;
    }
    return all;
}


int tratar_mana(string s) {
    string num;
    int i = 0;
    while (s[i] != PONTO && i < s.length()) {
        num.push_back(s[i]);
        i++;
    }
    return atoi(num.c_str());
}




void guardar_carta(Carta c, ofstream &archivo) {
    archivo.write(reinterpret_cast<const ostream::char_type *>(&c), sizeof(Carta));
}
