#include <string>
#include <vector>
#include <windows.h>

#include "../models/actividad.h"

using namespace std;

#ifndef AUXILIAR_H
#define AUXILIAR_H

const int DIAS_MES = 31;
const int COLOR_AZUL = 3;
const int COLOR_AMARILLO = 6;
const int COLOR_ROJO = 4;
const int COLOR_BLANCO = 7;
const string RUTA_ARCHIVO_ACTIVIDADES = "data/actividades.dat";

int tamanio ();
void calcularImportanciasPorDia(const vector<Actividad>& actividades, int vecImportancia[31]);
bool eliminarTareaPorNombre(const char* nombreTarea);
vector<Actividad> cargarActividades();
bool guardarActividades(const vector<Actividad>& actividades);
void editarActividad(Actividad& actividad);
bool buscarYModificarTarea(const char* nombreTarea);
bool buscarYMostrarTarea(const char* nombreTarea);
void mostrarActividad(const Actividad& actividad);
Actividad capturarActividad();
void imprimirBloqueImportancia(int importancia, HANDLE hConsole);
void imprimirLeyenda(HANDLE hConsole);
void cambiarColor(HANDLE hConsole, int color);
int colorSegunImportancia(int importancia);


#endif