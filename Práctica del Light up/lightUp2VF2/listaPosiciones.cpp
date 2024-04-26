#include "listaPosiciones.h"
#include "posicion.h"

void redimensionar(tListaPosiciones& lp);
void copiar(tListaPosiciones& arrayDestino, const tListaPosiciones& arrayOrigen);

void iniciaListaPosiciones(tListaPosiciones& lp) {
	lp.cont = 0;
	lp.size = DIM;
	lp.arrayPos = new tPosicion[DIM];
}

void destruyeListaPosiciones(tListaPosiciones& lp) {
	delete[] lp.arrayPos;
	lp.arrayPos = nullptr;
	lp.cont = 0;
	lp.size = 0;
}

void insertar(tListaPosiciones& lp, const tPosicion& pos) {
	if (lp.cont == lp.size) {
		redimensionar(lp);
	}
	lp.arrayPos[lp.cont] = pos;
	lp.cont++;
}

void redimensionar(tListaPosiciones& lp) {
	tListaPosiciones aux;
	aux.arrayPos = new tPosicion[lp.size * 2];
	copiar(aux, lp);
	delete[] lp.arrayPos;
	lp.arrayPos = aux.arrayPos;
}

void copiar(tListaPosiciones& arrayDestino, const tListaPosiciones& arrayOrigen) {
	for (int i = 0; i < arrayOrigen.cont; i++) {
		arrayDestino.arrayPos[i] = arrayOrigen.arrayPos[i];
	}
}

int dameNumElem(const tListaPosiciones& lp) {
	return lp.cont;
}

tPosicion dameElem(const tListaPosiciones& lp, int i) {
	return lp.arrayPos[i];
}

void guardarListaBombillas(ofstream& archivo, const tListaPosiciones& lp) {
	archivo << lp.cont << endl;
	for (int i = 0; i < lp.cont; i++) {
		guardarPosicion(archivo, lp.arrayPos[i]);
	}
}