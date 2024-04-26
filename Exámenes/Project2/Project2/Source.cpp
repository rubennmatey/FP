#include <iostream>
#include <string>
#include <fstream>
#include <locale>
using namespace std;

const int MAX_NINNOS = 2;  // ser�a 50 pero se ha bajado para hacer las pruebas
const int MAX_HOSPITALES = 10;

struct tCita {
    string CIPA;
    string nombreApellidos;
};

typedef tCita tArrayCitas[MAX_NINNOS];

struct tListaCitas {
    tArrayCitas citas;
    int numC;
};

struct tHospital {
    string nombre;
    char turno;
    tListaCitas lc;
};

typedef tHospital tArrayHospitales[MAX_HOSPITALES];

struct tListaHospitales {
    tArrayHospitales hospitales;
    int numH;
};

// subprogramas pedidos
void cargar(tListaHospitales& lh);
bool buscarCIPA(const tListaHospitales& lh, string cipa);
int buscarHospital(const tListaHospitales& lh, string hospital);
void insertarListaCitas(tListaCitas& lc, tCita cita);
int localizarHospitalMasLibre(const tListaHospitales& lh);
void pedirCita(tListaHospitales& lh);
void estadoSistema(const tListaHospitales& lh);
int menu();

int main() {
    tListaHospitales lh;
    int opcion;

    setlocale(LC_ALL, "spanish");

    cargar(lh);
    opcion = menu();
    while (opcion != 0) {
        switch (opcion) {
        case 1:
            pedirCita(lh);
            break;
        case 2:
            estadoSistema(lh);
            break;
            /*case 3:
                cout << "Introduzca el turno (M, T, I): ";
                cin >> turno;
                turno = toupper(turno);
                disponibles(lh, turno);
                break;*/
        }
        opcion = menu();
    }
    return 0;
}


void cargar(tListaHospitales& lh) {
    ifstream fh;

    fh.open("hospitales.txt");
    if (fh.is_open()) {
        fh >> lh.numH;
        for (int i = 0; i < lh.numH; i++) {
            fh >> lh.hospitales[i].nombre >> lh.hospitales[i].turno;
            lh.hospitales[i].lc.numC = 0;
        }
        fh.close();
    }
    else lh.numH = 0;
}

void pedirCita(tListaHospitales& lh) {
    tCita cita;
    char turno;
    int indiceHospital, puestoEnFila;
    string hospitalDeseado;
    int posHospital;

    cout << "Introduzca el CIPA: ";
    cin >> cita.CIPA;
    cout << "Introduzca el nombre completo: ";
    cin >> cita.nombreApellidos;
    int hospital;
    if (buscarCIPA(lh, cita.CIPA))
        cout << "Ya tiene cita\n";
    else {
        cout << "Introduzca el nombre del hospital: ";
        cin >> hospitalDeseado;
        posHospital = buscarHospital(lh, hospitalDeseado);
        if (posHospital != -1 && lh.hospitales[posHospital].lc.numC != MAX_NINNOS) {
            insertarListaCitas(lh.hospitales[posHospital].lc, cita);
            cout << "Cita asignada en el hospital deseado, en el puesto numero " << lh.hospitales[posHospital].lc.numC;
            cout << " y en turno de ";
            if (lh.hospitales[posHospital].turno == 'M')
                cout << "ma�ana\n";
            else
                cout << "tarde\n";
        }
        else {
            posHospital = localizarHospitalMasLibre(lh);
            if (posHospital == -1)
                cout << "No quedan citas disponibles en ningun hospital";
            else {
                insertarListaCitas(lh.hospitales[posHospital].lc, cita);
                cout << "Imposible en el hospital indicado, pero te vacunas en el " << lh.hospitales[posHospital].nombre << " en el puesto numero " << lh.hospitales[posHospital].lc.numC;
                cout << " y en turno de ";
                if (lh.hospitales[posHospital].turno == 'M')
                    cout << "ma�ana\n";
                else
                    cout << "tarde\n";
            }
        }
    }
}

//auxiliar para implementar buscarCIPA
bool buscarCIPAenHospital(const tListaCitas& lc, string cipa) {
    bool encontrado = false;
    int puesto = 0;
    while (puesto < lc.numC && !encontrado) {
        if (lc.citas[puesto].CIPA == cipa)
            encontrado = true;
        else
            puesto++;
    }
    return encontrado;
}

bool buscarCIPA(const tListaHospitales& lh, string cipa) {
    bool encontrado = false;
    int puesto;
    int hospital = 0;
    while (hospital < lh.numH && !encontrado) {
        if (buscarCIPAenHospital(lh.hospitales[hospital].lc, cipa))
            encontrado = true;
        else
            hospital++;
    }
    return encontrado;
}

int buscarHospital(const tListaHospitales& lh, string hospital) {
    int i = 0;
    bool encontrado = false;
    while (i < lh.numH && !encontrado)
        if (lh.hospitales[i].nombre == hospital)
            encontrado = true;
        else
            i++;
    if (!encontrado)
        i = -1;
    return i;
}

void insertarListaCitas(tListaCitas& lc, tCita cita) {
    lc.citas[lc.numC] = cita;
    lc.numC++;
}

int localizarHospitalMasLibre(const tListaHospitales& lh) {
    int pos = -1;
    int numCitas = MAX_NINNOS;
    for (int i = 0; i < lh.numH; i++)
        if (lh.hospitales[i].lc.numC < numCitas) {
            pos = i;
            numCitas = lh.hospitales[i].lc.numC;
        }
    return pos;
}

// auxiliar para estadoCitas
void imprimirCitas(const tListaCitas& lc) {
    for (int c = 0; c < lc.numC; c++)
        cout << "[" << lc.citas[c].CIPA << " " << lc.citas[c].nombreApellidos << "] ";
}

void estadoSistema(const tListaHospitales& lh) {
    for (int i = 0; i < lh.numH; i++) {
        cout << "Hospital: " << lh.hospitales[i].nombre << " - Turno:" << lh.hospitales[i].turno << endl;
        cout << lh.hospitales[i].lc.numC << " citas asignadas: ";
        imprimirCitas(lh.hospitales[i].lc);
        cout << endl;
    }
}

int menu() {
    int opcion;

    cout << "\n1. Pedir cita - ";
    cout << "2. Estado del sistema - ";
    //cout << "3. Hospitales con citas libres - ";
    cout << "0. Salir\n";
    do {
        cout << "Opcion (entre 0 y 2): ";
        cin >> opcion;
    } while (opcion < 0 || opcion > 2);
    cout << endl;

    return opcion;
}