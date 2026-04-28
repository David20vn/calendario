#include <iostream>
#include <cctype>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <windows.h>

#include "../models/actividad.h"

using namespace std;

const string ARCHIVO_ACTIVIDADES = "data/actividades.dat";

int tamanio (){
	
	Actividad aux;
	int counter = 0;
	ifstream archivo ( ARCHIVO_ACTIVIDADES, ios::binary );
	
	if ( !archivo )
		cout << "Error en abrir el archivo.";
	
	while ( archivo.read ( reinterpret_cast <char*> (&aux), sizeof ( Actividad ))){
		counter++;
	}
	
	archivo.close();
	return counter;
}