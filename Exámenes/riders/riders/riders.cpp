#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_JUGUETES = 10;
const int MAX_CARTAS = 10;
const int MAX_CARACTERES = 10;
const int MAX_PEDIDOS = 3;

 struct tJuguetes{
	string nombre;
	double peso;
	int disponibles;
};

typedef tJuguetes tArrayJuguetes[MAX_JUGUETES];

 struct tListaJuguetes {
	tArrayJuguetes arrayJuguetes;
	int cont;
};

typedef string tArrayPedidos[MAX_PEDIDOS];

 struct tCartas {
	string nombre;
	string ciudad;
	tArrayPedidos arrayPedidos;
	bool cargado;
	bool pendiente;
};

typedef tCartas tArrayCartas[MAX_CARTAS];

 struct tListaCartas{
	tArrayCartas arrayCartas;
	int cont;
};

////////////////////////////////
bool cargarJuguetes(tListaJuguetes& listaJuguetes);
bool cargarCartas(tListaCartas& listaCartas);
void listarJuguetes(const tListaJuguetes& listaJuguetes);
int buscarJuguete(const tListaJuguetes& listaJuguetes, const string& juguete);
double trineoDestino(tListaCartas& listaCartas, tListaJuguetes& listaJuguetes, const string& ciudad);
bool comprobarPedido(string pedido[MAX_PEDIDOS], const tListaJuguetes& listaJuguetes);
void cargarTrineos(tListaCartas& listaCartas, tListaJuguetes& listaJuguetes);
bool buscarCiudad(const tListaCartas& listaCartas, string& ciudad);
void listarPendientes(tListaCartas listaCartas);
/////////////////////////

int main() {
	tListaCartas listaCartas;
	tListaJuguetes listaJuguetes;
	bool ok = cargarJuguetes(listaJuguetes);
	if (!ok) {
		cout << "No se ha podido cargar el archivo de los juguetes" << endl;
	}
	else {
		ok = cargarCartas(listaCartas);
		if (!ok) {
			cout << "No se ha podido cargar el archivo de las cartas" << endl;
		}
		else{
			cout << "Bienvenido a la fabrica de juguetes de Papa Noel" << endl;
			cout << "------------------------------------------------" << endl;
			cout << endl;
			listarJuguetes(listaJuguetes);
	
			cargarTrineos(listaCartas, listaJuguetes);
		
			listarPendientes(listaCartas);
			
		}
	}
	return 0;
}

bool cargarJuguetes(tListaJuguetes& listaJuguetes) {
	bool cargado = false;
	ifstream archivo;
	archivo.open("juguetes.txt");

	if (archivo.is_open()) {
		int i = 0;
		string nombre;
		archivo >> nombre;
		while (i < MAX_JUGUETES && nombre != "XXX") {
			listaJuguetes.arrayJuguetes[i].nombre = nombre;
			archivo >> listaJuguetes.arrayJuguetes[i].peso >> listaJuguetes.arrayJuguetes[i].disponibles;
			i++;
			archivo >> nombre;
		}
		cargado = true;
		listaJuguetes.cont = i;
		archivo.close();
	}
	return cargado;
}

bool cargarCartas(tListaCartas& listaCartas) {
	bool cargado = false;
	fstream archivo;
	archivo.open("cartas.txt");
	if (archivo.is_open()) {
		int i = 0;
		string nombre;
		archivo >> nombre;
		while (i < MAX_CARTAS && nombre != "XXX") {
			listaCartas.arrayCartas[i].nombre = nombre;
			archivo >> listaCartas.arrayCartas[i].ciudad;
			for (int j = 0; j < MAX_PEDIDOS; j++) {
				archivo >> listaCartas.arrayCartas[i].arrayPedidos[j];
			}
			listaCartas.arrayCartas[i].cargado = false;
			listaCartas.arrayCartas[i].pendiente = false;
			i++;
			archivo >> nombre;
		}
		listaCartas.cont = i;
		cargado = true;
		archivo.close();
	}
	return cargado;
}

void listarJuguetes(const tListaJuguetes& listaJuguetes) {
	cout << "Listado de los juguetes que hay en la fabrica" << endl;
	cout << setw(MAX_CARACTERES) << left << "Nombre" << left << setw(MAX_CARACTERES) << "Ciudad" << left << setw(MAX_CARACTERES) << "Juguetes" << endl;
	for (int i = 0; i < listaJuguetes.cont; i++) {
		cout << setw(MAX_CARACTERES) << left << listaJuguetes.arrayJuguetes[i].nombre;
		cout << setw(MAX_CARACTERES) << fixed << setprecision(2) << listaJuguetes.arrayJuguetes[i].peso;
		cout << setw(MAX_CARACTERES) << listaJuguetes.arrayJuguetes[i].disponibles;
		cout << endl;
	}
}

int buscarJuguete(const tListaJuguetes& listaJuguetes, const string& juguete) {
	int i = 0;
	while (i < listaJuguetes.cont && juguete != listaJuguetes.arrayJuguetes[i].nombre) {
		i++;
	}
	return i;
}

double trineoDestino(tListaCartas& listaCartas, tListaJuguetes& listaJuguetes, const string& ciudad) {
	cout << "Cargando el trineo con destino " << ciudad << endl;
	double pesoTotal = 0;
	for (int i = 0; i < listaCartas.cont; i++) {
		if (ciudad == listaCartas.arrayCartas[i].ciudad) {
			if (comprobarPedido(listaCartas.arrayCartas[i].arrayPedidos, listaJuguetes)) {
				cout << "Carta: " << listaCartas.arrayCartas[i].nombre << "Juguetes:";
				for (int j = 0; j < MAX_PEDIDOS; j++) {
					cout << ' ' << listaCartas.arrayCartas[i].arrayPedidos[j];
					int pos = buscarJuguete(listaJuguetes, listaCartas.arrayCartas[i].arrayPedidos[j]);
					listaJuguetes.arrayJuguetes[pos].disponibles--;
					pesoTotal = pesoTotal + listaJuguetes.arrayJuguetes[pos].peso;
				}
				cout << endl;
				listaCartas.arrayCartas[i].cargado = true;
			}
			else {
				listaCartas.arrayCartas[i].pendiente = true;
			}
		}
	}
	return pesoTotal;
}

bool comprobarPedido(string pedido[MAX_PEDIDOS], const tListaJuguetes& listaJuguetes) {
	int i = 0;
	bool comprobado = true;
	while (i < MAX_PEDIDOS && comprobado) {
		int pos = buscarJuguete(listaJuguetes, pedido[i]);
		if (pos == listaJuguetes.cont || listaJuguetes.arrayJuguetes[pos].disponibles <= 0) {
			comprobado = false;
		}
		else {
			i++;
		}
	}
	return comprobado;
}

void cargarTrineos(tListaCartas& listaCartas, tListaJuguetes& listaJuguetes) {
	cout << endl;
	cout << "Comenzando a cargar los trineos..." << endl;
	string ciudad;
	bool encontrado = buscarCiudad(listaCartas, ciudad);
	while (encontrado) {
		double peso = trineoDestino(listaCartas, listaJuguetes, ciudad);
		cout << "Peso del trineo con destino " << ciudad << ":" << peso << endl;
		cout << endl;
		encontrado = buscarCiudad(listaCartas, ciudad);
	}
	cout << "Carga finalizada" << endl;

}

bool buscarCiudad(const tListaCartas& listaCartas, string& ciudad) {
	int i = 0;
	bool encontrado = false;
	while (i < listaCartas.cont && !encontrado) {
		if (!listaCartas.arrayCartas[i].cargado && !listaCartas.arrayCartas[i].pendiente) {
			encontrado = true;
		}
		else {
			i++;
		}
	}
	if (encontrado) {
		ciudad = listaCartas.arrayCartas[i].ciudad;
	}
	return encontrado;
}

void listarPendientes(tListaCartas listaCartas) {
	cout << "Listado de cartas sin cargar en los trineos" << endl;
	cout << setw(10) << left << "Nombre" << left << setw(10) << "Ciudad" << left << setw(30) << "Juguetes" << '\n';
	for (int i = 0; i < listaCartas.cont; i++) {
		if (listaCartas.arrayCartas[i].pendiente) {
			cout << left << setw(MAX_CARACTERES) << listaCartas.arrayCartas[i].nombre;
			cout << left << setw(MAX_CARACTERES) << listaCartas.arrayCartas[i].ciudad;
			for (int j = 0; j < MAX_PEDIDOS; j++)
				cout << left << setw(MAX_CARACTERES) << listaCartas.arrayCartas[i].arrayPedidos[j];
			cout << endl;;
		}
	}
}