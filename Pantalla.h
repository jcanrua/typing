#ifndef PANTALLA_H
#define PANTALLA_H

#include "Ejercicio.h"
#include <ncurses.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include <chrono>
#include <locale.h>

class Pantalla{
private:
	static int maxX, maxY;
    static int posX, posY;
	static int posicion;
	static int espacioDisponible;
public:
    static int iniciar_pantalla();
    static void mostrar_ejercicio(std::string frase);
	static int input(std::string frase);
	static void letra_correcta(std::string frase);
	static int menu();
	static void borrar(std::string frase);
	static void letra_incorrecta(std::string frase, char incorrecto);
	static int resultado_final(float ppm, float precision, float segundos_totales);
};


#endif
