#include "palabras.h"
#include "Pantalla.h"
#include "Ejercicio.h"
#include <ncurses.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <string>

int main(int argc, char *argv[]){
	bool signos = false, numeros = false;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            for (int j = 1; j < std::strlen(argv[i]); j++) {
                if (argv[i][j] == 's') {
                    signos = true;
                } else if (argv[i][j] == 'n') {
                    numeros = true;
                }
            }
        }
    }
	if(Pantalla::iniciar_pantalla() < 0){
		return -1;
	}
	
	int a = 0;
	do{
		std::string frase = Ejercicio::crear_ejercicio(numeros, signos);
		Pantalla::mostrar_ejercicio(frase);
		Ejercicio::set(4);
		if(Pantalla::input(frase) == -1){
			a = -1;
		}
		Ejercicio::set(5);
		Ejercicio::gestionar_tiempo();
		if(Pantalla::resultado_final(Ejercicio::ppm(), Ejercicio::precision(), Ejercicio::segundos_total())){
			a == -1;
		}
	} while(a == 0);
		
		
	endwin();;
	return 0;	

}
