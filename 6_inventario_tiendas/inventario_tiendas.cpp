
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>

using namespace std;

const char* ARCHIVO_CANTERAS = "canteras.bin";
const char* ARCHIVO_PRADOS   = "prados.bin";
const char* ARCHIVO_REPORTE  = "inventario.txt";


struct Producto {
    int id;
    char nombre[50];
    int cantidad;
    double compra;
};

void altaProducto(const string& archivoBin, const Producto& p) {
    ofstream salida(archivoBin, ios::binary | ios::app);
    if (!salida.is_open()) {
        cerr << "No se pudo abrir " << archivoBin << " para escritura.\n";
        return;
    }
    salida.write(reinterpret_cast<const char*>(&p), sizeof(Producto));
    salida.close();
}

void altaProductoInteractiva(const string& archivoBin) {
    Producto p{};
    string nombre;

    cout << "Id: ";
    cin >> p.id;
    cin.ignore();
    cout << "Nombre del producto: ";
    getline(cin, nombre);
    strncpy(p.nombre, nombre.c_str(), sizeof(p.nombre) - 1);
    p.nombre[sizeof(p.nombre) - 1] = '\0';
    cout << "Cantidad: ";
    cin >> p.cantidad;
    cout << "Precio de compra: ";
    cin >> p.compra;

    altaProducto(archivoBin, p);
    cout << "Producto agregado a " << archivoBin << ".\n";
}

vector<Producto> leerProductos(const string& archivoBin) {
    vector<Producto> productos;
    ifstream entrada(archivoBin, ios::binary);
    if (!entrada.is_open()) {
        return productos; // archivo aun no existe: inventario vacio
    }

    Producto p;
    while (entrada.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        productos.push_back(p);
    }
    entrada.close();
    return productos;
}


void generarReporteInventario() {
    vector<Producto> canteras = leerProductos(ARCHIVO_CANTERAS);
    vector<Producto> prados   = leerProductos(ARCHIVO_PRADOS);


    struct Acumulado {
        int id;
        int cantidad;
        double compra;
    };
    map<string, Acumulado> combinados; 

    auto acumular = [&](const vector<Producto>& lista) {
        for (const auto& p : lista) {
            string nombre(p.nombre);
            auto it = combinados.find(nombre);
            if (it == combinados.end()) {
                combinados[nombre] = Acumulado{p.id, p.cantidad, p.compra};
            } else {
                it->second.cantidad += p.cantidad;
               
            }
        }
    };

    acumular(canteras);
    acumular(prados);


    vector<pair<string, Acumulado>> reporte(combinados.begin(), combinados.end());
    sort(reporte.begin(), reporte.end(),
         [](const auto& a, const auto& b) { return a.first < b.first; });

    ofstream salida(ARCHIVO_REPORTE);
    if (!salida.is_open()) {
        cerr << "No se pudo crear " << ARCHIVO_REPORTE << "\n";
        return;
    }

    salida << left << setw(4)  << "Id"
           << left << setw(22) << "Nombre del producto"
           << right << setw(10) << "Cantidad"
           << right << setw(10) << "Compra" << "\n";

    double totalInventario = 0.0;
    for (const auto& [nombre, acc] : reporte) {
        salida << left << setw(4)  << acc.id
               << left << setw(22) << nombre
               << right << setw(10) << acc.cantidad
               << right << setw(10) << fixed << setprecision(2) << acc.compra
               << "\n";
        totalInventario += acc.cantidad * acc.compra;
    }

    salida << right << setw(46) << fixed << setprecision(2) << totalInventario << "\n";
    salida.close();

    // Tambien se muestra en pantalla
    ifstream verificacion(ARCHIVO_REPORTE);
    cout << verificacion.rdbuf();
    cout << "\nReporte generado en: " << ARCHIVO_REPORTE << "\n";
}


void poblarDatosDemo() {
    remove(ARCHIVO_CANTERAS);
    remove(ARCHIVO_PRADOS);

    auto nuevo = [](int id, const char* nombre, int cantidad, double compra) {
        Producto p{};
        p.id = id;
        strncpy(p.nombre, nombre, sizeof(p.nombre) - 1);
        p.cantidad = cantidad;
        p.compra = compra;
        return p;
    };

    altaProducto(ARCHIVO_CANTERAS, nuevo(1, "Aceite", 3, 10.00));
    altaProducto(ARCHIVO_CANTERAS, nuevo(2, "Servilletas", 25, 20.00));
    altaProducto(ARCHIVO_CANTERAS, nuevo(5, "Detergente", 20, 15.00));

    altaProducto(ARCHIVO_PRADOS, nuevo(1, "Aceite", 5, 10.00));
    altaProducto(ARCHIVO_PRADOS, nuevo(2, "Servilletas", 10, 20.00));
    altaProducto(ARCHIVO_PRADOS, nuevo(3, "Jabon Sote", 30, 8.00));
    altaProducto(ARCHIVO_PRADOS, nuevo(5, "Detergente", 10, 15.00));

    cout << "Datos de demostracion generados en " << ARCHIVO_CANTERAS
         << " y " << ARCHIVO_PRADOS << ".\n\n";
}


void menu() {
    int opcion = -1;
    do {
        cout << "\n=== Inventario Canteras / Prados ===\n";
        cout << "1. Alta de producto en Canteras\n";
        cout << "2. Alta de producto en Prados\n";
        cout << "3. Generar reporte de inventario (inventario.txt)\n";
        cout << "4. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: altaProductoInteractiva(ARCHIVO_CANTERAS); break;
            case 2: altaProductoInteractiva(ARCHIVO_PRADOS);   break;
            case 3: generarReporteInventario();                break;
            case 4: cout << "Saliendo...\n";                   break;
            default: cout << "Opcion invalida.\n";             break;
        }
    } while (opcion != 4);
}

int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "--demo") {
        poblarDatosDemo();
        generarReporteInventario();
        return 0;
    }

    menu();
    return 0;
}
