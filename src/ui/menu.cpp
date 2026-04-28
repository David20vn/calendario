#include <iostream>
#include <cctype>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <windows.h>

#include "models/actividad.h"
#include "utils/validacion.cpp" 
#include "utils/archivo_utils.cpp"

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

int menuModificar (){
	
	int opcion;
	
	cout << "Cual campo desea modificar:\n";
	
	cout << "1. Dia." << endl;
	cout << "2. Nombre." << endl;
	cout << "3. Importancia." << endl;
	cout << "4. Tiempo.\n" << endl;
	
	cout << "Opcion: ";
	opcion = validacionRango ( 1, 4 );
	
	return opcion;
	system ( "cls" );
	
}