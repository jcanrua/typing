#include "Ejercicio.h"

int Ejercicio::correcto = 0;

int Ejercicio::incorrecto = 0;

int Ejercicio::corregido = 0;

std::chrono::high_resolution_clock::time_point Ejercicio::inicio;

std::chrono::high_resolution_clock::time_point Ejercicio::fin;

std::vector<std::chrono::high_resolution_clock::time_point> Ejercicio::pausas;

float Ejercicio::segundos_totales = 0;

std::string Ejercicio::crear_ejercicio(bool numeros, bool signos_){
	std::vector<std::string> elegidas;
	std::string frase;
    srand(time(NULL));
    for (int i = 0; i < NºPALABRAS; i++){
		elegidas.push_back(palabras[std::rand() % palabras.size()]);
    }

    if(signos_){
        for (int i = 0; i < NºSIGNOS; i++){
            int pos = std::rand() % NºPALABRAS;
            elegidas[pos] += signos[std::rand() % signos.size()];
        }
    }

    if(numeros){
        for (int i = 0; i < NºNUMEROS; i++){
			std::string valor = std::to_string(std::rand() % 1000);
            int pos = std::rand() % NºPALABRAS;
			elegidas[pos] = valor;
        }
    }
	
	for (int i = 0; i < NºPALABRAS; i++){
		frase += elegidas[i];
		if(i != NºPALABRAS-1){
			frase += " ";
		}
	}	

    return frase;
}

float Ejercicio::ppm(){
	int pulsaciones = correcto + incorrecto + corregido;
	return pulsaciones / float(60 * segundos_totales);
}

float Ejercicio::precision(){
	int total_pulsaciones = correcto + incorrecto;
	if(total_pulsaciones == 0){
		return 0;
	}
	return (float(correcto) / total_pulsaciones) * 100;

}

int Ejercicio::set(int option){
	switch(option){
		case 1:
			correcto++;
			break;
		case 2:
			incorrecto++;
			break;
		case 3:
			corregido++;
			break;
		case 4:
			inicio = std::chrono::high_resolution_clock::now();
			break;
		case 5:
			fin = std::chrono::high_resolution_clock::now();
			break;
		case 6:
			pausas.push_back(std::chrono::high_resolution_clock::now());
			break;
		default:
			return -1;
	}
	return 0;
}

void Ejercicio::gestionar_tiempo(){
	long int duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
	
	for (int i = 0; i < (pausas.size()/2); i += 2){
		duracion -= std::chrono::duration_cast<std::chrono::microseconds>(pausas[i+1] - pausas[i]).count();
	}

	segundos_totales = std::round((static_cast<double>(duracion) / 1000000.0) * 100) / 100;
}

float Ejercicio::segundos_total(){
	return segundos_totales;
}
