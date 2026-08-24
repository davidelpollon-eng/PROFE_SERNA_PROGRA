
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <iomanip>

using namespace std;

const char* ARCHIVO_ALMACEN = "almacen.dat";
const char* ARCHIVO_BAJO_STOCK = "articulos_bajo_stock.txt";


struct Herramienta {
    int registro;
    char nombre[50];
    int cantidad;
    double costo;
};


void altaHerramienta(const Herramienta& h) {
    ofstream salida(ARCHIVO_ALMACEN, ios::binary | ios::app);
    if (!salida.is_open()) {
        cerr << "No se pudo abrir " << ARCHIVO_ALMACEN << " para escritura.\n";
        return;
    }
    salida.write(reinterpret_cast<const char*>(&h), sizeof(Herramienta));
    salida.close();
}

void altaHerramientaInteractiva() {
    Herramienta h{};
    string nombre;

    cout << "# registro: ";
    cin >> h.registro;
    cin.ignore();
    cout << "Nombre de la herramienta: ";
    getline(cin, nombre);
    strncpy(h.nombre, nombre.c_str(), sizeof(h.nombre) - 1);
    h.nombre[sizeof(h.nombre) - 1] = '\0';
    cout << "Cantidad: ";
    cin >> h.cantidad;
    cout << "Costo: ";
    cin >> h.costo;

    altaHerramienta(h);
    cout << "Herramienta agregada a " << ARCHIVO_ALMACEN << ".\n";
}


vector<Herramienta> leerHerramientas() {
    vector<Herramienta> lista;
    ifstream entrada(ARCHIVO_ALMACEN, ios::binary);
    if (!entrada.is_open()) return lista;

    Herramienta h;
    while (entrada.read(reinterpret_cast<char*>(&h), sizeof(Herramienta))) {
        lista.push_back(h);
    }
    entrada.close();
    return lista;
}

bool consultarHerramienta(int registroBuscado, Herramienta& resultado) {
    vector<Herramienta> lista = leerHerramientas();
    for (const auto& h : lista) {
        if (h.registro == registroBuscado) {
            resultado = h;
            return true;
        }
    }
    return false;
}

void consultarHerramientaInteractiva() {
    int registro;
    cout << "Numero de registro a consultar: ";
    cin >> registro;

    Herramienta h;
    if (consultarHerramienta(registro, h)) {
        cout << "Registro: " << h.registro
             << " | Nombre: " << h.nombre
             << " | Cantidad: " << h.cantidad
             << " | Costo: " << fixed << setprecision(2) << h.costo << "\n";
    } else {
        cout << "No se encontro el registro " << registro << ".\n";
    }
}


double calcularTotalInventario() {
    vector<Herramienta> lista = leerHerramientas();
    double total = 0.0;
    for (const auto& h : lista) {
        total += h.cantidad * h.costo;
    }
    return total;
}

void mostrarTotalInventario() {
    vector<Herramienta> lista = leerHerramientas();

    cout << left << setw(10) << "Registro"
         << left << setw(24) << "Herramienta"
         << right << setw(10) << "Cantidad"
         << right << setw(10) << "Costo" << "\n";

    double total = 0.0;
    for (const auto& h : lista) {
        cout << left << setw(10) << h.registro
             << left << setw(24) << h.nombre
             << right << setw(10) << h.cantidad
             << right << setw(10) << fixed << setprecision(2) << h.costo << "\n";
        total += h.cantidad * h.costo;
    }

    cout << "\nTotal en inventario: " << fixed << setprecision(2) << total << "\n";
}


void generarReporteBajoStock() {
    vector<Herramienta> lista = leerHerramientas();

    ofstream salida(ARCHIVO_BAJO_STOCK);
    if (!salida.is_open()) {
        cerr << "No se pudo crear " << ARCHIVO_BAJO_STOCK << "\n";
        return;
    }

    salida << left << setw(10) << "Registro"
           << left << setw(24) << "Herramienta"
           << right << setw(10) << "Cantidad"
           << right << setw(10) << "Costo" << "\n";

    for (const auto& h : lista) {
        if (h.cantidad < 5) {
            salida << left << setw(10) << h.registro
                   << left << setw(24) << h.nombre
                   << right << setw(10) << h.cantidad
                   << right << setw(10) << fixed << setprecision(2) << h.costo << "\n";
        }
    }
    salida.close();

    ifstream verificacion(ARCHIVO_BAJO_STOCK);
    cout << verificacion.rdbuf();
    cout << "\nReporte generado en: " << ARCHIVO_BAJO_STOCK << "\n";
}


void poblarDatosDemo() {
    remove(ARCHIVO_ALMACEN);

    auto nuevo = [](int registro, const char* nombre, int cantidad, double costo) {
        Herramienta h{};
        h.registro = registro;
        strncpy(h.nombre, nombre, sizeof(h.nombre) - 1);
        h.cantidad = cantidad;
        h.costo = costo;
        return h;
    };

    altaHerramienta(nuevo(1,  "Lijadora electrica", 7,  257.98));
    altaHerramienta(nuevo(5,  "Martillo",           76, 41.99));
    altaHerramienta(nuevo(12, "Guia de serrucho",   21, 11.00));
    altaHerramienta(nuevo(13, "Podadora",           3,  779.50));

    cout << "Datos de demostracion generados en " << ARCHIVO_ALMACEN << ".\n\n";
}


void menu() {
    int opcion = -1;
    do {
        cout << "\n=== Inventario de Almacen ===\n";
        cout << "1. Alta de herramienta\n";
        cout << "2. Consultar herramienta por registro\n";
        cout << "3. Mostrar inventario y total en pantalla\n";
        cout << "4. Generar reporte de articulos con cantidad < 5\n";
        cout << "5. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: altaHerramientaInteractiva();      break;
            case 2: consultarHerramientaInteractiva(); break;
            case 3: mostrarTotalInventario();          break;
            case 4: generarReporteBajoStock();         break;
            case 5: cout << "Saliendo...\n";           break;
            default: cout << "Opcion invalida.\n";     break;
        }
    } while (opcion != 5);
}

int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "--demo") {
        poblarDatosDemo();
        mostrarTotalInventario();
        cout << "\n--- Articulos con cantidad < 5 ---\n";
        generarReporteBajoStock();
        return 0;
    }

    menu();
    return 0;
}
