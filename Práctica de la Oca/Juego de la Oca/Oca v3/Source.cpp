//
// Oca version 3
// Ruben Matey Martín y Mario Miralles Melendro, 1ºA, grupo 22
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>
#include <fstream>
#include <cstdlib>

using namespace std;


const int MODO_DEBUG = true;

const int TURNOS_POSADA = 1;
const int TURNOS_CARCEL = 2;
const int TURNOS_POZO = 3;

const int CENTINELA = 0;

const int CASILLA_INICIAL = 1;
const int CASILLA_META = 63;

const int RETROCESO_LABERINTO = 12;
// número de jugadores actual
const int NUM_JUGADORES = 4;
// máximo número de jugadores
const int MAX_JUGADORES = 4;
// número de filas a dibujar
const int NUM_FILAS_A_DIBUJAR = 3;
// numero maximo de partidas
const int MAX_PARTIDAS = 10;

typedef enum { NORMAL, OCA, PUENTE1, PUENTE2, POZO, POSADA, LABERINTO, DADO1, DADO2, CARCEL, CALAVERA } tCasilla;

typedef tCasilla tTablero[CASILLA_META];

typedef int tJugadores[NUM_JUGADORES];
//-------------------------------------------------------------------------
//Estructuras
typedef struct {
    int casilla;
    int penalizaciones;
} tEstadoJugador;

typedef tEstadoJugador tEstadoJugadores[NUM_JUGADORES];

typedef struct {
    tEstadoJugadores jugadores;
    tTablero tablero;
    int turno;
} tEstadoPartida;

typedef tEstadoPartida tArrayPartidas[MAX_PARTIDAS];

typedef struct {
    int contador;
    tArrayPartidas arrayPartidas;
} tListaPartidas;
//-------------------------------------------------------------------------
// Subprogramas para pintar el tablero o mostrar informaci�n
void iniciaTablero(tTablero tablero);
void iniciaJugadores(tEstadoJugadores jugadores);
bool cargaNuevoTablero(tTablero tablero);

void pintaTablero(const tEstadoPartida& partida);
void pintaNumCasilla(int fila, int casillasPorFila);
void pintaBorde(int casillasPorFila);
void pintaTipoCasilla(const tTablero tablero, int fila, int casillasPorFila);
void pintaJugadores(const tEstadoJugadores jugadores, int fila, int casillasPorFila);
string casillaAstring(tCasilla casilla);
tCasilla stringACasilla(string casilla);
string casillaAstringEntero(tCasilla casilla);
//---------------------------------------------------------------------------
// Subprogramas de juego
int tirarDado();
int tirarDadoManual();
int quienEmpieza();

void tirada(const tTablero tablero, tEstadoJugador& estadoJug);
int partida(tEstadoPartida& estado);

bool esCasillaPremio(const tTablero tablero, int casilla);
void efectoTirada(const tTablero tablero, tEstadoJugador& estadoJug);

int saltaACasilla(const tTablero tablero, int casillaActual);
void buscaCasillaAvanzando(const tTablero tablero, tCasilla tipo, int& posicion);
void buscaCasillaRetrocediendo(const tTablero tablero, tCasilla tipo, int& posicion);
//---------------------------------------------------------------------------
// Subprogramas para el guardado de partidas
bool cargaPartidas(tListaPartidas& partidas);
void cargaTablero(tTablero tablero, ifstream& archivo);
void cargaJugadores(tEstadoJugadores& jugadores, ifstream& archivo);
void eliminarPartida(tListaPartidas& partidas, int indice);
bool insertaNuevaPartida(tListaPartidas& partidas, const tEstadoPartida& partidaOca);
void guardaPartidas(const tListaPartidas& partidas);
void guardaTablero(const tTablero tablero, ofstream& archivo);
void guardaJugadores(const tEstadoJugadores jugadores, ofstream& archivo);
void muestraID(const tListaPartidas& partidas);

int main() {
    tEstadoPartida estado;
    tListaPartidas partidas;
    ifstream archivo;

    srand(time(NULL)); // Semilla aleatoria
    if (!cargaPartidas(partidas)) {
        cout << "Error al cargar el tablero" << endl;
    }
    else {
        cout << "Fichero cargador correctamente" << endl << endl;
        cout << "Deseas jugar una partida nueva o una existente? (n = nueva, e = existente): ";
        char opcion;
        cin >> opcion;
        if (opcion == 'n' || opcion == 'N') {
            // Partida nueva
            iniciaTablero(estado.tablero);
            bool abierto = cargaNuevoTablero(estado.tablero);
            iniciaJugadores(estado.jugadores);
            if (!abierto) {
                cout << "Error al cargar el tablero" << endl;
            }
            else {
                estado.turno = quienEmpieza();
                int ganador = partida(estado);
                if (ganador == -1) {
                    bool insertado = insertaNuevaPartida(partidas, estado);
                    if (insertado) {
                        cout << endl << "PARTIDA NO ACABADA" << endl;
                        cout << "Partida guardada correctamente con el identificador: " << partidas.contador << endl;
                    }
                    else {
                        cout << "ERROR AL GUARDAR LA PARTIDA" << endl;
                    }
                }
                else {
                    cout << "_____ GANA EL JUGADOR " << ganador << " _____" << endl;
                }
            }

        }
        else {
            // Partida existente
            int id;
            muestraID(partidas);
            cout << "Que partida quieres continuar? ";
            cin >> id;

            int ganador = partida(partidas.arrayPartidas[id - 1]);
            if (ganador == -1) {
                eliminarPartida(partidas, id - 1);
                bool insertado = insertaNuevaPartida(partidas, partidas.arrayPartidas[id - 1]);
                if (insertado) {
                    cout << endl << "PARTIDA NO ACABADA" << endl;
                    cout << "Partida guardada correctamente con el identificador: " << id + 1 << endl;
                }
                else {
                    cout << "ERROR AL GUARDAR LA PARTIDA" << endl;
                }
            }
            else {
                cout << "_____ GANA EL JUGADOR " << ganador << "_____" << endl;
                eliminarPartida(partidas, id - 1);
                guardaPartidas(partidas);
            }
        }
    }

    return 0;
}
void muestraID(const tListaPartidas& partidas) {
    cout << "Los identificadores disponibles son: ";
    for (int i = 1; i < partidas.contador + 1; i++) {
        cout << i << " ";
    }
    cout << endl;
}

int partida(tEstadoPartida& estado) {
    bool finPartida = false;

    pintaTablero(estado);

    cout << "________EMPIEZA EL JUGADOR " << estado.turno << "________" << endl;
    while (!finPartida) {
        cout << "TURNO DEL JUGADOR " << estado.turno << endl;
        if (estado.jugadores[estado.turno - 1].penalizaciones == 0) {
            tirada(estado.tablero, estado.jugadores[estado.turno - 1]);
        }
        else {
            cout << "Te quedan " << estado.jugadores[estado.turno - 1].penalizaciones << " turno/s sin jugar" << endl;
            estado.jugadores[estado.turno - 1].penalizaciones--;
        }

        if (estado.jugadores[estado.turno - 1].casilla < CASILLA_META && !esCasillaPremio(estado.tablero, estado.jugadores[estado.turno - 1].casilla)) {
            estado.turno = (estado.turno % NUM_JUGADORES) + 1;
            cout << "FIN DEL TURNO" << endl;
            cout << "Si quieres guardar la partida pulsa la tecla A o cualquier otra tecla para continuar...";
            string c;
            getline(cin, c);
            if (c == "A" || c == "a") {
                finPartida = true;
                estado.turno = -1;
            }
            cout << endl << endl;
        }
        if (estado.jugadores[estado.turno - 1].casilla > CASILLA_META - 1 ) {
            finPartida = true;
        }
        pintaTablero(estado);

    }
    return estado.turno;
}

void tirada(const tTablero tablero, tEstadoJugador& estadoJug) {
    cout << "Casilla actual: " << estadoJug.casilla + 1 << endl;
    int dado;
    if (MODO_DEBUG) {
        dado = tirarDadoManual();
    }
    else {
        dado = tirarDado();
    }
    cout << "Valor del dado: " << dado << endl;

    estadoJug.casilla += dado;
    if (estadoJug.casilla < CASILLA_META) {
        cout << "Pasas a la casilla: " << estadoJug.casilla + 1 << endl;
        efectoTirada(tablero, estadoJug);
    }
    else {
        // Si el jugador se pasa de la casilla 63, ponemos la posicion en el 63 para que aparezca en la casilla final en el tablero
        estadoJug.casilla = CASILLA_META - 1;
        cout << "Pasas a la casilla: " << estadoJug.casilla + 1 << endl;
    }
}


// Pintar el tablero
void pintaTablero(const tEstadoPartida& partida) {


    int casillasPorFila = CASILLA_META / NUM_FILAS_A_DIBUJAR;
    cout << endl;
    for (int fila = 0; fila < NUM_FILAS_A_DIBUJAR; fila++) {
        pintaBorde(casillasPorFila);
        pintaNumCasilla(fila, casillasPorFila);
        pintaTipoCasilla(partida.tablero, fila, casillasPorFila);
        pintaJugadores(partida.jugadores, fila, casillasPorFila);
    }
    pintaBorde(casillasPorFila);
    cout << endl;
}
void pintaBorde(int casillasPorFila) {

    for (int i = 1; i <= casillasPorFila; i++)
        cout << "|====";

    cout << "|" << endl;

}
void pintaNumCasilla(int fila, int casillasPorFila) {

    for (int i = 1; i <= casillasPorFila; i++)
        cout << "| " << setw(2) << setfill('0') << i + fila * casillasPorFila << " ";

    cout << "|" << endl;

}
void pintaTipoCasilla(const tTablero tablero, int fila, int casillasPorFila) {

    for (int i = 1; i <= casillasPorFila; i++)
        cout << "|" << setw(4) << setfill(' ') << casillaAstring(tablero[i - 1 + fila * casillasPorFila]);

    cout << "|" << endl;

}
void pintaJugadores(const tEstadoJugadores jugadores, int fila, int casillasPorFila) {
    int casilla = 0;

    int blancos = MAX_JUGADORES - NUM_JUGADORES;
    string b = "";
    for (int i = 0; i < blancos; i++) b = b + " ";
    cout << "|";
    for (int i = 1; i <= casillasPorFila; i++) {
        casilla = i - 1 + fila * casillasPorFila;
        for (int jug = 0; jug < NUM_JUGADORES; jug++) {
            if (jugadores[jug].casilla == casilla)
                cout << jug + 1;
            else
                cout << " ";
        }
        cout << b;
        cout << "|";
    }
    cout << endl;

}

// Inicilización y carga de tableros
void iniciaTablero(tTablero tablero) {
    for (int i = 0; i < CASILLA_META - 1; i++) {
        tablero[i] = NORMAL;
    }
    tablero[CASILLA_META - 1] = OCA;
}
void iniciaJugadores(tEstadoJugadores jugadores) {
    for (int i = 0; i < NUM_JUGADORES; i++) {
        jugadores[i].casilla = CASILLA_INICIAL - 1;
        jugadores[i].penalizaciones = 0;
    }
}
bool cargaNuevoTablero(tTablero tablero) {
    string basura;
    getline(cin, basura);

    ifstream archivo;
    string nombre;
    cout << "Introduzca el nombre del archivo:  ";
    getline(cin, nombre);
    archivo.open(nombre);
    bool abierto = archivo.is_open();
    if (abierto) {
        int casilla;
        string tipo;
        char aux;
        archivo >> casilla;
        while (casilla != CENTINELA) {
            archivo.get(aux);
            archivo >> tipo;
            tablero[casilla - 1] = stringACasilla(tipo);
            archivo >> casilla;
        }
    }
    archivo.close();

    return abierto;
}
// Guardado de partidas
bool cargaPartidas(tListaPartidas& partidas) {
    ifstream archivo;
    string nombre;
    cout << "Introduzca el nombre del archivo que contenga las partidas guardadas:  ";
    getline(cin, nombre);
    archivo.open(nombre);
    bool abierto = archivo.is_open();

    if (abierto) {
        int num_partidas;
        archivo >> num_partidas;
        partidas.contador = num_partidas;
        for (int i = 0; i < num_partidas; i++) {
            cargaTablero(partidas.arrayPartidas[i].tablero, archivo);
            archivo >> partidas.arrayPartidas[i].turno;
            cargaJugadores(partidas.arrayPartidas[i].jugadores, archivo);
        }
    }
    archivo.close();
    return abierto;
}

void cargaTablero(tTablero tablero, ifstream& archivo) {
    string nombre;
    int casilla;
    string tipo;
    char aux;
    archivo >> casilla;
    iniciaTablero(tablero);
    while (casilla != CENTINELA) {
        archivo.get(aux);
        archivo >> tipo;
        tablero[casilla - 1] = stringACasilla(tipo);
        archivo >> casilla;
    }
}

void cargaJugadores(tEstadoJugadores& jugadores, ifstream& archivo) {
    for (int i = 0; i < NUM_JUGADORES; i++) {
        archivo >> jugadores[i].casilla;
        jugadores[i].casilla--;
        archivo >> jugadores[i].penalizaciones;
    }
}
void eliminarPartida(tListaPartidas& partidas, int indice) {
    if (indice < partidas.contador) {
        for (int i = indice; i < partidas.contador - 1; i++) {
            partidas.arrayPartidas[i] = partidas.arrayPartidas[i + 1];
        }
    }
    partidas.contador--;
}

bool insertaNuevaPartida(tListaPartidas& partidas, const tEstadoPartida& partidaOca) {
    bool insertado = false;
    if (partidas.contador < MAX_PARTIDAS) {
        partidas.arrayPartidas[partidas.contador] = partidaOca;
        partidas.contador++;
        insertado = true;
    }
    guardaPartidas(partidas);
    return insertado;
}

void guardaPartidas(const tListaPartidas& partidas) {
    ofstream archivo;
    string nombre;
    cout << "Introduzca el nombre del archivo en el que quieres guardar la partida: ";
    cin >> nombre;
    archivo.open(nombre);
    bool abierto = archivo.is_open();
    if (abierto) {
        archivo << partidas.contador << endl;
        for (int i = 0; i < partidas.contador; i++) {
            guardaTablero(partidas.arrayPartidas[i].tablero, archivo);
            guardaJugadores(partidas.arrayPartidas[i].jugadores, archivo);
        }
    }
    else {
        cout << "Error al abrir el archivo" << endl;
    }
    archivo.close();
}
void guardaTablero(const tTablero tablero, ofstream& archivo) {
    for (int i = 0; i < CASILLA_META; i++) {
        if (casillaAstring(tablero[i]) != " ") {
            archivo << i + 1 << " " << casillaAstringEntero(tablero[i]) << endl;
        }
    }
    archivo << 0 << endl;

}
void guardaJugadores(const tEstadoJugadores jugadores, ofstream& archivo) {
    archivo << NUM_JUGADORES << endl;
    for (int i = 0; i < NUM_JUGADORES; i++) {
        archivo << jugadores[i].casilla + 1 << " " << jugadores[i].penalizaciones << endl;
    }
}


// Subprogramas del juego
int tirarDado() {
    return 1 + rand() % (6);
}

int tirarDadoManual() {
    int dadoManual;
    cout << "Introduce el valor del dado" << endl;
    cin >> dadoManual;
    // Recolectar los enter para que no se salte la pausa
    char basura;
    cin.get(basura);
    return dadoManual;

}

int quienEmpieza() {
    return 1 + rand() % (NUM_JUGADORES);
}


bool esCasillaPremio(const tTablero tablero, int casilla) {
    return tablero[casilla] == OCA || tablero[casilla] == PUENTE1 || tablero[casilla] == PUENTE2 || tablero[casilla] == DADO1 || tablero[casilla] == DADO2;
}
void efectoTirada(const tTablero tablero, tEstadoJugador& estadoJug) {
    switch (tablero[estadoJug.casilla]) {
    case OCA: {
        cout << "De oca en oca y tiro porque me toca" << endl;
        estadoJug.casilla = saltaACasilla(tablero, estadoJug.casilla);
    }break;

    case PUENTE1:
    case PUENTE2: {
        cout << "De puente en puente y tiro porque me lleva la corriente" << endl;
        estadoJug.casilla = saltaACasilla(tablero, estadoJug.casilla);
    }break;

    case DADO1:
    case DADO2: {
        cout << "De dado a dado y tiro porque me ha tocado" << endl;
        estadoJug.casilla = saltaACasilla(tablero, estadoJug.casilla);
    }break;

    case POSADA: {
        cout << "Has caido en una posada, " << TURNOS_POSADA << " turno sin jugar" << endl;
        estadoJug.penalizaciones = TURNOS_POSADA;
    }break;

    case CARCEL: {
        cout << "Has caido en la carcel, " << TURNOS_CARCEL << " turnos sin jugar" << endl;
        estadoJug.penalizaciones = TURNOS_CARCEL;
    }break;

    case POZO: {
        cout << "Has caido en un pozo, " << TURNOS_POZO << " turnos sin jugar" << endl;
        estadoJug.penalizaciones = TURNOS_POZO;
    }break;

    case LABERINTO: {
        estadoJug.casilla = estadoJug.casilla - RETROCESO_LABERINTO - 1;
        cout << "Has caido en el laberinto, vuelves 12 casillas atrás" << endl;
    }break;

    case CALAVERA: {
        estadoJug.casilla = CASILLA_INICIAL - 1;
        cout << "Has caido en la muerte, vuelves a la casilla 1" << endl;
    }break;

    }
}


int saltaACasilla(const tTablero tablero, int casillaActual) {
    int posicion = casillaActual;
    switch (tablero[casillaActual]) {
    case OCA: {
        buscaCasillaAvanzando(tablero, OCA, posicion);
    }break;

    case PUENTE1: {
        buscaCasillaAvanzando(tablero, PUENTE2, posicion);
    }break;

    case PUENTE2: {
        buscaCasillaRetrocediendo(tablero, PUENTE1, posicion);
    }break;

    case DADO1: {
        buscaCasillaAvanzando(tablero, DADO2, posicion);
    }break;

    case DADO2: {
        buscaCasillaRetrocediendo(tablero, DADO1, posicion);
    }break;
    }

    cout << "Pasas a la casilla " << posicion + 1 << endl;
    return posicion;

}
void buscaCasillaAvanzando(const tTablero tablero, tCasilla tipo, int& posicion) {
    while (tablero[posicion + 1] != tipo && posicion < CASILLA_META) {
        posicion++;
    }
    posicion++;
}
void buscaCasillaRetrocediendo(const tTablero tablero, tCasilla tipo, int& posicion) {
    while (tablero[posicion] != tipo && posicion > CASILLA_INICIAL) {
        posicion--;
    }
}



string casillaAstring(tCasilla casilla) {
    string cadena;
    switch (casilla) {
    case NORMAL:
        cadena = " ";
        break;
    case OCA:
        cadena = "OCA";
        break;
    case DADO1:
    case DADO2:
        cadena = "DADO";
        break;
    case PUENTE1:
    case PUENTE2:
        cadena = "PNTE";
        break;
    case POSADA:
        cadena = "PSDA";
        break;
    case CALAVERA:
        cadena = "MUER";
        break;
    case LABERINTO:
        cadena = "LBRN";
        break;
    case POZO:
        cadena = "POZO";
        break;
    case CARCEL:
        cadena = "CRCL";
        break;
    default:
        cadena = " ";
    }
    return cadena;
}

string casillaAstringEntero(tCasilla casilla) {
    string cadena;
    switch (casilla) {
    case NORMAL:
        cadena = " ";
        break;
    case OCA:
        cadena = "OCA";
        break;
    case DADO1:
        cadena = "DADO1";
        break;
    case DADO2:
        cadena = "DADO2";
        break;
    case PUENTE1:
        cadena = "PUENTE1";
        break;
    case PUENTE2:
        cadena = "PUENTE2";
        break;
    case POSADA:
        cadena = "POSADA";
        break;
    case CALAVERA:
        cadena = "MUERTE";
        break;
    case LABERINTO:
        cadena = "LABERINTO";
        break;
    case POZO:
        cadena = "POZO";
        break;
    case CARCEL:
        cadena = "CARCEL";
        break;
    default:
        cadena = " ";
    }
    return cadena;
}

tCasilla stringACasilla(string casilla) {
    tCasilla cadena;
    if (casilla == "NORMAL") {
        cadena = NORMAL;
    }
    else if (casilla == "OCA") {
        cadena = OCA;
    }
    else if (casilla == "PUENTE1") {
        cadena = PUENTE1;
    }
    else if (casilla == "PUENTE2") {
        cadena = PUENTE2;
    }
    else if (casilla == "POZO") {
        cadena = POZO;
    }
    else if (casilla == "POSADA") {
        cadena = POSADA;
    }
    else if (casilla == "LABERINTO") {
        cadena = LABERINTO;
    }
    else if (casilla == "DADO1") {
        cadena = DADO1;
    }
    else if (casilla == "DADO2") {
        cadena = DADO2;
    }
    else if (casilla == "CARCEL") {
        cadena = CARCEL;
    }
    else {
        cadena = CALAVERA;
    }
    return cadena;
}