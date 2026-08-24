

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {

    if (argc < 3) {
        cerr << "Uso: " << argv[0] << " <palabra_a_buscar> <archivo1> [archivo2 ...]\n";
        return 1;
    }

    string palabra = argv[1];

    for (int i = 2; i < argc; i++) {
        string nombreArchivo = argv[i];
        ifstream archivo(nombreArchivo);

        if (!archivo.is_open()) {
            cerr << "No se pudo abrir el archivo: " << nombreArchivo << "\n";
            continue;
        }

        bool encabezadoImpreso = false;
        string linea;

        while (getline(archivo, linea)) {
   
            if (linea.find(palabra) != string::npos) {
                if (!encabezadoImpreso) {
                    cout << nombreArchivo << "\n";
                    encabezadoImpreso = true;
                }
                cout << linea << "\n";
            }
        }

        if (encabezadoImpreso) {
            cout << "\n"; 
        }

        archivo.close();
    }

    return 0;
}
