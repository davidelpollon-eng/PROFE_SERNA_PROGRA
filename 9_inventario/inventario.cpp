// Tarea 3 - Ejercicio 2
// Gestor de inventario con struct Articulo y std::vector<Articulo>.
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Articulo {
    string nombre;
    int cantidad;
    float precio;
};

void agregarArticulo(vector<Articulo> &inventario);
void buscarYActualizar(vector<Articulo> &inventario);
void limpiarInventario(vector<Articulo> &inventario);
void mostrarInventario(const vector<Articulo> &inventario);

int main() {
    vector<Articulo> inventario;
    int opcion;

    do {
        cout << "\n=== Gestor de Inventario ===\n"
             << "1) Agregar articulo\n"
             << "2) Buscar y actualizar articulo\n"
             << "3) Mostrar inventario\n"
             << "4) Limpiar inventario (elimina stock en 0)\n"
             << "5) Salir\n"
             << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: agregarArticulo(inventario); break;
            case 2: buscarYActualizar(inventario); break;
            case 3: mostrarInventario(inventario); break;
            case 4: limpiarInventario(inventario); break;
            case 5: cout << "Saliendo...\n"; break;
            default: cout << "Opcion invalida\n";
        }
    } while (opcion != 5);

    return 0;
}

void agregarArticulo(vector<Articulo> &inventario) {
    Articulo nuevo;
    cin.ignore();
    cout << "Nombre del articulo: ";
    getline(cin, nuevo.nombre);
    cout << "Cantidad inicial: ";
    cin >> nuevo.cantidad;
    cout << "Precio: ";
    cin >> nuevo.precio;

    inventario.push_back(nuevo);
    cout << "Articulo agregado.\n";
}

void buscarYActualizar(vector<Articulo> &inventario) {
    if (inventario.empty()) {
        cout << "El inventario esta vacio.\n";
        return;
    }

    string buscar;
    cin.ignore();
    cout << "Nombre del articulo a buscar: ";
    getline(cin, buscar);

    bool encontrado = false;
    for (Articulo &item : inventario) {   // referencia: modifica el elemento real del vector
        if (item.nombre == buscar) {
            encontrado = true;
            cout << "Encontrado: " << item.nombre
                 << " | Cantidad: " << item.cantidad
                 << " | Precio: " << item.precio << "\n";

            int opcion;
            cout << "1) Actualizar precio\n2) Actualizar cantidad\n3) Ambos\nOpcion: ";
            cin >> opcion;

            if (opcion == 1 || opcion == 3) {
                cout << "Nuevo precio: ";
                cin >> item.precio;
            }
            if (opcion == 2 || opcion == 3) {
                cout << "Nueva cantidad: ";
                cin >> item.cantidad;
            }
            cout << "Articulo actualizado.\n";
            break;
        }
    }

    if (!encontrado) {
        cout << "Articulo no encontrado.\n";
        return;
    }

    limpiarInventario(inventario);  // validacion automatica tras actualizar
}

void limpiarInventario(vector<Articulo> &inventario) {
    auto it = inventario.begin();
    int eliminados = 0;

    while (it != inventario.end()) {
        if (it->cantidad == 0) {
            it = inventario.erase(it);
            eliminados++;
        } else {
            ++it;
        }
    }

    if (eliminados > 0) {
        cout << eliminados << " articulo(s) con stock 0 eliminado(s).\n";
    }
}

void mostrarInventario(const vector<Articulo> &inventario) {
    if (inventario.empty()) {
        cout << "El inventario esta vacio.\n";
        return;
    }

    cout << "\nNombre\t\tCantidad\tPrecio\n";
    for (const auto &item : inventario) {
        cout << item.nombre << "\t\t" << item.cantidad << "\t\t" << item.precio << "\n";
    }
}
