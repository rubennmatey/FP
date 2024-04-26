#pragma once
#include "celda.h"
#include <fstream>
using namespace std;

const int MAX_FILS = 10;
const int MAX_COLS = 10;
typedef struct {
	int nFils, nCols;
	tCelda tablero[MAX_FILS][MAX_COLS];
} tTablero;

int getNumFilas(const tTablero& tab);
int getNumCols(const tTablero& tab);
tCelda celdaEnPos(const tTablero& tab, int x, int y);
void ponCeldaEnPos(tTablero& tab, int x, int y, const tCelda& c);
bool leerTablero(ifstream& archivo, tTablero& tab);
void mostrarTablero(const tTablero& tab);

