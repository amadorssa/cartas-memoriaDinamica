#include <string>
using namespace std;

struct Carta {
    int valor;
    string figura;
    struct Carta* siguiente;
};