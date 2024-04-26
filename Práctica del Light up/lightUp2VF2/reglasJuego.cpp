#include <iostream>
using namespace std;

#include "tablero.h"
#include "reglasJuego.h"

typedef enum tDir { NORTE, SUR, ESTE, OESTE };

int bombillasAlrededor(tTablero const& tab, int x, int y);
void mover(int& x, int& y, tDir dir);
void apagarOencender(tTablero& tab, int x, int y, bool ilumina);
void iluminar(tTablero& tab, int x, int y, tDir dir, bool iluminar);
bool esPosReset(int x, int y);
void resetearTablero(tTablero& tab);
bool esValida(const tTablero& tab, int x, int y);


// FUNCIONES PÚBLICAS
bool estaTerminado(tTablero const& tab) {
	int i = 0;
	int j = 0;
	bool terminado = true;
	tCelda celda;

	while (terminado && i < getNumFilas(tab)) {
		j = 0;
		while (terminado && j < getNumCols(tab)) {
			if (estaApagada(celdaEnPos(tab, i, j))) {
				terminado = false;
			}
			else if (esParedRestringida(celdaEnPos(tab, i, j))) {
				terminado = numParedRestringida(celdaEnPos(tab, i, j)) == bombillasAlrededor(tab, i, j);
			}
			j++;
		}
		i++;
	}
	return terminado;
}


void ejecutarPos(tTablero& tab, int x, int y) {
	if (esPosReset(x, y)) {
		resetearTablero(tab);
	}
	else if (!esPared(celdaEnPos(tab, x, y))) {
		bool ilumina = !esBombilla(celdaEnPos(tab, x, y));
		if (ilumina && !estaIluminada(celdaEnPos(tab, x, y))) {
			apagarOencender(tab, x, y, true);
		}
		else if (!ilumina) {
			apagarOencender(tab, x, y, false);
		}
	}
}



// FUNCIONES AUXILIARES
// función auxiliar para estaTerminado
int bombillasAlrededor(const tTablero& tab, int x, int y) {
	int res = 0;
	for (tDir dir = NORTE; dir <= OESTE; dir = tDir(int(dir) + 1)) {
		int posX = x;
		int posY = y;
		mover(posX, posY, dir);
		
		if (esValida(tab, x, y) && esBombilla(celdaEnPos(tab, posX, posY))) res++;
	}
	return res;
}


bool esValida(const tTablero& tab, int x, int y) {
	return x >= 0 && y >= 0 && x < getNumFilas(tab) && y < getNumCols(tab);
}

// actualiza el valor de x e y, dependiendo de la dirección
void mover(int& x, int& y, tDir dir) {
	switch (dir) {
	case NORTE: {
		x--;
		break;
	}case SUR: {
		x++;
		break;
	}case ESTE: {
		y++;
		break;
	}case OESTE: {
		y--;
	}
	}
}

// función auxiliar para ejecutarPos
void apagarOencender(tTablero& tab, int x, int y, bool ilumina){
	tCelda celda = celdaEnPos(tab, x, y);

	if (ilumina) ponBombilla(celda);
	else apagaCelda(celda);

	ponCeldaEnPos(tab, x, y, celda);

	for (tDir dir = NORTE; dir <= OESTE; dir = tDir(int(dir) + 1)) {
		iluminar(tab, x, y, dir, ilumina);
	}
}

// actualizar la iluminación de cada celda afectada al colocar una bombilla
void iluminar(tTablero& tab, int x, int y, tDir dir, bool iluminar) {
	mover(x, y, dir);
	while (x >= 0 && y >= 0 && x < getNumFilas(tab) && y < getNumCols(tab) && !esPared(celdaEnPos(tab, x, y))) {
		tCelda celda = celdaEnPos(tab, x, y);
		actualizaIluminacionCelda(celda, iluminar);
		ponCeldaEnPos(tab, x, y, celda);
		mover(x, y, dir);
	}
}

bool esPosQuit(int x, int y) {
	return x == -1 && y == 0;
}

bool esPosReset(int x, int y) {
	return x == -1 && y == -1;
}

void resetearTablero(tTablero& tab) {
	tCelda c;
	for (int i = 0; i < getNumFilas(tab); i++){
		for (int j = 0; j < getNumCols(tab); j++) {
			c = celdaEnPos(tab, i, j);
			if (!esPared(c)) {
				apagaCelda(c);
				ponCeldaEnPos(tab, i, j, c);
			}
		}
	}
}