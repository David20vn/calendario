#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "../models/actividad.h"
#include "../ui_proyect/menu.h"
#include "../validation/validation.h"
#include "auxiliars.h"


using namespace std;

int tamanio (){
	
	Actividad aux;
	int counter = 0;
	ifstream archivo ( RUTA_ARCHIVO_ACTIVIDADES, ios::binary );
	
	if ( !archivo )
		cout << "Error en abrir el archivo.";
	
	while ( archivo.read ( reinterpret_cast <char*> (&aux), sizeof ( Actividad ))){
		counter++;
	}
	
	archivo.close();
	return counter;
}

void calcularImportanciasPorDia(const vector<Actividad>& actividades, int vecImportancia[31]) {
    for (const Actividad& actividad : actividades) {
        int indice = actividad.dia - 1;

        if (vecImportancia[indice] < actividad.importancia) {
            vecImportancia[indice] = actividad.importancia;
        }
    }
}

bool eliminarTareaPorNombre(const char* nombreTarea) {
    vector<Actividad> actividades = cargarActividades();

    if (actividades.empty()) {
        return false;
    }

    size_t tamanoOriginal = actividades.size();

    actividades.erase(
        remove_if(actividades.begin(), actividades.end(),
            [nombreTarea](const Actividad& actividad) {
                return strcmp(actividad.nombre, nombreTarea) == 0;
            }),
        actividades.end()
    );

    if (actividades.size() == tamanoOriginal) {
        return false;
    }

    return guardarActividades(actividades);
}

vector<Actividad> cargarActividades() {
    vector<Actividad> actividades;
    Actividad actividad;

    ifstream archivo(RUTA_ARCHIVO_ACTIVIDADES, ios::binary);

    if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        return actividades;
    }

    while (archivo.read(reinterpret_cast<char*>(&actividad), sizeof(Actividad))) {
        actividades.push_back(actividad);
    }

    archivo.close();
    return actividades;
}

bool guardarActividades(const vector<Actividad>& actividades) {
    ofstream archivo(RUTA_ARCHIVO_ACTIVIDADES, ios::binary | ios::trunc);

    if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        return false;
    }

    for (const Actividad& actividad : actividades) {
        archivo.write(reinterpret_cast<const char*>(&actividad), sizeof(Actividad));
    }

    archivo.close();
    return true;
}

void editarActividad(Actividad& actividad) {
    char nombre[40];

    switch (menuModificar()) {
        case 1:
            cout << "Nuevo dia: ";
            actividad.dia = validacionRango(1, 31);
            break;

        case 2:
            cout << "Nuevo nombre: ";
            validacionNombre(nombre);
            strcpy(actividad.nombre, nombre);
            break;

        case 3:
            cout << "Nueva importancia (1 - 10): ";
            actividad.importancia = validacionRango(1, 10);
            break;

        case 4:
            cout << "Nuevo tiempo (minutos): ";
            actividad.tiempo = validacionRango(1, 1440);
            break;
    }
}

bool buscarYModificarTarea(const char* nombreTarea) {
    fstream archivo(RUTA_ARCHIVO_ACTIVIDADES, ios::binary | ios::in | ios::out);

    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return false;
    }

    Actividad actividad;
    bool encontrada = false;

    while (true) {
        streampos posicionRegistro = archivo.tellg();

        if (!archivo.read(reinterpret_cast<char*>(&actividad), sizeof(Actividad))) {
            break;
        }

        if (strcmp(actividad.nombre, nombreTarea) == 0) {
            cout << "Datos actuales:\n";
            mostrarActividad(actividad);

            editarActividad(actividad);

            archivo.seekp(posicionRegistro, ios::beg);
            archivo.write(reinterpret_cast<char*>(&actividad), sizeof(Actividad));

            cout << "Actividad modificada con exito.\n";
            encontrada = true;

            archivo.seekg(posicionRegistro + static_cast<streamoff>(sizeof(Actividad)), ios::beg);
        }
    }

    archivo.close();
    return encontrada;
}

bool buscarYMostrarTarea(const char* nombreTarea) {
    ifstream archivo(RUTA_ARCHIVO_ACTIVIDADES, ios::binary);

    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return false;
    }

    Actividad actividad;
    bool encontrada = false;

    while (archivo.read(reinterpret_cast<char*>(&actividad), sizeof(Actividad))) {
        if (strcmp(actividad.nombre, nombreTarea) == 0) {
            mostrarActividad(actividad);
            encontrada = true;
        }
    }

    archivo.close();
    return encontrada;
}

void mostrarActividad(const Actividad& actividad) {
    cout << "------------------------" << endl;
    cout << "Dia: " << actividad.dia << endl;
    cout << "Nombre: " << actividad.nombre << endl;
    cout << "Importancia: " << actividad.importancia << endl;
    cout << "Tiempo: " << actividad.tiempo << endl;
    cout << "------------------------" << endl;
}

Actividad capturarActividad() {
    Actividad actividad;
    char nombre[40];

    cout << "Fecha (dia): ";
    actividad.dia = validacionRango(1, 31);

    cout << "Actividad: ";
    validacionNombre(nombre);
    strcpy(actividad.nombre, nombre);

    cout << "Importancia (1 - 10): ";
    actividad.importancia = validacionRango(1, 10);

    cout << "Tiempo estimado de la actividad (minutos): ";
    actividad.tiempo = validacionRango(1, 1440);

    return actividad;
}

void imprimirBloqueImportancia(int importancia, HANDLE hConsole) {
    char bloque = 219;

    if (importancia > 0) {
        cambiarColor(hConsole, colorSegunImportancia(importancia));
        cout << bloque << bloque;
        cambiarColor(hConsole, COLOR_BLANCO);
    } else {
        cout << "  ";
    }
}

void imprimirLeyenda(HANDLE hConsole) {
    char bloque = 219;

    cout << "Cada dia esta representado por la actividad de mayor importancia.\n";
    cout << "Importancia:\n\n";

    cout << "( 1 - 4 ):\t";
    cambiarColor(hConsole, COLOR_AZUL);
    cout << bloque << bloque;
    cambiarColor(hConsole, COLOR_BLANCO);

    cout << "\n( 5 - 7 ):\t";
    cambiarColor(hConsole, COLOR_AMARILLO);
    cout << bloque << bloque;
    cambiarColor(hConsole, COLOR_BLANCO);

    cout << "\n( 8 - 10 ):\t";
    cambiarColor(hConsole, COLOR_ROJO);
    cout << bloque << bloque << endl << endl;
    cambiarColor(hConsole, COLOR_BLANCO);
}

void cambiarColor(HANDLE hConsole, int color) {
    SetConsoleTextAttribute(hConsole, color);
}

int colorSegunImportancia(int importancia) {
    if (importancia >= 8) return COLOR_ROJO;
    if (importancia >= 5) return COLOR_AMARILLO;
    if (importancia > 0)  return COLOR_AZUL;
    return COLOR_BLANCO;
}