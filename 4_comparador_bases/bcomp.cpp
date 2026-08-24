

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


unsigned long long convertirABase10(const string& numero, int base) {
    unsigned long long valor = 0;
    for (char c : numero) {
        int digito = c - '0';
        valor = valor * static_cast<unsigned long long>(base) + static_cast<unsigned long long>(digito);
    }
    return valor;
}

int main(int argc, char* argv[]) {
    string nombreArchivo = "bcomp.in";
    if (argc > 1) {
        nombreArchivo = argv[1];
    }

    ifstream entrada(nombreArchivo);
    if (!entrada.is_open()) {
        cerr << "No se pudo abrir el archivo de entrada: " << nombreArchivo << "\n";
        return 1;
    }

    string s, t;
    int b, c;


    while (entrada >> s >> b >> t >> c) {
        unsigned long long valorS = convertirABase10(s, b);
        unsigned long long valorT = convertirABase10(t, c);

        if (valorS < valorT) {
            cout << "<\n";
        } else if (valorS > valorT) {
            cout << ">\n";
        } else {
            cout << "=\n";
        }
    }

    entrada.close();
    return 0;
}
