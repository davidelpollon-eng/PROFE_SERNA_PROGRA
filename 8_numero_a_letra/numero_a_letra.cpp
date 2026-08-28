// Tarea 3 - Ejercicio 1
// Convierte una cantidad (0-99) a su representacion en letra, con el
// sufijo "pesos 00/100 M.N.". Practica con std::array y std::string.
#include <array>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

string numeroALetra(float monto) {
    static const array<string, 10> unidades = {
        "cero", "uno", "dos", "tres", "cuatro",
        "cinco", "seis", "siete", "ocho", "nueve"
    };
    static const array<string, 10> decenas = {
        "", "diez", "veinte", "treinta", "cuarenta",
        "cincuenta", "sesenta", "setenta", "ochenta", "noventa"
    };
    static const array<string, 10> teens = {
        "", "once", "doce", "trece", "catorce", "quince",
        "dieciseis", "diecisiete", "dieciocho", "diecinueve"
    };

    int entero = static_cast<int>(round(monto));  // se ignoran los centavos: siempre "00/100"

    if (entero < 0 || entero > 99) {
        return "Fuera de rango (0-99)";
    }

    int decena = entero / 10;
    int unidad = entero % 10;
    string letra;

    if (decena == 0) {
        letra = unidades[unidad];
    } else if (decena == 1) {
        letra = (unidad == 0) ? decenas[1] : teens[unidad];
    } else if (decena == 2) {
        letra = (unidad == 0) ? decenas[2] : "veinti" + unidades[unidad];
    } else {
        letra = decenas[decena];
        if (unidad != 0) {
            letra += " y " + unidades[unidad];
        }
    }

    return letra + " pesos 00/100 M.N.";
}

int main() {
    cout << "=== Conversor de cantidad a letra (0-99) ===\n";
    float monto;
    char continuar = 's';

    while (continuar == 's' || continuar == 'S') {
        cout << "\nIngresa una cantidad (0-99): ";
        cin >> monto;
        cout << "-> " << numeroALetra(monto) << "\n";
        cout << "¿Otra conversion? (s/n): ";
        cin >> continuar;
    }

    return 0;
}
