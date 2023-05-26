#include "barajaAuxiliar02.h"

using namespace std;

int main() {
    Carta* baraja = generarBaraja(); // Genera la baraja
    if (baraja == nullptr) { // Revisar si la baraja se genero exitosamente
        cout << "No se pudo generar la baraja" << endl;
    }
    
    cout << endl << "***   BARAJA   ***" << endl;
    imprimirBaraja(baraja); // Imprime la baraja

    Carta* partida[6][5];
    repartirBaraja(baraja, partida); // Reparte las cartas a los jugadores

    cout << endl << "***   PARTIDA ACTUAL   ***" << endl;
    imprimirPartida(partida); // Imprime las manos de los jugadores

    int ganador;
    Carta* cartaGanadora = nullptr;
    obtenerGanador(partida, ganador, cartaGanadora); // Determina al ganador

    cout << endl << "El ganador es el jugador " << (ganador + 1) << " con la carta: (" << cartaGanadora->figura << "," << cartaGanadora->valor << ")" << endl;

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