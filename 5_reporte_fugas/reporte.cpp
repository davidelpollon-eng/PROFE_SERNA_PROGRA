
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct RegistroFuga {
    string entidad;
    string acronimo;
    int anterior;
    int actual;
};


vector<string> separarPorComas(const string& linea) {
    vector<string> campos;
    stringstream flujo(linea);
    string campo;
    while (getline(flujo, campo, ',')) {
        campos.push_back(campo);
    }
    return campos;
}

string correlacion(int anterior, int actual) {
    if (actual > anterior) return "Subio";
    if (actual < anterior) return "Bajo";
    return "Igual";
}

string histograma(int actual) {
    if (actual < 0) actual = 0;
    return string(actual, '*');
}

int main(int argc, char* argv[]) {
    string archivoEntrada = (argc > 1) ? argv[1] : "fugasAgua.csv";
    string archivoSalida  = (argc > 2) ? argv[2] : "reporteFugas.txt";

    ifstream entrada(archivoEntrada);
    if (!entrada.is_open()) {
        cerr << "No se pudo abrir el archivo de entrada: " << archivoEntrada << "\n";
        return 1;
    }

    vector<RegistroFuga> registros;
    string linea;
    while (getline(entrada, linea)) {
        if (linea.empty()) continue;
        vector<string> campos = separarPorComas(linea);
        if (campos.size() < 4) continue; // linea mal formada, se ignora

        RegistroFuga r;
        r.entidad  = campos[0];
        r.acronimo = campos[1];
        r.anterior = stoi(campos[2]);
        r.actual   = stoi(campos[3]);
        registros.push_back(r);
    }
    entrada.close();

    ofstream salida(archivoSalida);
    if (!salida.is_open()) {
        cerr << "No se pudo crear el archivo de salida: " << archivoSalida << "\n";
        return 1;
    }

    // Encabezado
    salida << left  << setw(20) << "Entidad Federativa"
           << right << setw(10) << "Anterior"
           << right << setw(8)  << "Actual"
           << right << setw(12) << "Acronimo"
           << "  " << left << setw(8) << "Correlacion"
           << "  " << "Histograma" << "\n";

    for (const auto& r : registros) {
        salida << left  << setw(20) << r.entidad
               << right << setw(10) << r.anterior
               << right << setw(8)  << r.actual
               << right << setw(12) << r.acronimo
               << "  " << left << setw(8) << correlacion(r.anterior, r.actual)
               << "  " << histograma(r.actual) << "\n";
    }

    salida.close();

   
    ifstream reGenerado(archivoSalida);
    cout << reGenerado.rdbuf();

    cout << "\nReporte generado en: " << archivoSalida << "\n";
    return 0;
}
