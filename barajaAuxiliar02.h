#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include "barajaAuxiliar01.h"

using namespace std;

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

    while (cartaActual) { 
        cout << "Figura: " << cartaActual->figura << ", Valor: - " << cartaActual->valor << endl;
        cartaActual = cartaActual->siguiente;
    }
    cout << "4";
}

void shuffle(Carta* baraja) {
    // Get the total number of nodes
    int count = 0;
    Carta* temp = baraja;
    while (temp) {
        count++;
        temp = temp->siguiente;
    }

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Shuffle nodes
    temp = baraja;
    for (int i=0; i<count; ++i) {
        // Generate random number between i and count
        std::uniform_int_distribution<> dis(i, count-1);
        int swapIdx = dis(gen);

        // Traverse to the swapIdx node
        Carta* swapNode = baraja;
        for (int j=0; j<swapIdx; ++j) {
            swapNode = swapNode->siguiente;
        }

        // Swap values of temp node and swapNode
        std::swap(temp->valor, swapNode->valor);
        std::swap(temp->figura, swapNode->figura);

        // Move to next node
        temp = temp->siguiente;
    }
}



void repartirBaraja(Carta*& primerCarta, Carta* partida[][5]) {

    
    shuffle(primerCarta);

    for (int i = 0; i < 6; ++i) { // Para cada jugador
        for (int j = 0; j < 5; ++j) { // Para cada carta
            // Asegurarse de que hay cartas disponibles
            if (primerCarta == nullptr) {
                std::cout << "No hay suficientes cartas en la baraja.\n";
                return;
            }

            // Asignar la carta al jugador
            partida[i][j] = primerCarta;

            // Remover la carta de la baraja
            Carta* cartaASacar = primerCarta;
            primerCarta = primerCarta->siguiente;
            cartaASacar->siguiente = nullptr;
        }
    }
}

void imprimirPartida(Carta* partida[6][5]) {
    cout << "7";
    for (int i = 0; i < 6; ++i) { // Para cada jugador
        cout << "Jugador " << (i + 1) << ":\n";
        for (int j = 0; j < 5; ++j) { // Para cada carta
            if (partida[i][j] != nullptr) {
                cout << "\tFigura: " << partida[i][j]->figura << "," << partida[i][j]->valor << endl;
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