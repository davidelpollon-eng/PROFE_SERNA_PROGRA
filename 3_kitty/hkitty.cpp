

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


string rotarIzquierda(const string& s, size_t pos) {
    pos %= s.size();
    return s.substr(pos) + s.substr(0, pos);
}


void imprimirPatronKitty(const string& w, int n) {
    if (w.empty() || n <= 0) return;

    string base;
    base.reserve(w.size() * n);
    for (int i = 0; i < n; i++) {
        base += w;
    }

    for (size_t i = 0; i < w.size(); i++) {
        cout << rotarIzquierda(base, i) << "\n";
    }
}

int main(int argc, char* argv[]) {
    string nombreArchivo = "hkitty.in";
    if (argc > 1) {
        nombreArchivo = argv[1]; 
    }

    ifstream entrada(nombreArchivo);
    if (!entrada.is_open()) {
        cerr << "No se pudo abrir el archivo de entrada: " << nombreArchivo << "\n";
        return 1;
    }

    string linea;
    while (getline(entrada, linea)) {
  
        if (linea == ".") {
            break;
        }
        if (linea.empty()) continue;

        istringstream flujo(linea);
        string palabra;
        int n;
        if (flujo >> palabra >> n) {
            imprimirPatronKitty(palabra, n);
        }
    }

    entrada.close();
    return 0;
}
