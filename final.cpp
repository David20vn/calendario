/*

trabajo final basado en un programa que ofrece 31 casillas que se pueden usar libremente para
la organizacion de actividades para un mes. Teniendo opciones como:
( Agregar tarea, Listar tareas, Buscar una tarea, Modificar una tarea, Ordenar tareas, Borrar una tarea, Mostrar calendario )

David Vasquez Naranjo
5.11
6/11/2024

*/

#include <iostream>
#include <cctype>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <windows.h>

using namespace std;

// ----- estructura de la actividad ------- //

struct Actividad {
	int dia;
	char nombre [40];
	int importancia;
	int tiempo;
};

// ---------- validaciones --------- //

int validacionRango ( int minimo, int maximo ){
	
	bool validez ;
	string n;
	int num;
	
	do {
		
		cin >> n;
		fflush(stdin);
		
		num = 0;
		validez = true;
		
		for ( int i = 0; i < n.length(); i++ ){
			
			if ( !isdigit ( n[i] ))
				validez = false;
			
		}
		
		for ( int i = 0; i < n.length(); i++ ){
			num = num * 10 + ( n[i] - '0' );
		}
		
		if ( num < minimo || num > maximo )
			validez = false;
		
		if ( !validez  )
			cout << "Numero no valido. rango (" << minimo << " - " << maximo << ")\nintentelo de nuevo: ";
		else
			return num;
		
	} while (  !validez );
}

void validacionNombre ( char nombre[] ){
	
	cin.getline( nombre, 40 ); 
	
	while ( strlen (nombre) > 40 ){
			cout << "\nNombre de actividad muy largo ( maximo 40 )\nintentelo de nuevo:";
			cin.getline( nombre,  40 );
	}
}

// ------------- menu ------------ //

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

//----------- auxiliares -------------//

int tamanio (){
	
	Actividad aux;
	int counter = 0;
	ifstream archivo ( "actividades.dat", ios::binary );
	
	if ( !archivo )
		cout << "Error en abrir el archivo.";
	
	while ( archivo.read ( reinterpret_cast <char*> (&aux), sizeof ( Actividad ))){
		counter++;
	}
	
	archivo.close();
	return counter;
}

// --------- opciones ---------------- //

// 1.

void agregar(){

	int opcion = 1;
	char nombre [40];
	Actividad stru;
	
	ofstream archivo ( "actividades.dat", ios::binary | ios::app );
	
	if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
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

// 2.

void listar (){
	
	ifstream archivo ( "actividades.dat", ios::binary );
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

// 3.


void buscarTarea (){
	
	Actividad aux;
	char nombreTarea[40];
	bool encontrada;
	int opcion;
	
	do {
		
		encontrada = false;
		
		cout << "Digite el nombre de la tarea a buscar: ";
		cin.getline( nombreTarea, 40 );
	
		ifstream archivo ( "actividades.dat", ios::binary );
		
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

// 4.

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
	
		fstream archivo ( "actividades.dat", ios::binary | ios::out | ios::in );
		
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

// 5. 

void ordenar (){
	
	int n = tamanio();
	Actividad *arr = new Actividad [n], aux;
	
	fstream archivo ( "actividades.dat", ios::binary | ios::in | ios::out );
	
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

// 6.

void borrarTarea (){
	
	int n = tamanio(), continuar;
	Actividad *arr = new Actividad [n], aux;
	bool encontrado = false;
	char nombreTarea[40];
	
	do {
		
		cout << "Digite el nombre de la tarea que desea eliminar: ";
		cin.getline( nombreTarea, 40 );
		fflush ( stdin );
	
		fstream archivo ( "actividades.dat", ios::binary | ios::in );
		
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
 		
 		archivo.open ( "actividades.dat", ios::binary | ios::out ) ; 
	
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

// 7.

void imprimirMatriz ( int arr[] ){

	int diaContador = 1, diaImportancia = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char ch = 219;
	
	cout << "Cada dia esta representado por la actividad de mayor importancia.\nImportancia:\n\n";
	
	cout << "( 1 - 4 ):\t";
	SetConsoleTextAttribute(hConsole, 3); // convertirlo azul
   cout << ch << ch;
	SetConsoleTextAttribute(hConsole, 7); // volver a blanco
	
	cout << "\n( 5 - 7 ):\t";
	SetConsoleTextAttribute(hConsole, 6); // convertirlo amarillo
   cout << ch << ch;
	SetConsoleTextAttribute(hConsole, 7); // volver a blanco
	
	cout << "\n( 8 - 10 ):\t";
	SetConsoleTextAttribute(hConsole, 4 ); // convertirlo rojo
   cout << ch << ch << endl << endl;
	SetConsoleTextAttribute(hConsole, 7); // volver a blanco
	
	for ( int i = 0; i < 16; i++ ){
		
		if ( i == 0 )
			cout << char ( 218 ) << "--------------------" << char ( 191 ) << endl;
		else if ( i % 3 == 0 && i != 15  )
			cout << "|--" << char ( 197 ) << "--" << char ( 197 ) << "--" << char ( 197 ) << "--" << char ( 197 ) << "--" << char ( 197 ) << "--" << char ( 197 ) << "--|\n";
		else if ( i == 15 )
			cout << char ( 192 ) << "--+--+--|";
		else {
			for ( int j = 0; j < 22; j++ ){
				
				if ( i <= 12 || j <= 9 ){
					
					if ( j % 3 == 0 )
						cout << "|";
						
					else if ( (i - 1) % 3 == 0 && (j - 1) % 3 == 0 ){
						cout << setw(2) << diaContador;
						diaContador++;
								
					} else if ( (i - 2) % 3 == 0 && (j - 1) % 3 == 0 ){
					
						if ( arr[diaImportancia] > 0 && arr[diaImportancia] < 5 ){
					
   						SetConsoleTextAttribute(hConsole, 3); // convertirlo azul
    						cout << ch << ch;
    						SetConsoleTextAttribute(hConsole, 7); // volver a blanco
						
						} else if ( arr[diaImportancia] >= 5 && arr[diaImportancia] < 8 ){
						
   						SetConsoleTextAttribute(hConsole, 6); // convertirlo amarillo
    						cout << ch << ch;
    						SetConsoleTextAttribute(hConsole, 7); // volver a blanco
						
						} else if ( arr[diaImportancia] >= 8 ){
						
   						SetConsoleTextAttribute(hConsole, 4 ); // convertirlo rojo
    						cout << ch << ch;
    						SetConsoleTextAttribute(hConsole, 7); // volver a blanco
    					
						} else 
							cout << "  ";
					
						diaImportancia++;
					}
				}	
			}
			cout << endl;
		}
	}
	cout << endl;
}

void calendario (){
	
	int n = tamanio();
	Actividad *arr = new Actividad[n], aux;
	int vecImportancia[31] = {};
	
	ifstream archivo ( "actividades.dat", ios::binary );
	
	for ( int i = 0; i < n; i++ ){
			archivo.read ( reinterpret_cast <char*> (&aux), sizeof ( Actividad ));
			arr[i] = aux;
		}
		
	archivo.close();
	
	for ( int i = 0; i < n; i++ ){
		if ( vecImportancia[ arr[i].dia - 1 ] < arr[i].importancia )
			vecImportancia[ arr[i].dia - 1 ] = arr[i].importancia;
	}
	
	imprimirMatriz ( vecImportancia );
	system ( "pause" );
	system ( "cls" );
}

// ----- funcion principal -----//

int main (){
	
	int opcion, auxNum;
	char auxChar;
	
	while ( opcion != 8 ){
		
		opcion = menuPrincipal();
	
		switch ( opcion ){
			
			case 1: 
				agregar();
				break;
				
			case 2:
				listar(); 
				break;
				
			case 3:
				buscarTarea();
				break;
				
			case 4:
				modificar();
				break;
				
			case 5:
				ordenar();
				break;
				
			case 6:
				borrarTarea();
				break;
				
			case 7:
				calendario();
				break;
		}
	}
}













