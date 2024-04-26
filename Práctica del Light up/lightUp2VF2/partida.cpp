#include "partida.h"
#include "reglasJuego.h"


void colocarBombillas(tPartida& partida);
bool esPosQuit(int x, int y);
bool esPosReset(int x, int y);
void menu(int& x, int& y, bool terminado, bool& abandona, int nFils, int nCols);
void guardarListaBombillas(tPartida& partida);
void leerBombillas(ifstream& archivo, tPartida& partida);
void guardarTablero(ofstream& archivo, const tPartida& partida);
bool esValida(int x, int y, int nFils, int nCols);

void iniciaPartida(tPartida& partida) {
	iniciaListaPosiciones(partida.listaBombillas);
	partida.nivel = 0;
}

void cargarPartida(ifstream& archivo, tPartida& partida) {
	string basura;
	int nivel;
	archivo >> basura >> nivel;
	iniciaPartida(partida);
	partida.nivel = nivel;
	leerTablero(archivo, partida.tablero);
	leerBombillas(archivo, partida);
}

bool operator < (const tPartida& partida, int nivel) {
	return partida.nivel < nivel;
}

bool operator < (const tPartida& partida1, const tPartida& partida2) {
	return partida1.nivel < partida2.nivel;
}

bool juega(tPartida& partida, int& nIt) {
	colocarBombillas(partida);

	mostrarTablero(partida.tablero);

	bool terminado = estaTerminado(partida.tablero);
	int x = 0, y = 0;
	bool abandona = false;

	// tutorial
	menu(x, y, terminado, abandona, getNumFilas(partida.tablero), getNumCols(partida.tablero));


	while (!terminado && !abandona) {
		system("cls");
		
		ejecutarPos(partida.tablero, x, y);
		mostrarTablero(partida.tablero);

		terminado = estaTerminado(partida.tablero);
		menu(x, y, terminado, abandona, getNumFilas(partida.tablero), getNumCols(partida.tablero));
		nIt++;
	}
	if (abandona) {
		cout << "ABANDONADO" << endl;
		guardarListaBombillas(partida);
	}

	return abandona;

}


void colocarBombillas(tPartida& partida) {
	int numBombillas = dameNumElem(partida.listaBombillas);
	for (int i = 0; i < numBombillas; i++) {
		tPosicion pos = dameElem(partida.listaBombillas, i);
		ejecutarPos(partida.tablero, dameX(pos), dameY(pos));
	}
}

void leerBombillas(ifstream& archivo, tPartida& partida) {
	int numBombillas;
	archivo >> numBombillas;
	for (int i = 0; i < numBombillas; i++) {
		int x, y;
		archivo >> x >> y;
		tPosicion pos;
		iniciaPosicion(pos, x, y);
		insertar(partida.listaBombillas, pos);
	}
}

void menu(int& x, int& y, bool terminado, bool& abandona, int nFils, int nCols) {
	if (!terminado) {
		cout << "(-1, 0) para abandonar" << endl;
		cout << "(-1, -1) para resetear" << endl;
		do {
			cout << "Introduzca casilla (fila, columna): ";
			cin >> x >> y;
			//cout << endl << endl;
			abandona = esPosQuit(x, y);
		} while (esValida(x, y, nFils, nCols) && !abandona && !(x == -1 && y == -1));
		
	}
	else {
		cout << "TERMINADO" << endl;
	}
}
bool esValida(int x, int y, int nFils, int nCols) {
	return x > nFils || x < 0 || y > nCols || y < 0;
}


void guardarListaBombillas(tPartida& partida) {
	destruyeListaPosiciones(partida.listaBombillas);
	iniciaListaPosiciones(partida.listaBombillas);
	for (int i = 0; i < getNumFilas(partida.tablero); i++) {
		for (int j = 0; j < getNumCols(partida.tablero); j++) {
			if (esBombilla(celdaEnPos(partida.tablero, i, j))) {
				tPosicion pos;
				iniciaPosicion(pos, i, j);
				insertar(partida.listaBombillas, pos);
			}
		}
	}
}

void guardaPartida(ofstream& archivo, const tPartida& partida) {
	guardarTablero(archivo, partida);
	guardarListaBombillas(archivo, partida.listaBombillas);
	
}

void guardarTablero(ofstream& archivo, const tPartida& partida) {
	int filas = getNumFilas(partida.tablero);
	int columnas = getNumCols(partida.tablero);
	archivo << "LEVEL " << partida.nivel << endl;
	archivo << filas << " " << columnas << endl;
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			char c = celdaToCharArchivo(celdaEnPos(partida.tablero, i, j));
			archivo << c;
		}
		archivo << endl;
	}
}

void destruyePartida(tPartida& partida) {
	destruyeListaPosiciones(partida.listaBombillas);
	partida.nivel = 0;
}

int getNivel(const tPartida& partida) {
	return partida.nivel;
}