#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Define aquí las CONSTANTES Y TIPOS necesarios:
const int MAX_OFERTAS = 10;
const int MAX_PREFERENCIAS = 3;

struct tOferta {
	string modelo;
	int nDisp;
	int precio;
	bool pagar; // 0 = contado; 1 = plazos
};

typedef tOferta tArrayOfertas[MAX_OFERTAS];

struct tListaOfertas {
	tArrayOfertas arrayOfertas;
	int cont;
};

typedef string tPreferencias[MAX_PREFERENCIAS];

struct tTablaPreferencias {
	tPreferencias listaPref;
	int cont;
};

// Prototipos de los subprogramas pedidos en el enunciado, 
// 
// añade los & y const que faltan:

bool cargarCatalogo(tListaOfertas& catalogo);
void guardarCatalogo(tListaOfertas& catalogo);
void mostrarOfertasEnPresupuesto(const tListaOfertas& catalogo, double presupuesto);
void leerPreferencias(tTablaPreferencias pref);
bool hacerVenta(tListaOfertas catalogo, tTablaPreferencias pref, double presupuesto, string modelo);
int buscaOferta(tListaOfertas catalogo, string modelo, double presupuesto);

int main(){
	system("chcp 1252");
	system("cls");
	tListaOfertas catalogo;
	tTablaPreferencias preferencias;
	string modelo;
	double presupuesto;
	if(!cargarCatalogo(catalogo))
		cout << "No se ha podido cargar el catalogo" << endl;
	else{
		cout << endl << "Dame tu presupuesto: ";
		cin >> presupuesto;
		mostrarOfertasEnPresupuesto(catalogo, presupuesto);
		leerPreferencias(preferencias);
		if(hacerVenta(catalogo, preferencias, presupuesto, modelo)){
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

void guardarCatalogo(tListaOfertas catalogo){
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

void mostrarOfertasEnPresupuesto(tListaOfertas catalogo, double presupuesto){
	// incluye aquí tu código
}

void leerPreferencias(tTablaPreferencias pref){
	// incluye aquí tu código
}

int buscaOferta(tListaOfertas catalogo, string modelo, double presupuesto){
	// incluye aquí tu código
}

bool hacerVenta(tListaOfertas catalogo, tTablaPreferencias pref, double presupuesto, string modelo){
	// incluye aquí tu código
}