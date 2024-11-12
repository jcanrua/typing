#ifndef EJERCICIO_H
#define EJERCICIO_H

#include "palabras.h"
#include "define.h"
#include <ncurses.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <string>
#include <chrono>
#include <cmath>

class Ejercicio{
	private:
		static int correcto;
		static int incorrecto;
		static int corregido;
		static std::chrono::high_resolution_clock::time_point inicio;
		static std::chrono::high_resolution_clock::time_point fin;
		static std::vector<std::chrono::high_resolution_clock::time_point> pausas;
		static float segundos_totales;
	public:
		static std::string crear_ejercicio(bool numeros, bool signos_);
		static float ppm();
		static float precision();
		static int set(int opcion);
		static void gestionar_tiempo();
		static float segundos_total();
};

#endif 
