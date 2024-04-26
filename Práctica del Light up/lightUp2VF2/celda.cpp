#include "celda.h"
#include <cctype>


char celdaToChar(const tCelda& celda) {
	char c;
	if (esParedRestringida(celda)) {
		c = numParedRestringida(celda);
	}
	else  if (esPared(celda)) {
		c = 'X';
	}
	else if (esBombilla(celda)) {
		c = '*';
	}
	else {
		c = '.';
	}
	return c;
}

tCelda charToCelda(char c) {
	tCelda celda;
	if (c == 'X') {
		celda.tipo = PARED;
		celda.numBombillas = -1;
	}
	else if (isdigit(c)) {
		celda.tipo = PARED;
		// convertir de ASCII a decimal
		celda.numBombillas = (int)c - 48;
	}
	else if (c == '.') {
		celda.tipo = LIBRE;
		celda.numBombillas = 0;
	}
	else {
		celda.tipo = BOMBILLA;
		celda.numBombillas = 1;
	}
	return celda;
}

bool esPared(const tCelda& c) {
	return c.tipo == PARED;
}

bool esParedRestringida(const tCelda& c) {
	return esPared(c) && c.numBombillas != -1;
}

int numParedRestringida(const tCelda& c) {
	return c.numBombillas;
}

bool esBombilla(const tCelda& c) {
	return c.tipo == BOMBILLA;
}

bool estaApagada(const tCelda& c) {
	return c.tipo == LIBRE && c.numBombillas <= 0;
}

bool estaIluminada(const tCelda& c) {
	return c.tipo == LIBRE && c.numBombillas > 0;
}

void apagaCelda(tCelda& c) {
	c.tipo = LIBRE;
	c.numBombillas = 0;
}

void actualizaIluminacionCelda(tCelda& c, bool iluminar) {
	if (iluminar) {
		c.numBombillas++;
	}
	else {
		c.numBombillas--;
	}
}

void ponBombilla(tCelda& c) {
	c.tipo = BOMBILLA;
	actualizaIluminacionCelda(c, true);
}

char celdaToCharArchivo(const tCelda& celda) {
	char c;
	if (esParedRestringida(celda)) {
		c = char(numParedRestringida(celda) + 48);
	}
	else  if (esPared(celda)) {
		c = 'X';
	}
	else {
		c = '.';
	}
	return c;
}