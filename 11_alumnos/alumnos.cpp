// Tarea 3 - Ejercicio 4
// struct Alumno con vector<float> de calificaciones, gestionado con
// std::vector<Alumno>. capturar()/datosCaptura() llenan cada registro y
// calculan 'aprobado'; mostrar()/datosMostrar() imprimen la tabla final.
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct Alumno {
    int id;
    char sexo;                      // 'H' o 'M'
    vector<float> calificaciones;   // tamano 3
    bool aprobado;
};

void datosCaptura(Alumno &alumno) {
    cout << "ID del alumno: ";
    cin >> alumno.id;

    cout << "Sexo (H/M): ";
    cin >> alumno.sexo;

    alumno.calificaciones.resize(3);
    float suma = 0;
    for (int i = 0; i < 3; ++i) {
        cout << "Calificacion " << (i + 1) << ": ";
        cin >> alumno.calificaciones[i];
        suma += alumno.calificaciones[i];
    }

    float promedio = suma / alumno.calificaciones.size();
    alumno.aprobado = (promedio >= 6.0f);   // criterio de aprobacion
}

void capturar(vector<Alumno> &alumnos) {
    for (auto &alumno : alumnos) {
        cout << "\n--- Nuevo alumno ---\n";
        datosCaptura(alumno);
    }
}

void datosMostrar(const Alumno &alumno) {
    float suma = 0;
    for (float c : alumno.calificaciones) suma += c;
    float promedio = suma / alumno.calificaciones.size();

    cout << alumno.id << "\t"
         << (alumno.sexo == 'H' ? "Hombre" : "Mujer") << "\t"
         << (alumno.aprobado ? "Si" : "No") << "\t"
         << fixed << setprecision(1) << promedio << "\n";
}

void mostrar(const vector<Alumno> &alumnos) {
    cout << "\nID\tSexo\tAprobo\tPromedio\n";
    for (const auto &alumno : alumnos) {
        datosMostrar(alumno);
    }
}

int main() {
    int n;
    cout << "Numero de alumnos: ";
    cin >> n;

    vector<Alumno> alumnos(n);
    capturar(alumnos);
    mostrar(alumnos);

    return 0;
}
