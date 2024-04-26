#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_AFECTACIONES = 3;
const int MAX_ENTRADAS = 50;

typedef string tArrayAfect[MAX_AFECTACIONES];

struct tListaAfectaciones {
	tArrayAfect afectaciones;
	int cont = 0;
	
};

 struct tEntrada {
	tListaAfectaciones afectTotales;
	string carretera = " ";
	int puntoOrigen = 0;
	int puntoFin = 0;
	
};

typedef tEntrada tArrayTramos[MAX_ENTRADAS];

struct tListaTramos {
	tArrayTramos entrada;
	int numEntradas = 0;
	
};


bool cargar(tListaTramos& listaTramos);
int buscaEntrada(tListaTramos lista, string carretera, int punto);
void consulta(tListaTramos lista, string carretera, int punto);
bool elimina(tListaTramos& lista, string carretera, int punto);
void listado(const tListaTramos lista);
int menu();



int main() {
	tListaTramos lista;
	int opcion, punto;
	string id;
	bool eliminado;


	if (!cargar(lista)) {
		cout << "No se puede cargar el archivo" << endl;
	}
	else {
		opcion = menu();
		while (opcion != 0) {
			switch (opcion) {
			case 1: {
				cout << "Introzuca la carretera ";
				cin >> id;
				cout << endl;
				cout << "Introzuca el kilometro ";
				cin >> punto;
				consulta(lista, id,punto);
				cout << endl;

			}break;
			case 2: {
				cout << "Introzuca la carretera ";
				cin >> id;
				cout << endl;
				cout << "Introzuca el kilometro ";
				cin >> punto;
				eliminado = elimina(lista, id, punto);
				if (!eliminado) {
					cout << "No se pudo eliminar" << endl;
				}
				else if (eliminado) {
					cout << "Entrada eliminada con exito" << endl;
				}
			}break;
			case 3: {
				listado(lista);
			}break;
			}
			opcion = menu();
		}
	}
	return 0;
}

bool cargar(tListaTramos& listaTramos) {
	ifstream archivo;
	bool abierto = false;
	int i = 0;
	archivo.open("carreteras.txt");
	if (archivo.is_open()) {
		archivo >> listaTramos.entrada[i].carretera;
		while (listaTramos.entrada[i].carretera != "XXX" && i < MAX_ENTRADAS) {
			archivo >> listaTramos.entrada[i].puntoOrigen;
			archivo >> listaTramos.entrada[i].puntoFin;
			archivo >> listaTramos.entrada[i].afectTotales.cont;
			for (int j = 0; j < listaTramos.entrada[i].afectTotales.cont; j++) {
				archivo >> listaTramos.entrada[i].afectTotales.afectaciones[j];
			}
			i++;
			listaTramos.numEntradas++;
			archivo >> listaTramos.entrada[i].carretera;
		}
		archivo.close();
		abierto = true;
	}
	return abierto;
}

int buscaEntrada(tListaTramos lista, string carretera, int punto) {
	int posicion = 0;
	for (int i = 0; i < lista.numEntradas; i++) {
		if (carretera == lista.entrada[i].carretera && punto >= lista.entrada[i].puntoOrigen && punto <= lista.entrada[i].puntoFin) {
			posicion = i;
		}
		else {
			posicion = -1;
		}
	}

	return posicion;
}

void consulta(tListaTramos lista, string carretera, int punto) {
	int posicion;
	posicion = buscaEntrada(lista, carretera, punto);
	if (posicion == -1) {
		cout << "Se puede transitar por esta carretera" << endl;
		;
	}
	else {
		for (int i = 0; i < lista.entrada[posicion].afectTotales.cont; i++) {
			cout << lista.entrada[posicion].afectTotales.afectaciones[i] << " ";
		}
		cout << endl;
	}
}

bool elimina(tListaTramos& lista, string carretera, int punto) {
	bool eliminado;
	int posicion;
	posicion = buscaEntrada(lista, carretera, punto);

	if (posicion == -1) {
		eliminado = false;
	}
	else {
		for (int i = posicion; i < lista.numEntradas; i++) {
			lista.entrada[i] = lista.entrada[i + 1];
			lista.numEntradas--;

		}
		eliminado = true;
	}
	return eliminado;
}

void listado(const tListaTramos lista) {
	for (int i = 0; i < lista.numEntradas; i++) {
		cout << "Carretera " << lista.entrada[i].carretera << endl;
		cout << "Kilometro inicial " << lista.entrada[i].puntoOrigen << endl;
		cout << "Kilometro final " << lista.entrada[i].puntoFin << endl;
		cout << "Numero de incidencias " << lista.entrada[i].afectTotales.cont << endl;
		cout << "Incidencias ";
		for (int t = 0; t < lista.entrada[i].afectTotales.cont; i++) {
			cout << lista.entrada[i].afectTotales.afectaciones[i] << " ";
		}
		cout << endl;
		cout << "------------------------" << endl;
	}
}

int menu() {
	int opcion;
	cout << "1.- Consultar" << endl;
	cout << "2.- Eliminar" << endl;
	cout << "3.- Listado" << endl;
	cout << "4.- Salir" << endl;

	do {
		cout << "Introduzca opcion ";
		cin >> opcion;
		cout << endl;
	} while (opcion >= 4 || opcion <= 1);
	return opcion;
}