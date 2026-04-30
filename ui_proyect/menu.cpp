#include <iostream>
#include <windows.h>
#include <iomanip>

#include "../validation/validation.h"
#include "../auxiliars/auxiliars.h"
#include "menu.h"

using namespace std;

int menuPrincipal (){
	
	int opcion;
	
		cout << "Digite:\n" << endl;
		cout << "1. Agregar tarea." << endl;
		cout << "2. Listar tareas." << endl;
		cout << "3. Buscar una tarea." << endl;
		cout << "4. Modificar una tarea." << endl;
		cout << "5. Ordenar tareas (importancia)." << endl;
		cout << "6. Borrar una tarea." << endl;
		cout << "7. Mostrar calendario." << endl;
		cout << "8. salir." << endl;
		cout << "\nOpcion: ";
	
		opcion = validacionRango ( 1, 8 );
	
	system ( "cls" );
	return opcion;
	
}

int menuModificar () {
	
	int opcion;
	
	cout << "Cual campo desea modificar:\n";
	cout << "1. Dia." << endl;
	cout << "2. Nombre." << endl;
	cout << "3. Importancia." << endl;
	cout << "4. Tiempo.\n" << endl;
	cout << "Opcion: ";
	
	opcion = validacionRango(1, 4);
	return opcion;
}

void imprimirMatriz(int arr[]) {
    int diaContador = 1;
    int diaImportancia = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    imprimirLeyenda(hConsole);

    for (int fila = 0; fila < 16; fila++) {

        if (fila == 0) {
            cout << char(218) << "--------------------" << char(191) << endl;
        }
        else if (fila % 3 == 0 && fila != 15) {
            cout << "|--" << char(197) << "--" << char(197) << "--" << char(197)
                 << "--" << char(197) << "--" << char(197) << "--"
                 << char(197) << "--|\n";
        }
        else if (fila == 15) {
            cout << char(192) << "--+--+--|";
        }
        else {
            for (int columna = 0; columna < 22; columna++) {

                if (fila <= 12 || columna <= 9) {

                    if (columna % 3 == 0) {
                        cout << "|";
                    }
                    else if ((fila - 1) % 3 == 0 && (columna - 1) % 3 == 0) {
                        cout << setw(2) << diaContador;
                        diaContador++;
                    }
                    else if ((fila - 2) % 3 == 0 && (columna - 1) % 3 == 0) {
                        imprimirBloqueImportancia(arr[diaImportancia], hConsole);
                        diaImportancia++;
                    }
                }
            }
            cout << endl;
        }
    }

    cout << endl;
}