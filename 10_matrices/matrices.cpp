// Tarea 3 - Ejercicio 3
// Operaciones con matrices de tamano variable: capturar, escalar, sumar,
// multiplicar y mostrar. Usa una struct Matriz sobre std::vector<vector<double>>.
#include <iostream>
#include <vector>

using namespace std;

struct Matriz {
    int filas = 0;
    int columnas = 0;
    vector<vector<double>> datos;
};

void capturar(Matriz &m) {
    cout << "Numero de filas: ";
    cin >> m.filas;
    cout << "Numero de columnas: ";
    cin >> m.columnas;

    m.datos.assign(m.filas, vector<double>(m.columnas));

    for (int i = 0; i < m.filas; ++i) {
        for (int j = 0; j < m.columnas; ++j) {
            cout << "Elemento [" << i << "][" << j << "]: ";
            cin >> m.datos[i][j];
        }
    }
}

Matriz escalar(const Matriz &m, double k) {
    Matriz resultado = m;
    for (auto &fila : resultado.datos) {
        for (auto &valor : fila) {
            valor *= k;
        }
    }
    return resultado;
}

Matriz sumar(const Matriz &a, const Matriz &b) {
    Matriz resultado;
    if (a.filas != b.filas || a.columnas != b.columnas) {
        cout << "Las matrices no tienen la misma dimension.\n";
        return resultado;
    }
    resultado = a;
    for (int i = 0; i < a.filas; ++i) {
        for (int j = 0; j < a.columnas; ++j) {
            resultado.datos[i][j] = a.datos[i][j] + b.datos[i][j];
        }
    }
    return resultado;
}

Matriz multiplicar(const Matriz &a, const Matriz &b) {
    Matriz resultado;
    if (a.columnas != b.filas) {
        cout << "Las columnas de A deben coincidir con las filas de B.\n";
        return resultado;
    }

    resultado.filas = a.filas;
    resultado.columnas = b.columnas;
    resultado.datos.assign(resultado.filas, vector<double>(resultado.columnas, 0.0));

    for (int i = 0; i < a.filas; ++i) {
        for (int j = 0; j < b.columnas; ++j) {
            double suma = 0;
            for (int k = 0; k < a.columnas; ++k) {
                suma += a.datos[i][k] * b.datos[k][j];
            }
            resultado.datos[i][j] = suma;
        }
    }
    return resultado;
}

void mostrar(const Matriz &m) {
    if (m.filas == 0 || m.columnas == 0) {
        cout << "(matriz vacia)\n";
        return;
    }
    for (const auto &fila : m.datos) {
        for (double valor : fila) {
            cout << valor << "\t";
        }
        cout << "\n";
    }
}

int main() {
    Matriz A, B, resultado;
    int opcion;

    do {
        cout << "\n=== Operaciones con Matrices ===\n"
             << "1) Capturar matriz A\n"
             << "2) Capturar matriz B\n"
             << "3) Escalar matriz A\n"
             << "4) Sumar A + B\n"
             << "5) Multiplicar A * B\n"
             << "6) Mostrar matriz A\n"
             << "7) Mostrar matriz B\n"
             << "8) Mostrar ultimo resultado\n"
             << "9) Salir\n"
             << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                capturar(A);
                break;
            case 2:
                capturar(B);
                break;
            case 3: {
                double k;
                cout << "Valor escalar: ";
                cin >> k;
                resultado = escalar(A, k);
                cout << "Resultado:\n";
                mostrar(resultado);
                break;
            }
            case 4:
                resultado = sumar(A, B);
                cout << "Resultado:\n";
                mostrar(resultado);
                break;
            case 5:
                resultado = multiplicar(A, B);
                cout << "Resultado:\n";
                mostrar(resultado);
                break;
            case 6:
                mostrar(A);
                break;
            case 7:
                mostrar(B);
                break;
            case 8:
                mostrar(resultado);
                break;
            case 9:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida\n";
        }
    } while (opcion != 9);

    return 0;
}
