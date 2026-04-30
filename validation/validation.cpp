#include <iostream>
#include <string.h>
#include <cctype>
#include <string>
#include <limits>

#include "validation.h"

using namespace std;

int validacionRango(int minimo, int maximo) {
    string entrada;
    int numero = 0;

    while (true) {
        cin >> entrada;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        bool entradaValida = !entrada.empty();
        numero = 0;

        for (char caracter : entrada) {
            if (!isdigit(static_cast<unsigned char>(caracter))) {
                entradaValida = false;
                break;
            }

            numero = numero * 10 + (caracter - '0');
        }

        if (entradaValida && numero >= minimo && numero <= maximo) {
            return numero;
        }

        cout << "Numero no valido. Rango (" << minimo << " - " << maximo
             << ")\nIntentelo de nuevo: ";
    }
}

void validacionNombre ( char nombre[] ){

	cin.getline( nombre, 40 ); 
	
	while ( strlen (nombre) > 40 || strlen(nombre)==0 ){
			cout << "\nNombre de actividad invalido\nintentelo de nuevo:";
			cin.getline( nombre,  40 );
	}
}