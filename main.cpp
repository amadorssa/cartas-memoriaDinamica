//#include "barajaAuxiliar01.h"
#include "barajaAuxiliar02.h"

using namespace std;

int main() {
    Carta* baraja = generarBaraja(); // Genera la baraja
    if (baraja == nullptr) {
        cout << "No se pudo generar la baraja" << endl;
    }
    
    cout << "K";
    imprimirBaraja(baraja); // Imprime la baraja
    cout << "G";

    
    Carta* partida[6][5];
    repartirBaraja(baraja, partida); // Reparte las cartas a los jugadores
    cout << "H";


    imprimirPartida(partida); // Imprime las manos de los jugadores

    cout << "A";
    int ganador;
    Carta* cartaGanadora = nullptr;
    cout << "B";
    obtenerGanador(partida, ganador, cartaGanadora); // Determina al ganador

    cout << "C";
    cout << "El ganador es el jugador " << (ganador + 1) << " con la carta: Figura: " << cartaGanadora->figura << ", Valor: " << cartaGanadora->valor << endl;

    cout << "D";
    almacenarPartida(partida, ganador, cartaGanadora); // Almacena la partida en un archivo
    cout << "E";

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