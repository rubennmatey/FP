#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_PEDIDOS = 10;


 typedef struct tPedido {
	 int nPedido = 0;
	 string nombre;
	 string direccion;
	 string codigo;
	 string registro_pedido = "Pendiente de entrega";
 } ;

typedef tPedido tArrayPedidos [MAX_PEDIDOS];

typedef struct tListaPedidos {
	tArrayPedidos listapedidos;
	int cont = 0;
} ;

bool cargarPedidos(tListaPedidos& listaPedidos);
bool actualizarPedido(tListaPedidos& listaPedidos, int numPedido);
void mostrarPedidos(const tListaPedidos& listaPedidos);
int posicionRepartidor(const tListaPedidos& listaPedidos, string codigo);
void mostrarPedidosRepartidor(const tListaPedidos& listaPedidos, string codigo, int posicion);
bool guardarPedidos(tListaPedidos& listPedidos);
int menu();



int main() {
	tListaPedidos listaPedidos;
	int opcion = 0;
	int numPedido = 0;
	bool guardado;
	string codigo;

	if (!cargarPedidos(listaPedidos)) {
		cout << "No se han podido cargar los pedidos" << endl;
	}
	else {
		opcion = menu(); 
		while (opcion != 0) {
			switch (opcion){
			case 1: {
				cout << "Indique codigo de repartidor" << endl;
				cin >> codigo;
				cout << endl;
				cout << "Pedidos pendientes del repartidor " << codigo << endl;
				mostrarPedidosRepartidor(listaPedidos, codigo, posicionRepartidor(listaPedidos, codigo));
			}break;
			case 2: {
				cout << "Lista de pedidos" << endl;
				mostrarPedidos(listaPedidos);
				cout << endl;
			}break;
			case 3: {
				cout << "Indique numero de pedido:" << endl;
				cin >> numPedido;
				cout << endl;
				actualizarPedido(listaPedidos, numPedido);
				cout << endl;
			}break;
			case 0: {
				guardado = guardarPedidos(listaPedidos);
				if (guardado) {
					cout << "Adios, se han guardado los pedidos pendientes de asignar" << endl;
				}
				else {
					cout << "No se han podido guardar los pedidos pendientes" << endl;
				}
			}break;
			}
			opcion = menu();
		}
	}
	return 0;
}

bool cargarPedidos(tListaPedidos& listaPedidos) {
	ifstream archivo;
	int cont = 0;
	bool abierto = false;
	char aux;

	archivo.open("pedidos.txt");
	if (archivo.is_open()) {
		archivo >> listaPedidos.listapedidos[cont].nPedido;
		while (cont < MAX_PEDIDOS && listaPedidos.listapedidos[cont].nPedido != 0) {
			archivo.get(aux);
			getline(archivo, listaPedidos.listapedidos[cont].nombre);
			getline(archivo, listaPedidos.listapedidos[cont].direccion);
			archivo >> listaPedidos.listapedidos[cont].codigo;
			cont++;
			listaPedidos.cont++;
			archivo >> listaPedidos.listapedidos[cont].nPedido;
		}
		archivo.close();
		abierto = true;
	}
	return abierto;
}

bool actualizarPedido(tListaPedidos& listaPedidos, int numPedido) {
	bool encontrado = false;
	for (int i = 0; i < MAX_PEDIDOS; i++) {
		if (numPedido == listaPedidos.listapedidos[i].nPedido) {
			listaPedidos.listapedidos[i].registro_pedido = "Entregado";
			encontrado = true;
		}
	}
	return encontrado;
}

void mostrarPedidos(const tListaPedidos& listaPedidos) {
	for (int i = 0; i < listaPedidos.cont; i++) {
		cout << "Numero pedido: " << listaPedidos.listapedidos[i].nPedido << endl;
		cout << "Cliente: " << listaPedidos.listapedidos[i].nombre << endl;
		cout << "Direccion: " << listaPedidos.listapedidos[i].direccion << endl;
		cout << "Codigo repartidor: " << listaPedidos.listapedidos[i].codigo << endl;
		cout << listaPedidos.listapedidos[i].registro_pedido << endl;
		cout << "-----------------------------------" << endl;
	}
}

int posicionRepartidor(const tListaPedidos& listaPedidos, string codigo) {
	int pos = listaPedidos.cont;
	int i = 0;
	while ((i < listaPedidos.cont) && (pos = listaPedidos.cont)){
		if (listaPedidos.listapedidos[i].codigo == codigo) {
			pos = i;
		 }
		else {
			i++;
		}

	}
	return pos;
}

void mostrarPedidosRepartidor(const tListaPedidos& listaPedidos, string codigo, int posicion) {
	int i = 0;
	while (i < listaPedidos.cont && i >= posicion) {
		if (listaPedidos.listapedidos[i].codigo == codigo && listaPedidos.listapedidos[i].registro_pedido == "Pendiente de entrega") {
			cout << "Numero de pedido: " << listaPedidos.listapedidos[i].nPedido << endl;
			cout << "Cliente: " << listaPedidos.listapedidos[i].nombre << endl;
			cout << "Direccion: " << listaPedidos.listapedidos[i].direccion << endl;
			cout << "------------------------------" << endl;
			i++;
		}
		else {
			i++;
		}
	}
}

bool guardarPedidos(tListaPedidos& listPedidos) {
	bool guardado = true;
	ofstream archivo;
	archivo.open("pedidos.txt");
	

	for (int i = 0; i < listPedidos.cont; i++) {
		archivo << listPedidos.listapedidos[i].nPedido << endl;
		archivo << listPedidos.listapedidos[i].nombre << endl;
		archivo << listPedidos.listapedidos[i].direccion << endl;
		archivo << listPedidos.listapedidos[i].codigo << endl;
	}
	archivo << '0' << endl;
	archivo.close();
	return guardado;
}

int menu() {
	int opcion;
	
	cout << "1.- Mostrar todos los pedidos pendientes de repartidor" << endl;
	cout << "2.- Mostrar todos los pedidos " << endl;
	cout << "3.- Registro de pedido entregado" << endl;
	cout << "0.- Salir" << endl;
	do {
		cout << "Opcion: ";
		cin >> opcion;
	} while (opcion > 3 || opcion < 0);
	return opcion;
}