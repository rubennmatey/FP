#include <iostream>
#include <fstream>
#include <string>
using namespace std;

typedef enum { MATEMATICAS, FISICA, INFORMATICA }tArea;

const int MAX_ESTANT = 15;
const int MAX_LIBROS = 100;

typedef struct tLibro {
	string nombre;
	tArea area;
	int paginas = 0;
};

typedef tLibro tArrayLibros[MAX_LIBROS];

typedef struct tListaLibros {
	tArrayLibros libro;
	int cont = 0;
};

typedef struct tEstanteria {
	tArea area;
	tListaLibros lista_libros;
	int capacidad = 0;
	int pag_disp = 0;
};

typedef tEstanteria tArrayBiblioteca[MAX_ESTANT];

typedef struct tBiblioteca{
	tArrayBiblioteca array_biblioteca;
	int cont = 0;
};

///////////////////////////////////

tArea strToArea(string str);
bool cargarEstanterias(tBiblioteca& biblioteca);
bool cargarLibros(tListaLibros& listaLibros);
tLibro mayor(tListaLibros& listaLibros);
int	buscarEstanteria(const	tBiblioteca& biblioteca, tLibro	libro);
void asignar(tBiblioteca& biblioteca, tListaLibros& listaLibros, tListaLibros& sinColocar);
string areaToStr(tArea area);
void mostrarLibros(const tListaLibros& listaLibros);
void mostrarBiblioteca(const tBiblioteca& biblioteca);

///////////////////////////////////////

int main() {
	tBiblioteca biblioteca;
	biblioteca.cont = 0;

	tListaLibros listaLibros;
	listaLibros.cont = 0;

	tListaLibros listaLibrosColocar;
	listaLibrosColocar.cont = 0;

	if (cargarEstanterias(biblioteca)) {
		if (cargarLibros(listaLibros)) {
			asignar(biblioteca, listaLibros, listaLibrosColocar);
			mostrarBiblioteca(biblioteca);
			cout << "Libros sin colocar: " << endl;
			mostrarLibros(listaLibrosColocar);
		}
		else {
			cout << "Error al cargar el archivo" << endl;
		}
	}
	else {
		cout << "Error al cargar el archivo" << endl;
	}
	return 0;
}

///////////////////////////////////////

tArea strToArea(string str) {
	tArea area;
	if (str == "INF") {
		area = INFORMATICA;
	}
	else if(str == "MAT") {
		area = MATEMATICAS;
	}
	else {
		area = FISICA;
	}
	return area;
}

bool cargarEstanterias(tBiblioteca& biblioteca) {
	ifstream archivo;
	string areaAux;
	int cont = 0;
	bool abierto = false;
	archivo.open("biblioteca.txt");
	if (archivo.is_open()) {
		abierto = true;
		archivo >> biblioteca.cont;
		while (areaAux != "XXX"){
			archivo >> areaAux;
			biblioteca.array_biblioteca[cont].area = strToArea(areaAux);
			archivo >> biblioteca.array_biblioteca[cont].capacidad;
			biblioteca.array_biblioteca[cont].pag_disp = biblioteca.array_biblioteca[cont].capacidad;
			cont++;
		}
		
	}
	archivo.close();
	return abierto;
}

bool cargarLibros(tListaLibros& listaLibros) {
	ifstream archivo;
	string areaAux;
	int cont = 0;
	bool abierto = false;
	archivo.open("libros.txt");
	if (archivo.is_open()) {
		abierto = true;
		while (areaAux != "XXX" && listaLibros.cont < MAX_LIBROS) {
			archivo >> areaAux;
			listaLibros.libro[cont].area = strToArea(areaAux);
			archivo >> listaLibros.libro[cont].paginas;
			getline(archivo, listaLibros.libro[cont].nombre);
			listaLibros.cont++;
			cont++;
		}
	}
	archivo.close();
	return abierto;
}

/////////

void borrarLibro(tListaLibros& listaLibros, int indice) {
	if (listaLibros.cont > 0) {
		for (int i = indice; i < listaLibros.cont - 1; i++) {
			listaLibros.libro[i] = listaLibros.libro[i + 1];
		}
		listaLibros.cont--;
	}
}

tLibro mayor(tListaLibros& listaLibros) {
	tLibro libro;
	int max = 0;
	int indiceMax = 0;

	for (int i = 0; i < listaLibros.cont; i++) {
		if (listaLibros.libro[i].paginas > max){
			max = listaLibros.libro[i].paginas;
			indiceMax = i;
			libro = listaLibros.libro[indiceMax];
		}
		borrarLibro(listaLibros, indiceMax);
	}
	return libro;
}

int	buscarEstanteria(const	tBiblioteca& biblioteca, tLibro	libro) {
	int pos = -1;
	int i = 0;
	while (i < biblioteca.cont && pos == -1) {
		if (biblioteca.array_biblioteca[i].area == libro.area && biblioteca.array_biblioteca[i].pag_disp >= libro.paginas) {
			pos = i;
		}
	}
	return pos;
}


void asignar (tBiblioteca& biblioteca, tListaLibros& listaLibros, tListaLibros& sinColocar) {
	tLibro libro;
	int pos = 0;
	while (listaLibros.cont > 0) {
		libro = mayor(listaLibros);
		pos = buscarEstanteria(biblioteca, libro);
		if (pos == -1) {
			sinColocar.libro[sinColocar.cont] = libro;
			sinColocar.cont++;
		}
		else {
			biblioteca.array_biblioteca[pos].lista_libros.libro[biblioteca.array_biblioteca[pos].lista_libros.cont] = libro;
			biblioteca.array_biblioteca[pos].pag_disp -= libro.paginas;
			biblioteca.array_biblioteca[pos].capacidad++;
		}
	}
}

string areaToStr(tArea area) {
	string area_s;
	switch (area) {
	case INFORMATICA: {
		area_s = "Informatica";
	}
	break;
	case MATEMATICAS: {
		area_s = "Matematicas";
	}break;
	case FISICA: {
		area_s = "Fisica";
	}break;
	}
	return area_s;
}

void mostrarLibros(const tListaLibros& listaLibros) {
	for (int i = 0; i < listaLibros.cont; i++) {
		cout << listaLibros.libro[i].nombre << " (" << listaLibros.libro[i].paginas << "paginas)" << endl;
	}
}

void mostrarBiblioteca(const tBiblioteca& biblioteca) {
	int nMat = 0;
	int nInf = 0;
	int nFis = 0;
	for (int i = 0; i < biblioteca.cont; i++) {
		cout << areaToStr(biblioteca.array_biblioteca[i].area) << " - ";
		switch (biblioteca.array_biblioteca[i].area) {
		case INFORMATICA: {
			nInf++;
			cout << nInf;
		}break;
		case MATEMATICAS: {
			nMat++;
			cout << nMat;
		}break;
		case FISICA: {
			nFis++;
			cout << nFis;
		}
		}
		cout << " (" << biblioteca.array_biblioteca[i].capacidad << "/" << biblioteca.array_biblioteca[i].pag_disp << ")" << endl;
		mostrarLibros(biblioteca.array_biblioteca[i].lista_libros);
		cout << endl;
	}
}

