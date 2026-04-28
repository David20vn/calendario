#include <iostream>
#include <cctype>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <windows.h>


#include "models/actividad.h"
#include "utils/validacion.cpp" 
#include "utils/archivo_utils.cpp"
#include "ui/menu.cpp"

using namespace std;

void agregar(){

	int opcion = 1;
	char nombre [40];
	Actividad stru;
	
	ofstream archivo ( ARCHIVO_ACTIVIDADES, ios::binary | ios::app );
	
	if (!archivo) {
        cerr << "No se pudo abrir el archivoooooooooooo." << endl;
        return;
    }
	
	while ( opcion == 1 ){
		
		cout << "Fecha (dia): ";
		stru.dia = validacionRango ( 1, 31);
		
		cout << "Actividad: ";
		validacionNombre ( nombre );
		strcpy ( stru.nombre, nombre );
		
		cout << "Importancia (1 - 10): ";
		stru.importancia = validacionRango ( 1, 10 );
		
		cout << "Tiempo estimado de la actividad (minutos): ";
		stru.tiempo = validacionRango ( 1, 1440 );
		
		cout << "\n1. Agregar otra tarea.\n2. Volver al menu.\nOpcion: ";
		opcion = validacionRango ( 1, 2 );
		
		system ( "cls" );
		
		archivo.write ( reinterpret_cast <char*> (&stru), sizeof (Actividad));
		
	}
	
	archivo.close();
}

void listar (){
	
	ifstream archivo ( ARCHIVO_ACTIVIDADES, ios::binary );
	Actividad stru;
	
	if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }
	
	cout << "Tareas: \n\n";
	cout << "------------------------" << endl;
	
	while ( archivo.read( reinterpret_cast<char*>(&stru), sizeof(Actividad) ) ){
		
		cout << "Dia: " << stru.dia << endl;
		cout << "Nombre: " << stru.nombre << endl;
		cout << "Importancia: " << stru.importancia << endl;
		cout << "Tiempo: " << stru.tiempo << endl;
		cout << "------------------------" << endl;
	}
		
		archivo.seekg (0);
		
	
	archivo.close(); 
	
	system( "pause" );
	system ( "cls" );
	
}

void buscarTarea (){
	
	Actividad aux;
	char nombreTarea[40];
	bool encontrada;
	int opcion;
	
	do {
		
		encontrada = false;
		
		cout << "Digite el nombre de la tarea a buscar: ";
		cin.getline( nombreTarea, 40 );
	
		ifstream archivo ( ARCHIVO_ACTIVIDADES, ios::binary );
		
		if (!archivo){
			cout << "error en abrir el archivo.";
			return;
		}
    		
	
		while ( archivo.read( reinterpret_cast <char*> ( &aux ), sizeof ( Actividad ))){
			if ( strcmp ( aux.nombre, nombreTarea ) == 0 ){
				
				cout << "------------------------" << endl;
				cout << "Dia: " << aux.dia << endl;
				cout << "Nombre: " << aux.nombre << endl;
				cout << "Importancia: " << aux.importancia << endl;
				cout << "Tiempo: " << aux.tiempo << endl;
				
				
				encontrada = true;
				
			}
		}
		
		cout << "------------------------" << endl;
		
		if ( !encontrada )
			cout << "Tarea no encontrada.";
			
		cout << "\n\n1. Buscar otra tarea.\n2. Volver al menu.\nOpcion: ";
		opcion = validacionRango ( 1, 2 );
		
		system ( "cls" );
		
		archivo.close();
		
	} while ( opcion == 1 );
}

void modificar (){
	
	Actividad aux;
	char nombreTarea[40];
	bool encontrada;
	int continuar;
	char nombre[40];
	
	do {
		
		encontrada = false;
		
		cout << "Digite el nombre de la tarea a modificar (si hay 2 o mas tareas con el mismo nombre modificara todas): ";
		cin.getline( nombreTarea, 40 );
	
		fstream archivo ( ARCHIVO_ACTIVIDADES, ios::binary | ios::out | ios::in );
		
		if (!archivo)
    		cout << "error en abrir el archivo.";
			 
		for ( int i = 0;  archivo.read( reinterpret_cast <char*> ( &aux ), sizeof ( Actividad )); i++ ){
			if ( strcmp ( aux.nombre, nombreTarea ) == 0 ){
				
				cout << "Datos actuales: " << endl;
				
				cout << "------------------------" << endl;
				cout << "Dia: " << aux.dia << endl;
				cout << "Nombre: " << aux.nombre << endl;
				cout << "Importancia: " << aux.importancia << endl;
				cout << "Tiempo: " << aux.tiempo << endl;
				cout << "------------------------" << endl;
				
				switch ( menuModificar () ){
					case 1:
						cout << "Nuevo dia: ";
						aux.dia = validacionRango ( 1, 31);
						break;
					case 2:
						cout << "Nuevo nombre: ";
						validacionNombre ( nombre );
						strcpy ( aux.nombre, nombre );
						break;
					case 3:
						cout << "Nueva importancia (1 - 10): ";
						aux.importancia = validacionRango ( 1, 10 );
					case 4:
						cout << "Nuevo tiempo (minutos): ";
						aux.tiempo = validacionRango ( 1, 1440 );	
				}
				
				cout << "------------------------" << endl;
				
				encontrada = true;
				
				archivo.seekp ( i * sizeof ( Actividad ), ios::beg );
				archivo.write( reinterpret_cast <char*> ( &aux ), sizeof ( Actividad )); 
				
				cout << "Actividad modificada con exito.\n";
				
			}
		}
		

		
		if ( !encontrada )
			cout << "Tarea no encontrada.";
			
		cout << "\n1. Modificar otra tarea.\n2. Volver al menu.\nOpcion: ";
		continuar = validacionRango ( 1, 2 );
		
		system ( "cls" );
		
		archivo.close();
		
	} while ( continuar == 1 );
}


void ordenar (){
	
	int n = tamanio();
	Actividad *arr = new Actividad [n], aux;
	
	fstream archivo ( ARCHIVO_ACTIVIDADES, ios::binary | ios::in | ios::out );
	
	for (int i = 0; i < n; i++) {
        archivo.read( reinterpret_cast <char*> (&aux), sizeof ( Actividad ));
        arr[i] = aux;
    }
    
    for ( int i = 0; i < n - 1; i++ ){
    	for ( int j = 0; j < n - i - 1; j++ ){
    		if ( arr[j].importancia < arr[ j + 1 ].importancia ){
    			aux = arr[j];
    			arr[j] = arr[j + 1];
    			arr[j + 1] = aux;
			 }
		 }
	 }
	 
	 archivo.seekp( 0, ios::beg );
	 
	 for ( int i = 0; i < n; i++ ){
	 	archivo.write ( reinterpret_cast <char*> (&arr[i]), sizeof ( Actividad ) );
	 }
    
   archivo.close();
	
	cout << "Actividades ordenadas con exito.\n";
	system ( "pause" );
	system ( "cls" );
	
    
}


void borrarTarea (){
	
	int n = tamanio(), continuar;
	Actividad *arr = new Actividad [n], aux;
	bool encontrado = false;
	char nombreTarea[40];
	
	do {
		
		cout << "Digite el nombre de la tarea que desea eliminar: ";
		cin.getline( nombreTarea, 40 );
		fflush ( stdin );
	
		fstream archivo ( ARCHIVO_ACTIVIDADES, ios::binary | ios::in );
		
		if (!archivo) {
            cerr << "Error al abrir el archivo." << endl;
            delete[] arr;
            return;
        }
	
		for ( int i = 0; i < n; i++ ){
			archivo.read ( reinterpret_cast <char*> (&aux), sizeof ( Actividad ));
			arr[i] = aux;
		}
		
		archivo.close();
	
		for ( int i = 0; i < n; i++ ){
		
			if ( strcmp ( arr[i].nombre, nombreTarea) == 0 ){
				for ( int j = i; j < n - 1; j++ ){
					arr[j] = arr[j + 1];
				}
				n--;
				encontrado = true;
			}
		}
	
 		cout << ( encontrado ? "Tarea eliminada exitosamente" : "Tarea no encontrada" );
 		
 		archivo.open ( ARCHIVO_ACTIVIDADES, ios::binary | ios::out ) ; 
	
		for ( int i = 0; i < n; i++ ){
			archivo.write( reinterpret_cast <char*> ( &arr[i] ), sizeof ( Actividad )); 
		}
	
		archivo.close();
		
		cout << "\n\n1. Eliminar otra tarea.\n2. Volver al menu.\nOpcion: ";
		continuar = validacionRango ( 1, 2 );
		
	} while ( continuar == 1 );
	
	system ( "cls" );
	delete [] arr;
	
}