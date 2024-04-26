#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Define aquí las CONSTANTES Y TIPOS necesarios:
const int MAX_OFERTAS = 10;
const int MAX_PREFERENCIAS = 3;

struct tOferta {
	string modelo;
	int nDisp = 0;
	double precio = 0;
	bool pagar = false; // 0 = contado; 1 = plazos
};

typedef tOferta tArrayOfertas[MAX_OFERTAS];

struct tListaOfertas {
	tArrayOfertas arrayOfertas;
	int cont = 0;
};

typedef string tPreferencias[MAX_PREFERENCIAS];

struct tTablaPreferencias {
	tPreferencias listaPref;
	int cont = 0;
};

// Prototipos de los subprogramas pedidos en el enunciado, 
// 
// añade los & y const que faltan:

bool cargarCatalogo(tListaOfertas& catalogo);
void guardarCatalogo(const tListaOfertas catalogo);
void mostrarOfertasEnPresupuesto(const tListaOfertas& catalogo, double presupuesto);
void leerPreferencias(tTablaPreferencias& pref);
bool hacerVenta(tListaOfertas& catalogo, tTablaPreferencias& pref, double presupuesto, string modelo);
int buscaOferta(tListaOfertas& catalogo, string modelo, double presupuesto);

int main() {
	system("chcp 1252");
	system("cls");
	tListaOfertas catalogo;
	tTablaPreferencias preferencias;
	string modelo;
	double presupuesto;
	if (!cargarCatalogo(catalogo))
		cout << "No se ha podido cargar el catalogo" << endl;
	else {
		cout << endl << "Dame tu presupuesto: ";
		cin >> presupuesto;
		mostrarOfertasEnPresupuesto(catalogo, presupuesto);
		leerPreferencias(preferencias);
		if (hacerVenta(catalogo, preferencias, presupuesto, modelo)) {
			cout << endl << "Modelo vendido: " << modelo << endl;
			guardarCatalogo(catalogo);
		}
		else
			cout << endl << "No hay disponibilidad con esas preferencias" << endl;
	}
	system("pause");
	return 0;
}

// (Recuerda que en adelante faltan los & y const.)
bool cargarCatalogo(tListaOfertas& catalogo) {
	bool cargado = false;
	ifstream archivo;
	int i = 0;
	string modelo;
	archivo.open("catalogoOfertas.txt");
	if (archivo.is_open()) {
		archivo >> modelo;
		while (modelo != "XXX" && i < MAX_OFERTAS) {
			catalogo.arrayOfertas[i].modelo = modelo;
			archivo >> catalogo.arrayOfertas[i].nDisp >> catalogo.arrayOfertas[i].precio >> catalogo.arrayOfertas[i].pagar;
			archivo >> modelo;
			i++;
		}
		catalogo.cont = i;
		cargado = true;
		archivo.close();
	}
	return cargado;
}

void guardarCatalogo(const tListaOfertas catalogo) {
	ofstream archivo;
	archivo.open("catalogoOfertasFin.txt");
	if (archivo.is_open()) {
		for (int i = 0; i < catalogo.cont; i++) {
			archivo << catalogo.arrayOfertas[i].modelo << " " << catalogo.arrayOfertas[i].nDisp << " " << catalogo.arrayOfertas[i].precio << " " << catalogo.arrayOfertas[i].pagar << " " << endl;
		}
		cout << "XXX" << endl;
		archivo.close();
	}
}

void mostrarOfertasEnPresupuesto( tListaOfertas& catalogo, double presupuesto) {
	int i = 0;
	string pago;
	cout << "Ofertas que puedes	permitirte:" << endl;
	cout << endl;
	while (i < catalogo.cont) {
		if (catalogo.arrayOfertas[i].pagar = 1) {
			pago = "a plazos";
			cout << "Modelo: " << catalogo.arrayOfertas[i].modelo << "; " << "disponibles: " << catalogo.arrayOfertas[i].nDisp << "; " << "precio: " << catalogo.arrayOfertas[i].precio << "; " << "modo: " << pago << endl;
			
		}
		else {
			pago = "al contado";
			cout << "Modelo: " << catalogo.arrayOfertas[i].modelo << "; " << "disponibles: " << catalogo.arrayOfertas[i].nDisp << "; " << "precio: " << catalogo.arrayOfertas[i].precio << "; " << "modo: " << pago << endl;

		}
		i++;
	}
}

void leerPreferencias(tTablaPreferencias& pref) {
	cout << "Escribe	tus	modelos	por	orden	de	preferencia	(de	mayor	a	menor)" << endl;
	cout << endl;
	for (int i = 0; i < MAX_PREFERENCIAS; i++) {
		cin >> pref.listaPref[i];
		pref.cont++;
		cout << "Modelo" << pref.cont << ": " << pref.listaPref[i] << endl;
	}
}

int buscaOferta(tListaOfertas& catalogo, string modelo, double presupuesto) {
	int pos = 0;
	int i = 0;
	while (i < catalogo.cont ) {
		if (catalogo.arrayOfertas[i].modelo == modelo) {
			if (catalogo.arrayOfertas[i].precio <= presupuesto && catalogo.arrayOfertas[i].nDisp != 0) {
				pos = i;
			}
			else {
				pos = -1;
			}
		}
		i++;
	}
	return pos;
}

bool hacerVenta(tListaOfertas& catalogo, tTablaPreferencias& pref, double presupuesto, string modelo) {
	bool venta = false;
	for (int i = 0; i < pref.cont; i++) {
		modelo = pref.listaPref[i];
		if (buscaOferta(catalogo, modelo, presupuesto) != -1) {
			bool venta = true;
		}
	}
	if (venta = false) {
		cout << "No	hay	disponibilidad	con	esas	preferencias" << endl;
	}
	return venta;
	
}