#include <iostream>
#include <cctype>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <windows.h>

#include "models/actividad.h"
#include "utils/validacion.cpp" 
#include "utils/archivo_utils.cpp"

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
	
	ifstream archivo ( ARCHIVO_ACTIVIDADES, ios::binary );
	
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