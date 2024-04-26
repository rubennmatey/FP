#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Definicion de constantes
const int MAX_HOSPITALES = 10;
const int MAX_NINOS = 50;


//Definicion de structs 
typedef struct {
	string CIPA;
	string nombre_niño;
}tCita;

typedef tCita tArrayCitas[MAX_NINOS];
typedef struct {
	tArrayCitas citas;
	int numCitas;
}tListaCitas;

typedef struct {
	tListaCitas citas;
	string nombre_hospital;
	char turno; //M de mañana y T de tarde
}tHospital;

typedef tHospital tArrayHospitales[MAX_HOSPITALES];

typedef struct {
	int numHospitales;
	tArrayHospitales hospitales;

}tListaHospitales;

//Subprogramas
void cargar(tListaHospitales& listaHospitales);
bool buscaCIPAH(const tListaCitas& cita, string cipa);
bool buscarCIPA(tListaHospitales lh, string cipa);
int buscarHospital(const tListaHospitales& listaHospital, string nHospital);
void insertarListasCitas(tListaCitas lc, tCita cita);

//Main
int main() {

	return 0;
}


void cargar(tListaHospitales& listaHospitales) {
	ifstream archivo;
	archivo.open("hospitales.txt");
	if (archivo.is_open()) {
		archivo >> listaHospitales.numHospitales;
		for (int i = 0; i < MAX_HOSPITALES; i++) {
			archivo >> listaHospitales.hospitales[i].nombre_hospital >> listaHospitales.hospitales[i].turno;
			listaHospitales.hospitales[i].citas.numCitas = 0;
		}
		archivo.close();
	}
	else {
		listaHospitales.numHospitales = 0;
	}
}


bool buscaCIPAH(const tListaCitas& cita, string cipa) {
	bool encontrado = false;
	int puesto = 0;
	while (puesto < cita.numCitas && !encontrado) {
		if (cita.citas[puesto].CIPA == cipa) {
			encontrado = true;
		}
		else {
			puesto++;
		}
	}
	return encontrado;
}

bool buscarCIPA(tListaHospitales lh, string cipa) {
	bool encontrado = false;
	int puesto;
	int hospitales = 0;
	while (hospitales < lh.numHospitales && !encontrado) {
		if (buscaCIPAH(lh.hospitales[hospitales].citas, cipa)) {
			encontrado = true;
		}
		else {
			hospitales++;
		}	
	}
	return encontrado;
}

int buscarHospital(const tListaHospitales& listaHospital, string nHospital) { // probar a quitar el &
	int i = 0;
	bool encontrado = false;
	while (i < listaHospital.numHospitales && !encontrado) {
		if (listaHospital.hospitales[i].nombre_hospital == nHospital) {
			encontrado = true;
		}
		else {
			i++;
		}
		if (!encontrado) {
			i = -1;
		}
	}
	return i;
}

void insertarListasCitas(tListaCitas lc, tCita cita) {
	lc.citas[lc.numCitas] = cita;
	lc.numCitas++;
}

int localizarHospitalMasLibre(const tListaHospitales& lh) { // probar a quitar el &
	int pos = 0;
	int numCitas = MAX_NINOS;
	for (int i = 0; i < MAX_HOSPITALES; i++) {
		pos = i;
		numCitas = lh.hospitales[i].citas.numCitas;
	}
	return pos;
}