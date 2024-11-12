#include "Pantalla.h"

int Pantalla::maxX = 0;

int Pantalla::maxY = 0;

int Pantalla::posX = 0;

int Pantalla::posY = 0;

int Pantalla::posicion = 0;

int Pantalla::espacioDisponible = 0;

int Pantalla::iniciar_pantalla(){
	setlocale(LC_ALL, "");
    if(initscr() == NULL){
		std::cout << "ERROR al iniciar ncurses" << std::endl;
		return -1;
	}

	if(!has_colors()) {
		endwin();
		std::cout << "ERROR terminal no tiene color" << std::endl;
		return -1;
	}
	
	noecho();
	keypad(stdscr, FALSE);
    getmaxyx(stdscr, maxY, maxX);
	posX = maxX/4;
	posY = maxY/3;
	espacioDisponible = (3 * maxX)/4 - (maxX/4);

	start_color();
	init_color(COLOR_GREEN, 180, 545, 341);
	init_color(COLOR_BLACK, 156, 172, 203);
	init_color(COLOR_RED, 769, 337, 337);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);

	return 0;
}

void Pantalla::mostrar_ejercicio(std::string frase){
	int i = 0;
	while(i < frase.size()){
		mvprintw(posY, posX, frase.substr(i, espacioDisponible).c_str());
		i += espacioDisponible;
		posY++;
		if(posY >= maxY){
			break;
		}
	}
	posX = maxX/4;
	posY = maxY/3;
	move(posY, posX);
    refresh();
}

int Pantalla::input(std::string frase){
	char a;
	int posicionLinea = 0;
    do{
       	a = getch();
        if(a == 27){
			Ejercicio::set(6);
            if(Pantalla::menu() == -1){
				return -1;
			}
			else{
				Ejercicio::set(6);
				continue;				
			}
		}
        else if(a == 127){
			if(posicionLinea == 0 && posY != maxY/3){
				posY--;
				posX = (3 * maxX/4);
				posicionLinea = espacioDisponible - 1;
				Pantalla::borrar(frase);
				posicion--;
				Ejercicio::set(3);
				move(posY, posX);
				refresh();
			}
			else if(posicionLinea > 0){
            	Pantalla::borrar(frase);
				posicion--;
				posicionLinea--;
				Ejercicio::set(3);
			}
		}
		else if(posicionLinea < espacioDisponible){
        	if(a == frase[posicion]){
            	Pantalla::letra_correcta(frase);
				posicion++;
				posicionLinea++;
				Ejercicio::set(1);
        	}
       		else{
            	Pantalla::letra_incorrecta(frase, a);
				posicion++;
				posicionLinea++;
				Ejercicio::set(2);
       		}
		}
		else if (a == 10){
			posicionLinea = 0;
            posY++;
			posX = maxX/4;
			Ejercicio::set(1);
            move(posY, posX); 
            refresh();
		}
    } while(posicion < frase.size());
	return 1;
}


void Pantalla::letra_correcta(std::string frase){
	attron(COLOR_PAIR(1));
	mvaddch(posY, posX, frase[posicion]);
	attroff(COLOR_PAIR(1));
    posX++;
}

void Pantalla::letra_incorrecta(std::string frase, char incorrecto){
	if(frase[posicion] != 32){
		attron(COLOR_PAIR(2));
		mvaddch(posY, posX, frase[posicion]);
		attroff(COLOR_PAIR(2));
	}
	else{
		attron(COLOR_PAIR(2));
		mvaddch(posY, posX, incorrecto);
		attroff(COLOR_PAIR(2));
	}
	posX++;
}

void Pantalla::borrar(std::string frase){
	if(posX > maxX/4 || posY != maxY/3){
		posX--;
		mvaddch(posY, posX, ' ');
		mvaddch(posY, posX, frase[posicion - 1]);
		move(posY, posX);
		refresh();
	}
}

int Pantalla::menu(){
	int menuAltura = 7;
	int menuAncho = 40;
	int startY = (maxY - menuAltura) / 2;
	int startX = (maxX - menuAncho) / 2;

	WINDOW* menuWin = newwin(menuAltura, menuAncho, startY, startX);
	curs_set(0);
    box(menuWin, 0, 0);
    mvwprintw(menuWin, 3, 3, "ESC para salir, otra para quedarte");

    wrefresh(menuWin);

	int option = wgetch(menuWin);
    delwin(menuWin);
	touchwin(stdscr);
	refresh();
	curs_set(1);

    if (option == 27) {
        return -1;  
    } 
	else{
        return 0;
    }
}

int Pantalla::resultado_final(float ppm, float precision, float segundos_totales){
	int resultadoAltura = maxY/3;
	int resultadoAncho = maxX/2;
	int startY = (maxY - resultadoAltura) / 2;
	int startX = (maxX - resultadoAncho) / 2;

	WINDOW* resultadoWin = newwin(resultadoAltura, resultadoAncho, startY, startX);
	curs_set(0);
	clear();
	box(resultadoWin, 0, 0);
	mvwprintw(resultadoWin, resultadoAltura/3, resultadoAncho/4, "PPM: %.2f", ppm);
	mvwprintw(resultadoWin, resultadoAltura/3, (2 * resultadoAncho)/4, "Tiempo: %.2f s", segundos_totales);
	mvwprintw(resultadoWin, resultadoAltura/3, (3 * resultadoAncho)/4, "Precisión: %.2f", precision);
	
	//mvwprintw(resultadoWin, resultadoAltura/2 resultadoAncho/2, "Nota final: %f", ppm);
	
	wrefresh(resultadoWin);
	
	int option = wgetch(resultadoWin);
	delwin(resultadoWin);
	touchwin(stdscr);
	refresh();

	if(option == 27){
		return -1;
	}
	else{
		return 0;
	}
}



