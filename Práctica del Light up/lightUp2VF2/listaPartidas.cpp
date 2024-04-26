#include "listaPartidas.h"


void iniciaListaPartidas(tListaPartidas& listaPartidas) {
	listaPartidas.nElem = 0;
}

void cargarListaPartidas(ifstream& archivo, tListaPartidas& listaPartidas) {
	int nElem;
	archivo >> nElem;
	if (nElem > MAX_PARTIDAS) nElem = MAX_PARTIDAS;
	for (int i = 0; i < nElem; i++) {
		tPtrPartida partida = new tPartida;
		cargarPartida(archivo, *partida);
		insertarOrd(listaPartidas, *partida);
		delete partida;
	}
}


void insertarOrd(tListaPartidas& listaPartidas, const tPartida& partida) {
	if (listaPartidas.nElem < MAX_PARTIDAS) {
		int i = 0;
		while ( i < dameNumElem(listaPartidas) && *listaPartidas.datos[i] < partida) {
			i++;
		}
		for (int j = listaPartidas.nElem; j > i; j--) {
			listaPartidas.datos[j] = listaPartidas.datos[j - 1];
		}
		listaPartidas.datos[i] = new tPartida (partida);
		listaPartidas.nElem++;
	}
}

int buscaPos(const tListaPartidas& listaPartidas, int nivel) {
	int i = 0;
	while (i < listaPartidas.nElem && *listaPartidas.datos[i] < nivel) {
		i++;
	}
	if (i == listaPartidas.nElem) i--;
	return i;
}

tPtrPartida dameElem(const tListaPartidas& listaPartidas, int pos) {
	return listaPartidas.datos[pos];
}

int dameNumElem(const tListaPartidas& listaPartidas) {
	return listaPartidas.nElem;
}

void eliminarPartida(tListaPartidas& listaPartidas, const tPartida& partida) {
	int i = 0;
	while (*listaPartidas.datos[i] < partida) {
		i++;
	}
	listaPartidas.nElem--;
	for (int j = i; j < listaPartidas.nElem; j++) {
		listaPartidas.datos[j] = listaPartidas.datos[j + 1];
	}
}

void guardarListaPartidas(ofstream& archivo, const tListaPartidas& listaPartidas) {
	archivo << listaPartidas.nElem << endl;
	for (int i = 0; i < listaPartidas.nElem; i++) {
		guardaPartida(archivo, *listaPartidas.datos[i]);
	}
}

void destruyeListaPartidas(tListaPartidas& listaPartidas) {
	for (int i = 0; i < listaPartidas.nElem; i++) {
		destruyePartida(*listaPartidas.datos[i]);
		delete listaPartidas.datos[i];
		listaPartidas.datos[i] = nullptr;
	}
}