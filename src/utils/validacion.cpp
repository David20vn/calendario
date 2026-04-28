#include <iostream>
#include <string.h>

#include "validacion.h"

using namespace std;

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
		
	} while ( !validez );
}

void validacionNombre ( char nombre[] ){
	
	cin.getline( nombre, 40 ); 
	
	while ( strlen (nombre) > 40 ){
			cout << "\nNombre de actividad muy largo ( maximo 40 )\nintentelo de nuevo:";
			cin.getline( nombre,  40 );
	}
}