main: typing.cpp
	sudo g++ -o /usr/bin/prueba palabras.cpp Pantalla.cpp Ejercicio.cpp typing.cpp -lncurses

exe: typing.cpp
	sudo g++ -o typing.exe palabras.cpp Pantalla.cpp Ejercicio.cpp typing.cpp -lncurses

clean:
	sudo rm -f /usr/bin/prueba *.exe
