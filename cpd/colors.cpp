#include "colors.h"

void color_store(string cores_carta, Indexador local) {
    string path = COLOR_PATH;
    int tam = cores_carta.length();
    if (tam == 0) {
        path += "Uncolored";
        if (!local.to_index_f(path)) {
            cerr << "Couldn't find Uncolored" << endl;
        }
        return;
    }
    for (int i = 0; i < tam; i++) {
        switch (cores_carta[i]) {
            case 'R':
                path += "Red";
                if (!local.to_index_f(path)) {
                    cerr << "Couldn't find Red" << endl;
                }
                path = COLOR_PATH;
                break;
            case 'G':
                path += "Green";
                if (!local.to_index_f(path)) {
                    cerr << "Couldn't find Green" << endl;
                }
                path = COLOR_PATH;
                break;
            case 'U':
                path += "Blue";
                if (!local.to_index_f(path)) {
                    cerr << "Couldn't find Blue" << endl;
                }
                path = COLOR_PATH;
                break;
            case 'W':
                path += "White";
                if (!local.to_index_f(path)) {
                    cerr << "Couldn't find White" << endl;
                }
                path = COLOR_PATH;
                break;
            case 'B':
                path += "Black";
                if (!local.to_index_f(path)) {
                    cerr << "Couldn't find Black" << endl;
                }
                path = COLOR_PATH;
                break;
            default:
                break;
        }
    }
}
