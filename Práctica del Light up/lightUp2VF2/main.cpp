// Rubén Matey y Mario Miralles, 1ºA

#include <iostream>
#include <fstream>
using namespace std;

#include "celda.h"
#include "tablero.h"
#include "colores.h"
#include "reglasJuego.h"
#include "listaPartidas.h"
#include "checkML.h"

// Funciones auxiliares
int pedirNivel();
ofstream pedirFichero(bool& abierto);

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	tListaPartidas listaPartidas;

	iniciaListaPartidas(listaPartidas);

	ifstream archivo;
	archivo.open("tableros.txt");
	bool abierto = archivo.is_open();
	if (abierto) {

		cargarListaPartidas(archivo, listaPartidas);
		int nivel = pedirNivel();
		tPtrPartida partida = dameElem(listaPartidas, buscaPos(listaPartidas, nivel));

		int nIt = 0;
		bool abandona = juega(*partida, nIt);
		cout << "Numero de pasos realizados: " << nIt << endl;

		if (!abandona) {
			eliminarPartida(listaPartidas, *partida);
		}

		bool abiertoSegundoArchivo;
		ofstream archivo2 = pedirFichero(abiertoSegundoArchivo);
		if (abiertoSegundoArchivo) {
			guardarListaPartidas(archivo2, listaPartidas);
		}
		archivo2.close();
	}
	else {
		cout << "No leido" << endl;
	}
	destruyeListaPartidas(listaPartidas);
	archivo.close();
	return 0;
}

int pedirNivel() {
	int nivel;
	do {
		cout << "Introduzca nivel: ";
		cin >> nivel;
	} while (nivel <= 0);
	return nivel;
}

ofstream pedirFichero(bool &abierto) {
	cout << "Introduzca el nombre del fichero para guardar la partida: ";
	string nombre;
	cin >> nombre;
	ofstream archivo;
	archivo.open(nombre);
	abierto = archivo.is_open();
	return archivo;
}