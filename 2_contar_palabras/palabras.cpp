
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;


string recortarPuntuacion(const string& palabra) {
    size_t inicio = 0;
    size_t fin = palabra.size();

    while (inicio < fin && !isalpha(static_cast<unsigned char>(palabra[inicio]))) {
        inicio++;
    }
    while (fin > inicio && !isalpha(static_cast<unsigned char>(palabra[fin - 1]))) {
        fin--;
    }

    return palabra.substr(inicio, fin - inicio);
}


string capitalizar(const string& palabra) {
    if (palabra.empty()) return palabra;
    string resultado = palabra;
    resultado[0] = toupper(static_cast<unsigned char>(resultado[0]));
    return resultado;
}


int contarLetras(const string& palabra) {
    int contador = 0;
    for (unsigned char c : palabra) {
        if (isalpha(c)) contador++;
    }
    return contador;
}

void procesarArchivo(const string& nombreArchivo, bool mostrarEncabezado) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << "\n";
        return;
    }

    if (mostrarEncabezado) {
        cout << nombreArchivo << "\n";
    }

    string linea;
    while (getline(archivo, linea)) {
        istringstream flujoLinea(linea);
        string token;
        while (flujoLinea >> token) {
            string palabra = recortarPuntuacion(token);
            if (palabra.empty()) continue;

            string palabraCapitalizada = capitalizar(palabra);
            int letras = contarLetras(palabra);

            cout << palabraCapitalizada << "\t" << letras << "\n";
        }
    }

    archivo.close();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " <archivo1> [archivo2 ...]\n";
        return 1;
    }

    bool variosArchivos = (argc - 1) > 1;

    for (int i = 1; i < argc; i++) {
        procesarArchivo(argv[i], variosArchivos);
        if (variosArchivos) cout << "\n";
    }

    return 0;
}
