#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include "barajaAuxiliar01.h"
#include "barajaAuxiliar02.h"

using namespace std;

struct Carta {
    int valor;
    string figura;
    Carta* siguiente;
};

Carta* generarBaraja() {
    cout << "1";
    Carta* primerCarta = nullptr;
    Carta* cartaActual = nullptr;

    string figuras[] = {"Diamante", "Corazón", "Pica", "Trébol"};

    for (int i = 0; i < 4; ++i) { // Para cada figura
        for (int j = 1; j <= 13; ++j) { // Para cada valor
            Carta* nuevaCarta = new Carta;
            nuevaCarta->valor = j;
            nuevaCarta->figura = figuras[i];
            nuevaCarta->siguiente = nullptr;

            if (primerCarta == nullptr) { // Si es la primera carta
                primerCarta = nuevaCarta;
                cartaActual = nuevaCarta;
            } else {
                cartaActual->siguiente = nuevaCarta;
                cartaActual = nuevaCarta;
            }
        }
    }
    return primerCarta;
    cout << "2";
}

void imprimirBaraja(Carta* primerCarta) {
    cout << "3";
    Carta* cartaActual = primerCarta;

    while (cartaActual != nullptr) {
        cout << "Figura: " << cartaActual->figura << ", Valor: " << cartaActual->valor << endl;
        cartaActual = cartaActual->siguiente;
    }
    cout << "4";
}

void repartirBaraja(Carta*& primerCarta, Carta* partida[6][5]) {
    cout << "5";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 51);

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            int pos = distrib(gen);
            Carta* actual = primerCarta;
            Carta* previa = NULL;

            for (int k = 0; k < pos; k++) {
                previa = actual;
                actual = actual->siguiente;
            }

            // Sacar la carta seleccionada de la lista
            if (previa) {
                previa->siguiente = actual->siguiente;
            } else {
                primerCarta = actual->siguiente;
            }

            // Asignar la carta al jugador
            partida[i][j] = actual;
            actual->siguiente = NULL;
        }
    }
    cout << "6";
}

void imprimirPartida(Carta* partida[6][5]) {
    cout << "7";
    for (int i = 0; i < 6; ++i) { // Para cada jugador
        cout << "Jugador " << (i + 1) << ":\n";
        for (int j = 0; j < 5; ++j) { // Para cada carta
            if (partida[i][j] != nullptr) {
                cout << "\tFigura: " << partida[i][j]->figura << ", " << partida[i][j]->valor << endl;
            } else {
                cout << "\tNo hay carta.\n";
            }
        }
    }
    cout << "8";
}

void obtenerGanador(Carta* partida[6][5], int& ganador, Carta*& cartaGanadora) {
    cout << "9";
    for (int i = 0; i < 6; ++i) { // Para cada jugador
        for (int j = 0; j < 5; ++j) { // Para cada carta
            if (cartaGanadora == nullptr || partida[i][j]->valor > cartaGanadora->valor) {
                // Si esta carta es de mayor valor que la carta ganadora actual, actualizar el ganador y la carta ganadora
                ganador = i;
                cartaGanadora = partida[i][j];
            } else if (partida[i][j]->valor == cartaGanadora->valor) {
                // Si esta carta tiene el mismo valor que la carta ganadora actual, se debe decidir el ganador por la figura de la carta
                if (partida[i][j]->figura < cartaGanadora->figura) { // Asume que las figuras están codificadas en orden de importancia
                    ganador = i;
                    cartaGanadora = partida[i][j];
                }
            }
        }
    }
    cout << "10";
}

void almacenarPartida(Carta* partida[6][5], int ganador, Carta* cartaGanadora) {
    cout << "11";
    string nombreArchivo;
    cout << "Ingrese el nombre del archivo donde desea guardar la partida: ";
    cin >> nombreArchivo;

    ofstream archivo(nombreArchivo, ios::app); // Abre el archivo en modo append

    if (archivo.is_open()) {
        // Escribe la mano ganadora
        archivo << "Ganador: Jugador " << (ganador + 1) << "\n";
        archivo << "Carta ganadora: Figura " << cartaGanadora->figura << ", Valor " << cartaGanadora->valor << "\n";

        // Escribe las manos de los demás jugadores
        for (int i = 0; i < 6; ++i) {
            if (i != ganador) {
                archivo << "Jugador " << (i + 1) << ":\n";
                for (int j = 0; j < 5; ++j) {
                    archivo << "\tFigura: " << partida[i][j]->figura << ", Valor: " << partida[i][j]->valor << "\n";
                }
            }
        }

        archivo.close(); // Cierra el archivo
    } else {
        cout << "No se pudo abrir el archivo.\n";
    }
    cout << "12";
}

//#include "barajaAuxiliar01.h"

int main() {
    Carta* baraja = generarBaraja(); // Genera la baraja
    if (baraja == nullptr) {
        cout << "No se pudo generar la baraja" << endl;
    }
    
    imprimirBaraja(baraja); // Imprime la baraja
    
    Carta* partida[6][5];
    repartirBaraja(baraja, partida); // Reparte las cartas a los jugadores

    imprimirPartida(partida); // Imprime las manos de los jugadores

    int ganador;
    Carta* cartaGanadora = nullptr;
    obtenerGanador(partida, ganador, cartaGanadora); // Determina al ganador

    cout << "El ganador es el jugador " << (ganador + 1) << " con la carta: Figura: " << cartaGanadora->figura << ", Valor: " << cartaGanadora->valor << endl;

    almacenarPartida(partida, ganador, cartaGanadora); // Almacena la partida en un archivo

    // Liberar la memoria
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 5; ++j) {
            delete partida[i][j];
            partida[i][j] = nullptr;  // es bueno poner a nullptr los punteros después de liberarlos
        }
    }
    Carta* temp;
    while (baraja != nullptr) {
        temp = baraja;
        baraja = baraja->siguiente;
        delete temp;
    }

    return 0;
}