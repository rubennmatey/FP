#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#include "tablero.h"
#include "celda.h"
#include "colores.h"

void dibujarSeparador(int col);
void dibujarLinea(const tTablero& tab, int linea);

// FUNCIONES PUBLICAS
int getNumFilas(const tTablero& tab) {
	return tab.nFils;
}

int getNumCols(const tTablero& tab) {
	return tab.nCols;
}

tCelda celdaEnPos(const tTablero& tab, int x, int y) {
	return tab.tablero[x][y];
}

void ponCeldaEnPos(tTablero& tab, int x, int y, const tCelda& c) {
	tab.tablero[x][y] = c;
}

bool leerTablero(ifstream& archivo, tTablero& tab) {
	archivo >> tab.nFils;
	archivo >> tab.nCols;
	char c;

	for (int i = 0; i < tab.nFils; i++) {
		for (int j = 0; j < tab.nCols; j++) {
			archivo >> c;
			tab.tablero[i][j] = charToCelda(c);
		}
	}
	return true;
}

void mostrarTablero(const tTablero& tab) {
	cout << setw(10) << "";
	for (int col = 0; col < tab.nCols; col++) {
		cout << setw(2) << "|" << CYAN << setw(2) << right << col << RESET;
	}
	cout << setw(2) << "|" << endl;
	dibujarSeparador(tab.nCols);
	for (int fila = 0; fila < tab.nFils; fila++) {
		dibujarLinea(tab, fila);
		dibujarSeparador(tab.nCols);

	}
}


// FUNCIONES AUXILIARES
void dibujarSeparador(int col) {
	cout << setw(11) << "-";
	for (int i = 0; i < col; i++) {
		cout << "+---";
	}
	cout << "+" << endl;
}

void dibujarLinea(const tTablero& tab, int linea) {
	cout << CYAN << setw(11) << linea << RESET;
	for (int i = 0; i < tab.nCols; i++) {
		cout << "|";
		if (esParedRestringida(tab.tablero[linea][i])) {
			cout << " " << right << numParedRestringida(tab.tablero[linea][i]) << " ";
		}
		else if (estaApagada(tab.tablero[linea][i])) {
			cout << BG_WHITE << "   ";
		}
		else if (esBombilla(tab.tablero[linea][i])) {
			cout << BG_YELLOW << " * ";
		}
		else if (estaIluminada(tab.tablero[linea][i])) {
			cout << BG_YELLOW << "   ";
		}
		else {
			cout << "   ";
		}
		cout << RESET;
	}
	cout << "|" << endl;
}

