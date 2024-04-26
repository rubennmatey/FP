#pragma once
#include <iostream>
#include <fstream>
using namespace std;

#include "tablero.h"
#include "listaPosiciones.h"
#include "reglasJuego.h"
#include "celda.h"


typedef struct {
	tTablero tablero;
	tListaPosiciones listaBombillas;
	int nivel;
} tPartida;

void iniciaPartida(tPartida& partida);
void cargarPartida(ifstream& archivo, tPartida& partida);
bool operator <(const tPartida& partida, int nivel);
bool operator < (const tPartida& partida1, const tPartida& partida2);
bool juega(tPartida& partida, int& nIt);
void guardaPartida(ofstream& archivo, const tPartida& partida);
void destruyePartida(tPartida& partida);

// preguntar
int getNivel(const tPartida& partida);