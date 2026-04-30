#include <fstream>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <algorithm>

#include "../models/actividad.h"
#include "../validation/validation.h"
#include "../ui_proyect/menu.h"
#include "../auxiliars/auxiliars.h"
#include "actividad_service.h"

using namespace std;

// 1

void agregar() {
    const int AGREGAR_OTRA = 1;
    const int VOLVER_MENU = 2;

    int opcion = AGREGAR_OTRA;

    ofstream archivo(RUTA_ARCHIVO_ACTIVIDADES, ios::binary | ios::app);

    if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    while (opcion == AGREGAR_OTRA) {
        Actividad actividad = capturarActividad();

        archivo.write(reinterpret_cast<char*>(&actividad), sizeof(Actividad));

        cout << "\n1. Agregar otra tarea.\n";
        cout << "2. Volver al menu.\n";
        cout << "Opcion: ";
        opcion = validacionRango(AGREGAR_OTRA, VOLVER_MENU);

        system("cls");
    }

    archivo.close();
}


// 2.

void listar() {
    ifstream archivo(RUTA_ARCHIVO_ACTIVIDADES, ios::binary);

    if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    Actividad actividad;

    cout << "Tareas:\n\n";
    cout << "------------------------" << endl;

    while (archivo.read(reinterpret_cast<char*>(&actividad), sizeof(Actividad))) {
        mostrarActividad(actividad);
    }

    archivo.close();

    system("pause");
    system("cls");
}

// 3.

void buscarTarea() {
    const int BUSCAR_OTRA = 1;
    const int VOLVER_MENU = 2;

    int opcion = BUSCAR_OTRA;
    char nombreTarea[40];

    do {
        cout << "Digite el nombre de la tarea a buscar: ";
        cin.getline(nombreTarea, 40);

        bool encontrada = buscarYMostrarTarea(nombreTarea);

        if (!encontrada) {
            cout << "Tarea no encontrada." << endl;
        }

        cout << "\n\n1. Buscar otra tarea.\n";
        cout << "2. Volver al menu.\n";
        cout << "Opcion: ";
        opcion = validacionRango(BUSCAR_OTRA, VOLVER_MENU);

        system("cls");

    } while (opcion == BUSCAR_OTRA);
}


// 4.


void modificar() {
    const int MODIFICAR_OTRA = 1;
    const int VOLVER_MENU = 2;

    int continuar = MODIFICAR_OTRA;
    char nombreTarea[40];

    do {
        cout << "Digite el nombre de la tarea a modificar "
             << "(si hay 2 o mas tareas con el mismo nombre modificara todas): ";
        cin.getline(nombreTarea, 40);

        bool encontrada = buscarYModificarTarea(nombreTarea);

        if (!encontrada) {
            cout << "Tarea no encontrada." << endl;
        }

        cout << "\n1. Modificar otra tarea.\n";
        cout << "2. Volver al menu.\n";
        cout << "Opcion: ";
        continuar = validacionRango(MODIFICAR_OTRA, VOLVER_MENU);

        system("cls");

    } while (continuar == MODIFICAR_OTRA);
}

// 5. 

void ordenar() {
    vector<Actividad> actividades = cargarActividades();

    if (actividades.empty()) {
        cout << "No hay actividades para ordenar." << endl;
        system("pause");
        system("cls");
        return;
    }

    sort(actividades.begin(), actividades.end(),
        [](const Actividad& a, const Actividad& b) {
            return a.importancia > b.importancia;
        }
    );

    guardarActividades(actividades);

    cout << "Actividades ordenadas con exito.\n";
    system("pause");
    system("cls");
}

// 6.

void borrarTarea() {
    const int ELIMINAR_OTRA = 1;
    const int VOLVER_MENU = 2;

    int continuar = ELIMINAR_OTRA;
    char nombreTarea[40];

    do {
        cout << "Digite el nombre de la tarea que desea eliminar: ";
        cin.getline(nombreTarea, 40);

        bool eliminada = eliminarTareaPorNombre(nombreTarea);

        if (eliminada) {
            cout << "Tarea eliminada exitosamente" << endl;
        } else {
            cout << "Tarea no encontrada" << endl;
        }

        cout << "\n\n1. Eliminar otra tarea.\n";
        cout << "2. Volver al menu.\n";
        cout << "Opcion: ";
        continuar = validacionRango(1, 2);

        system("cls");

    } while (continuar == ELIMINAR_OTRA);
}

// 7

void calendario() {
    vector<Actividad> actividades = cargarActividades(); 

    if (actividades.empty()) {
        cout << "No hay actividades registradas." << endl;
        system("pause");
        system("cls");
        return;
    }

    int vecImportancia[31] = {};
    calcularImportanciasPorDia(actividades, vecImportancia);

    imprimirMatriz(vecImportancia);

    system("pause");
    system("cls");
}