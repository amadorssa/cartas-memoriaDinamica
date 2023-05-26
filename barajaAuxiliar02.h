#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include "barajaAuxiliar01.h"

using namespace std;

Carta* generarBaraja() {
    Carta* primerCarta = nullptr;
    Carta* cartaActual = nullptr;

    string figuras[] = {"Diamante", "Corazón", "Pica", "Trébol"};

    for (int i = 0; i < 4; ++i) { // Para cada figura
        for (int j = 1; j <= 13; ++j) { // Para cada valor
            Carta* nuevaCarta = new Carta;
            nuevaCarta -> valor = j;
            nuevaCarta -> figura = figuras[i];
            nuevaCarta -> siguiente = nullptr;

            if (primerCarta == nullptr) { // Si es la primera carta
                primerCarta = nuevaCarta;
                cartaActual = nuevaCarta;
            } else {
                cartaActual -> siguiente = nuevaCarta;
                cartaActual = nuevaCarta;
            }
        }
    }
    return primerCarta;
}

void imprimirBaraja(Carta* primerCarta) {
    Carta* cartaActual = primerCarta;
    int i = 0;

    while (cartaActual) {
        i++;
        cout << "Carta " << i << ": (" << cartaActual -> figura << "," << cartaActual -> valor << ")" << endl;
        cartaActual = cartaActual -> siguiente;
    }
}

void repartirBaraja(Carta*& primerCarta, Carta* partida[6][5]) {
    Carta* temp = primerCarta;
    int numCartas = 52;

    random_device rd;
    mt19937 generator(rd());

    // Repartir las cartas a cada jugador
    for (int i = 0; i < 6; ++i) { // Para cada jugador
        for (int j = 0; j < 5; ++j) { // Para cada carta

            uniform_int_distribution<int> distribution(0, numCartas - 1);

            // Generar un índice aleatorio dentro del rango de las cartas restantes
            int indiceAleatorio = distribution(generator);

            // Avanzar al nodo correspondiente al índice aleatorio
            temp = primerCarta;
            for (int k = 0; k < indiceAleatorio; ++k) {
                temp = temp -> siguiente;
            }

            // Asignar la carta al jugador
            partida[i][j] = temp;

            // Remover la carta de la baraja
            if (temp == primerCarta) {
                primerCarta = temp -> siguiente;
            } else {
                Carta* prev = primerCarta;
                while (prev -> siguiente != temp) {
                    prev = prev -> siguiente;
                }
                prev -> siguiente = temp -> siguiente;
            }
            temp -> siguiente = nullptr; // Desconectar el nodo de la baraja
            numCartas--;
        }
    }
}

void imprimirPartida(Carta* partida[6][5]) {
    for (int i = 0; i < 6; ++i) { // Para cada jugador
        cout << "Jugador " << (i + 1) << ":\n";
        for (int j = 0; j < 5; ++j) { // Para cada carta
            if (partida[i][j] != nullptr) {
                cout << "\t(" << partida[i][j]->figura << "," << partida[i][j]->valor << ")" << endl;
            } else {
                cout << "\tNo hay carta.\n";
            }
        }
    }
}

void obtenerGanador(Carta* partida[6][5], int& ganador, Carta*& cartaGanadora) {
    for (int i = 0; i < 6; ++i) { // Para cada jugador
        for (int j = 0; j < 5; ++j) { // Para cada carta
            if (cartaGanadora == nullptr || partida[i][j] -> valor > cartaGanadora -> valor) {
                // Si esta carta es de mayor valor que la carta ganadora actual, actualizar el ganador y la carta ganadora
                ganador = i;
                cartaGanadora = partida[i][j];
            } else if (partida[i][j] -> valor == cartaGanadora -> valor) {
                // Si esta carta tiene el mismo valor que la carta ganadora actual, se debe decidir el ganador por la figura de la carta
                if (partida[i][j] -> figura < cartaGanadora -> figura) { // Asume que las figuras están codificadas en orden de importancia
                    ganador = i;
                    cartaGanadora = partida[i][j];
                }
            }
        }
    }
}

void almacenarPartida(Carta* partida[6][5], int ganador, Carta* cartaGanadora) {
    string nombreArchivo;
    cout << endl << "Ingrese el nombre del archivo donde desea guardar la partida: ";
    cin >> nombreArchivo;

    ofstream archivo(nombreArchivo, ios::app); // Abre el archivo en modo append

    if (archivo.is_open()) {
        // Escribe la mano ganadora
        archivo << "* * * * * * * * * * * * * * * * * * *";
        archivo << "\nGanador: Jugador " << (ganador + 1) << "\n";
        archivo << "Mano del jugador ganador:\n";
        for (int j = 0; j < 5; ++j) {
            if (partida[ganador][j] != nullptr) {
                archivo << "\t(" << partida[ganador][j]->figura << "," << partida[ganador][j]->valor << ")" "\n";
            } else {
                archivo << "\tNo hay carta.\n";
            }
        }
        archivo << "\n";

        // Escribe las manos de los demás jugadores
        for (int i = 0; i < 6; ++i) {
            if (i != ganador) {
                archivo << "Jugador " << (i + 1) << ":\n";
                for (int j = 0; j < 5; ++j) {
                    archivo << "\t(" << partida[i][j] -> figura << "," << partida[i][j] -> valor << ")\n";
                }
            }
        }

        archivo.close(); // Cierra el archivo
    } else {
        cout << "No se pudo abrir el archivo.\n";
    }
}