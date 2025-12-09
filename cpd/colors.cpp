#include "colors.h"

void color_store(string cores_carta, Indexador local) {
    string path = COLOR_PATH;
    int tam = cores_carta.length();
    if (tam == 0) {
        path += "Uncolored.bin";
        if (!local.to_index_f(path)) {
            cerr << "Couldn't find Uncolored" << endl;
        }
        return;
    }
    for (int i = 0; i < tam; i++) {
        switch (cores_carta[i]) {
            case 'R':
                path += "Red.bin";
                if (!local.to_index_f(path)) {
                    cerr << "Couldn't find Red" << endl;
                }
                path = COLOR_PATH;
                break;
            case 'G':
                path += "Green.bin";
                if (!local.to_index_f(path)) {
                    cerr << "Couldn't find Green" << endl;
                }
                path = COLOR_PATH;
                break;
            case 'U':
                path += "Blue.bin";
                if (!local.to_index_f(path)) {
                    cerr << "Couldn't find Blue" << endl;
                }
                path = COLOR_PATH;
                break;
            case 'W':
                path += "White.bin";
                if (!local.to_index_f(path)) {
                    cerr << "Couldn't find White" << endl;
                }
                path = COLOR_PATH;
                break;
            case 'B':
                path += "Black.bin";
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

void value_store(int value, Indexador local) {
    fstream file;
    fstream file_info;
    file_info.open(VALUES_PATH, ios::app | ios::in | ios::binary);
    string num;
    itoa(value, num.data(), 0);
    string path = VALUE_PATH;
    path += num;
    file.open(path, ios::app | ios::binary);
    file.write(reinterpret_cast<char *>(&local), sizeof(local));
    file.close();
    int temp1, temp2;
    bool should = false;
    while (!file_info.eof()) {
        file_info.read(reinterpret_cast<char *>(&temp1), sizeof(temp1));
        if (temp1 == value) {
            return;
        }
        if (temp1 > value) {
            should = true;
            temp2 = value;
        }
        if (should) {
            file_info.seekp(-sizeof(temp1), ios::cur);
            file_info.write(reinterpret_cast<char *>(&temp2), sizeof(temp2));
            temp2 = temp1;
            file_info.read(reinterpret_cast<char *>(&temp1), sizeof(temp1));
        }
    }
    file_info.write(reinterpret_cast<char *>(&temp2), sizeof(temp2));
}
