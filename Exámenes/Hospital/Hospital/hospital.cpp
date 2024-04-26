#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_HOSPITALES = 10;
const int MAX_NINOS = 50;

struct tCita {
	string cipa;
	string nombre;
};

struct tListaCitas {
	tCita tArrayCitas[MAX_NINOS];
	int numCitas;
};

struct tHospital {
	string nombreHospital;
	char turno;
	tListaCitas listaCitas;
};

struct tListaHospital {
	tHospital tlistaHospital[MAX_HOSPITALES];
	int numHospitales;
};

////////////////////////////
void cargar(tListaHospital& lh);
bool buscarCIPA(const tListaHospital& listaHospitales, string cipa);
bool buscarCIPAenHospital(const tListaCitas& listaCitas, string cipa);
int buscarHospital(tListaHospital& listaHospital, string nombre);
void insertarListaCitas(tListaCitas& listaCitas, tCita cita);
int localizarHospitalMasLibre(const tListaHospital& listaHospital);

////////////////////////////

int main() {

	return 0;
}

void cargar(tListaHospital& lh){
	ifstream archivo;
	archivo.open("hospitales.txt");
	if (archivo.is_open()) {
		archivo >> lh.numHospitales;
		for (int i = 0; i < lh.numHospitales; i++) {
			archivo >> lh.tlistaHospital[i].nombreHospital >> lh.tlistaHospital[i].turno;
			lh.tlistaHospital[i].listaCitas.numCitas = 0;
		}
	}
	else {
		lh.numHospitales = 0;
	}
	archivo.close();
}

bool buscarCIPA(const tListaHospital& listaHospitales, string cipa) {
	bool encontrado = false;
	int i = 0;
	while (!encontrado && i < listaHospitales.numHospitales) {
		if (buscarCIPAenHospital(listaHospitales.tlistaHospital[i].listaCitas, cipa)) {
			encontrado = true;
		}
		else {
			i++;
		}
	}
	return 0;
}

bool buscarCIPAenHospital(const tListaCitas& listaCitas, string cipa) {
	bool encontrado = false;
	int pos = 0;
	while (!encontrado && pos < listaCitas.numCitas) {
		if (listaCitas.tArrayCitas[pos].cipa == cipa) {
			encontrado = true;

		}else{
			pos++;
		}
	}
	return encontrado;
}

int buscarHospital(const tListaHospital& listaHospital, string nombre) {
	int pos = 0;
	bool encontrado = false;
	while (pos < listaHospital.numHospitales) {
		if (listaHospital.tlistaHospital[pos].nombreHospital == nombre) {
			encontrado = true;
			
		}
		else {
			pos++;
		}
		if (!encontrado) {
			pos = -1;
		}
	}
	return pos;
}

void insertarListaCitas(tListaCitas& listaCitas, tCita cita) {
	listaCitas.tArrayCitas[listaCitas.numCitas] = cita;
	listaCitas.numCitas++;
}

int localizarHospitalMasLibre(const tListaHospital& listaHospital) {
	int pos = -1;
	int numCitas = MAX_NINOS;
	for (int i = 0; i < listaHospital.numHospitales; i++) {
		if (listaHospital.tlistaHospital[i].listaCitas.numCitas < numCitas) {
			pos = i;
			numCitas = listaHospital.tlistaHospital[i].listaCitas.numCitas;
		}
	}
	return pos;
}

void pedirCita(tListaHospital& listaHospitales) {
	string hospitalDeseado;
	tCita cita;
	
	cout << "Introduzca el nombre del niño" << endl;
	cin >> cita.nombre;
	cout << endl << "Introduzca el CIPA";
	cin >> cita.cipa;
	cout << endl;


}