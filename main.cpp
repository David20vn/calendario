/*

trabajo final basado en un programa que ofrece 31 casillas que se pueden usar libremente para
la organizacion de actividades para un mes. Teniendo opciones como:
( Agregar tarea, Listar tareas, Buscar una tarea, Modificar una tarea, Ordenar tareas, Borrar una tarea, Mostrar calendario )

David Vasquez Naranjo
5.11
6/11/2024

*/

#include "models/actividad.h"
#include "validation/validation.h"
#include "ui_proyect/menu.h"
#include "auxiliars/auxiliars.h"
#include "services/actividad_service.h"

using namespace std;
 
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
